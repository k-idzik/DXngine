///Kevin Idzik
///Materials define the look of a mesh when it is drawn
#include "Material.h"

//Constructor
Material::Material(ID3D11Device* device, SimpleVertexShader* vertShader, SimplePixelShader* pixShader, ID3D11ShaderResourceView* shadResourceView, char* srvName, char* sampStateName)
{
	vertexShader = vertShader;
	pixelShader = pixShader;
	shaderResourceView = shadResourceView;
	shaderResourceViewName = srvName;
	samplerStateName = sampStateName;

	//Initialize the sampler description
	samplerDescription = {}; //Make sure all values aren't garbage data
	samplerDescription = {
		D3D11_FILTER_MIN_MAG_MIP_LINEAR, //Filter
		D3D11_TEXTURE_ADDRESS_WRAP, //AddressU
		D3D11_TEXTURE_ADDRESS_WRAP, //AddressV
		D3D11_TEXTURE_ADDRESS_WRAP, //AddressW
	};
	samplerDescription.MaxLOD = D3D11_FLOAT32_MAX; //MaxLOD

	//Create the device's sampler state
	device->CreateSamplerState(&samplerDescription, &samplerState);
}

//Destructor
Material::~Material()
{
	//Release DirectX texture resources
	shaderResourceView->Release();
	samplerState->Release();
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
	pixelShader->SetSamplerState(samplerStateName, samplerState); //Send the sampler state to the pixel shader
}