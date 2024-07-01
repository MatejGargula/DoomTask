#define STB_IMAGE_IMPLEMENTATION
#include "BTexture.h"
#include "stb_image.h"

BTexture::BTexture(DTGraphics& gfx, std::string path, DXGI_FORMAT format)
{
	// Needed for macro throws
	DxgiInfoManager& infoManager = GetInfoManager(gfx);
	HRESULT hr;

	int imageDesiredChannels = 4;
	int w = 0;
	int h = 0;
	int ch = 0;

	std::unique_ptr<unsigned char> ImageData(stbi_load(path.c_str(),
		&w,
		&h,
		&ch, imageDesiredChannels));

	assert(ImageData);

	width = w;
	height = h;
	channels = ch;
	
	// Texture creation
	D3D11_TEXTURE2D_DESC td = {};
	td.Width = width;
	td.Height = height;
	td.MipLevels = 1;
	td.ArraySize = 1; // Means that it creates a single texture
	td.Format = format;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = (void*)ImageData.get();
	sd.SysMemPitch = width * 4;

	GFX_THROW_INFO(GetDevice(gfx)->CreateTexture2D(&td, &sd, &pTexture));

	//Resource view from created texture
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd = {};
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;

	GFX_THROW_INFO(GetDevice(gfx)->CreateShaderResourceView(pTexture.Get(), &srvd, &pTextureView));

}

void BTexture::Bind(DTGraphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShaderResources(0u, 1u, pTextureView.GetAddressOf());
}
