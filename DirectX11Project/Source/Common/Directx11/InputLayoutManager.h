//==========================================================================
// �C���v�b�g���C�A�E�g [InputLayoutManager.h]
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
	// Content : �C���v�b�g���C�A�E�g
	// details : �p���֎~
	//
	//==========================================================================
	class InputLayoutManager final :
		public Container<InputLayout>
	{
	private:
		DirectXDevice m_device; // �f�o�C�X
	public:
		InputLayoutManager() = delete;
		InputLayoutManager(DirectXDevice device);
		~InputLayoutManager();

		/**
		@brief ���̓��C�A�E�g�쐬
		@param [in] layout : D3D11_INPUT_ELEMENT_DESC
		@param [in] elem_num : D3D11_INPUT_ELEMENT_DESC �̃T�C�Y
		@param [in] cso_file_path : .cos�̃t�@�C���p�X
		@return InputLayout
		*/
		InputLayout CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& cso_file_path);

		/**
		@brief ���̓��C�A�E�g�쐬
		@param [in] layout : D3D11_INPUT_ELEMENT_DESC
		@param [in] elem_num : D3D11_INPUT_ELEMENT_DESC �̃T�C�Y
		@param [in] filename : �t�@�C���p�X
		@param [in] entrypath : �G���g���[�p�b�`(vsMain �Ƃ� psMain)
		@return InputLayout
		*/
		InputLayout CompileInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& filename, const std::string& entrypath = "");
	};
}

_MDX_SYSTEM_END