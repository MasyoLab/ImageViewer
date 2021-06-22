//==========================================================================
// �V�F�[�_�[�e�N�X�`�� [ShaderTextureManager.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "../System.h"

_MDX_SYSTEM_BEGIN

namespace common
{
	_MDX_USING_COMMON
	_MDX_USING_STRUCTURE

	//==========================================================================
	//
	// class : ShaderTextureManager
	// Content : ShaderResource�������@�\�ł�
	// details : �p���֎~
	//
	//==========================================================================
	class ShaderTextureManager final :
		public Container<Texture>
	{
	private:
		DirectXDevice m_device; // �f�o�C�X
	public:
		ShaderTextureManager() = delete;
		ShaderTextureManager(DirectXDevice device);
		~ShaderTextureManager();
	public:
		/**
		@brief �e�N�X�`���̓ǂݍ���
		@param [in] filename : �t�@�C���p�X
		@return ShaderTexture
		*/
		Texture CreateTextureFromFile(const std::wstring& filename);

		/**
		@brief �e�N�X�`���̓ǂݍ���
		@param [in] filename : �t�@�C���p�X
		@return ID3D11ShaderResourceView*
		*/
		Texture CreateTextureFromFile(const wchar_t* filename);

		/**
		@brief �e�N�X�`���̓ǂݍ���
		@param [in] filename : �t�@�C���p�X
		@return ShaderTexture
		*/
		Texture CreateTextureFromFile(const std::string& filename);

		/**
		@brief �e�N�X�`���̓ǂݍ���
		@param [in] filename : �t�@�C���p�X
		@return ShaderTexture
		*/
		Texture CreateTextureFromFile(const char* filename);
	};
}

_MDX_SYSTEM_END