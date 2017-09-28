#include "Game.h"
#include "Vertex.h"

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
	//Delete mesh objects
	if (!meshes.empty())
	{
		//Loop to make sure each model is deleted
		for each (Mesh* model in meshes)
			delete model;

		meshes.clear();
	}

	//Delete materials
	if (!materials.empty())
	{
		//Loop to make sure each material is deleted
		for each (Material* matl in materials)
			delete matl;

		materials.clear();
	}

	//Delete entities
	if (!entities.empty())
	{
		//Loop to make sure each entity is deleted
		for each (Entity* ent in entities)
			delete ent;

		entities.clear();
	}
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

	//Initialize the material
	materials.push_back(new Material(vertexShader, pixelShader));

	//Load models and initialize the geometry
	CreateBasicGeometry();

	//Initialize lights
	CreateLights();

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
}


// --------------------------------------------------------
// Creates the geometry we're going to draw
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	//Load the models from their files and add them to the meshes vector
	meshes.push_back(new Mesh("../../Assets/Models/cone.obj", device));
	meshes.push_back(new Mesh("../../Assets/Models/cube.obj", device));
	meshes.push_back(new Mesh("../../Assets/Models/cylinder.obj", device));
	meshes.push_back(new Mesh("../../Assets/Models/helix.obj", device));
	meshes.push_back(new Mesh("../../Assets/Models/sphere.obj", device));
	meshes.push_back(new Mesh("../../Assets/Models/torus.obj", device));

	//Add entities to the entities vector
	entities.push_back(new Entity(meshes[0], materials[0]));
	entities.push_back(new Entity(meshes[1], materials[0]));
	entities.push_back(new Entity(meshes[2], materials[0]));
	entities.push_back(new Entity(meshes[3], materials[0]));
	entities.push_back(new Entity(meshes[4], materials[0]));
	entities.push_back(new Entity(meshes[5], materials[0]));

	//Arrange the models
	entities[0]->ModifyPosition(XMFLOAT3(-2.5f, 0, 0));
	entities[1]->ModifyPosition(XMFLOAT3(2, 1, 0));
	entities[2]->ModifyPosition(XMFLOAT3(-1, -1, 0));
	entities[3]->ModifyPosition(XMFLOAT3(-.5f, 1.5f, 0));
	entities[4]->ModifyPosition(XMFLOAT3(3, -1, 0));
	entities[5]->ModifyPosition(XMFLOAT3(0, 0, 0));
}

//Create lights for the engine
void Game::CreateLights()
{
	//Initialize the directional lights
	//Ambient
	//Diffuse
	//Direction
	dLights[0] = { XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, -1.0f, 0.0f) };
	dLights[1] = { XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f) };
}

// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	//Handle base-level DX resize stuff
	DXCore::OnResize();

	//Update our projection matrix since the window size changed
	gameCamera.UpdateProjectionMatrix(width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	//Camera
	gameCamera.Update(deltaTime); //Update the camera

	//Update entity transformations
	entities[0]->ModifyRotation(XMFLOAT3(.5f * deltaTime, 0, 0));
	entities[1]->ModifyRotation(XMFLOAT3(0, .5f * deltaTime, 0));
	entities[2]->ModifyRotation(XMFLOAT3(0, 0, .5f * deltaTime));
	entities[3]->ModifyRotation(XMFLOAT3(.5f * deltaTime, .5f * deltaTime, 0));
	entities[4]->ModifyRotation(XMFLOAT3(.5f * deltaTime, 0, .5f * deltaTime));
	entities[5]->ModifyRotation(XMFLOAT3(0, .5f * deltaTime, .5f * deltaTime));
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
		//Send lighting data to the pixel shader
		//Name of the variable in the shader
		//The address of the light being passed in
		//The size of the light struct being passed in
		entities[i]->GetMaterial()->GetPixelShader()->SetData("dirLight0", &dLights[0], sizeof(DirectionalLight));
		entities[i]->GetMaterial()->GetPixelShader()->SetData("dirLight1", &dLights[1], sizeof(DirectionalLight));

		//Render the entities
		//Prepares materials
		//Updates world matrix
		//Sets buffers and draws
		entities[i]->Draw(context, &gameCamera.GetViewMatrix(), &gameCamera.GetProjectionMatrix());
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
	//When the left mouse button is held down
	if (buttonState && 0x0001)
	{
		//Move the camera with the mouse
		float nextX = x - (float)prevMousePos.x;
		float nextY = y - (float)prevMousePos.y;

		gameCamera.MouseInput(nextX, nextY);

		// Save the previous mouse position, so we have it for the future
		prevMousePos.x = x;
		prevMousePos.y = y;
	}
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