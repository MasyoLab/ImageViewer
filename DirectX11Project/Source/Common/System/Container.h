//==========================================================================
// コンテナ [Container.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "dx11afx.h"

_MDX_COMMON_BEGIN

//==========================================================================
//
// class : Container 
// Content : コンテナ
// details : 継承して使うことを想定したコンテナです。
//
//==========================================================================
template <typename _Ty>
class Container
{
private:
	std::unordered_map<std::string, _Ty> m_resource_data; // データの管理
public:
	Container() {}
	~Container() {}
protected:
	/**
	@brief 名前でデータを取り出します。
	@param [in] tag : データのタグ
	@return 存在する場合は実体が返ります。
	*/
	_Ty get(const std::string& tag) {
		auto itr = m_resource_data.find(tag);
		if (itr != m_resource_data.end())
			return itr->second;
		return _Ty();
	}

	/**
	@brief データを登録します。
	@param [in] tag : データのタグ
	@param [in] resource : 登録するデータ
	@return 実体が返ります。
	*/
	_Ty set(const std::string& tag, _Ty resource) {
		m_resource_data[tag] = resource;
		return resource;
	}
public:
	/**
	@brief データを指定して破棄します。
	@param [in] tag : データのタグ
	*/
	void destroy(const std::string& tag) {
		auto itr = m_resource_data.find(tag);
		if (itr == m_resource_data.end())
			return;
		m_resource_data.erase(itr);
	}

	/**
	@brief データを指定して破棄します。
	@param [in] resource : 破棄するデータ
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
	@brief 登録してあるデータ数を取得します。
	@return データ数
	*/
	size_t size() {
		return m_resource_data.size();
	}
};

_MDX_COMMON_END