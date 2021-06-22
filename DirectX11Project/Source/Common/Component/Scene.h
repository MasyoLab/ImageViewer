//==========================================================================
// シーン [Scene.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <string>
#include <list>
#include <algorithm>
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

_MDX_OBJECT_BEGIN

//==========================================================================
//
// class : Scene 
// Content : シーンの機能
// details : 継承用
//
//==========================================================================
class Scene
{
	friend GameObject;
private:
	std::string m_Name; // シーンの名前
	std::list<common::SharePtr<GameObject>> m_GameObjectList; // ゲームオブジェクトリスト
	std::list<common::SharePtr<GameObject>> m_GameObjectChild; // 子のゲームオブジェクト
	system::DirectX11Manager* m_Manager; // マネージャー
public:
	Scene() = delete;
	Scene(system::DirectX11Manager* ManagerPtr);
	Scene(const std::string& SceneName, system::DirectX11Manager* ManagerPtr);
	virtual ~Scene();

	/**
	@brief ゲームオブジェクトを追加します。
	*/
	common::SharePtr<GameObject> AddGameObject();

	/**
	@brief ゲームオブジェクトを追加します。
	@param [in] str : オブジェクト名
	*/
	common::SharePtr<GameObject> AddGameObject(const std::string& str);

	/**
	@brief ゲームオブジェクトを追加します。
	@param [in] obj : オブジェクトのポインタ
	*/
	common::SharePtr<GameObject> AddGameObject(GameObject* obj);

	/**
	@brief 指定した名前のオブジェクトを取得します。
	@param [in] str : オブジェクト名
	*/
	common::SharePtr<GameObject> Find(const std::string& str);

	/**
	@brief シーンのオブジェクトを更新します。
	*/
	void Update();

	/**
	@brief シーンのオブジェクトを描画します。
	*/
	void Draw();
private:
	/**
	@brief ゲームオブジェクトを登録します。
	@param [in] obj : オブジェクトのポインタ
	*/
	void SetGameObject(common::SharePtr<GameObject>& obj);

	/**
	@brief ゲームオブジェクトを解放します。
	@param [in] obj : オブジェクトのポインタ
	*/
	void ReleaseGameObject(GameObject* obj);
};

_MDX_OBJECT_END