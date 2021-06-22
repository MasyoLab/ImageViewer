//==========================================================================
// オブジェクト [Object.cpp]
// author : MasyoLab
//==========================================================================
#include "Object.h"

_MDX_OBJECT_BEGIN

Object::Object() :
	m_DisplayFlags(true)
{
}

Object::Object(const std::string& ObjectName) :
	m_DisplayFlags(true), m_ObjectName(ObjectName)
{
}

Object::~Object()
{
}

void Object::SetObjectName(const std::string& ObjectName)
{
	m_ObjectName = ObjectName;
}

const std::string& Object::GetObjectName()
{
	return m_ObjectName;
}

void Object::SetDisplayFlags(bool bFlag)
{
	m_DisplayFlags = bFlag;
}

bool Object::GetDisplayFlags()
{
	return m_DisplayFlags;
}

_MDX_OBJECT_END