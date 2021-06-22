//==========================================================================
// オブジェクト [Object.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <string>
#include "../System.h"

_MDX_OBJECT_BEGIN

//==========================================================================
//
// class : Object 
// Content : オブジェクト
// details : 継承用
//
//==========================================================================
class Object
{
private:
	std::string m_ObjectName; // オブジェクト名
	bool m_DisplayFlags; // オブジェクト表示フラグ
public:
	Object();
	Object(const std::string& ObjectName);
	~Object();

	/**
	@brief オブジェクト名を登録します。
	@param [in] ObjectName : オブジェクト名
	*/
	void SetObjectName(const std::string& ObjectName);

	/**
	@brief オブジェクト名を取得します。
	@return オブジェクト名
	*/
	const std::string& GetObjectName();

	/**
	@brief 処理の有効/無効を指定します。
	@param [in] bFlag : フラグ
	@details true で有効。デフォルトで有効になっています。
	*/
	void SetDisplayFlags(bool bFlag);

	/**
	@brief 処理の有無を取得します。
	@details true で有効。
	*/
	bool GetDisplayFlags();
};

_MDX_OBJECT_END