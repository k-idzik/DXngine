///Kevin Idzik
///Entities
#pragma once

#include <DirectXMath.h> //DXMath library
#include "Mesh.h"

//Less unnecessary repetition, Windows.h could be included instead
using namespace DirectX;

class Entity
{
private:
	XMFLOAT4X4 worldMatrix; //Represents this entity's current position, rotation, and scale
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	Mesh* entityMesh;

public:
	Entity(Mesh* objectMesh); //Constructor
	~Entity(); //Destructor

	//Accessors and mutators
	XMFLOAT4X4 GetWorldMatrix();
	void SetWorldMatrix(XMFLOAT4X4 worldMat);
	XMFLOAT3 GetPosition();
	void SetPosition(XMFLOAT3 pos);
	XMFLOAT3 GetRotation();
	void SetRotation(XMFLOAT3 rot);
	XMFLOAT3 GetScale();
	void SetScale(XMFLOAT3 scal);

	void ModifyPosition(XMFLOAT3 pos); //Translate this entity
	void ModifyRotation(XMFLOAT3 rot); //Rotate this entity
	void ModifyScale(XMFLOAT3 scal); //Scale this entity
	void UpdateWorldMatrix(); //Update the world matrix
	void Draw(ID3D11DeviceContext* deviceContext); //Draw this entity
};