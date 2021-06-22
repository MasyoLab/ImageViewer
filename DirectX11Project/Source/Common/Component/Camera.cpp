//==========================================================================
// カメラ [Camera.cpp]
// author : MasyoLab
//==========================================================================
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "../DirectX11.h"

_MDX_COMPONENT_BEGIN
_MDX_USING_OBJECT

#pragma region Entity declaration
//==========================================================================
// 実体の宣言
//==========================================================================
std::unordered_map<Scene*, std::list< Camera*>> Camera::m_Cameras;
#pragma endregion

Camera::Camera() :
	Component("Camera"), m_Up(0.0f, 1.0f, 0.0f), m_LookAt(0.0f, 0.0f, 0.0f), 
	m_CameraType(CameraType::Normal), m_Distance(10.0f)
{
}

Camera::~Camera()
{
	// 属しているシーン
	auto scenePtr = m_Cameras.find(m_GameObject->GetScene());
	if (scenePtr == m_Cameras.end())
		return;

	// 対象となるカメラ
	auto cameraPtr = std::find(scenePtr->second.begin(), scenePtr->second.end(), this);
	if (cameraPtr == scenePtr->second.end())
		return;

	scenePtr->second.erase(cameraPtr);
}

void Camera::Update()
{
	// 共通のデータ
	const auto& cameraPosition = m_GameObject->m_Transform->GetPosition();

	switch (m_CameraType)
	{
	case CameraType::LockOn:
	{
		// 単位ベクトル取得
		const auto& worldMatrix = m_GameObject->m_Transform->GetWorldMatrix();
		auto playerToTarget = m_LookAt - cameraPosition;
		auto length = playerToTarget.GetLength();
		auto unitvecPlayerToTarget = playerToTarget / length;

		//カメラ位置取得
		auto position = math::Vector3(cameraPosition.x - unitvecPlayerToTarget.x * m_Distance, cameraPosition.y, cameraPosition.z - unitvecPlayerToTarget.z * m_Distance);

		//注視点取得
		auto target = m_LookAt + unitvecPlayerToTarget;

		m_View = math::Matrix::MakeLookAtLH(position, target, worldMatrix.GetUp());
	}
	break;
	case CameraType::Normal:
	{
		auto& rotMat = m_GameObject->m_Transform->GetRotationMatrix();
		auto distancePosition = rotMat.GetFront() * m_Distance;
		m_View = math::Matrix::MakeLookAtLH(cameraPosition - distancePosition, cameraPosition + m_LookAt, rotMat.GetUp());
	}
	break;
	default:
		break;
	}
}

const math::Matrix& Camera::GetViewMatrix() const
{
	return m_View;
}

const math::Matrix& Camera::GetProjectionMatrix() const
{
	return m_Projection;
}

void Camera::SetLookAt(const math::Vector3& lookAt)
{
	m_LookAt = lookAt;
}

void Camera::SetCameraType(const CameraType& cameraType)
{
	m_CameraType = cameraType;
}

void Camera::Init()
{
	m_Cameras[m_GameObject->GetScene()].push_back(this);
	m_Projection = math::Matrix::MakePerspectiveFovLH(math::Math::ToRadians(60),
		m_Manager->GetViewport().Width / m_Manager->GetViewport().Height, 0.1f, 1000);  // 左手座標系のパースペクティブ射影行列
}

const std::list<Camera*>& Camera::GetCameras(Scene* scene)
{
	return m_Cameras.find(scene)->second;
}

void Camera::ReleaseSceneCameras(Scene* scene)
{
	auto itr = m_Cameras.find(scene);
	if (itr == m_Cameras.end())
		return;
	m_Cameras.erase(itr);
}

_MDX_COMPONENT_END