///Kevin Idzik
///First person camera
#include "Camera.h"

Camera::Camera(unsigned int width, unsigned int height) //Constructor
{
	XMStoreFloat4x4(&viewMatrix, XMMatrixIdentity()); //Store the identity matrix in the view matrix
	XMStoreFloat4x4(&projectionMatrix, XMMatrixIdentity()); //Store the identity matrix in the projection matrix
	position = XMVectorSet(0, 0, -5, 0); //Default position is at world origin
	forward = XMVectorSet(0, 0, 1, 0); //The camera's forward vector
	rotation = XMFLOAT3(0, 0, 0); //Default rotation is none
	movementSpeed = 2; //The camera's movement speed
	rotationSpeed = .5f; //The camera's rotation speed

	//Initialize the view matrix
	UpdateViewMatrix();

	//Initialize the projection matrix
	UpdateProjectionMatrix(width, height);

	//SetCursorPos(width, height);
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

void Camera::SetRotation(XMFLOAT3 rot) //Set the camera's rotation
{
	
}

void Camera::KeyboardInput(float deltaTime) //Handles keyboard input
{
	XMVECTOR normalizedForward = XMVector3Normalize(forward); //Create a normalized forward vector for movement
	XMVECTOR up = XMVectorSet(0, 1, 0, 0); //The camera's up vector

	//Keyboard inputs use a bit mask because we only need the high bit
	//Move the camera for WASD controls
	//Space and X control vertical movement
	//Move forward
	if (GetAsyncKeyState('W') & 0x8000)
		position += normalizedForward * movementSpeed * deltaTime;
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
		position -= up * movementSpeed * deltaTime;
	//Move up
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		position += up * movementSpeed * deltaTime;
}

void Camera::UpdateViewMatrix() //Updates the view matrix
{
	XMVECTOR updatedRotation = XMQuaternionRotationRollPitchYaw(rotation.x, rotation.y, rotation.z); //Create a new rotation quaternion

	XMFLOAT3 unitForward = XMFLOAT3(0, 0, 1); //Create a unit forward vector for transformations
	forward = XMVector3Rotate(XMLoadFloat3(&unitForward), updatedRotation); //Apply the new rotation matrix to the camera's forward vector

	XMFLOAT3 up = XMFLOAT3(0, 1, 0); //The camera's up vector
	XMMATRIX updatedViewMatrix = XMMatrixLookToLH(position, forward, XMLoadFloat3(&up)); //Update the view matrix
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(updatedViewMatrix)); //Transpose and update the camera's view matrix
}

void Camera::Update(float deltaTime) //Updates the camera's view matrix
{
	UpdateViewMatrix();

	KeyboardInput(deltaTime); //Handle keybaord input
}

void Camera::UpdateProjectionMatrix(unsigned int width, unsigned int height) //Updates the projection matrix
{
	//Matches the window's aspect ratio, updates on window resize
	//Field of view angle
	//Aspect ratio
	//Near clip plane distance
	//Far clip plane distance
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * 3.1415926535f, (float)width / height, 0.1f, 100.0f);
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); //Transpose for HLSL
}

void Camera::MouseInput(float xAxis, float yAxis) //Handles mouse input
{
	//Scale the rotations in terms of radians
	float xRadianized = -xAxis / 100;
	float yRadianized = -yAxis / 100;

	rotation.x += yRadianized * rotationSpeed; //Rotate around the Y axis
	rotation.y += xRadianized * rotationSpeed; //Rotate around the X axis

	//"Clamp" the rotation within 360 and -360
	if (rotation.x > 360)
		rotation.x = 360;
	else if (rotation.x < -360)
		rotation.x = -360;

	if (rotation.y > 360)
		rotation.y = 360;
	else if (rotation.y < -360)
		rotation.y = -360;
}