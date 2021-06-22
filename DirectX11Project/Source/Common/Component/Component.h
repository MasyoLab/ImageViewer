//==========================================================================
// �R���|�[�l���g [Component.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Object.h"
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

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : Component 
// Content : �R���|�[�l���g
// details : �p���p
//
//==========================================================================
class Component :
	public object::Object
{
	friend object::GameObject;
protected:
	object::GameObject* m_GameObject; // �Q�[���I�u�W�F�N�g
	system::DirectX11Manager* m_Manager; // �}�l�[�W���[
public:
	Component();
	Component(const std::string& ComponentName);
	virtual ~Component();
private:
	/**
	@brief �Q�[���I�u�W�F�N�g�̃|�C���^�������܂��B
	@param [in] ObjectPtr : �I�u�W�F�N�g�̃|�C���^
	*/
	void SetGameObject(object::GameObject* ObjectPtr);

	/**
	@brief �}�l�[�W���[��o�^���܂��B
	@param [in] ManagerPtr : �}�l�[�W���[
	*/
	void SetDirectX11Manager(system::DirectX11Manager* ManagerPtr);
protected:
	/**
	@brief ������
	*/
	virtual void Init();

	/**
	@brief �X�V
	*/
	virtual void Update();
};

_MDX_COMPONENT_END