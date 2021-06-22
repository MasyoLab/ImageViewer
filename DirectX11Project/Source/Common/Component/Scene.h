//==========================================================================
// �V�[�� [Scene.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <string>
#include <list>
#include <algorithm>
#include "../System.h"

#pragma region forward declaration
// �O���錾
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
// Content : �V�[���̋@�\
// details : �p���p
//
//==========================================================================
class Scene
{
	friend GameObject;
private:
	std::string m_Name; // �V�[���̖��O
	std::list<common::SharePtr<GameObject>> m_GameObjectList; // �Q�[���I�u�W�F�N�g���X�g
	std::list<common::SharePtr<GameObject>> m_GameObjectChild; // �q�̃Q�[���I�u�W�F�N�g
	system::DirectX11Manager* m_Manager; // �}�l�[�W���[
public:
	Scene() = delete;
	Scene(system::DirectX11Manager* ManagerPtr);
	Scene(const std::string& SceneName, system::DirectX11Manager* ManagerPtr);
	virtual ~Scene();

	/**
	@brief �Q�[���I�u�W�F�N�g��ǉ����܂��B
	*/
	common::SharePtr<GameObject> AddGameObject();

	/**
	@brief �Q�[���I�u�W�F�N�g��ǉ����܂��B
	@param [in] str : �I�u�W�F�N�g��
	*/
	common::SharePtr<GameObject> AddGameObject(const std::string& str);

	/**
	@brief �Q�[���I�u�W�F�N�g��ǉ����܂��B
	@param [in] obj : �I�u�W�F�N�g�̃|�C���^
	*/
	common::SharePtr<GameObject> AddGameObject(GameObject* obj);

	/**
	@brief �w�肵�����O�̃I�u�W�F�N�g���擾���܂��B
	@param [in] str : �I�u�W�F�N�g��
	*/
	common::SharePtr<GameObject> Find(const std::string& str);

	/**
	@brief �V�[���̃I�u�W�F�N�g���X�V���܂��B
	*/
	void Update();

	/**
	@brief �V�[���̃I�u�W�F�N�g��`�悵�܂��B
	*/
	void Draw();
private:
	/**
	@brief �Q�[���I�u�W�F�N�g��o�^���܂��B
	@param [in] obj : �I�u�W�F�N�g�̃|�C���^
	*/
	void SetGameObject(common::SharePtr<GameObject>& obj);

	/**
	@brief �Q�[���I�u�W�F�N�g��������܂��B
	@param [in] obj : �I�u�W�F�N�g�̃|�C���^
	*/
	void ReleaseGameObject(GameObject* obj);
};

_MDX_OBJECT_END