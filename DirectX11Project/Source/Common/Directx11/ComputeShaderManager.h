//==========================================================================
// コンピュートシェーダーのマネージャー [ComputeShaderManager.h]
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
	// class : ComputeShaderManager 
	// Content : コンピュートシェーダーのマネージャー
	// details : 継承禁止
	//
	//==========================================================================
	class ComputeShaderManager final :
		public Container<structure::ComputeShader>
	{
	private:
		DirectXDevice m_device; // デバイス
	public:
		ComputeShaderManager() = delete;
		ComputeShaderManager(DirectXDevice device);
		~ComputeShaderManager();

		/**
		@brief コンピュートシェーダー生成
		@param [in] cso_file_path : .cosのファイルパス
		@return ComputeShader
		*/
		ComputeShader CreateComputeShader(const std::string& cso_file_path);

		/**
		@brief コンピュートシェーダーのコンパイラ
		@param [in] filename : ファイルパス
		@param [in] entrypath : エントリーパッチ(vsMain とか psMain)
		@return ComputeShader
		*/
		ComputeShader CompileComputeShader(const std::string& filename, const std::string& entrypath = "");
	};
}

_MDX_SYSTEM_END