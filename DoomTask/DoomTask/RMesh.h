#pragma once
#include "DTRenderObjectBase.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

/// <summary>
/// Class for rendering a single mesh geometry. For multi mesh rendering use RMultiMesh
/// </summary>
class RMesh : public DTRenderObjectBase
{
public:
	/// <summary>
	/// Constructor. Parses the mesh from file located at the given path.
	/// </summary>
	/// <param name="gfx"> reference to DTGraphics class. Required for graphics manipulations. </param>
	/// <param name="path"> path to the given mesh. </param>
	RMesh(DTGraphics& gfx, std::string path);

	/// <summary>
	/// Constructor. Creates a single mesh for rendering. 
	/// </summary>
	/// <param name="gfx"></param>
	/// <param name="mesh"> Assimp structure for holding mesh data. </param>
	/// <param name="materials"> Pointer to assimp structure holding material data. </param>
	RMesh(DTGraphics& gfx, aiMesh& mesh /*, const aiMaterial* const* materials*/);
};

