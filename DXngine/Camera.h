///Kevin Idzik
///First person camera
#pragma once

#include <DirectXMath.h> //DXMath library
#include <Windows.h> //Input

using namespace DirectX; //Less unnecessary repetition

class Camera
{
private:
	XMFLOAT4X4 viewMatrix; //Describes where the viewer is in the scene
	XMFLOAT4X4 projectionMatrix; //Maps the 3D scene onto the 2D screen

	//XMVECTOR and XMMATRIX are used for calculation
	//XMFLOAT3 is used for storage/passing the data around
	//Could make these XMFLOAT3, but this would require more method calls in the class
	XMVECTOR position; //The camera's position
	XMVECTOR forward; //The camera's forward vector

	XMFLOAT3 rotation; //The camera's rotation
	float movementSpeed; //The camera's movement speed
	float rotationSpeed; //The camera's rotation speed

public:
	Camera(); //Constructor
	~Camera(); //Destructor

	//Accessors
	XMFLOAT4X4 GetViewMatrix();
	XMFLOAT4X4 GetProjectionMatrix();

	void Update(float deltaTime); //Updates the camera's view matrix
	void InputHandler(float deltaTime); //Handles camera input
};