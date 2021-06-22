//==========================================================================
// レンダラーマネージャー [RendererManager.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Component.h"
#include "GameObject.h"
#include "../System.h"

#pragma region forward declaration
// 前方宣言
_MDX_OBJECT_BEGIN
class Scene;
_MDX_OBJECT_END
#pragma endregion

_MDX_COMPONENT_BEGIN

// 描画機能リスト
enum class ERendererList : int
{
	Empty = -1,
	GridRenderer,
	MeshRenderer,
	CanvasRenderer,
	PointRenderer,
	Max
};

//==========================================================================
//
// class : RendererManager 
// Content : レンダラーマネージャー
// details : 継承用/シーン内で使用
//
//==========================================================================
class RendererManager :
	public Component
{
	friend object::Scene;
private:
	// レンダラーの管理
	// [属しているシーン][レンダラーの種類][レンダラー]
	static std::unordered_map<object::Scene*, std::unordered_map<ERendererList, std::list< RendererManager*>>> m_Renderers;
public:
	RendererManager();
	~RendererManager();
protected:
	/**
	@brief 色を登録します。
	@param [in] color : 色
	@details 0.0f～1.0fの間でお願いします。
	*/
	virtual void SetColor(const math::Vector4& color);

	/**
	@brief 色を登録します。
	@param [in] r : R値
	@param [in] g : G値
	@param [in] b : B値
	@param [in] a : A値
	@details 0.0f～1.0fの間でお願いします。
	*/
	virtual void SetColor(float r, float g, float b, float a);

	/**
	@brief 色を取得します。
	@return 色
	*/
	virtual const math::Vector4& GetColor() const;

	/**
	@brief 頂点シェーダーを登録します。
	@param [in] shader : シェーダー
	@details デフォルトシェーダーは保持されています。
	*/
	virtual void SetVertexShader(const structure::VertexShader& shader);

	/**
	@brief ピクセルシェーダーを登録します。
	@param [in] shader : シェーダー
	@details デフォルトシェーダーは保持されています。
	*/
	virtual void SetPixelShader(const structure::PixelShader& shader);

	/**
	@brief 頂点レイアウトを登録します。
	@param [in] layout : レイアウト
	@details デフォルトレイアウトは保持されています。
	*/
	virtual void SetInputLayout(const structure::InputLayout& layout);

	/**
	@brief デフォルトシェーダーを復元します。
	@details 指定したシェーダーの登録は解除されます。
	*/
	virtual void RestoreDefaultShader();

	/**
	@brief 描画
	@param [in] view : ビュー行列
	@param [in] projection : プロジェクション行列
	*/
	virtual void Draw(const math::Matrix& view, const math::Matrix& projection);

	/**
	@brief 描画
	*/
	virtual void Draw();

	/**
	@brief レンダラーの登録
	@param [in] RendererPtr : レンダラーのポインタ。
	@param [in] ObjectPtr : オブジェクトのポインタ。
	*/
	void SetRenderer(ERendererList RendererType, RendererManager* RendererPtr, object::GameObject* ObjectPtr);

	/**
	@brief レンダラーの解放
	@param [in] RendererPtr : レンダラーのポインタ。
	@param [in] ObjectPtr : オブジェクトのポインタ。
	*/
	void ReleaseRenderer(ERendererList RendererType, RendererManager* RendererPtr, object::GameObject* ObjectPtr);
private:
	/**
	@brief シーン用のレンダラー管理枠の生成。
	@param [in] scene : シーンのポインタ。
	*/
	static void CreateSceneRenderer(object::Scene* scene);

	/**
	@brief シーンに属しているレンダラーの破棄。
	@param [in] scene : シーンのポインタ
	*/
	static void ReleaseSceneRenderer(object::Scene* scene);

	/**
	@brief シーンに属しているレンダラー全ての描画
	@param [in] scene : シーンのポインタ。
	*/
	static void DrawSceneRenderer(object::Scene* scene, const math::Matrix& view, const math::Matrix& projection);
};

_MDX_COMPONENT_END