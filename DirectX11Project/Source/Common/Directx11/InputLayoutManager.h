//==========================================================================
// インプットレイアウト [InputLayoutManager.h]
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
	// class : InputLayoutManager 
	// Content : インプットレイアウト
	// details : 継承禁止
	//
	//==========================================================================
	class InputLayoutManager final :
		public Container<InputLayout>
	{
	private:
		DirectXDevice m_device; // デバイス
	public:
		InputLayoutManager() = delete;
		InputLayoutManager(DirectXDevice device);
		~InputLayoutManager();

		/**
		@brief 入力レイアウト作成
		@param [in] layout : D3D11_INPUT_ELEMENT_DESC
		@param [in] elem_num : D3D11_INPUT_ELEMENT_DESC のサイズ
		@param [in] cso_file_path : .cosのファイルパス
		@return InputLayout
		*/
		InputLayout CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& cso_file_path);

		/**
		@brief 入力レイアウト作成
		@param [in] layout : D3D11_INPUT_ELEMENT_DESC
		@param [in] elem_num : D3D11_INPUT_ELEMENT_DESC のサイズ
		@param [in] filename : ファイルパス
		@param [in] entrypath : エントリーパッチ(vsMain とか psMain)
		@return InputLayout
		*/
		InputLayout CompileInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& filename, const std::string& entrypath = "");
	};
}

_MDX_SYSTEM_END