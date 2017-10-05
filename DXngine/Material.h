///Kevin Idzik
///Materials define the look of a mesh when it is drawn
#pragma once

#include "SimpleShader.h" //For vertex and pixel shaders

class Material
{
private:
	SimpleVertexShader* vertexShader; //Pointer to the simple vertex shader
	SimplePixelShader* pixelShader; //Pointer to the simple pixel shader
	ID3D11ShaderResourceView* shaderResourceView; //Initialize SRVs, defines what the surface looks like (textures)
	D3D11_SAMPLER_DESC samplerDescription; //Initialize sampler description
	ID3D11SamplerState* samplerState; //Initialize sampler state, defines how we interact with the texture
	char* shaderResourceViewName; //Store the SRV's name
	char* samplerStateName; //Store the SamplerState's name

public:
	Material(ID3D11Device* device, SimpleVertexShader* vertShader, SimplePixelShader* pixShader, ID3D11ShaderResourceView* shadResourceView, char* srvName, char* samplerStateName); //Constructor
	~Material(); //Destructor

	//Accessors
	SimpleVertexShader* GetVertexShader();
	SimplePixelShader* GetPixelShader();

	void SendTextureDataToShader(); //Send the texture data to the shader
};