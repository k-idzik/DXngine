///Kevin Idzik
///Mesh renderer
#pragma once

#include <d3d11.h>
#include <DirectXMath.h> //DXMath library
#include "Vertex.h" //For vertices

class Mesh
{
private:
	//Geometry data
	ID3D11Buffer* vertexBuffer = NULL;
	ID3D11Buffer* indexBuffer = NULL;

	int indicesInBuffer; //Number of indices in the mesh's index buffer

public:
	///Constructor
	Mesh(Vertex* vert, int numVertices, unsigned int* indices, int numIndices, ID3D11Device* device);
	///Destructor
	~Mesh();

	ID3D11Buffer** GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();
};