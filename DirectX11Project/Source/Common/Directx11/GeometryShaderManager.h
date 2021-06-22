//==========================================================================
// �W�I���g���[�V�F�[�_�[�̃}�l�[�W���[ [GeometryShaderManager.h]
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
	// Content : �W�I���g���[�V�F�[�_�[�̃}�l�[�W���[
	// details : �p���֎~
	//
	//==========================================================================
	class GeometryShaderManager final :
		public Container<GeometryShader>
	{
	private:
		DirectXDevice m_device; // �f�o�C�X
	public:
		GeometryShaderManager() = delete;
		GeometryShaderManager(DirectXDevice device);
		~GeometryShaderManager();

		/**
		@brief �W�I���g���V�F�[�_�[����
		@param [in] cso_file_path : .cos�̃t�@�C���p�X
		@return GeometryShader
		*/
		GeometryShader CreateGeometryShader(const std::string& cso_file_path);

		/**
		@brief �W�I���g���V�F�[�_�[�̃R���p�C��
		@param [in] filename : �t�@�C���p�X
		@param [in] entrypath : �G���g���[�p�b�`(vsMain �Ƃ� psMain)
		@param [in] erorr : �G���[���������邩�ǂ���(�f�t�H���g�ŗL��)
		@return GeometryShader
		*/
		GeometryShader CompileGeometryShader(const std::string& filename, const std::string& entrypath = "", bool erorr = true);
	};
}

_MDX_SYSTEM_END