//==========================================================================
// ���_�V�F�[�_�[�̃}�l�[�W���[ [VertexShaderManager.h]
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
	// Content : ���_�V�F�[�_�[�̃}�l�[�W���[
	// details : �p���֎~
	//
	//==========================================================================
	class VertexShaderManager final :
		public Container<VertexShader>
	{
	private:
		DirectXDevice m_device; // �f�o�C�X
	public:
		VertexShaderManager() = delete;
		VertexShaderManager(DirectXDevice device);
		~VertexShaderManager();

		/**
		@brief �o�[�e�b�N�X�V�F�[�_�[����
		@param [in] cso_file_path : .cos�̃t�@�C���p�X
		@return VertexShader
		*/
		VertexShader CreateVertexShader(const std::string& cso_file_path);

		/**
		@brief �o�[�e�b�N�X�V�F�[�_�[�̃R���p�C��
		@param [in] filename : �t�@�C���p�X
		@param [in] entrypath : �G���g���[�p�b�`(vsMain �Ƃ� psMain)
		@param [in] erorr : �G���[���������邩�ǂ���(�f�t�H���g�ŗL��)
		@return VertexShader
		*/
		VertexShader CompileVertexShader(const std::string& filename, const std::string& entrypath, bool erorr = true);
	};
}

_MDX_SYSTEM_END