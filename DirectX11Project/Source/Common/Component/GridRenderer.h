//==========================================================================
// グリッドレンダラー [GridRenderer.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "RendererManager.h"

// グリッドの頂点
_MDX_STRUCTURE_BEGIN
struct GridVertex :
	public Vertex
{
	math::Vector4 color; // 色
};
_MDX_STRUCTURE_END

_MDX_COMPONENT_BEGIN
//==========================================================================
//
// class : GridRenderer 
// Content : グリッドレンダラー
// details : 継承禁止/デフォルトのシェーダーが設定されています
//
//==========================================================================
class GridRenderer final :
	public RendererManager
{
private:
	std::vector<structure::GridVertex> m_Vertex; // 頂点データ
	int m_Size; // サイズの記録
	structure::VertexShader m_VertexShader; // 頂点シェーダー
	structure::PixelShader m_PixelShader; // ピクセルシェーダー
	structure::InputLayout m_InputLayout; // レイアウト
	structure::VertexBuffer m_VertexBuffer; // 共通のバーテックスバッファ
	static structure::VertexShader m_ShareVertexShader; // デフォルトの頂点シェーダー
	static structure::PixelShader m_SharePixelShader; // デフォルトのピクセルシェーダー
	static structure::InputLayout m_ShareInputLayout; // 共通のレイアウト
	static structure::ConstantBuffer m_ShareConstantBuffer; // バッファ
	static structure::MatrixBuffer m_ShareMatrixBuffer; // 共通のマトリクスバッファ
public:
	GridRenderer() = delete;
	GridRenderer(int size);
	virtual ~GridRenderer();

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