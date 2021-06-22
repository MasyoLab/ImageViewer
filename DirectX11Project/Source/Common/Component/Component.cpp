//==========================================================================
// コンポーネント [Component.cpp]
// author : MasyoLab
//==========================================================================
#include "Component.h"
#include "GameObject.h"
#include "../DirectX11.h"

_MDX_COMPONENT_BEGIN
_MDX_USING_OBJECT
_MDX_USING_SYSTEM

Component::Component() :
	Object("Component"), m_GameObject(nullptr), m_Manager(nullptr)
{
}

Component::Component(const std::string& ComponentName) :
	Object(ComponentName), m_GameObject(nullptr), m_Manager(nullptr)
{
}

Component::~Component()
{
}

void Component::SetGameObject(GameObject* ObjectPtr)
{
	m_GameObject = ObjectPtr;
}

void Component::SetDirectX11Manager(DirectX11Manager* ManagerPtr)
{
	m_Manager = ManagerPtr;
}

void Component::Init()
{
}

void Component::Update()
{
}

_MDX_COMPONENT_END