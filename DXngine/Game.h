#pragma once

#include <DirectXMath.h>
#include "WICTextureLoader.h" //Loading textures, part of DirectX
#include "DXCore.h"
#include "SimpleShader.h"
#include "Mesh.h" //Mesh renderer
#include "Entity.h" //Entities
#include "Camera.h" //Camera
#include "Material.h" //Materials
#include "Light.h" //Lights
#include "Macro.h" //Macros

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

	//Initialize meshes
	vector<Mesh*> meshes;

	//Render states
	//Initialize sampler state, defines how we interact with the texture
	//Initialize raster state
	ID3D11SamplerState* samplerState;
	//ID3D11RasterizerState* rasterState;

	//Initialize materials
	vector<Material*> materials;

	//Initialize entities
	vector<Entity*> entities;

	//Initialize lights
	DirectionalLight dLights[2];

	//Initialize the camera
	Camera gameCamera;

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadAssets();
	void CreateMatrices();
	void CreateBasicGeometry();
	void CreateLights();

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