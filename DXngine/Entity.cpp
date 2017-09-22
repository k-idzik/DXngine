///Kevin Idzik
///Entities
#include "Entity.h"

Entity::Entity(Mesh* objectMesh, Material* objectMaterial) //Constructor
{
	//Initialize variables
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity()); //Store the identity matrix in the world matrix
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);
	entityMesh = objectMesh;
	entityMaterial = objectMaterial;
}

Entity::~Entity() //Destructor
{
}

XMFLOAT4X4 Entity::GetWorldMatrix() //Get the world matrix of this entity
{
	return worldMatrix;
}

void Entity::SetWorldMatrix(XMFLOAT4X4 worldMat) //Set the world matrix of this entity
{
	worldMatrix = worldMat;
}

XMFLOAT3 Entity::GetPosition() //Get the position of this entity
{
	return position;
}

void Entity::SetPosition(XMFLOAT3 pos) //Set the position of this entity
{
	position = pos;
}

XMFLOAT3 Entity::GetRotation() //Get the rotation of this entity
{
	return rotation;
}

void Entity::SetRotation(XMFLOAT3 rot) //Set the rotation of this entity
{
	rotation = rot;
}

XMFLOAT3 Entity::GetScale() //Get the scale of this entity
{
	return scale;
}

void Entity::SetScale(XMFLOAT3 scal) //Set the scale of this entity
{
	scale = scal;
}

void Entity::ModifyPosition(XMFLOAT3 pos) //Move this entity
{
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;
}

void Entity::ModifyRotation(XMFLOAT3 rot) //Rotate this entity
{
	rotation.x += rot.x;
	rotation.y += rot.y;
	rotation.z += rot.z;
}

void Entity::ModifyScale(XMFLOAT3 scal) //Scale this entity
{
	scale.x += scal.x;
	scale.y += scal.y;
	scale.z += scal.z;
}

void Entity::UpdateWorldMatrix() //Update the world matrix
{
	XMMATRIX updatedTranslation = XMMatrixTranslation(position.x, position.y, position.z); //Calculate translation
	XMMATRIX updatedRotation = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //Calculate rotation
	XMMATRIX updatedScaling = XMMatrixScaling(scale.x, scale.y, scale.z); //Calculate scale

	XMMATRIX updatedWorld = updatedScaling * updatedRotation * updatedTranslation; //Combine the transformation matrices

	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(updatedWorld)); //Transpose and store the updated matrix
}

void Entity::PrepareMaterial(XMFLOAT4X4 viewMat, XMFLOAT4X4 projectionMat) //Prepare the material for this object
{
	//Send data to shader variables
	//Do this ONCE PER OBJECT you're drawing
	//This is actually a complex process of copying data to a local buffer
	//and then copying that entire buffer to the GPU.  
	//The "SimpleShader" class handles all of that for you.
	entityMaterial->GetVertexShader()->SetMatrix4x4("world", worldMatrix);
	entityMaterial->GetVertexShader()->SetMatrix4x4("view", viewMat);
	entityMaterial->GetVertexShader()->SetMatrix4x4("projection", projectionMat);

	//Once you've set all of the data you care to change for
	//the next draw call, you need to actually send it to the GPU
	//If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	entityMaterial->GetVertexShader()->CopyAllBufferData();

	//Set the vertex and pixel shaders to use for the next Draw() command
	//These don't technically need to be set every frame...YET
	//Once you start applying different shaders to different objects,
	//you'll need to swap the current shaders before each draw
	entityMaterial->GetVertexShader()->SetShader();
	entityMaterial->GetPixelShader()->SetShader();
}

void Entity::Draw(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMat, XMFLOAT4X4 projectionMat) //Draw this entity
{
	//Prepare the materials
	PrepareMaterial(viewMat, projectionMat);

	//Set values for buffers
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	//Set the buffer for the current object
	deviceContext->IASetVertexBuffers(0, 1, entityMesh->GetVertexBuffer(), &stride, &offset);
	deviceContext->IASetIndexBuffer(entityMesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	//Draw the object, passing in the number of vertices
	//DrawIndexed() uses the currently set index buffer to look up corresponding vertices in the currently set VERTEX BUFFER
	deviceContext->DrawIndexed(
		entityMesh->GetIndexCount(), //The number of indices to use (we could draw a subset if we wanted)
		0, //Offset to the first index we want to use
		0); //Offset to add to each index when looking up vertices
}