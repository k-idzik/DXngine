///Kevin Idzik
///Entities
#include "Entity.h"

Entity::Entity(Mesh* objectMesh) //Constructor
{
	//Initialize variables
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity()); //Store the identity matrix in the world matrix
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);
	entityMesh = objectMesh;
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
	XMMATRIX updateTranslation = XMMatrixTranslation(position.x, position.y, position.z); //Calculate translation
	XMMATRIX updateRotation = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //Calculate rotation
	XMMATRIX updateScaling = XMMatrixScaling(scale.x, scale.y, scale.z); //Calculate scale

	XMMATRIX updateWorld = updateScaling * updateRotation * updateTranslation; //Combine the transformation matrices

	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(updateWorld)); //Transpose and store the updated matrix
}

void Entity::Draw(ID3D11DeviceContext* deviceContext) //Draw this entity
{
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