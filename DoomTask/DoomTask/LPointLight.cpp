#include "LPointLight.h"

LPointLight::LPointLight(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT3 spec, float constant, float linear, float quadratic)
	:
	pPcbuf(nullptr),
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

	//pPcbuf = std::make_unique<BPixelConstantBuffer<PointLightCBuf>>(gfx, 1u);
}

//LPointLight::LPointLight()
//	:
//	showLightRO(false),
//	lightRO(nullptr),
//	pPcbuf(nullptr),
//	position(0.0f,0.0f, 0.0f),
//	ambient(1.0f, 1.0f, 1.0f),
//	diffuse(1.0f, 1.0f, 1.0f),
//	specular(1.0f, 1.0f, 1.0f),
//	constant(1.0f),
//	linear(0.045f),//linear(0.35f),
//	quadratic(0.0075f)//quadratic(0.44f)
//
//{
//}

void LPointLight::Bind(DTGraphics& gfx) noexcept
{
	if (pPcbuf == nullptr)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<PointLightCBuf>>(gfx, 1u);
	}

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


