#pragma once

#include "DTBindObjectBase.h"
#include "BConstantBuffer.h"

#include <DirectXMath.h>

/// <summary>
/// Class for handling the position and rotation of the objects.
/// </summary>
class BTransform : public DTBindObjectBase
{	
private:
	struct CbuffCameraData
	{
		DirectX::XMFLOAT3 pos;
		float pad;
	};

	struct Transforms
	{
		DirectX::XMMATRIX model;
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX modelViewProj;
	};

	struct HullShaderConstData
	{
		DirectX::XMFLOAT3 CameraPosition;
		float pad1;

		float TessellationRange;
		float MinTessFactor;
		float MaxTessFactor;
		float pad2;
	};

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	std::unique_ptr<BVertexConstantBuffer<Transforms>> pVcbuf;
	std::unique_ptr<BHullConstantBuffer<HullShaderConstData>> pHcbuf;
	std::unique_ptr<BPixelConstantBuffer<CbuffCameraData>> pPcbuf;

	DirectX::XMMATRIX modelMat;
	
	void updateTransformMatrix();
	Transforms getTransformMatrices(DTGraphics& gfx);

public:

	BTransform(DTGraphics& gfx);
	BTransform(DTGraphics& gfx, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot);

	void Bind(DTGraphics& gfx) noexcept override;
	/// <summary>
	/// Translates the object by the given positions.
	/// </summary>
	/// <param name="xPos"></param>
	/// <param name="yPos"></param>
	/// <param name="zPos"></param>
	void Translate(float xPos, float yPos, float zPos) noexcept;
	
	/// <summary>
	/// Sets the position
	/// </summary>
	/// <param name="xPos">X position</param>
	/// <param name="yPos">Y position</param>
	/// <param name="zPos">Z position</param>
	void SetPosition(float xPos, float yPos, float zPos) noexcept;
	
	/// <summary>
	/// Sets the rotation
	/// </summary>
	/// <param name="xPos">X rotation</param>
	/// <param name="yPos">Y rotation</param>
	/// <param name="zPos">Z rotation</param>
	void SetRotation(float xRot, float yRot, float zRot) noexcept;

	/// <summary>
	/// Returns the transformation matrix.
	/// </summary>
	/// <returns></returns>
	DirectX::XMMATRIX GetTransormMat() noexcept;

};

