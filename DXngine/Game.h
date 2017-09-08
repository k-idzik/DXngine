#pragma once

#include <DirectXMath.h>
#include "DXCore.h"
#include "SimpleShader.h"
#include "Mesh.h" //Mesh renderer

///Macro to get the size of an array
///Not safe if a pointer is passed in, but hopefully nobody does that
///Macro syntax from https://stackoverflow.com/questions/4415524/common-array-length-macro-for-c
#define sizeofArray(x) (sizeof(x) / sizeof(*x))

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

	//Create mesh objects, initalize them to NULL because that creates fewer problems
	Mesh* triangle = NULL;
	Mesh* square = NULL;
	Mesh* hexagon = NULL;
};