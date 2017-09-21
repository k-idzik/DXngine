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
	XMFLOAT3 position; //The camera's position
	XMFLOAT3 forward; //The camera's forward vector
	XMFLOAT3 rotation; //The camera's rotation

public:
	Camera(); //Constructor
	~Camera(); //Destructor

	//Accessors
	XMFLOAT4X4 GetViewMatrix();
	XMFLOAT4X4 GetProjectionMatrix();

	void Update(); //Updates the camera's view matrix
	void InputHandler(); //Handles camera input
};