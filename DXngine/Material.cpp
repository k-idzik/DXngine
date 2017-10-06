///Kevin Idzik
///Materials define the look of a mesh when it is drawn
#include "Material.h"

//Parameterized constructor
Material::Material(ID3D11Device* device, SimpleVertexShader* vertShader, SimplePixelShader* pixShader, ID3D11ShaderResourceView* shadResourceView, char* srvName)
{
	vertexShader = vertShader;
	pixelShader = pixShader;
	shaderResourceView = shadResourceView;
	shaderResourceViewName = srvName;
}

//Destructor
Material::~Material()
{
	//Release DirectX texture resources
	shaderResourceView->Release();
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

//Send the texture data to the shader
void Material::SendTextureDataToShader()
{
	pixelShader->SetShaderResourceView(shaderResourceViewName, shaderResourceView); //Send the SRV to the pixel shader
}