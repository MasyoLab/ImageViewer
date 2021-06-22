//==========================================================================
// トランスフォーム [Transform.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Component.h"
#include "../System.h"

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : Transform 
// Content : トランスフォーム
// details : 継承用禁止
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
	math::Matrix m_WorldMatrix; // ワールド行列
	math::Matrix m_LocalMatrix; // ローカル行列
	math::Matrix m_RotationMatrix; // 回転行列
	math::Quaternion m_Quaternion; // 回転
	math::Vector3 m_Position; // 座標
	math::Vector3 m_Scale; // 拡縮
	math::Vector3 m_Rotation; // 回転
	bool m_Vec3InputFlags[EVecType::num]; // 座標,拡縮,回転の更新フラグ
public:
	Transform();
	~Transform();

	/**
	@brief 初期化します。
	*/
	void Identity();

	/**
	@brief 座標入力
	*/
	void SetPosition(const math::Vector3& vec3);

	/**
	@brief 座標入力
	*/
	void SetPosition(float x, float y, float z);

	/**
	@brief 平行移動します。
	*/
	void AddPosition(const math::Vector3& vec3);

	/**
	@brief 平行移動します。
	*/
	void AddPosition(float x, float y, float z);

	/**
	@brief 平行移動行列を初期化します。
	*/
	void PositionIdentity();

	/**
	@brief 平行移動情報を取得します。
	*/
	const math::Vector3& GetPosition() const;

	/**
	@brief 各軸にそってスケーリングします。
	*/
	void SetScale(const math::Vector3& vec3);

	/**
	@brief 各軸にそってスケーリングします。
	*/
	void SetScale(float x, float y, float z);

	/**
	@brief 各軸にそってスケーリングします。
	*/
	void AddScale(const math::Vector3& vec3);

	/**
	@brief 各軸にそってスケーリングします。
	*/
	void AddScale(float x, float y, float z);

	/**
	@brief スケーリング値を初期化します。
	*/
	void ScaleIdentity();

	/**
	@brief スケーリング値を取得します。
	*/
	const math::Vector3& GetScale() const;

	/**
	@brief 各要素に値を設定します。
	*/
	void SetQuaternion(float x, float y, float z);

	/**
	@brief 各要素に値を設定します。
	*/
	void SetQuaternion(float x, float y, float z, float w);

	/**
	@brief 各要素に値を設定します。
	*/
	void SetQuaternion(const math::Quaternion &qua);

	/**
	@brief ヨー、ピッチ、ロールを指定して行列を作成します。
	@param [in]	yaw : y 軸を中心とするヨー (ラジアン単位)
	@param [in]	pitch : x 軸を中心とするピッチ (ラジアン単位)
	@param [in]	roll : z 軸を中心とするロール (ラジアン単位)
	*/
	void AddQuaternion(float pitch, float yaw, float roll);

	/**
	@brief クォータニオンを初期化します。
	*/
	void QuaternionIdentity();

	/**
	@brief クォータニオンを正規化します。
	*/
	void QuaternionNormalize();

	/**
	@brief クォータニオンを回転軸と角度を指定して回転します。
	@param [in] axis : 回転軸
	@param [in] r : 回転角度 (ラジアン単位)
	@details axis が単位ベクトルでなければ正規化してから計算を行います。
	*/
	void QuaternionAxis(const math::Vector3& axis, float r);

	/**
	@brief このクォータニオンの回転軸と回転角度を取得します。
	@param [in] axis : 回転軸を格納するベクトルのポインタ
	@param [in] angle : 回転角度を格納する変数のポインタ
	@details axis には単位ベクトルを格納します。
	*/
	void ToQuaternionAxisAngle(math::Vector3* axis, float* angle) const;

	/**
	@brief クオータニオンを取得します。
	*/
	const math::Quaternion& GetQuaternion() const;

	/**
	@brief ヨー、ピッチ、ロールを指定して行列を作成します。
	@param [in]	yaw : y 軸を中心とするヨー (ラジアン単位)
	@param [in]	pitch : x 軸を中心とするピッチ (ラジアン単位)
	@param [in]	roll : z 軸を中心とするロール (ラジアン単位)
	*/
	void SetRotation(float pitch, float yaw, float roll);

	/**
	@brief ヨー、ピッチ、ロールを指定して行列を作成します。
	@param [in]	yaw : y 軸を中心とするヨー (ラジアン単位)
	@param [in]	pitch : x 軸を中心とするピッチ (ラジアン単位)
	@param [in]	roll : z 軸を中心とするロール (ラジアン単位)
	@param [in]	pitchUpperLimit : ピッチの移動上限 (ラジアン単位)
	*/
	void SetRotation(float pitch, float yaw, float roll, float pitchUpperLimit);

	/**
	@brief 各要素に値を設定します。
	*/
	void SetRotation(const math::Vector3& axis);

	/**
	@brief ヨー、ピッチ、ロールを指定して行列を作成します。
	@param [in]	yaw : y 軸を中心とするヨー (ラジアン単位)
	@param [in]	pitch : x 軸を中心とするピッチ (ラジアン単位)
	@param [in]	roll : z 軸を中心とするロール (ラジアン単位)
	*/
	void AddRotation(float pitch, float yaw, float roll);

	/**
	@brief ヨー、ピッチ、ロールを指定して行列を作成します。
	@param [in]	yaw : y 軸を中心とするヨー (ラジアン単位)
	@param [in]	pitch : x 軸を中心とするピッチ (ラジアン単位)
	@param [in]	roll : z 軸を中心とするロール (ラジアン単位)
	@param [in]	pitchUpperLimit : ピッチの移動上限 (ラジアン単位)
	*/
	void AddRotation(float pitch, float yaw, float roll, float pitchUpperLimit);

	/**
	@brief オイラー角を初期化します。
	*/
	void RotationIdentity();

	/**
	@brief オイラー角を正規化します。
	*/
	void RotationNormalize();

	/**
	@brief オイラー角を取得します。
	*/
	const math::Vector3& GetRotation() const;

	/**
	@brief ワールド行列を取得します。
	*/
	const math::Matrix& GetWorldMatrix() const;

	/**
	@brief ローカル行列を取得します。
	*/
	const math::Matrix& GetLocalMatrix() const;

	/**
	@brief 回転行列を取得します。
	*/
	const math::Matrix& GetRotationMatrix() const;
protected:
	/**
	@brief 行列を更新します。
	*/
	void Update() override;
};

_MDX_COMPONENT_END