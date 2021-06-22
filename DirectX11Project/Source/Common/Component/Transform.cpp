//==========================================================================
// トランスフォーム [Transform.cpp]
// author : MasyoLab
//==========================================================================
#include "Transform.h"
#include "GameObject.h"

_MDX_COMPONENT_BEGIN

Transform::Transform() :
	Component("Transform"), m_Vec3InputFlags{ false,false,false,false }, m_Scale(math::Vector3::Ones)
{
	m_LocalMatrix.m14 = m_LocalMatrix.m24 = m_LocalMatrix.m34 = 0.0f;
	m_LocalMatrix.m44 = 1.0f;
}

Transform::~Transform()
{
}

void Transform::Identity()
{
	PositionIdentity();
	ScaleIdentity();
	QuaternionIdentity();
}

void Transform::SetPosition(const math::Vector3& vec3)
{
	m_Position = m_RotationMatrix.GetRight() * vec3.x;
	m_Position += m_RotationMatrix.GetUp() * vec3.y;
	m_Position += m_RotationMatrix.GetFront() * vec3.z;
	m_Vec3InputFlags[EVecType::position] = true;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_Position = m_RotationMatrix.GetRight() * x;
	m_Position += m_RotationMatrix.GetUp() * y;
	m_Position += m_RotationMatrix.GetFront() * z;
	m_Vec3InputFlags[EVecType::position] = true;
}

void Transform::AddPosition(const math::Vector3& vec3)
{
	m_Position += m_RotationMatrix.GetRight() * vec3.x;
	m_Position += m_RotationMatrix.GetUp() * vec3.y;
	m_Position += m_RotationMatrix.GetFront() * vec3.z;
	m_Vec3InputFlags[EVecType::position] = true;
}

void Transform::AddPosition(float x, float y, float z)
{
	m_Position += m_RotationMatrix.GetRight() * x;
	m_Position += m_RotationMatrix.GetUp() * y;
	m_Position += m_RotationMatrix.GetFront() * z;
	m_Vec3InputFlags[EVecType::position] = true;
}

void Transform::PositionIdentity()
{
	m_Position = math::Vector3::Zero;
	m_Vec3InputFlags[EVecType::position] = true;
}

const math::Vector3& Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetScale(const math::Vector3& vec3)
{
	m_Scale = vec3;
	m_Vec3InputFlags[EVecType::scale] = true;
}

void Transform::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
	m_Vec3InputFlags[EVecType::scale] = true;
}

void Transform::AddScale(const math::Vector3& vec3)
{
	m_Scale += vec3;
	m_Vec3InputFlags[EVecType::scale] = true;
}

void Transform::AddScale(float x, float y, float z)
{
	m_Scale.x += x;
	m_Scale.y += y;
	m_Scale.z += z;
	m_Vec3InputFlags[EVecType::scale] = true;
}

void Transform::ScaleIdentity()
{
	m_Scale = math::Vector3::Ones;
	m_Vec3InputFlags[EVecType::scale] = true;
}

