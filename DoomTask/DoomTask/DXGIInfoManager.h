#pragma once
#include "DTWnds.h"
#pragma warning(disable:4265)
#include <wrl.h>
#pragma warning(default:4265)
#include <vector>
#include <string>
#include <dxgidebug.h>

class DXGIInfoManager
{
public:
	DXGIInfoManager();
	~DXGIInfoManager() = default;
	DXGIInfoManager(const DXGIInfoManager&) = delete;
	DXGIInfoManager& operator=(const DXGIInfoManager&) = delete;
	void Set() noexcept;
	std::vector<std::string> GetMessages() const;
private:
	unsigned long long next = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> pDxgiInfoQueue;
};