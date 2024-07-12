#pragma once
#include "DTWnds.h"
#include <wrl.h>
#include <vector>
#include <dxgidebug.h>
#include <string>

/// <summary>
/// Class for managing the infomations about error in the pipeline. 
/// </summary>
class DxgiInfoManager
{
public:
	DxgiInfoManager();
	~DxgiInfoManager() = default;
	DxgiInfoManager(const DxgiInfoManager&) = delete;
	DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessages() const;
private:
	unsigned long long next = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
};