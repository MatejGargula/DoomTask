#include "LPointLight.h"

LPointLight::LPointLight(DTGraphics& gfx, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT3 spec, float constant, float linear, float quadratic)
	:
	position(pos),
	ambient(amb),
	diffuse(diff),
	specular(spec),
	constant(constant),
	linear(linear),
	quadratic(quadratic)
{
	PointLightCBuf data = {};
	data.position = position;
	data.ambient = ambient;
	data.diffuse = diffuse;
	data.specular = specular;
	data.att = { constant, linear, quadratic };

	pPcbuf = std::make_unique<BPixelConstantBuffer<PointLightCBuf>>(gfx, 1u);
}

void LPointLight::Bind(DTGraphics& gfx) noexcept
{
	PointLightCBuf data = {};
	data.position = position;
	data.ambient = ambient;
	data.diffuse = diffuse;
	data.specular = specular;
	data.att = { constant, linear, quadratic };

	pPcbuf->Update(gfx, data);
	pPcbuf->Bind(gfx);
}

void LPointLight::EnableLightRenderObject(std::shared_ptr<DTRenderObjectBase> mesh)
{
	showLightRO = true;
	lightRO = mesh;
}

void LPointLight::DisableLightRenderObject()
{
	showLightRO = false;
	lightRO = nullptr;
}

void LPointLight::SetPosition(DirectX::XMFLOAT3 pos)
{
	position = pos;
}

void LPointLight::Render(DTGraphics& gfx)
{
	BTransform transf(gfx);
	transf.SetPosition(position.x, position.y, position.z);
	
	lightRO->Render(gfx, transf);
}


