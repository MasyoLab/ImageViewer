//==========================================================================
// ゲームオブジェクト [GameObject.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <cstdio>
#include <list>
#include <unordered_map>
#include <typeinfo>
#include "Object.h"
#include "Component.h"
#include "../System.h"

#pragma region forward declaration
// 前方宣言
_MDX_SYSTEM_BEGIN
class DirectX11Manager;
_MDX_SYSTEM_END
_MDX_COMPONENT_BEGIN
class RendererManager;
class Transform;
class Camera;
_MDX_COMPONENT_END
_MDX_OBJECT_BEGIN
class Scene;
_MDX_OBJECT_END
#pragma endregion

_MDX_OBJECT_BEGIN

//==========================================================================
//
// class : GameObject 
// Content : ゲームオブジェクト
// details : 継承禁止
//
//==========================================================================
class GameObject final :
	public Object
{
	friend Scene;
	friend component::Camera;
	friend component::Transform;
	friend component::RendererManager;
private:
#pragma region Always necessary
	std::unordered_map <size_t, std::list<component::Component*>> m_ComponentList; // コンポーネントリスト
	std::list<common::SharePtr<GameObject>> m_Child; // 子
	GameObject* m_Parent; // 親
	Scene* m_Scene; // 自分が属しているシーン
	system::DirectX11Manager* m_Manager; // マネージャー
#pragma endregion
#pragma region Components
	component::Transform* m_Transform; // トランスフォーム
#pragma endregion
public:
	GameObject();
	GameObject(const std::string& ObjectName);
	virtual ~GameObject();

	/**
	@brief コンポーネントを追加してください。Componentを継承しないとエラーになります。
	@param [in] ComponentPtr : 生ポインタ
	@return 監視機能の参照クラス
	*/
	template <typename _Ty, class = std::enable_if_t<std::is_base_of<component::Component, _Ty>::value>>
	_Ty* AddComponent(_Ty* ComponentPtr) {
		return AssociateComponents(ComponentPtr);
	}

	/**
	@brief コンポーネントの取得
	@return 監視機能の参照クラス
	*/
	template <typename _Ty>
	_Ty* GetComponent() {
		// 取得対象の型があるかのチェック
		auto itr = m_ComponentList.find(typeid(_Ty).hash_code());
		if (itr == m_ComponentList.end())
			return nullptr;

		// 専用の管理枠があったが、機能が無い場合終了
		if ((int)itr->second.size() == 0)
			return nullptr;

		// 一番最後に登録されたコンポーネントを取得
		return static_cast<_Ty*>((*(--itr->second.end())));
	}

	/**
	@brief ゲームオブジェクトを追加します。
	*/
	common::SharePtr<GameObject> AddGameObject();

	/**
	@brief ゲームオブジェクトを追加します。
	@param [in] ObjectName : オブジェクト名
	*/
	common::SharePtr<GameObject> AddGameObject(const std::string& ObjectName);

	/**
	@brief ゲームオブジェクトを追加します。
	@param [in] ObjectPtr : オブジェクトのポインタ
	*/
	common::SharePtr<GameObject> AddGameObject(GameObject* ObjectPtr);

	/**
	@brief 子オブジェクトを取得します。
	@details std::list<SharePtr<GameObject>> の型で取得できます。
	*/
	const std::list<common::SharePtr<GameObject>>& GetChild();

	/**
	@brief 子オブジェクトの数を取得します。
	@return size_t
	*/
	size_t GetNumChild();
private:
	/**
	@brief シーンを登録します。
	@param [in] ScenePtr : シーンのポインタ
	*/
	void SetScene(Scene* ScenePtr);

	/**
	@brief 所属しているシーンを取得します。
	*/
	Scene* GetScene();

	/**
	@brief 親オブジェクトを登録します。
	@param [in] ParentPtr : 親のポインタ
	*/
	void SetParent(GameObject* ParentPtr);

	/**
	@brief 親オブジェクトを取得します。
	*/
	GameObject* GetParent();

	/**
	@brief マネージャーを登録します。
	@param [in] ManagerPtr : マネージャーのポインタ
	*/
	void SetDirectX11Manager(system::DirectX11Manager* ManagerPtr);

	/**
	@brief コンポーネントの関連付け
	@param [in] ComponentPtr : コンポーネントのポインタ
	*/
	template <typename _Ty>
	_Ty* AssociateComponents(_Ty* ComponentPtr) {
		// 関連付け
		ComponentPtr->SetGameObject(this);
		ComponentPtr->SetDirectX11Manager(m_Manager);
		static_cast<component::Component*>(ComponentPtr)->Init();
		// クラス領域に格納します
		m_ComponentList[typeid(_Ty).hash_code()].emplace_back(ComponentPtr);
		return ComponentPtr;
	}

	/**
	@brief オブジェクトの更新機能
	*/
	void Update();
};

#pragma region Components
template <>
component::Transform* GameObject::AddComponent<component::Transform, void>(component::Transform* TransformPtr);

template <>
component::Transform* GameObject::GetComponent();
#pragma endregion

using GameObjectReference = common::SharePtr<GameObject>;

_MDX_OBJECT_END