const math::Vector3& Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetQuaternion(float x, float y, float z)
{
	m_Quaternion.Set(x, y, z, math::Quaternion::Identity.w);
	m_RotationMatrix = math::Matrix::MakeRotationQuaternion(m_Quaternion);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::SetQuaternion(float x, float y, float z, float w)
{
	m_Quaternion.Set(x, y, z, w);
	m_RotationMatrix = math::Matrix::MakeRotationQuaternion(m_Quaternion);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::SetQuaternion(const math::Quaternion& qua)
{
	m_Quaternion = qua;
	m_RotationMatrix = math::Matrix::MakeRotationQuaternion(m_Quaternion);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::AddQuaternion(float pitch, float yaw, float roll)
{
	m_Quaternion.RotateX(pitch);
	m_Quaternion.RotateY(yaw);
	m_Quaternion.RotateZ(roll);
	m_RotationMatrix = math::Matrix::MakeRotationQuaternion(m_Quaternion);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::QuaternionIdentity()
{
	m_Quaternion = math::Quaternion::Identity;
	m_RotationMatrix = math::Matrix::Identity;
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::QuaternionNormalize()
{
	m_Quaternion.Normalize();
	m_RotationMatrix = math::Matrix::MakeRotationQuaternion(m_Quaternion);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::QuaternionAxis(const math::Vector3& axis, float r)
{
	m_Quaternion.RotateAxis(axis, r);
	m_RotationMatrix = math::Matrix::MakeRotationQuaternion(m_Quaternion);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::ToQuaternionAxisAngle(math::Vector3* axis, float* angle) const
{
	m_Quaternion.ToAxisAngle(axis, angle);
}

const math::Quaternion& Transform::GetQuaternion() const
{
	return m_Quaternion;
}

void Transform::SetRotation(float pitch, float yaw, float roll)
{
	m_Rotation.x = pitch;
	m_Rotation.y = yaw;
	m_Rotation.z = roll;
	m_RotationMatrix = math::Matrix::MakeRotationEulerAngles(m_Rotation);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::SetRotation(float pitch, float yaw, float roll, float pitchUpperLimit)
{
	m_Rotation.x = pitch;
	m_Rotation.y = yaw;
	m_Rotation.z = roll;

	// 超えたとき
	if (pitchUpperLimit < m_Rotation.x)
		m_Rotation.x = pitchUpperLimit;
	// 同じく超えたとき
	else if (m_Rotation.x < -pitchUpperLimit)
		m_Rotation.x = -pitchUpperLimit;

	m_RotationMatrix = math::Matrix::MakeRotationEulerAngles(m_Rotation);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::SetRotation(const math::Vector3& axis)
{
	m_Rotation = axis;
	m_RotationMatrix = math::Matrix::MakeRotationEulerAngles(m_Rotation);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::AddRotation(float pitch, float yaw, float roll)
{
	m_Rotation.x += pitch;
	m_Rotation.y += yaw;
	m_Rotation.z += roll;
	m_RotationMatrix = math::Matrix::MakeRotationEulerAngles(m_Rotation);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::AddRotation(float pitch, float yaw, float roll, float pitchUpperLimit)
{
	m_Rotation.x += pitch;
	m_Rotation.y += yaw;
	m_Rotation.z += roll;

	// 超えたとき
	if (pitchUpperLimit < m_Rotation.x)
		m_Rotation.x = pitchUpperLimit;
	// 同じく超えたとき
	else if (m_Rotation.x < -pitchUpperLimit)
		m_Rotation.x = -pitchUpperLimit;

	m_RotationMatrix = math::Matrix::MakeRotationEulerAngles(m_Rotation);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::RotationIdentity()
{
	m_Rotation = math::Vector3::Zero;
	m_RotationMatrix = math::Matrix::Identity;
	m_Vec3InputFlags[EVecType::rotation] = true;
}

void Transform::RotationNormalize()
{
	m_Rotation.Normalize();
	m_RotationMatrix = math::Matrix::MakeRotationEulerAngles(m_Rotation);
	m_Vec3InputFlags[EVecType::rotation] = true;
}

const math::Vector3& Transform::GetRotation() const
{
	return m_Rotation;
}

const math::Matrix& Transform::GetWorldMatrix() const
{
	return m_WorldMatrix;
}

const math::Matrix& Transform::GetLocalMatrix() const
{
	return m_LocalMatrix;
}

const math::Matrix& Transform::GetRotationMatrix() const
{
	return m_RotationMatrix;
}

void Transform::Update()
{
	// 拡縮,回転に更新があるとき
	if (m_Vec3InputFlags[EVecType::scale] || m_Vec3InputFlags[EVecType::rotation])
	{
		m_LocalMatrix.m11 = m_Scale.x * m_RotationMatrix.m11;
		m_LocalMatrix.m12 = m_Scale.x * m_RotationMatrix.m12;
		m_LocalMatrix.m13 = m_Scale.x * m_RotationMatrix.m13;

		m_LocalMatrix.m21 = m_Scale.y * m_RotationMatrix.m21;
		m_LocalMatrix.m22 = m_Scale.y * m_RotationMatrix.m22;
		m_LocalMatrix.m23 = m_Scale.y * m_RotationMatrix.m23;

		m_LocalMatrix.m31 = m_Scale.z * m_RotationMatrix.m31;
		m_LocalMatrix.m32 = m_Scale.z * m_RotationMatrix.m32;
		m_LocalMatrix.m33 = m_Scale.z * m_RotationMatrix.m33;

		m_Vec3InputFlags[EVecType::rotation] = false;
		m_Vec3InputFlags[EVecType::scale] = false;
		m_Vec3InputFlags[EVecType::update] = true;
	}

	// 座標系に変更があるとき
	if (m_Vec3InputFlags[EVecType::position])
	{
		m_LocalMatrix.m41 = m_Position.x;
		m_LocalMatrix.m42 = m_Position.y;
		m_LocalMatrix.m43 = m_Position.z;
		m_Vec3InputFlags[EVecType::position] = false;
		m_Vec3InputFlags[EVecType::update] = true;
	}

	// 親オブジェクトが存在しないとき
	if (m_GameObject->GetParent() == nullptr)
	{
		// 更新がない場合終了
		if (!m_Vec3InputFlags[EVecType::update])
			return;
		m_WorldMatrix = m_LocalMatrix;
		m_Vec3InputFlags[EVecType::update] = false;
	}
	// 親オブジェクトが存在するとき
	else if (m_GameObject->GetParent() != nullptr)
	{
		// 親のtransform
		auto parentTransform = m_GameObject->GetParent()->m_Transform;

		// 更新がない場合終了
		if (!m_Vec3InputFlags[EVecType::update] && !parentTransform->m_Vec3InputFlags[EVecType::update])
			return;
		// どちらかに、またはお互いに更新がある場合
		else if (m_Vec3InputFlags[EVecType::update] || parentTransform->m_Vec3InputFlags[EVecType::update])
		{
			m_Vec3InputFlags[EVecType::update] = true;
			m_WorldMatrix = m_LocalMatrix * parentTransform->m_WorldMatrix;
		}
	}
}

_MDX_COMPONENT_END