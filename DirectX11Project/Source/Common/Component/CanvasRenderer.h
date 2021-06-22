//==========================================================================
// キャンバスレンダラー [CanvasRenderer.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "RendererManager.h"

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : CanvasRenderer 
// Content : キャンバスレンダラー
// details : 継承禁止/デフォルトのシェーダーが設定されています
//
//==========================================================================
class CanvasRenderer final :
	public RendererManager
{
private:
	common::Texture m_Texture; // テクスチャ
	math::Vector3 m_Polygon; // ポリゴン
	math::Matrix m_PolygonMatrix; // ポリゴン
	structure::VertexShader m_VertexShader; // 頂点シェーダー
	structure::PixelShader m_PixelShader; // ピクセルシェーダー
	structure::InputLayout m_InputLayout; // レイアウト
	structure::SpriteMatrixBuffer m_MatrixBuffer; // マトリクスバッファ
	static structure::VertexShader m_ShareVertexShader; // デフォルトの頂点シェーダー
	static structure::PixelShader m_SharePixelShader; // デフォルトのピクセルシェーダー
	static structure::InputLayout m_ShareInputLayout; // 共通のレイアウト
	static structure::VertexBuffer m_ShareVertexBuffer; // 共通のバーテックスバッファ
	static structure::IndexBuffer m_ShareIndexBuffer; // 共通のインデックスバッファ
	static structure::ConstantBuffer m_ShareConstantBuffer; // バッファ
	static std::vector<structure::Vertex2D> m_ShareVertex; // 共通のデータ
	static std::vector<UINT> m_ShareIndex; // 共通のインデックス情報の設定
	static D3D11_INPUT_ELEMENT_DESC m_ShareInputElementDesc[3]; // 共通のインプットレイアウト
public:
	CanvasRenderer();
	virtual ~CanvasRenderer();

	/**
	@brief テクスチャの登録。
	@param [in] texture : テクスチャのデータ。
	*/
	void SetTexture(const common::Texture& texture, bool offset = true);

	/**
	@brief 色を登録します。
	@param [in] color : 色
	@details 0.0f～1.0fの間でお願いします。
	*/
	void SetColor(const math::Vector4& color) override;

	/**
	@brief 色を登録します。
	@param [in] r : R値
	@param [in] g : G値
	@param [in] b : B値
	@param [in] a : A値
	@details 0.0f～1.0fの間でお願いします。
	*/
	void SetColor(float r, float g, float b, float a) override;

	/**
	@brief 色を取得します。
	@return 色
	*/
	const math::Vector4& GetColor() const override;

	/**
	@brief 頂点シェーダーを登録します。
	@param [in] shader : シェーダー
	@details デフォルトシェーダーは保持されています。
	*/
	void SetVertexShader(const structure::VertexShader& shader) override;

	/**
	@brief ピクセルシェーダーを登録します。
	@param [in] shader : シェーダー
	@details デフォルトシェーダーは保持されています。
	*/
	void SetPixelShader(const structure::PixelShader& shader) override;

	/**
	@brief 頂点レイアウトを登録します。
	@param [in] layout : レイアウト
	@details デフォルトレイアウトは保持されています。
	*/
	void SetInputLayout(const structure::InputLayout& layout) override;

	/**
	@brief デフォルトシェーダーを復元します。
	@details 指定したシェーダーの登録は解除されます。
	*/
	void RestoreDefaultShader() override;
private:
	/**
	@brief 初期化
	*/
	void Init() override;

	/**
	@brief 描画
	*/
	void Draw() override;
};

_MDX_COMPONENT_END