///Kevin Idzik
///Entities
#include "Entity.h"

//Constructor
Entity::Entity(Mesh* objectMesh, Material* objectMaterial)
{
	//Initialize variables
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity()); //Store the identity matrix in the world matrix
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);
	entityMesh = objectMesh;
	entityMaterial = objectMaterial;
}

//Destructor
Entity::~Entity()
{
}

//Get the world matrix of this entity
XMFLOAT4X4 Entity::GetWorldMatrix()
{
	return worldMatrix;
}

//Set the world matrix of this entity
void Entity::SetWorldMatrix(XMFLOAT4X4 worldMat)
{
	worldMatrix = worldMat;
}

//Get the position of this entity
XMFLOAT3 Entity::GetPosition()
{
	return position;
}

//Set the position of this entity
void Entity::SetPosition(XMFLOAT3 pos)
{
	position = pos;
}

//Get the rotation of this entity
XMFLOAT3 Entity::GetRotation()
{
	return rotation;
}

//Set the rotation of this entity
void Entity::SetRotation(XMFLOAT3 rot)
{
	rotation = rot;
}

//Get the scale of this entity
XMFLOAT3 Entity::GetScale()
{
	return scale;
}

//Set the scale of this entity
void Entity::SetScale(XMFLOAT3 scal)
{
	scale = scal;
}

//Get the material of this entity
Material * Entity::GetMaterial()
{
	return entityMaterial;
}

//Move this entity
void Entity::ModifyPosition(XMFLOAT3 pos)
{
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;
}

//Rotate this entity
void Entity::ModifyRotation(XMFLOAT3 rot)
{
	rotation.x += rot.x;
	rotation.y += rot.y;
	rotation.z += rot.z;
}

//Scale this entity
void Entity::ModifyScale(XMFLOAT3 scal)
{
	scale.x += scal.x;
	scale.y += scal.y;
	scale.z += scal.z;
}

//Prepare the material for this object
void Entity::PrepareMaterial(XMFLOAT4X4* viewMat, XMFLOAT4X4* projectionMat)
{
	//Send data to shader variables
	//Do this ONCE PER OBJECT you're drawing
	//This is actually a complex process of copying data to a local buffer
	//and then copying that entire buffer to the GPU.  
	//The "SimpleShader" class handles all of that for you.
	entityMaterial->GetVertexShader()->SetMatrix4x4("world", worldMatrix);
	entityMaterial->GetVertexShader()->SetMatrix4x4("view", *viewMat);
	entityMaterial->GetVertexShader()->SetMatrix4x4("projection", *projectionMat);

	//Once you've set all of the data you care to change for
	//the next draw call, you need to actually send it to the GPU
	//If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	entityMaterial->GetVertexShader()->CopyAllBufferData();
	entityMaterial->GetPixelShader()->CopyAllBufferData();

	//Set the vertex and pixel shaders to use for the next Draw() command
	//These don't technically need to be set every frame...YET
	//Once you start applying different shaders to different objects,
	//you'll need to swap the current shaders before each draw
	entityMaterial->GetVertexShader()->SetShader();
	entityMaterial->GetPixelShader()->SetShader();
}

//Update the world matrix
void Entity::UpdateWorldMatrix()
{
	XMMATRIX updatedTranslation = XMMatrixTranslation(position.x, position.y, position.z); //Calculate translation
	XMMATRIX updatedRotation = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //Calculate rotation
	XMMATRIX updatedScaling = XMMatrixScaling(scale.x, scale.y, scale.z); //Calculate scale

	XMMATRIX updatedWorld = updatedScaling * updatedRotation * updatedTranslation; //Combine the transformation matrices

	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(updatedWorld)); //Transpose and store the updated matrix
}

//Draw this entity
void Entity::Draw(ID3D11DeviceContext* context, XMFLOAT4X4* viewMat, XMFLOAT4X4* projectionMat)
{
	//Prepare the material for this entity
	PrepareMaterial(viewMat, projectionMat);

	//Update the world matrix after all other updates are completed
	UpdateWorldMatrix();

	//Set the buffer for the current object
	context->IASetVertexBuffers(0, 1, entityMesh->GetVertexBuffer(), &stride, &offset);
	context->IASetIndexBuffer(entityMesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	//Draw the object, passing in the number of vertices
	//DrawIndexed() uses the currently set index buffer to look up corresponding vertices in the currently set VERTEX BUFFER
	context->DrawIndexed(
		entityMesh->GetIndexCount(), //The number of indices to use (we could draw a subset if we wanted)
		0, //Offset to the first index we want to use
		0); //Offset to add to each index when looking up vertices
}