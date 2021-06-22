//==========================================================================
// テクスチャ [Texture.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <DirectXTex.h>
#include <wrl/client.h>
#include <type_traits>
#include "mdx.h"

_MDX_COMMON_BEGIN

//==========================================================================
//
// class : Texture 
// Content : ID3D11ShaderResourceViewとImageを同時に扱うための機能
// details : 継承禁止
//
//==========================================================================
class Texture final
{
private:
	DirectX::Image m_ImageInfo; // テクスチャの情報
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture; // テクスチャ
public:
	Texture();
	Texture(nullptr_t);
	Texture(const DirectX::Image& image, ID3D11ShaderResourceView* resource);
	Texture(const Texture& tex);
	~Texture();

	/**
	@brief テクスチャの情報を取得します。
	*/
	const DirectX::Image& GetImageInfo() const;

	/**
	@brief テクスチャのサイズを設定
	*/
	void SetImageSize(size_t width, size_t height);

	/**
	@brief テクスチャを取得します。
	*/
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderTexture();

	Texture& operator=(const Texture& tex);
	bool operator!=(nullptr_t) const noexcept;
	bool operator==(nullptr_t) const noexcept;
	bool operator!=(const Texture& tex) const noexcept;
	bool operator==(const Texture& tex) const noexcept;
};

_MDX_COMMON_END