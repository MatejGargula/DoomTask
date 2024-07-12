#include "GBuffer.h"

GBuffer::GBuffer(DTGraphics& gfx)
	:
	VS(gfx, L"DefferedCollectionVS.cso"),
	PS(gfx, L"DefferedCollectionPS.cso"),
	depthRenderTexture(gfx, SCREEN_WIDTH, SCREEN_HEIGHT)
{
	for (unsigned int i = 0; i < N_GTEXTURES; i++)
	{
		gTextures.push_back(std::make_shared<RenderTargetTexture>(gfx, SCREEN_WIDTH, SCREEN_HEIGHT));
	}
}

void GBuffer::BindAsRenderTarget(DTGraphics& gfx)
{
	//ID3D11RenderTargetView* renderTargets[] = {
	//	gTextures[DIFFUSE_TEX]->pRenderTargetView.Get(),
	//	gTextures[POSITION_TEX]->pRenderTargetView.Get(),
	//	gTextures[NORMAL_TEX]->pRenderTargetView.Get()
	//};

	ID3D11RenderTargetView* renderTargets[N_GTEXTURES] = {};
	for (unsigned int i = 0; i < N_GTEXTURES; i++)
	{
		renderTargets[i] = gTextures[i]->pRenderTargetView.Get();
	}

	// TODO: Add stencil depth texture
	gfx.pContext->OMSetRenderTargets(N_GTEXTURES, renderTargets, depthRenderTexture.pDepthStencilView.Get());
}

void GBuffer::BindAsTextures(DTGraphics& gfx, UINT startSlot)
{
	for (unsigned int i = 0; i < N_GTEXTURES; i++)
	{
		UINT slotNum = startSlot + i;
		gTextures[i]->BindAsTexture(gfx,slotNum);
	}
}


void GBuffer::Clear(DTGraphics& gfx)
{
	for (unsigned int i = 0; i < N_GTEXTURES; i++)
	{
		float clearColor[3] = { 0.0f,0.0f,0.0f };
		gTextures[i]->ClearRenderTarget(gfx, clearColor);
	}

	depthRenderTexture.Clear(gfx);
}

void GBuffer::BindCollectionShaders(DTGraphics& gfx)
{
	VS.Bind(gfx);
	PS.Bind(gfx);
}

std::vector<std::shared_ptr<RenderTargetTexture>>& GBuffer::GetRenderTextures()
{
	return gTextures;
}


