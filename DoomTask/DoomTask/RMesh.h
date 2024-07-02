#pragma once
#include "DTRenderObjectBase.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class RMesh : public DTRenderObjectBase
{
public:
	RMesh(DTGraphics& gfx, std::string path);
};

