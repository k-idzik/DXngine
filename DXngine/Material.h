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
	char* shaderResourceViewName; //Store the SRV's name

public:
	Material(ID3D11Device* device, SimpleVertexShader* vertShader, SimplePixelShader* pixShader, ID3D11ShaderResourceView* shadResourceView, char* srvName); //Parameterized constructor
	~Material(); //Destructor

	//Accessors
	SimpleVertexShader* GetVertexShader();
	SimplePixelShader* GetPixelShader();

	void SendTextureDataToShader(); //Send the texture data to the shader
};