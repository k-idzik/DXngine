///Kevin Idzik
///Materials define the look of a mesh when it is drawn
#pragma once

#include "SimpleShader.h" //For vertex and pixel shaders

class Material
{
private:
	SimpleVertexShader* vertexShader; //Pointer to the simple vertex shader
	SimplePixelShader* pixelShader; //Pointer to the simple pixel shader

public:
	Material(SimpleVertexShader* vertShader, SimplePixelShader* pixShader); //Constructor
	~Material(); //Destructor

	//Accessors
	SimpleVertexShader* GetVertexShader();
	SimplePixelShader* GetPixelShader();
};