///Kevin Idzik
///First person camera
#include "Camera.h"

Camera::Camera() //Constructor
{
	XMStoreFloat4x4(&viewMatrix, XMMatrixIdentity()); //Store the identity matrix in the view matrix
	XMStoreFloat4x4(&projectionMatrix, XMMatrixIdentity()); //Store the identity matrix in the projection matrix
	position = XMFLOAT3(0, 0, 0); //Default position is at world origin
	forward = XMFLOAT3(0, 0, 1); //The camera's forward vector
}

Camera::~Camera() //Destructor
{
}

XMFLOAT4X4 Camera::GetViewMatrix() //Get the camera's view matrix
{
	return viewMatrix;
}

XMFLOAT4X4 Camera::GetProjectionMatrix() //Get the camera's projection matrix
{
	return projectionMatrix;
}

void Camera::Update() //Updates the camera's view matrix
{
	XMVECTOR updatedRotation = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, 0); //Create a rotation matrix

	XMVector3Rotate(XMLoadFloat3(&forward), updatedRotation);

	XMFLOAT3 up = XMFLOAT3(0, 1, 0);
	XMMatrixLookToLH(XMLoadFloat3(&position), updatedRotation, XMLoadFloat3(&up));
}

void Camera::InputHandler() //Handles camera input
{
	//Keyboard inputs use a bit mask because we only need the high bit

	//Move the camera for WASD controls
	//Space and X control vertical movement
	if (GetAsyncKeyState('W') & 0x8000) //Move forward
	{
		XMVECTOR direction = XMVector3Rotate(XMVectorSet(forward.x, forward.y, forward.z, 0), XMLoadFloat3(&rotation));
		XMStoreFloat3(&position, XMLoadFloat3(&position) + direction);
	}
	if (GetAsyncKeyState('A') & 0x8000) //Strafe left
	{
		XMVECTOR direction = XMVector3Rotate(XMVectorSet(forward.x, forward.y, forward.z, 0), XMLoadFloat3(&rotation));
		XMStoreFloat3(&position, XMLoadFloat3(&position) - direction);
	}
	if (GetAsyncKeyState('S') & 0x8000) //Move backward
	{

	}
	if (GetAsyncKeyState('D') & 0x8000) //Strafe right
	{

	}
	if (GetAsyncKeyState('X') & 0x8000) //Move down
	{
		position.y -= .05f;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) //Move up
	{
		position.y += .05f;
	}
}