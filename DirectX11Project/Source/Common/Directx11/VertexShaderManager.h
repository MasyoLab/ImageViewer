//==========================================================================
// 頂点シェーダーのマネージャー [VertexShaderManager.h]
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
	// class : VertexShaderManager 
	// Content : 頂点シェーダーのマネージャー
	// details : 継承禁止
	//
	//==========================================================================
	class VertexShaderManager final :
		public Container<VertexShader>
	{
	private:
		DirectXDevice m_device; // デバイス
	public:
		VertexShaderManager() = delete;
		VertexShaderManager(DirectXDevice device);
		~VertexShaderManager();

		/**
		@brief バーテックスシェーダー生成
		@param [in] cso_file_path : .cosのファイルパス
		@return VertexShader
		*/
		VertexShader CreateVertexShader(const std::string& cso_file_path);

		/**
		@brief バーテックスシェーダーのコンパイラ
		@param [in] filename : ファイルパス
		@param [in] entrypath : エントリーパッチ(vsMain とか psMain)
		@param [in] erorr : エラー処理をするかどうか(デフォルトで有効)
		@return VertexShader
		*/
		VertexShader CompileVertexShader(const std::string& filename, const std::string& entrypath, bool erorr = true);
	};
}

_MDX_SYSTEM_END