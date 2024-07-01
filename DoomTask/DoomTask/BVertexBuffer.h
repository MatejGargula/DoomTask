#pragma once

#include "DTBindObjectBase.h"
#include "DTThrowMacros.h"

class BVertexBuffer : public DTBindObjectBase
{
public:
	template<class V>
	BVertexBuffer(DTGraphics& gfx, const std::vector<V>& vertices)
		:
		stride(sizeof(V))
	{
		// Needed for macro throws
		DxgiInfoManager& infoManager = GetInfoManager(gfx);
		HRESULT hr;

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(sizeof(V) * vertices.size());
		bd.StructureByteStride = sizeof(V);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer));
	}
	void Bind(DTGraphics& gfx) noexcept override;
protected:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};


