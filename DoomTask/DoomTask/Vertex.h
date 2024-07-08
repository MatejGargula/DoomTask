#pragma once

#include <DirectXMath.h>

struct VertexPos2D 
{
	DirectX::XMFLOAT2 pos;
};

struct VertexPos
{
	DirectX::XMFLOAT3 pos;
};

struct VertexPosNorm
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
};

struct VertexPosNormTexCoord
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 texCoord;
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

