///Kevin Idzik
///Lights
#pragma once

#include <DirectXMath.h>

using namespace DirectX; //Less unnecessary repetition

//Defines a directional light
struct DirectionalLight
{
	XMFLOAT4 AmbientColor; //Ambient lighting, should be subtle
	XMFLOAT4 DiffuseColor; //Diffuse lighting, should be bright
	XMFLOAT3 Direction; //Light direction, will be normalized in the shader
};