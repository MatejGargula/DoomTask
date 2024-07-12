#include "LLightGroup.h"

void LLightGroup::updateData()
{
	data.nLights = lights.size();
	for (unsigned int i = 0; i < data.nLights; i++)
	{
		data.lights[i].position = lights[i]->position;
		data.lights[i].ambient = lights[i]->ambient;
		data.lights[i].diffuse = lights[i]->diffuse;
		data.lights[i].specular = lights[i]->specular;
		data.lights[i].att.x = lights[i]->constant;
		data.lights[i].att.y = lights[i]->linear;
		data.lights[i].att.z = lights[i]->quadratic;
	}
}

LLightGroup::LLightGroup(DTGraphics& gfx)
{
	data = {};
	if (!pPcbuf)
	{
		pPcbuf = std::make_unique<BPixelConstantBuffer<LightGroupCbuf>>(gfx, 1u);
	}
}

void LLightGroup::BindGroup(DTGraphics& gfx)
{
	updateData();

	auto LightbyteSize = sizeof(data.lights[0]);
	auto byteSize = sizeof(data);

	pPcbuf->Update(gfx, data);
	pPcbuf->Bind(gfx);
}

void LLightGroup::AddLight(std::unique_ptr<LPointLight> light)
{
	lights.push_back(std::move(light));
}

void LLightGroup::RenderLightsRO(DTGraphics& gfx)
{
	if (!lightMeshesSetUp)
		return;

	for (unsigned int i = 0; i < lights.size(); i++)
	{
		lights[i]->Render(gfx, ro.get());
	}
}

void LLightGroup::SetUpLightMeshes(std::shared_ptr<DTRenderObjectBase> roMesh)
{
	lightMeshesSetUp = true;
	ro = roMesh;
}
