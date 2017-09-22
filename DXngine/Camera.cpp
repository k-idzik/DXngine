///Kevin Idzik
///First person camera
#include "Camera.h"

Camera::Camera() //Constructor
{
	XMStoreFloat4x4(&viewMatrix, XMMatrixIdentity()); //Store the identity matrix in the view matrix
	XMStoreFloat4x4(&projectionMatrix, XMMatrixIdentity()); //Store the identity matrix in the projection matrix
	position = XMVectorSet(0, 0, -5, 0); //Default position is at world origin
	forward = XMVectorSet(0, 0, 1, 0); //The camera's forward vector
	rotation = XMFLOAT3(0, 0, 0); //Default rotation is none
	movementSpeed = 2; //The camera's movement speed
	rotationSpeed = 1; //The camera's rotation speed

	//Initialize the view matrix
	XMVECTOR updatedRotation = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //Create a new rotation quaternion

	XMFLOAT3 unitForward = XMFLOAT3(0, 0, 1); //Create a unit forward vector for transformations
	forward = XMVector3Rotate(XMLoadFloat3(&unitForward), updatedRotation); //Apply the new rotation matrix to the camera's forward vector

	XMFLOAT3 up = XMFLOAT3(0, 1, 0); //The camera's up vector
	XMMATRIX updatedViewMatrix = XMMatrixLookToLH(position, forward, XMLoadFloat3(&up)); //Update the view matrix
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(updatedViewMatrix)); //Transpose and update the camera's view matrix
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

void Camera::Update(float deltaTime) //Updates the camera's view matrix
{
	XMVECTOR updatedRotation = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //Create a new rotation quaternion

	XMFLOAT3 unitForward = XMFLOAT3(0, 0, 1); //Create a unit forward vector for transformations
	forward = XMVector3Rotate(XMLoadFloat3(&unitForward), updatedRotation); //Apply the new rotation matrix to the camera's forward vector

	XMFLOAT3 up = XMFLOAT3(0, 1, 0); //The camera's up vector
	XMMATRIX updatedViewMatrix = XMMatrixLookToLH(position, forward, XMLoadFloat3(&up)); //Update the view matrix
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(updatedViewMatrix)); //Transpose and update the camera's view matrix

	InputHandler(deltaTime); //Handle input
}

void Camera::InputHandler(float deltaTime) //Handles camera input
{
	//Keyboard inputs use a bit mask because we only need the high bit

	XMVECTOR normalizedForward = XMVector3Normalize(forward); //Create a normalized forward vector for movement
	XMVECTOR up = XMVectorSet(0, 1, 0, 0); //The camera's up vector

	//Move the camera for WASD controls
	//Space and X control vertical movement
	//Move forward
	if (GetAsyncKeyState('W') & 0x8000)
	{
		//XMVECTOR direction = XMVector3Rotate(forward, XMLoadFloat3(&rotation));

		//XMFLOAT3 
		//XMStoreFloat3(position, position + direction);

		position += normalizedForward * movementSpeed * deltaTime;
	}
	//Strafe left
	if (GetAsyncKeyState('A') & 0x8000)
		position += XMVector3Cross(normalizedForward, up) * movementSpeed * deltaTime; //Cross the forward vector and the up axis
	//Move backward
	if (GetAsyncKeyState('S') & 0x8000)
		position -= normalizedForward * movementSpeed * deltaTime;
	//Strafe right
	if (GetAsyncKeyState('D') & 0x8000)
		position -= XMVector3Cross(normalizedForward, up) * movementSpeed * deltaTime; //Cross the forward vector and the up axis
	//Move down
	if (GetAsyncKeyState('X') & 0x8000)
	{
		position -= up * movementSpeed * deltaTime;
	}
	//Move up
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		position += up * movementSpeed * deltaTime;
	}
}