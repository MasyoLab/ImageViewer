//==========================================================================
// ジオメトリーシェーダーのマネージャー [GeometryShaderManager.h]
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
	// class : GeometryShaderManager 
	// Content : ジオメトリーシェーダーのマネージャー
	// details : 継承禁止
	//
	//==========================================================================
	class GeometryShaderManager final :
		public Container<GeometryShader>
	{
	private:
		DirectXDevice m_device; // デバイス
	public:
		GeometryShaderManager() = delete;
		GeometryShaderManager(DirectXDevice device);
		~GeometryShaderManager();

		/**
		@brief ジオメトリシェーダー生成
		@param [in] cso_file_path : .cosのファイルパス
		@return GeometryShader
		*/
		GeometryShader CreateGeometryShader(const std::string& cso_file_path);

		/**
		@brief ジオメトリシェーダーのコンパイラ
		@param [in] filename : ファイルパス
		@param [in] entrypath : エントリーパッチ(vsMain とか psMain)
		@param [in] erorr : エラー処理をするかどうか(デフォルトで有効)
		@return GeometryShader
		*/
		GeometryShader CompileGeometryShader(const std::string& filename, const std::string& entrypath = "", bool erorr = true);
	};
}

_MDX_SYSTEM_END