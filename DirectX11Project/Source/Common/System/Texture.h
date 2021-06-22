//==========================================================================
// �e�N�X�`�� [Texture.h]
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
// Content : ID3D11ShaderResourceView��Image�𓯎��Ɉ������߂̋@�\
// details : �p���֎~
//
//==========================================================================
class Texture final
{
private:
	DirectX::Image m_ImageInfo; // �e�N�X�`���̏��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Texture; // �e�N�X�`��
public:
	Texture();
	Texture(nullptr_t);
	Texture(const DirectX::Image& image, ID3D11ShaderResourceView* resource);
	Texture(const Texture& tex);
	~Texture();

	/**
	@brief �e�N�X�`���̏����擾���܂��B
	*/
	const DirectX::Image& GetImageInfo() const;

	/**
	@brief �e�N�X�`���̃T�C�Y��ݒ�
	*/
	void SetImageSize(size_t width, size_t height);

	/**
	@brief �e�N�X�`�����擾���܂��B
	*/
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetShaderTexture();

	Texture& operator=(const Texture& tex);
	bool operator!=(nullptr_t) const noexcept;
	bool operator==(nullptr_t) const noexcept;
	bool operator!=(const Texture& tex) const noexcept;
	bool operator==(const Texture& tex) const noexcept;
};

_MDX_COMMON_END