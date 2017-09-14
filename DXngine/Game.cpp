#include "Game.h"
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DXngine",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Release any (and all!) DirectX objects
	// we've made in the Game class

	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;

	///Delete mesh objects
	if (triangle)
		delete triangle;
	if (square)
		delete square;
	if (hexagon)
		delete hexagon;

	//Delete entities
	if (!entities.empty())
		entities.clear();
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateMatrices();
	CreateBasicGeometry();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}



// --------------------------------------------------------
// Initializes the matrices necessary to represent our geometry's 
// transformations and our 3D camera
// --------------------------------------------------------
void Game::CreateMatrices()
{
	// Set up world matrix
	// - In an actual game, each object will need one of these and they should
	//    update when/if the object moves (every frame)
	// - You'll notice a "transpose" happening below, which is redundant for
	//    an identity matrix.  This is just to show that HLSL expects a different
	//    matrix (column major vs row major) than the DirectX Math library
	XMMATRIX W = XMMatrixIdentity();
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(W)); // Transpose for HLSL!

	// Create the View matrix
	// - In an actual game, recreate this matrix every time the camera 
	//    moves (potentially every frame)
	// - We're using the LOOK TO function, which takes the position of the
	//    camera and the direction vector along which to look (as well as "up")
	// - Another option is the LOOK AT function, to look towards a specific
	//    point in 3D space
	XMVECTOR pos = XMVectorSet(0, 0, -5, 0);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX V = XMMatrixLookToLH(
		pos,     // The position of the "camera"
		dir,     // Direction the camera is looking
		up);     // "Up" direction in 3D space (prevents roll)
	XMStoreFloat4x4(&viewMatrix, XMMatrixTranspose(V)); // Transpose for HLSL!

	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}


