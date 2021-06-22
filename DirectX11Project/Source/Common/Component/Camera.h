//==========================================================================
// カメラ [Camera.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Component.h"
#include "../System.h"

#pragma region forward declaration
// 前方宣言
_MDX_OBJECT_BEGIN
class Scene;
_MDX_OBJECT_END
#pragma endregion

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : CameraType 
// Content : カメラのタイプ
//
//==========================================================================
enum class CameraType
{
	LockOn = 0, // 対象を中心に捉え続けます
	Normal, // ただのカメラです(デフォルト)
};

//==========================================================================
//
// class : Camera 
// Content : カメラ
// details : 継承用禁止
//
//==========================================================================
class Camera final:
	public Component
{
	friend object::Scene;
private:
	// レンダラーの管理
	// [属しているシーン][レンダラーの種類][レンダラー]
	static std::unordered_map<object::Scene*, std::list< Camera*>> m_Cameras;
	math::Matrix m_View; // ビュー行列
	math::Matrix m_Projection; // パースペクティブ射影行列
	math::Vector3 m_LookAt; // 注視点
	math::Vector3 m_Up; // 上方向
	CameraType m_CameraType; // カメラのタイプ
	float m_Distance; // 中心からの距離
public:
	Camera();
	virtual ~Camera();

	/**
	@brief ビュー行列を取得します。
	*/
	const math::Matrix& GetViewMatrix() const;

	/**
	@brief プロジェクション行列を取得します。
	*/
	const math::Matrix& GetProjectionMatrix() const;

	/**
	@brief カメラが捉える座標を登録します。
	@param [in] lookAt : 捉える座標
	*/
	void SetLookAt(const math::Vector3& lookAt);

	/**
	@brief カメラのタイプを指定します。
	@param [in] cameraType : カメラのタイプ
	*/
	void SetCameraType(const CameraType& cameraType);
protected:
	/**
	@brief 初期化
	*/
	void Init() override;

	/**
	@brief 更新
	*/
	void Update() override;
private:
	/**
	@brief シーンに属している全カメラの取得
	@param [in] scene : シーンのポインタ
	*/
	static const std::list< Camera*>& GetCameras(object::Scene* scene);

	/**
	@brief シーンに属している全カメラの破棄
	@param [in] scene : シーンのポインタ
	*/
	static void ReleaseSceneCameras(object::Scene* scene);
};

_MDX_COMPONENT_END
