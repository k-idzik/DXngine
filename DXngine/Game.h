#pragma once

#include <DirectXMath.h>
#include "DXCore.h"
#include "SimpleShader.h"
#include "Mesh.h" //Mesh renderer
#include "Entity.h" //Entities
#include "Camera.h" //Camera
#include "Material.h" //Materials
#include "Macro.h" //Macros

using std::vector;

class Game : public DXCore
{
public:
	Game(HINSTANCE hInstance);
	~Game();
	
	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);

private:
	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateMatrices();
	void CreateBasicGeometry();

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	//Initialize mesh objects to NULL to minimize problems later
	Mesh* triangle = NULL;
	Mesh* square = NULL;
	Mesh* hexagon = NULL;

	//Initialize entities
	vector<Entity> entities;

	//Initialize the camera
	Camera* gameCamera = new Camera();
};