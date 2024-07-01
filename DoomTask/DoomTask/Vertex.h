#pragma once

#include <DirectXMath.h>

struct VertexPos
{
	DirectX::XMFLOAT3 pos;
};

struct VertexPosTex
{
	DirectX::XMFLOAT3 pos;
	struct
	{
		float u;
		float v;
	} tex;
};

struct VertexPosCol
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 col;
};

struct VertexPosNormTex
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 col;
	DirectX::XMFLOAT2 texCoords;

};
