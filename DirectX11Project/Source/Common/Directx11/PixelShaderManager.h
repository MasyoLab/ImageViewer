//==========================================================================
// ピクセルシェーダのマネージャー [PixelShaderManager.h]
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
	// class : PixelShaderManager 
	// Content : ピクセルシェーダのマネージャー
	// details : 継承禁止
	//
	//==========================================================================
	class PixelShaderManager final :
		public Container<PixelShader>
	{
	private:
		DirectXDevice m_device; // デバイス
	public:
		PixelShaderManager() = delete;
		PixelShaderManager(DirectXDevice device);
		~PixelShaderManager();

		/**
		@brief ピクセルシェーダー生成
		@param [in] cso_file_path : .cosのファイルパス
		@return PixelShader
		*/
		PixelShader CreatePixelShader(const std::string& cso_file_path);

		/**
		@brief ピクセルシェーダー生成
		@param [in] filename : ファイルパス
		@param [in] entrypath : エントリーパッチ(vsMain とか psMain)
		@param [in] erorr : エラー処理をするかどうか(デフォルトで有効)
		@return PixelShader
		*/
		PixelShader CompilePixelShader(const std::string& filename, const std::string& entrypath, bool erorr = true);
	};
}

_MDX_SYSTEM_END