#pragma once

#include <DirectXMath.h>
#include "DXCore.h"
#include "SimpleShader.h"
#include "Mesh.h" //Mesh renderer
#include "Entity.h" //Entities
#include "Camera.h" //Camera
#include "Material.h" //Materials
#include "Macro.h" //Macros

//using namespace DirectX; //For the DirectX Math library
using std::vector; //Vectors

class Game : public DXCore
{
private:
	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	XMFLOAT4X4 worldMatrix;
	XMFLOAT4X4 viewMatrix;
	XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	/*
	//Initialize mesh objects to NULL to minimize problems later
	Mesh* triangle = NULL;
	Mesh* square = NULL;
	Mesh* hexagon = NULL;
	*/

	//Initialize meshes
	vector<Mesh*> models;

	//Initialize materials
	vector<Material*> materials;

	//Initialize entities
	vector<Entity> entities;

	//Initialize the camera
	Camera gameCamera = Camera(width, height);

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders();
	void CreateMatrices();
	void CreateBasicGeometry();

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
};