//==========================================================================
// �I�u�W�F�N�g [Object.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <string>
#include "../System.h"

_MDX_OBJECT_BEGIN

//==========================================================================
//
// class : Object 
// Content : �I�u�W�F�N�g
// details : �p���p
//
//==========================================================================
class Object
{
private:
	std::string m_ObjectName; // �I�u�W�F�N�g��
	bool m_DisplayFlags; // �I�u�W�F�N�g�\���t���O
public:
	Object();
	Object(const std::string& ObjectName);
	~Object();

	/**
	@brief �I�u�W�F�N�g����o�^���܂��B
	@param [in] ObjectName : �I�u�W�F�N�g��
	*/
	void SetObjectName(const std::string& ObjectName);

	/**
	@brief �I�u�W�F�N�g�����擾���܂��B
	@return �I�u�W�F�N�g��
	*/
	const std::string& GetObjectName();

	/**
	@brief �����̗L��/�������w�肵�܂��B
	@param [in] bFlag : �t���O
	@details true �ŗL���B�f�t�H���g�ŗL���ɂȂ��Ă��܂��B
	*/
	void SetDisplayFlags(bool bFlag);

	/**
	@brief �����̗L�����擾���܂��B
	@details true �ŗL���B
	*/
	bool GetDisplayFlags();
};

_MDX_OBJECT_END