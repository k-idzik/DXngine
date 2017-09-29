///Kevin Idzik
///Entities
#pragma once

#include <DirectXMath.h> //DXMath library
#include <vector> //Vectors
#include "Mesh.h"
#include "Material.h"
#include "Light.h"

using namespace DirectX; //Less unnecessary repetition

class Entity
{
private:
	XMFLOAT4X4 worldMatrix; //Represents this entity's current position, rotation, and scale
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	Mesh* entityMesh;
	Material* entityMaterial;

	void PrepareMaterial(XMFLOAT4X4* viewMat, XMFLOAT4X4* projectionMat); //Prepare the material for this object
	void UpdateWorldMatrix(); //Update the world matrix

public:
	Entity(Mesh* objectMesh, Material* objectMaterial); //Constructor
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
	Material* GetMaterial();

	void ModifyPosition(XMFLOAT3 pos); //Translate this entity
	void ModifyRotation(XMFLOAT3 rot); //Rotate this entity
	void ModifyScale(XMFLOAT3 scal); //Scale this entity
	void Draw(ID3D11DeviceContext* deviceContext, XMFLOAT4X4* viewMat, XMFLOAT4X4* projectionMat); //Draw this entity
};