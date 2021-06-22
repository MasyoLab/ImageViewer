//==========================================================================
// シーン [Scene.cpp]
// author : MasyoLab
//==========================================================================
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RendererManager.h"
#include "Camera.h"
#include "../DirectX11.h"

_MDX_OBJECT_BEGIN
_MDX_USING_COMPONENT
_MDX_USING_SYSTEM
_MDX_USING_COMMON

Scene::Scene(DirectX11Manager* ManagerPtr) :
	m_Name("Scene"), m_Manager(ManagerPtr)
{
	// このシーン用の描画枠を生成
	RendererManager::CreateSceneRenderer(this);

	auto mainCamera = AddGameObject("MainCamera");
	mainCamera->AddComponent(new Camera);
}

Scene::Scene(const std::string& SceneName, DirectX11Manager* ManagerPtr) :
	m_Name(SceneName), m_Manager(ManagerPtr)
{
	// このシーン用の描画枠を生成
	RendererManager::CreateSceneRenderer(this);

	auto mainCamera = AddGameObject("MainCamera");
	mainCamera->AddComponent(new Camera);
}

Scene::~Scene()
{
	// このシーン用の描画枠を解放
	RendererManager::ReleaseSceneRenderer(this);
	Camera::ReleaseSceneCameras(this);

	// 属しているオブジェクトの管理を止める
	m_GameObjectList.clear();

	// 子オブジェクトを破棄
	for (auto& child : m_GameObjectChild)
		child.destroy();
	m_GameObjectChild.clear();
}

SharePtr<GameObject> Scene::AddGameObject()
{
	return AddGameObject(new GameObject("GameObject"));
}

SharePtr<GameObject> Scene::AddGameObject(const std::string& str)
{
	return AddGameObject(new GameObject(str));
}

SharePtr<GameObject> Scene::AddGameObject(GameObject* obj)
{
	auto shareObj = SharePtr<GameObject>(obj);
	SetGameObject(shareObj);
	m_GameObjectChild.emplace_back(shareObj);
	return shareObj;
}

SharePtr<GameObject> Scene::Find(const std::string& str)
{
	auto itr = std::find_if(m_GameObjectList.begin(), m_GameObjectList.end(),
		[&](const SharePtr<GameObject>& obj) {
			return obj->GetObjectName() == str; }); //ここでGameObjectへの参照をキャプチャしている
	if (itr != m_GameObjectList.end())
		return (*itr);
	return nullptr;
}

void Scene::Update()
{
	for (auto& itr : m_GameObjectList)
		itr->Update();
}

void Scene::Draw()
{
	// このシーンの描画機能を全て実行
	for (auto& itr : Camera::GetCameras(this))
		RendererManager::DrawSceneRenderer(this, itr->GetViewMatrix(), itr->GetProjectionMatrix());
}

void Scene::SetGameObject(SharePtr<GameObject>& obj)
{
	obj->SetScene(this);
	obj->SetDirectX11Manager(m_Manager);
	m_GameObjectList.push_back(obj);
}

void Scene::ReleaseGameObject(GameObject* obj)
{
	auto itr = std::find_if(m_GameObjectList.begin(), m_GameObjectList.end(),
		[&](const SharePtr<GameObject>& obj_itr) {
			return obj_itr == obj; }); //ここでGameObjectへの参照をキャプチャしている
	if (itr != m_GameObjectList.end())
		m_GameObjectList.erase(itr);
}

_MDX_OBJECT_END