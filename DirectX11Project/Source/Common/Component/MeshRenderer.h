//==========================================================================
// メッシュレンダラー [MeshRenderer.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "RendererManager.h"

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : MeshRenderer 
// Content : メッシュレンダラー
// details : 継承禁止/デフォルトのシェーダーが設定されています
//
//==========================================================================
class MeshRenderer final :
	public RendererManager
{
private:
	structure::VertexShader m_VertexShader; // 頂点シェーダー
	structure::PixelShader m_PixelShader; // ピクセルシェーダー
	structure::InputLayout m_InputLayout; // レイアウト
	structure::SpriteMatrixBuffer m_MatrixBuffer; // マトリクスバッファ
	static structure::VertexShader m_ShareVertexShader; // デフォルトの頂点シェーダー
	static structure::PixelShader m_SharePixelShader; // デフォルトのピクセルシェーダー
	static structure::InputLayout m_ShareInputLayout; // 共通のレイアウト
	static structure::VertexBuffer m_ShareVertexBuffer; // 共通のバーテックスバッファ
	static structure::ConstantBuffer m_ShareConstantBuffer; // バッファ
	static std::vector<structure::Vertex> m_ShareVertex; // 共通のデータ
	static D3D11_INPUT_ELEMENT_DESC m_ShareInputElementDesc[1]; // 共通のインプットレイアウト
public:
	MeshRenderer();
	virtual ~MeshRenderer();

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
	@param [in] view : ビュー行列
	@param [in] projection : プロジェクション行列
	*/
	void Draw(const math::Matrix& view, const math::Matrix& projection) override;
};

_MDX_COMPONENT_END