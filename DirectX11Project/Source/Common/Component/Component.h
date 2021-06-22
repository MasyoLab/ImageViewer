//==========================================================================
// コンポーネント [Component.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Object.h"
#include "../System.h"

#pragma region forward declaration
// 前方宣言
_MDX_SYSTEM_BEGIN
class DirectX11Manager;
_MDX_SYSTEM_END
_MDX_OBJECT_BEGIN
class GameObject;
_MDX_OBJECT_END
#pragma endregion

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : Component 
// Content : コンポーネント
// details : 継承用
//
//==========================================================================
class Component :
	public object::Object
{
	friend object::GameObject;
protected:
	object::GameObject* m_GameObject; // ゲームオブジェクト
	system::DirectX11Manager* m_Manager; // マネージャー
public:
	Component();
	Component(const std::string& ComponentName);
	virtual ~Component();
private:
	/**
	@brief ゲームオブジェクトのポインタを教えます。
	@param [in] ObjectPtr : オブジェクトのポインタ
	*/
	void SetGameObject(object::GameObject* ObjectPtr);

	/**
	@brief マネージャーを登録します。
	@param [in] ManagerPtr : マネージャー
	*/
	void SetDirectX11Manager(system::DirectX11Manager* ManagerPtr);
protected:
	/**
	@brief 初期化
	*/
	virtual void Init();

	/**
	@brief 更新
	*/
	virtual void Update();
};

_MDX_COMPONENT_END