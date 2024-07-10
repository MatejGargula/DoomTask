#include "PostProcessPass.h"
#include "Vertex.h"
#include "BVertexBuffer.h"
#include "BIndexBuffer.h"
#include "BInputLayout.h"
#include "BTopology.h"
#include "BSampler.h"

void PostProcessPass::createScreenQuad(DTGraphics& gfx)
{
	assert("Postprocess: Vertex Shader needs to be initialized" && vertexShader.GetBytecode());
	
	constexpr float side = 1.0f;

	std::vector<VertexPos2D> vertices(4);
	vertices[0].pos = DirectX::XMFLOAT2(-side, side );
	vertices[1].pos = DirectX::XMFLOAT2(side, side);
	vertices[2].pos = DirectX::XMFLOAT2(-side, -side);
	vertices[3].pos = DirectX::XMFLOAT2(side, -side);

	std::vector<unsigned short> indices = {0, 1, 2, 1, 3, 2};

	auto pvsbc = vertexShader.GetBytecode();
	
	const std::vector<D3D11_INPUT_ELEMENT_DESC>  ied =
	{
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	screenQuadBinds.push_back(std::make_unique<BVertexBuffer>(gfx, vertices));
	screenQuadBinds.push_back(std::make_unique<BIndexBuffer>(gfx, indices));
	screenQuadBinds.push_back(std::make_unique<BInputLayout>(gfx, ied, pvsbc));
	screenQuadBinds.push_back(std::make_unique<BTopology>(gfx, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

	screenQuadBinds.push_back(std::make_unique<BSampler>(gfx));

	indicesCount = (UINT)indices.size();
}

PostProcessPass::PostProcessPass(
	DTGraphics& gfx,
	const std::wstring& pixelShaderPath,
	const std::wstring& vertexShaderPath,
	std::vector<std::shared_ptr<RenderTargetTexture>> source,
	std::shared_ptr<RenderTargetTexture> target)
	:
	pixelShader(gfx, pixelShaderPath),
	vertexShader(gfx, vertexShaderPath)
{
	sourceTexture = source;
	if (target != nullptr)
		targetTexture = target;
	
	createScreenQuad(gfx);
}

PostProcessPass::PostProcessPass(DTGraphics& gfx, const std::wstring& pixelShaderPath, const std::wstring& vertexShaderPath, std::shared_ptr<RenderTargetTexture> source, std::shared_ptr<RenderTargetTexture> target)
	:
	pixelShader(gfx, pixelShaderPath),
	vertexShader(gfx, vertexShaderPath)
{
	sourceTexture.resize(1);
	sourceTexture[0] = source;
	if (target != nullptr)
		targetTexture = target;

	createScreenQuad(gfx);
}

void PostProcessPass::Render(DTGraphics& gfx) noexcept
{
	if (targetTexture == nullptr)
	{
		gfx.pContext->OMSetRenderTargets(1u, gfx.pTarget.GetAddressOf(), nullptr) ;
	}
	else
	{
		targetTexture->BindAsRenderTarget(gfx);
	}

	for (auto& b : screenQuadBinds) {
		b->Bind(gfx);
	}

	for (unsigned int i = 0; i < sourceTexture.size(); i++)
	{
		sourceTexture[i]->BindAsTexture(gfx, i);
	}

	pixelShader.Bind(gfx);
	vertexShader.Bind(gfx);

	gfx.DrawIndexed(indicesCount);
}

std::shared_ptr<RenderTargetTexture> PostProcessPass::GetTargetTexture()
{
	return targetTexture;
}

void PostProcessPass::SetTargetTexture(std::shared_ptr<RenderTargetTexture> targetTex)
{
	targetTexture = targetTex;
}