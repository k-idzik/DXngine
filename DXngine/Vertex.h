///Kevin Idzik, modified code from Chris Cascioli
///Custom vertex definition
#pragma once

#include <DirectXMath.h>

using namespace DirectX; //Less unnecessary repetition

struct Vertex
{
	XMFLOAT3 Position; //The position of the vertex
	XMFLOAT2 UV; //The UV coordinates
	XMFLOAT3 Normal; //The normal, for lighting
};