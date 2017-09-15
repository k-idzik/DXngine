///Kevin Idzik
///Mesh renderer
#include "Mesh.h"

///Constructor
///Array of vertex objects, number of vertices, array of indices, number of indices, device to create buffer for
Mesh::Mesh(Vertex* vert, int numVertices, unsigned int* indices, int numIndices, ID3D11Device* device)
{
	indicesInBuffer = numIndices; //Save this now, it's important later

	//Create the vertex buffer description
	//Doesn't need to be saved since it's only used to create the vertex buffer
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * numVertices; //Number of vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; //Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	//Create the struct to hold the initial vertex data
	//This data will be put into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vert;

	//Create the buffer with the initial vertex data
	//This buffer will not be changed
	device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);

	//Create the index buffer description
	//Doesn't need to be saved since it's only used to create the vertex buffer
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * indicesInBuffer; //Number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; //Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	//Create the struct to hold the initial index data
	//This data will be put into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	//Create the buffer with the initial index data
	//This buffer will not be changed
	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);
}

///Destructor
Mesh::~Mesh()
{
	//Release any DX objects
	if (vertexBuffer)
		vertexBuffer->Release();
	if (indexBuffer)
		indexBuffer->Release();
}

///Return a pointer to the vertex buffer object
ID3D11Buffer ** Mesh::GetVertexBuffer()
{
	return &vertexBuffer;
}

///Return the index buffer object
ID3D11Buffer * Mesh::GetIndexBuffer()
{
	return indexBuffer;
}

///Return the number of indices in the mesh
int Mesh::GetIndexCount()
{
	return indicesInBuffer;
}