//==========================================================================
// �R���e�i [Container.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "dx11afx.h"

_MDX_COMMON_BEGIN

//==========================================================================
//
// class : Container 
// Content : �R���e�i
// details : �p�����Ďg�����Ƃ�z�肵���R���e�i�ł��B
//
//==========================================================================
template <typename _Ty>
class Container
{
private:
	std::unordered_map<std::string, _Ty> m_resource_data; // �f�[�^�̊Ǘ�
public:
	Container() {}
	~Container() {}
protected:
	/**
	@brief ���O�Ńf�[�^�����o���܂��B
	@param [in] tag : �f�[�^�̃^�O
	@return ���݂���ꍇ�͎��̂��Ԃ�܂��B
	*/
	_Ty get(const std::string& tag) {
		auto itr = m_resource_data.find(tag);
		if (itr != m_resource_data.end())
			return itr->second;
		return _Ty();
	}

	/**
	@brief �f�[�^��o�^���܂��B
	@param [in] tag : �f�[�^�̃^�O
	@param [in] resource : �o�^����f�[�^
	@return ���̂��Ԃ�܂��B
	*/
	_Ty set(const std::string& tag, _Ty resource) {
		m_resource_data[tag] = resource;
		return resource;
	}
public:
	/**
	@brief �f�[�^���w�肵�Ĕj�����܂��B
	@param [in] tag : �f�[�^�̃^�O
	*/
	void destroy(const std::string& tag) {
		auto itr = m_resource_data.find(tag);
		if (itr == m_resource_data.end())
			return;
		m_resource_data.erase(itr);
	}

	/**
	@brief �f�[�^���w�肵�Ĕj�����܂��B
	@param [in] resource : �j������f�[�^
	*/
	void destroy(const _Ty& resource) {
		auto search = [&](const _Ty& resource) {
			auto itr = m_resource_data.begin();
			for (; itr != m_resource_data.end(); ++itr)
				if (itr->second == resource)
					return itr;
			return itr;
		};
		auto itr = search(resource);
		if (itr == m_resource_data.end())
			return;
		m_resource_data.erase(itr);
	}

	/**
	@brief �o�^���Ă���f�[�^�����擾���܂��B
	@return �f�[�^��
	*/
	size_t size() {
		return m_resource_data.size();
	}
};

_MDX_COMMON_END