#include "LPointLight.h"

LPointLight::LPointLight(DTGraphics& gfx, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 amb, DirectX::XMFLOAT3 diff, DirectX::XMFLOAT3 spec, float constant, float linear, float quadratic)
	:
	pPcbuf(nullptr),
	position(pos),
	ambient(amb),
	diffuse(diff),
	specular(spec),
	constant(constant),
	linear(linear),
	quadratic(quadratic),
	transf(gfx)
{
	PointLightCBuf data = {};
	data.position = position;
	data.ambient = ambient;
	data.diffuse = diffuse;
	data.specular = specular;
	data.att = { constant, linear, quadratic };

}

void LPointLight::SetPosition(DirectX::XMFLOAT3 pos)
{
	position = pos;
}

void LPointLight::Render(DTGraphics& gfx, DTRenderObjectBase* ro)
{
	BTransform transf(gfx);
	transf.SetPosition(position.x, position.y, position.z);
	transf.Bind(gfx);
	ro->Render(gfx);
}


