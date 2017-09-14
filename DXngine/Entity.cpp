///Kevin Idzik
///Entities
#include "Entity.h"

Entity::Entity(Mesh* objectMesh) //Constructor
{

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

void Entity::Move() //Move this entity
{
}