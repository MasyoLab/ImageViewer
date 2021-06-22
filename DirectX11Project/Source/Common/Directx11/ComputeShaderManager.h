//==========================================================================
// �R���s���[�g�V�F�[�_�[�̃}�l�[�W���[ [ComputeShaderManager.h]
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
	// Content : �R���s���[�g�V�F�[�_�[�̃}�l�[�W���[
	// details : �p���֎~
	//
	//==========================================================================
	class ComputeShaderManager final :
		public Container<structure::ComputeShader>
	{
	private:
		DirectXDevice m_device; // �f�o�C�X
	public:
		ComputeShaderManager() = delete;
		ComputeShaderManager(DirectXDevice device);
		~ComputeShaderManager();

		/**
		@brief �R���s���[�g�V�F�[�_�[����
		@param [in] cso_file_path : .cos�̃t�@�C���p�X
		@return ComputeShader
		*/
		ComputeShader CreateComputeShader(const std::string& cso_file_path);

		/**
		@brief �R���s���[�g�V�F�[�_�[�̃R���p�C��
		@param [in] filename : �t�@�C���p�X
		@param [in] entrypath : �G���g���[�p�b�`(vsMain �Ƃ� psMain)
		@return ComputeShader
		*/
		ComputeShader CompileComputeShader(const std::string& filename, const std::string& entrypath = "");
	};
}

_MDX_SYSTEM_END