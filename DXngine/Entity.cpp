///Kevin Idzik
///Entities
#include "Entity.h"

Entity::Entity(Mesh* objectMesh) //Constructor
{
	//Initialize variables
	XMStoreFloat4x4(&worldMatrix, XMMatrixIdentity()); //Store the identity matrix in the world matrix
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(0, 0, 0);
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

void Entity::Translate() //Move this entity
{
}

void Entity::Rotate() //Rotate this entity
{
}

void Entity::Scale() //Scale this entity
{
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