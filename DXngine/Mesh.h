///Kevin Idzik
///Mesh renderer
#pragma once

#include <d3d11.h>
#include <DirectXMath.h> //DXMath library
#include <fstream> //Read in files
#include <vector> //Vectors
#include "Vertex.h" //For vertices

using std::ifstream; //Read in files
using std::vector; //Vectors


class Mesh
{
private:
	//Geometry data
	ID3D11Buffer* vertexBuffer = NULL;
	ID3D11Buffer* indexBuffer = NULL;

	int indicesInBuffer; //Number of indices in the mesh's index buffer

	void CreateBuffers(Vertex* vert, int numVertices, unsigned int* indices, int numIndices, ID3D11Device* device); //Used to create the vertex and index buffers

public:
	Mesh(Vertex* vert, int numVertices, unsigned int* indices, int numIndices, ID3D11Device* device); //Constructor
	Mesh(char* filename, ID3D11Device* device); //Parameterized constructors
	~Mesh(); //Destructor

	//Accessors
	ID3D11Buffer** GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();
};