//==========================================================================
// �g�����X�t�H�[�� [Transform.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Component.h"
#include "../System.h"

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : Transform 
// Content : �g�����X�t�H�[��
// details : �p���p�֎~
//
//==========================================================================
class Transform final :
	public Component
{
private:
	enum EVecType : int
	{
		position,
		rotation,
		scale,
		update,
		num
	};
private:
	math::Matrix m_WorldMatrix; // ���[���h�s��
	math::Matrix m_LocalMatrix; // ���[�J���s��
	math::Matrix m_RotationMatrix; // ��]�s��
	math::Quaternion m_Quaternion; // ��]
	math::Vector3 m_Position; // ���W
	math::Vector3 m_Scale; // �g�k
	math::Vector3 m_Rotation; // ��]
	bool m_Vec3InputFlags[EVecType::num]; // ���W,�g�k,��]�̍X�V�t���O
public:
	Transform();
	~Transform();

	/**
	@brief ���������܂��B
	*/
	void Identity();

	/**
	@brief ���W����
	*/
	void SetPosition(const math::Vector3& vec3);

	/**
	@brief ���W����
	*/
	void SetPosition(float x, float y, float z);

	/**
	@brief ���s�ړ����܂��B
	*/
	void AddPosition(const math::Vector3& vec3);

	/**
	@brief ���s�ړ����܂��B
	*/
	void AddPosition(float x, float y, float z);

	/**
	@brief ���s�ړ��s������������܂��B
	*/
	void PositionIdentity();

	/**
	@brief ���s�ړ������擾���܂��B
	*/
	const math::Vector3& GetPosition() const;

	/**
	@brief �e���ɂ����ăX�P�[�����O���܂��B
	*/
	void SetScale(const math::Vector3& vec3);

	/**
	@brief �e���ɂ����ăX�P�[�����O���܂��B
	*/
	void SetScale(float x, float y, float z);

	/**
	@brief �e���ɂ����ăX�P�[�����O���܂��B
	*/
	void AddScale(const math::Vector3& vec3);

	/**
	@brief �e���ɂ����ăX�P�[�����O���܂��B
	*/
	void AddScale(float x, float y, float z);

	/**
	@brief �X�P�[�����O�l�����������܂��B
	*/
	void ScaleIdentity();

	/**
	@brief �X�P�[�����O�l���擾���܂��B
	*/
	const math::Vector3& GetScale() const;

	/**
	@brief �e�v�f�ɒl��ݒ肵�܂��B
	*/
	void SetQuaternion(float x, float y, float z);

	/**
	@brief �e�v�f�ɒl��ݒ肵�܂��B
	*/
	void SetQuaternion(float x, float y, float z, float w);

	/**
	@brief �e�v�f�ɒl��ݒ肵�܂��B
	*/
	void SetQuaternion(const math::Quaternion &qua);

	/**
	@brief ���[�A�s�b�`�A���[�����w�肵�čs����쐬���܂��B
	@param [in]	yaw : y ���𒆐S�Ƃ��郈�[ (���W�A���P��)
	@param [in]	pitch : x ���𒆐S�Ƃ���s�b�` (���W�A���P��)
	@param [in]	roll : z ���𒆐S�Ƃ��郍�[�� (���W�A���P��)
	*/
	void AddQuaternion(float pitch, float yaw, float roll);

	/**
	@brief �N�H�[�^�j�I�������������܂��B
	*/
	void QuaternionIdentity();

	/**
	@brief �N�H�[�^�j�I���𐳋K�����܂��B
	*/
	void QuaternionNormalize();

	/**
	@brief �N�H�[�^�j�I������]���Ɗp�x���w�肵�ĉ�]���܂��B
	@param [in] axis : ��]��
	@param [in] r : ��]�p�x (���W�A���P��)
	@details axis ���P�ʃx�N�g���łȂ���ΐ��K�����Ă���v�Z���s���܂��B
	*/
	void QuaternionAxis(const math::Vector3& axis, float r);

	/**
	@brief ���̃N�H�[�^�j�I���̉�]���Ɖ�]�p�x���擾���܂��B
	@param [in] axis : ��]�����i�[����x�N�g���̃|�C���^
	@param [in] angle : ��]�p�x���i�[����ϐ��̃|�C���^
	@details axis �ɂ͒P�ʃx�N�g�����i�[���܂��B
	*/
	void ToQuaternionAxisAngle(math::Vector3* axis, float* angle) const;

	/**
	@brief �N�I�[�^�j�I�����擾���܂��B
	*/
	const math::Quaternion& GetQuaternion() const;

	/**
	@brief ���[�A�s�b�`�A���[�����w�肵�čs����쐬���܂��B
	@param [in]	yaw : y ���𒆐S�Ƃ��郈�[ (���W�A���P��)
	@param [in]	pitch : x ���𒆐S�Ƃ���s�b�` (���W�A���P��)
	@param [in]	roll : z ���𒆐S�Ƃ��郍�[�� (���W�A���P��)
	*/
	void SetRotation(float pitch, float yaw, float roll);

	/**
	@brief ���[�A�s�b�`�A���[�����w�肵�čs����쐬���܂��B
	@param [in]	yaw : y ���𒆐S�Ƃ��郈�[ (���W�A���P��)
	@param [in]	pitch : x ���𒆐S�Ƃ���s�b�` (���W�A���P��)
	@param [in]	roll : z ���𒆐S�Ƃ��郍�[�� (���W�A���P��)
	@param [in]	pitchUpperLimit : �s�b�`�̈ړ���� (���W�A���P��)
	*/
	void SetRotation(float pitch, float yaw, float roll, float pitchUpperLimit);

	/**
	@brief �e�v�f�ɒl��ݒ肵�܂��B
	*/
	void SetRotation(const math::Vector3& axis);

	/**
	@brief ���[�A�s�b�`�A���[�����w�肵�čs����쐬���܂��B
	@param [in]	yaw : y ���𒆐S�Ƃ��郈�[ (���W�A���P��)
	@param [in]	pitch : x ���𒆐S�Ƃ���s�b�` (���W�A���P��)
	@param [in]	roll : z ���𒆐S�Ƃ��郍�[�� (���W�A���P��)
	*/
	void AddRotation(float pitch, float yaw, float roll);

	/**
	@brief ���[�A�s�b�`�A���[�����w�肵�čs����쐬���܂��B
	@param [in]	yaw : y ���𒆐S�Ƃ��郈�[ (���W�A���P��)
	@param [in]	pitch : x ���𒆐S�Ƃ���s�b�` (���W�A���P��)
	@param [in]	roll : z ���𒆐S�Ƃ��郍�[�� (���W�A���P��)
	@param [in]	pitchUpperLimit : �s�b�`�̈ړ���� (���W�A���P��)
	*/
	void AddRotation(float pitch, float yaw, float roll, float pitchUpperLimit);

	/**
	@brief �I�C���[�p�����������܂��B
	*/
	void RotationIdentity();

	/**
	@brief �I�C���[�p�𐳋K�����܂��B
	*/
	void RotationNormalize();

	/**
	@brief �I�C���[�p���擾���܂��B
	*/
	const math::Vector3& GetRotation() const;

	/**
	@brief ���[���h�s����擾���܂��B
	*/
	const math::Matrix& GetWorldMatrix() const;

	/**
	@brief ���[�J���s����擾���܂��B
	*/
	const math::Matrix& GetLocalMatrix() const;

	/**
	@brief ��]�s����擾���܂��B
	*/
	const math::Matrix& GetRotationMatrix() const;
protected:
	/**
	@brief �s����X�V���܂��B
	*/
	void Update() override;
};

_MDX_COMPONENT_END