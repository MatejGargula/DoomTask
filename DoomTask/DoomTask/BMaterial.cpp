#include "BMaterial.h"

BMaterial::BMaterial(DTGraphics& gfx)
	:
	diffTex(nullptr),
	specTex(nullptr),
	sampler(gfx)
{
	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffMaterialData>>(gfx, 2u);
	}

	Set(DirectX::XMFLOAT3(0.0f,0.0f,0.0f),
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
}

BMaterial::BMaterial(DTGraphics& gfx, DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec)
	:
	diffTex(nullptr),
	specTex(nullptr),
	sampler(gfx)
{
	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffMaterialData>>(gfx, 2u);
	}

	Set(amb, diff, spec);
}

BMaterial::BMaterial(DTGraphics& gfx, DirectX::XMFLOAT3 amb, std::unique_ptr<BTexture> diffTexture, std::unique_ptr<BTexture> specTexture, float shinniness)
	:
	sampler(gfx)
{
	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<CbuffMaterialData>>(gfx, 2u);
	}

	SetAmbient(amb);
	SetDiffuse(std::move(diffTexture));
	SetSpecular(std::move(specTexture), shinniness);
}

void BMaterial::Bind(DTGraphics& gfx) noexcept
{
	pPcbuf->Update(gfx, data);
	pPcbuf->Bind(gfx);

	sampler.Bind(gfx);
	if (data.useDiffTex)
		diffTex->Bind(gfx);
	
	if (data.useSpecTex)
		specTex->Bind(gfx);
}

void BMaterial::SetAmbient(DirectX::XMFLOAT3 amb)
{
	data.ambient = amb;
}

void BMaterial::SetDiffuse(DirectX::XMFLOAT3 diff)
{
	data.diffuse = diff;
	data.useDiffTex = false;
}

void BMaterial::SetDiffuse(std::unique_ptr<BTexture> diffTexture)
{
	data.useDiffTex = true;
	diffTex = std::move(diffTexture);
}

void BMaterial::SetSpecular(DirectX::XMFLOAT4 spec)
{
	data.useSpecTex = false;
	data.spec = spec;
}

void BMaterial::SetSpecular(std::unique_ptr<BTexture> specTexture, float shinniness)
{
	data.useSpecTex = true;
	specTex = std::move(specTexture);
	data.spec.z = shinniness;
}

void BMaterial::Set(DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT4 spec)
{
	data.useDiffTex = false;
	data.useSpecTex = false;

	data.ambient = amb;
	data.diffuse = diff;
	data.spec = spec;
}
