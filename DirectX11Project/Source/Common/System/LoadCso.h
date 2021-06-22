//==========================================================================
// .cso�ǂݍ��� [LoadCso.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <string>
#include <fstream>
#include "mdx.h"

_MDX_COMMON_BEGIN

//==========================================================================
//
// class : LoadCso 
// Content : .cso�ǂݍ��ݐ�p�̋@�\�ł��B
// details : �p���֎~
//
//==========================================================================
class LoadCso final
{
private:
	size_t cso_size; // �f�[�^�T�C�Y
	char* cso_data; // �f�[�^
private:
	LoadCso() = delete;
public:
	LoadCso(const std::string& cso_file_path);
	~LoadCso();

	/**
	@brief �f�[�^���擾���܂��B
	@return �f�[�^
	*/
	const char* GetData() const;

	/**
	@brief �f�[�^�̃T�C�Y���擾���܂��B
	@return �f�[�^�̃T�C�Y
	*/
	size_t GetSize() const;
};

_MDX_COMMON_END