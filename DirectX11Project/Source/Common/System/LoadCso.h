//==========================================================================
// .cso読み込み [LoadCso.h]
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
// Content : .cso読み込み専用の機能です。
// details : 継承禁止
//
//==========================================================================
class LoadCso final
{
private:
	size_t cso_size; // データサイズ
	char* cso_data; // データ
private:
	LoadCso() = delete;
public:
	LoadCso(const std::string& cso_file_path);
	~LoadCso();

	/**
	@brief データを取得します。
	@return データ
	*/
	const char* GetData() const;

	/**
	@brief データのサイズを取得します。
	@return データのサイズ
	*/
	size_t GetSize() const;
};

_MDX_COMMON_END