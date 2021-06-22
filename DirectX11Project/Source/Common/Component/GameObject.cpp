//==========================================================================
// ゲームオブジェクト [GameObject.cpp]
// author : MasyoLab
//==========================================================================
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "Camera.h"
#include "../DirectX11.h"

_MDX_OBJECT_BEGIN
_MDX_USING_COMPONENT
_MDX_USING_SYSTEM
_MDX_USING_COMMON

GameObject::GameObject() :
	Object("GameObject"), m_Scene(nullptr), m_Parent(nullptr),
	m_Transform(nullptr), m_Manager(nullptr)
{
	AddComponent(new Transform);
}

GameObject::GameObject(const std::string& ObjectName) :
	Object(ObjectName), m_Scene(nullptr), m_Parent(nullptr),
	m_Transform(nullptr), m_Manager(nullptr)
{
	AddComponent(new Transform);
}

GameObject::~GameObject()
{
	// シーンから自分を破棄
	if (m_Scene != nullptr)
	{
		m_Scene->ReleaseGameObject(this);
		m_Scene = nullptr;
	}

	// コンポーネントを破棄
	for (auto& componentType : m_ComponentList)
	{
		for (auto& componentPtr : componentType.second)
		{
			if (componentPtr == nullptr)
				continue;
			delete componentPtr;
			componentPtr = nullptr;
		}
	}

	// 子オブジェクトを破棄
	for (auto& childObject : m_Child)
		childObject.destroy();

	m_ComponentList.clear();
	m_Child.clear();
}

SharePtr<GameObject> GameObject::AddGameObject()
{
	return AddGameObject(new GameObject("GameObject"));
}

SharePtr<GameObject> GameObject::AddGameObject(const std::string& ObjectName)
{
	return AddGameObject(new GameObject(ObjectName));
}

SharePtr<GameObject> GameObject::AddGameObject(GameObject* ObjectPtr)
{
	auto shareObj = SharePtr<GameObject>(ObjectPtr);
	if (m_Scene != nullptr)
		m_Scene->SetGameObject(shareObj);
	ObjectPtr->SetParent(this);
	m_Child.emplace_back(shareObj);
	return shareObj;
}

const std::list<SharePtr<GameObject>>& GameObject::GetChild()
{
	return m_Child;
}

size_t GameObject::GetNumChild()
{
	return m_Child.size();
}

void GameObject::SetScene(Scene* ScenePtr)
{
	m_Scene = ScenePtr;
}

Scene* GameObject::GetScene()
{
	return m_Scene;
}

void GameObject::SetParent(GameObject* ParentPtr)
{
	m_Parent = ParentPtr;
}

GameObject* GameObject::GetParent()
{
	return m_Parent;
}

void GameObject::SetDirectX11Manager(DirectX11Manager* ManagerPtr)
{
	m_Manager = ManagerPtr;
}

void GameObject::Update()
{
	// コンポーネントの種類
	for (auto& componentType : m_ComponentList)
	{
		// コンポーネントのポインタ
		for (auto& componentPtr : componentType.second)
		{
			componentPtr->Update();
		}
	}
}
#pragma region Components
template<>
Transform* GameObject::AddComponent<Transform, void>(Transform* TransformPtr)
{
	m_Transform = AssociateComponents(TransformPtr);
	return m_Transform;
}

template <>
Transform* GameObject::GetComponent()
{
	return m_Transform;
}
#pragma endregion

_MDX_OBJECT_END