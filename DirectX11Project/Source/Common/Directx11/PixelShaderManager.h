//==========================================================================
// �s�N�Z���V�F�[�_�̃}�l�[�W���[ [PixelShaderManager.h]
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
	// Content : �s�N�Z���V�F�[�_�̃}�l�[�W���[
	// details : �p���֎~
	//
	//==========================================================================
	class PixelShaderManager final :
		public Container<PixelShader>
	{
	private:
		DirectXDevice m_device; // �f�o�C�X
	public:
		PixelShaderManager() = delete;
		PixelShaderManager(DirectXDevice device);
		~PixelShaderManager();

		/**
		@brief �s�N�Z���V�F�[�_�[����
		@param [in] cso_file_path : .cos�̃t�@�C���p�X
		@return PixelShader
		*/
		PixelShader CreatePixelShader(const std::string& cso_file_path);

		/**
		@brief �s�N�Z���V�F�[�_�[����
		@param [in] filename : �t�@�C���p�X
		@param [in] entrypath : �G���g���[�p�b�`(vsMain �Ƃ� psMain)
		@param [in] erorr : �G���[���������邩�ǂ���(�f�t�H���g�ŗL��)
		@return PixelShader
		*/
		PixelShader CompilePixelShader(const std::string& filename, const std::string& entrypath, bool erorr = true);
	};
}

_MDX_SYSTEM_END