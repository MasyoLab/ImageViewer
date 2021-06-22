//==========================================================================
// �J���� [Camera.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Component.h"
#include "../System.h"

#pragma region forward declaration
// �O���錾
_MDX_OBJECT_BEGIN
class Scene;
_MDX_OBJECT_END
#pragma endregion

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : CameraType 
// Content : �J�����̃^�C�v
//
//==========================================================================
enum class CameraType
{
	LockOn = 0, // �Ώۂ𒆐S�ɑ��������܂�
	Normal, // �����̃J�����ł�(�f�t�H���g)
};

//==========================================================================
//
// class : Camera 
// Content : �J����
// details : �p���p�֎~
//
//==========================================================================
class Camera final:
	public Component
{
	friend object::Scene;
private:
	// �����_���[�̊Ǘ�
	// [�����Ă���V�[��][�����_���[�̎��][�����_���[]
	static std::unordered_map<object::Scene*, std::list< Camera*>> m_Cameras;
	math::Matrix m_View; // �r���[�s��
	math::Matrix m_Projection; // �p�[�X�y�N�e�B�u�ˉe�s��
	math::Vector3 m_LookAt; // �����_
	math::Vector3 m_Up; // �����
	CameraType m_CameraType; // �J�����̃^�C�v
	float m_Distance; // ���S����̋���
public:
	Camera();
	virtual ~Camera();

	/**
	@brief �r���[�s����擾���܂��B
	*/
	const math::Matrix& GetViewMatrix() const;

	/**
	@brief �v���W�F�N�V�����s����擾���܂��B
	*/
	const math::Matrix& GetProjectionMatrix() const;

	/**
	@brief �J��������������W��o�^���܂��B
	@param [in] lookAt : ��������W
	*/
	void SetLookAt(const math::Vector3& lookAt);

	/**
	@brief �J�����̃^�C�v���w�肵�܂��B
	@param [in] cameraType : �J�����̃^�C�v
	*/
	void SetCameraType(const CameraType& cameraType);
protected:
	/**
	@brief ������
	*/
	void Init() override;

	/**
	@brief �X�V
	*/
	void Update() override;
private:
	/**
	@brief �V�[���ɑ����Ă���S�J�����̎擾
	@param [in] scene : �V�[���̃|�C���^
	*/
	static const std::list< Camera*>& GetCameras(object::Scene* scene);

	/**
	@brief �V�[���ɑ����Ă���S�J�����̔j��
	@param [in] scene : �V�[���̃|�C���^
	*/
	static void ReleaseSceneCameras(object::Scene* scene);
};

_MDX_COMPONENT_END
