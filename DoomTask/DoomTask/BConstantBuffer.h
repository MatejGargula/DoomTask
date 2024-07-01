#pragma once

#include "DTBindObjectBase.h"
#include "DTThrowMacros.h"

template<typename C>
class BConstantBuffer : public DTBindObjectBase
{
public:
	void Update(DTGraphics& gfx, const C& consts)
	{
		// Needed for macro throws
		DxgiInfoManager& infoManager = GetInfoManager(gfx);
		HRESULT hr;

		D3D11_MAPPED_SUBRESOURCE msr;
		GFX_THROW_INFO(GetContext(gfx)->Map(
			pConstantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		));
		memcpy(msr.pData, &consts, sizeof(consts));
		GetContext(gfx)->Unmap(pConstantBuffer.Get(), 0u);
	}
	BConstantBuffer(DTGraphics& gfx, const C& consts)
	{
		// Needed for macro throws
		DxgiInfoManager& infoManager = GetInfoManager(gfx);
		HRESULT hr;

		D3D11_BUFFER_DESC cbd = {};
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pConstantBuffer));
	}
	BConstantBuffer(DTGraphics& gfx)
	{
		// Needed for macro throws
		DxgiInfoManager& infoManager = GetInfoManager(gfx);
		HRESULT hr;

		D3D11_BUFFER_DESC cbd = {};
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&cbd, nullptr, &pConstantBuffer));
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};


template<typename C>
class BVertexConstantBuffer : public BConstantBuffer<C>
{
	using BConstantBuffer<C>::pConstantBuffer;
	using DTBindObjectBase::GetContext;
public:
	using BConstantBuffer<C>::BConstantBuffer;
	void Bind(DTGraphics& gfx) noexcept override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class BPixelConstantBuffer : public BConstantBuffer<C>
{
	using BConstantBuffer<C>::pConstantBuffer;
	using DTBindObjectBase::GetContext;
public:
	using BConstantBuffer<C>::BConstantBuffer;
	void Bind(DTGraphics& gfx) noexcept override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};