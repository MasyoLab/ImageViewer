//==========================================================================
// �S�Ẵt�@�C�����`�F�b�N [CheckAllFile.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <string>
#include <list>
#include <random>
#include "common.h"
#include "file_path.hpp"
#include "folder_path.hpp"

namespace check_all_file
{
	// �t�@�C���̃f�[�^
	struct DataInfo
	{
		std::wstring m_str_name; // �t�@�C����
		std::wstring m_str_path; // �t�@�C���p�X
		std::wstring m_str_extension; // �g���q

		DataInfo(const std::wstring& str_name, const std::wstring& str_path, const std::wstring& str_extension);
		DataInfo() {}
	};

	using DataInfoList = std::list<DataInfo>;
	using string_list = std::list<std::wstring>;

	// �S�Ẵf�[�^���`�F�b�N
	class CheckAllFile :
		public mdx::component::Component
	{
	private:
		DataInfoList m_InfoList; // �f�[�^�i�[�p
	public:
		CheckAllFile();
		virtual ~CheckAllFile();

		/**
		@brief �f�B���N�g���̓ǂݍ���
		*/
		void LoadDirectory(const std::wstring& directory);

		/**
		@brief �f�[�^���擾
		*/
		const DataInfoList& GetData() const;

		/**
		@brief �f�[�^�̒������擾
		*/
		size_t Length() const;

		/**
		@brief �����_���ŃC�e���[�^�[���擾
		*/
		DataInfoList::iterator GetRandomIterator(std::mt19937& engine);
	private:

		/**
		@brief �t�@�C���T��
		@param dir_name [in] �T���Ώۃf�B���N�g��
		@param extension [in] �g���q�w��
		@param set_ [in]
		*/
		DataInfoList search(const std::wstring& dir_name, const string_list& extension, const std::wstring set_);

		/**
		@brief ������
		*/
		void Init() override;
	};
}