// --------------------------------------------------------
// Creates the geometry we're going to draw - a single triangle for now
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	//Create colors
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	XMFLOAT4 yellow = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);


	///TRIANGLE
	//Make vertices to pass into the mesh renderer
	//When creating meshes, start them at the origin
	Vertex triangleVertices[] =
	{
		{ XMFLOAT3(+0.0f, +0.5f, +0.0f), red },
		{ XMFLOAT3(+0.5f, -0.5f, +0.0f), green },
		{ XMFLOAT3(-0.5f, -0.5f, +0.0f), blue },
	};

	//Order the vertices by their index number and pass them into the array
	unsigned int triangleIndices[] = { 0, 1, 2 };

	//Pass the vertices, indices, device, and other data into the mesh renderer
	triangle = new Mesh(triangleVertices, sizeofArray(triangleVertices), triangleIndices, sizeofArray(triangleIndices), device);

	
	///SQUARE
	//Make vertices to pass into the mesh renderer
	//When creating meshes, start them at the origin
	Vertex squareVertices[] =
	{
		{ XMFLOAT3(-0.5f, +0.5f, +0.0f), red },
		{ XMFLOAT3(+0.5f, +0.5f, +0.0f), green },
		{ XMFLOAT3(+0.5f, -0.5f, +0.0f), blue },
		{ XMFLOAT3(-0.5f, -0.5f, +0.0f), yellow },
	};

	//Order the vertices by their index number and pass them into the array
	unsigned int squareIndices[] = { 0, 1, 2, 0, 2, 3 };

	//Pass the vertices, indices, device, and other data into the mesh renderer
	square = new Mesh(squareVertices, sizeofArray(squareVertices), squareIndices, sizeofArray(squareIndices), device);


	///HEXAGON
	//Make vertices to pass into the mesh renderer
	//When creating meshes, start them at the origin
	Vertex hexagonVertices[] =
	{
		{ XMFLOAT3(+0.0f, +0.0f, +0.0f), yellow },
		{ XMFLOAT3(+0.0f, +0.5f, +0.0f), red },
		{ XMFLOAT3(+0.5f, +0.25f, +0.0f), green },
		{ XMFLOAT3(+0.5f, -0.25f, +0.0f), blue },
		{ XMFLOAT3(+0.0f, -0.5f, +0.0f), red },
		{ XMFLOAT3(-0.5f, -0.25f, +0.0f), green },
		{ XMFLOAT3(-0.5f, +0.25f, +0.0f), blue },
	};

	//Order the vertices by their index number and pass them into the array
	unsigned int hexagonIndices[] = { 0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1 };

	//Pass the vertices, indices, device, and other data into the mesh renderer
	hexagon = new Mesh(hexagonVertices, sizeofArray(hexagonVertices), hexagonIndices, sizeofArray(hexagonIndices), device);
	
	//Add entities to the vector of entities
	entities.push_back(Entity(triangle));
	entities.push_back(Entity(triangle));
	entities.push_back(Entity(square));
	entities.push_back(Entity(square));
	entities.push_back(Entity(square));
	entities.push_back(Entity(hexagon));
	entities.push_back(Entity(hexagon));
	entities.push_back(Entity(hexagon));

	//Move the triangle to it's new location
	entities[0].ModifyPosition(XMFLOAT3(-2.5f, 0, 0));
	entities[1].ModifyPosition(XMFLOAT3(2, 1, 0));
	entities[2].ModifyPosition(XMFLOAT3(-1, -1, 0));
	entities[3].ModifyPosition(XMFLOAT3(-.5f, 1.5f, 0));
	entities[4].ModifyPosition(XMFLOAT3(3, -1, 0));
	entities[5].ModifyPosition(XMFLOAT3(0, 0, 0));
	entities[6].ModifyPosition(XMFLOAT3(1.5f, -1.5f, 0));
	entities[7].ModifyPosition(XMFLOAT3(-2.25, -1.5f, 0));
}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our projection matrix since the window size changed
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,	// Field of View Angle
		(float)width / height,	// Aspect ratio
		0.1f,				  	// Near clip plane distance
		100.0f);			  	// Far clip plane distance
	XMStoreFloat4x4(&projectionMatrix, XMMatrixTranspose(P)); // Transpose for HLSL!
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	//Update entity transformations
	entities[0].ModifyRotation(XMFLOAT3(0, 0, .5f * deltaTime));
	entities[1].ModifyPosition(XMFLOAT3(0, .001f, 0));
	entities[2].ModifyPosition(XMFLOAT3(0, 0, deltaTime));
	if (entities[3].GetScale().x > .01f)
		entities[3].ModifyScale(XMFLOAT3(-deltaTime, 0, 0));
	else if (entities[3].GetScale().x <= .01f)
		entities[3].ModifyScale(XMFLOAT3(0, -deltaTime, 0));
	if (entities[3].GetScale().y < .01f)
		entities[3].SetScale(XMFLOAT3(1, 1, 1));
	entities[4].ModifyRotation(XMFLOAT3(-deltaTime, deltaTime, 0));
	entities[5].ModifyScale(XMFLOAT3(deltaTime, deltaTime, 0));
	if (entities[5].GetScale().x > 1.5f)
		entities[5].SetScale(XMFLOAT3(1, 1, 1));
	entities[5].ModifyRotation(XMFLOAT3(0, 0, deltaTime));
	entities[6].ModifyRotation(XMFLOAT3(.25f * deltaTime, .75f * deltaTime, .5f * deltaTime));
	entities[7].ModifyPosition(XMFLOAT3(0, 0, -deltaTime / 2));
}	

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	//Draw entities
	for (int i = 0; i < entities.size(); i++)
	{
		//Update the world matrix
		entities[i].UpdateWorldMatrix();

		// Send data to shader variables
		//  - Do this ONCE PER OBJECT you're drawing
		//  - This is actually a complex process of copying data to a local buffer
		//    and then copying that entire buffer to the GPU.  
		//  - The "SimpleShader" class handles all of that for you.
		vertexShader->SetMatrix4x4("world", entities[i].GetWorldMatrix());
		vertexShader->SetMatrix4x4("view", viewMatrix);
		vertexShader->SetMatrix4x4("projection", projectionMatrix);

		// Once you've set all of the data you care to change for
		// the next draw call, you need to actually send it to the GPU
		//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
		vertexShader->CopyAllBufferData();

		// Set the vertex and pixel shaders to use for the next Draw() command
		//  - These don't technically need to be set every frame...YET
		//  - Once you start applying different shaders to different objects,
		//    you'll need to swap the current shaders before each draw
		vertexShader->SetShader();
		pixelShader->SetShader();

		//Draw the entities
		entities[i].Draw(context);
	}

	//Show the back buffer to the user
	//Do this exactly once, at the end of the frame
	swapChain->Present(0, 0);
}


#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Add any custom code here...

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion