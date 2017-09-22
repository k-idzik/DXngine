///Kevin Idzik
///Materials define the look of a mesh when it is drawn
#include "Material.h"

Material::Material(SimpleVertexShader* vertShader, SimplePixelShader* pixShader) //Constructor
{
	vertexShader = vertShader;
	pixelShader = pixShader;
}

Material::~Material() //Destructor
{
	//Delete pointers
	if (vertexShader)
		delete vertexShader;
	if (pixelShader)
		delete pixelShader;
}

SimpleVertexShader* Material::GetVertexShader() //Get the simple vertex shader
{
	return vertexShader;
}

SimplePixelShader* Material::GetPixelShader() //Get the pixel shader
{
	return pixelShader;
}
