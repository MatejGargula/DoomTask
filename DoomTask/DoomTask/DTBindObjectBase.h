#pragma once

#include "DTGraphics.h"

#include <d3d11.h>
#include <string>

class DTGraphics;

class DTBindObjectBase
{
public:
public:
	/// <summary>
	/// Abstract methods for binding the object into the pipeline.
	/// </summary>
	/// <param name="gfx"></param>
	virtual void Bind(DTGraphics& gfx) noexcept = 0;

	/// <summary>
	/// (Optional) virtual method. Unbinds the object from the pipeline 
	/// </summary>
	/// <param name="gfx"></param>
	virtual void Unbind(DTGraphics& gfx) noexcept;
	virtual ~DTBindObjectBase() = default;
protected:
	/// <summary>
	/// Returns the context of the device context
	/// </summary>
	/// <param name="gfx"> The main graphical component </param>
	/// <returns></returns>
	static ID3D11DeviceContext* GetContext(DTGraphics& gfx) noexcept;

	/// <summary>
	/// Returns the graphics device
	/// </summary>
	/// <param name="gfx">The main graphical component</param>
	/// <returns></returns>
	static ID3D11Device* GetDevice(DTGraphics& gfx) noexcept;

	/// <summary>
	/// Returns the info manager. Needed for reporting exceptions.
	/// </summary>
	/// <param name="gfx"></param>
	/// <returns></returns>
	static DxgiInfoManager& GetInfoManager(DTGraphics& gfx) noexcept;
};

