//==========================================================================
// �Q�[���I�u�W�F�N�g [GameObject.h]
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
// �O���錾
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
// Content : �Q�[���I�u�W�F�N�g
// details : �p���֎~
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
	std::unordered_map <size_t, std::list<component::Component*>> m_ComponentList; // �R���|�[�l���g���X�g
	std::list<common::SharePtr<GameObject>> m_Child; // �q
	GameObject* m_Parent; // �e
	Scene* m_Scene; // �����������Ă���V�[��
	system::DirectX11Manager* m_Manager; // �}�l�[�W���[
#pragma endregion
#pragma region Components
	component::Transform* m_Transform; // �g�����X�t�H�[��
#pragma endregion
public:
	GameObject();
	GameObject(const std::string& ObjectName);
	virtual ~GameObject();

	/**
	@brief �R���|�[�l���g��ǉ����Ă��������BComponent���p�����Ȃ��ƃG���[�ɂȂ�܂��B
	@param [in] ComponentPtr : ���|�C���^
	@return �Ď��@�\�̎Q�ƃN���X
	*/
	template <typename _Ty, class = std::enable_if_t<std::is_base_of<component::Component, _Ty>::value>>
	_Ty* AddComponent(_Ty* ComponentPtr) {
		return AssociateComponents(ComponentPtr);
	}

	/**
	@brief �R���|�[�l���g�̎擾
	@return �Ď��@�\�̎Q�ƃN���X
	*/
	template <typename _Ty>
	_Ty* GetComponent() {
		// �擾�Ώۂ̌^�����邩�̃`�F�b�N
		auto itr = m_ComponentList.find(typeid(_Ty).hash_code());
		if (itr == m_ComponentList.end())
			return nullptr;

		// ��p�̊Ǘ��g�����������A�@�\�������ꍇ�I��
		if ((int)itr->second.size() == 0)
			return nullptr;

		// ��ԍŌ�ɓo�^���ꂽ�R���|�[�l���g���擾
		return static_cast<_Ty*>((*(--itr->second.end())));
	}

	/**
	@brief �Q�[���I�u�W�F�N�g��ǉ����܂��B
	*/
	common::SharePtr<GameObject> AddGameObject();

	/**
	@brief �Q�[���I�u�W�F�N�g��ǉ����܂��B
	@param [in] ObjectName : �I�u�W�F�N�g��
	*/
	common::SharePtr<GameObject> AddGameObject(const std::string& ObjectName);

	/**
	@brief �Q�[���I�u�W�F�N�g��ǉ����܂��B
	@param [in] ObjectPtr : �I�u�W�F�N�g�̃|�C���^
	*/
	common::SharePtr<GameObject> AddGameObject(GameObject* ObjectPtr);

	/**
	@brief �q�I�u�W�F�N�g���擾���܂��B
	@details std::list<SharePtr<GameObject>> �̌^�Ŏ擾�ł��܂��B
	*/
	const std::list<common::SharePtr<GameObject>>& GetChild();

	/**
	@brief �q�I�u�W�F�N�g�̐����擾���܂��B
	@return size_t
	*/
	size_t GetNumChild();
private:
	/**
	@brief �V�[����o�^���܂��B
	@param [in] ScenePtr : �V�[���̃|�C���^
	*/
	void SetScene(Scene* ScenePtr);

	/**
	@brief �������Ă���V�[�����擾���܂��B
	*/
	Scene* GetScene();

	/**
	@brief �e�I�u�W�F�N�g��o�^���܂��B
	@param [in] ParentPtr : �e�̃|�C���^
	*/
	void SetParent(GameObject* ParentPtr);

	/**
	@brief �e�I�u�W�F�N�g���擾���܂��B
	*/
	GameObject* GetParent();

	/**
	@brief �}�l�[�W���[��o�^���܂��B
	@param [in] ManagerPtr : �}�l�[�W���[�̃|�C���^
	*/
	void SetDirectX11Manager(system::DirectX11Manager* ManagerPtr);

	/**
	@brief �R���|�[�l���g�̊֘A�t��
	@param [in] ComponentPtr : �R���|�[�l���g�̃|�C���^
	*/
	template <typename _Ty>
	_Ty* AssociateComponents(_Ty* ComponentPtr) {
		// �֘A�t��
		ComponentPtr->SetGameObject(this);
		ComponentPtr->SetDirectX11Manager(m_Manager);
		static_cast<component::Component*>(ComponentPtr)->Init();
		// �N���X�̈�Ɋi�[���܂�
		m_ComponentList[typeid(_Ty).hash_code()].emplace_back(ComponentPtr);
		return ComponentPtr;
	}

	/**
	@brief �I�u�W�F�N�g�̍X�V�@�\
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