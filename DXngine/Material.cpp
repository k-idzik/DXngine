///Kevin Idzik
///Materials define the look of a mesh when it is drawn
#include "Material.h"

//Constructor
Material::Material(SimpleVertexShader* vertShader, SimplePixelShader* pixShader)
{
	vertexShader = vertShader;
	pixelShader = pixShader;
}

//Destructor
Material::~Material()
{
}

//Get the simple vertex shader
SimpleVertexShader* Material::GetVertexShader()
{
	return vertexShader;
}

//Get the pixel shader
SimplePixelShader* Material::GetPixelShader()
{
	return pixelShader;
}
