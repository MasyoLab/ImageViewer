//==========================================================================
// テクスチャ [Texture.cpp]
// author : MasyoLab
//==========================================================================
#include "Texture.h"

_MDX_COMMON_BEGIN

Texture::Texture() :
	m_ImageInfo(DirectX::Image()), m_Texture(nullptr)
{
}

Texture::Texture(nullptr_t) :
	m_ImageInfo(DirectX::Image()), m_Texture(nullptr)
{
}

Texture::Texture(const DirectX::Image& image, ID3D11ShaderResourceView* resource) :
	m_ImageInfo(image), m_Texture(resource)
{
	m_Texture.Attach(resource);
}

Texture::Texture(const Texture& tex)
{
	*this = tex;
}

Texture::~Texture()
{
}

const DirectX::Image& Texture::GetImageInfo() const
{
	return m_ImageInfo;
}

void Texture::SetImageSize(size_t width, size_t height)
{
	m_ImageInfo.width = width;
	m_ImageInfo.height = height;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture::GetShaderTexture()
{
	return m_Texture;
}

Texture& Texture::operator=(const Texture& tex)
{
	m_ImageInfo = tex.m_ImageInfo;
	m_Texture = tex.m_Texture;
	return *this;
}

bool Texture::operator!=(nullptr_t) const noexcept
{
	return m_Texture != nullptr;
}

bool Texture::operator==(nullptr_t) const noexcept
{
	return m_Texture == nullptr;
}

bool Texture::operator!=(const Texture& tex) const noexcept
{
	return m_Texture != tex.m_Texture;
}

bool Texture::operator==(const Texture& tex) const noexcept
{
	return m_Texture == tex.m_Texture;
}

_MDX_COMMON_END