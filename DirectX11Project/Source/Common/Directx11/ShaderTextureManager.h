//==========================================================================
// シェーダーテクスチャ [ShaderTextureManager.h]
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
	// Content : ShaderResourceを扱う機能です
	// details : 継承禁止
	//
	//==========================================================================
	class ShaderTextureManager final :
		public Container<Texture>
	{
	private:
		DirectXDevice m_device; // デバイス
	public:
		ShaderTextureManager() = delete;
		ShaderTextureManager(DirectXDevice device);
		~ShaderTextureManager();
	public:
		/**
		@brief テクスチャの読み込み
		@param [in] filename : ファイルパス
		@return ShaderTexture
		*/
		Texture CreateTextureFromFile(const std::wstring& filename);

		/**
		@brief テクスチャの読み込み
		@param [in] filename : ファイルパス
		@return ID3D11ShaderResourceView*
		*/
		Texture CreateTextureFromFile(const wchar_t* filename);

		/**
		@brief テクスチャの読み込み
		@param [in] filename : ファイルパス
		@return ShaderTexture
		*/
		Texture CreateTextureFromFile(const std::string& filename);

		/**
		@brief テクスチャの読み込み
		@param [in] filename : ファイルパス
		@return ShaderTexture
		*/
		Texture CreateTextureFromFile(const char* filename);
	};
}

_MDX_SYSTEM_END