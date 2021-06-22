//==========================================================================
// ポイントレンダラー [PointRenderer.cpp]
// author : MasyoLab
//==========================================================================
#include "PointRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "../DirectX11.h"

_MDX_COMPONENT_BEGIN
_MDX_USING_STRUCTURE
_MDX_USING_SHARED_CONSTANT

#pragma region Entity declaration
//==========================================================================
// 実体の宣言
//==========================================================================
VertexShader PointRenderer::m_ShareVertexShader;
PixelShader PointRenderer::m_SharePixelShader;
InputLayout PointRenderer::m_ShareInputLayout;
VertexBuffer PointRenderer::m_ShareVertexBuffer;
IndexBuffer PointRenderer::m_ShareIndexBuffer;
ConstantBuffer PointRenderer::m_ShareConstantBuffer;
std::vector<Vertex> PointRenderer::m_ShareVertex = std::vector<Vertex>({
	{ math::Vector3(0.0f, 0.0f, 0.0f)},{ math::Vector3(1.0f, 0.0f, 0.0f)},
	{ math::Vector3(1.0f, 1.0f, 0.0f)},{ math::Vector3(0.0f, 1.0f, 0.0f)} });
std::vector<UINT> PointRenderer::m_ShareIndex = std::vector<UINT>({ 0,1,2,0,2,3 });
D3D11_INPUT_ELEMENT_DESC PointRenderer::m_ShareInputElementDesc[1] = {
	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0} };
#pragma endregion

PointRenderer::PointRenderer() :
	m_Polygon(1, 1, 0)
{
	SetObjectName("PointRenderer");
	m_PolygonMatrix = math::Matrix::MakeScaling(m_Polygon);

	// ピボット分オフセット
	m_PolygonMatrix.m41 -= m_Polygon.x * 0.5f;
	m_PolygonMatrix.m42 -= m_Polygon.y * 0.5f;
}

PointRenderer::~PointRenderer()
{
	// レンダラーマネージャーから解放
	ReleaseRenderer(ERendererList::PointRenderer, this, m_GameObject);
}

void PointRenderer::SetColor(const math::Vector4& color)
{
	m_MatrixBuffer.color = color;
}

void PointRenderer::SetColor(float r, float g, float b, float a)
{
	m_MatrixBuffer.color = math::Vector4(r, g, b, a);
}

const math::Vector4& PointRenderer::GetColor() const
{
	return m_MatrixBuffer.color;
}

void PointRenderer::SetVertexShader(const VertexShader& shader)
{
	m_VertexShader = shader;
}

void PointRenderer::SetPixelShader(const PixelShader& shader)
{
	m_PixelShader = shader;
}

void PointRenderer::SetInputLayout(const InputLayout& layout)
{
	m_InputLayout = layout;
}

void PointRenderer::RestoreDefaultShader()
{
	// デフォルトシェーダを渡す
	m_VertexShader = m_ShareVertexShader;
	m_PixelShader = m_SharePixelShader;
	m_InputLayout = m_ShareInputLayout;
}

void PointRenderer::Init()
{
	if (m_Manager == nullptr)
		return;

	// デフォルトのシェーダーを読み込みます
	if (m_ShareVertexShader == nullptr)
		m_ShareVertexShader = m_Manager->CreateVertexShader("Assets/cso/2DDefaultPointShaderVS.cso");
	if (m_SharePixelShader == nullptr)
		m_SharePixelShader = m_Manager->CreatePixelShader("Assets/cso/2DDefaultPointShaderPS.cso");
	if (m_ShareInputLayout == nullptr)
		m_ShareInputLayout = m_Manager->CreateInputLayout(m_ShareInputElementDesc, sizeof(m_ShareInputElementDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC), "Assets/cso/2DDefaultPointShaderVS.cso");
	if (m_ShareVertexBuffer == nullptr)
		m_ShareVertexBuffer.Attach(m_Manager->CreateVertexBuffer(m_ShareVertex.data(), static_cast<UINT>(m_ShareVertex.size())));
	if (m_ShareIndexBuffer == nullptr)
		m_ShareIndexBuffer.Attach(m_Manager->CreateIndexBuffer(m_ShareIndex.data(), static_cast<UINT>(m_ShareIndex.size())));
	if (m_ShareConstantBuffer == nullptr)
		m_Manager->CreateConstantBuffer(sizeof(SpriteMatrixBuffer), &m_ShareConstantBuffer);

	// デフォルトシェーダーを登録
	RestoreDefaultShader();

	// レンダラーマネージャーに登録
	SetRenderer(ERendererList::PointRenderer, this, m_GameObject);
}

void PointRenderer::Draw()
{
	if (m_Manager == nullptr)
		return;
	auto transform = m_GameObject->GetComponent<Transform>();
	if (transform == nullptr)
		return;

	// ポリゴンを書くための各種パラメータセット
	m_Manager->SetVertexShader(m_VertexShader.Get());
	m_Manager->SetPixelShader(m_PixelShader.Get());
	m_Manager->SetInputLayout(m_InputLayout.Get());
	m_Manager->SetVertexBuffer(m_ShareVertexBuffer.Get(), sizeof(Vertex));
	m_Manager->SetIndexBuffer(m_ShareIndexBuffer.Get());

	// ワールド行列を更新、ポリゴンと合成します。
	m_MatrixBuffer.mat = m_PolygonMatrix * transform->GetWorldMatrix();

	// ずらしたピボットを戻します
	m_MatrixBuffer.mat.m41 += m_Polygon.x * 0.5f;
	m_MatrixBuffer.mat.m42 += m_Polygon.y * 0.5f;
	m_MatrixBuffer.mat *= g_TransformationMatrix2D;

	// マトリックスバッファの設定
	m_Manager->SetUpdateSubresource(m_ShareConstantBuffer.Get(), 0, nullptr, &m_MatrixBuffer, 0, 0);
	m_Manager->VSSetConstantBuffers(m_ShareConstantBuffer.Get());

	// DrawCall
	m_Manager->DrawIndexed(static_cast<UINT>(m_ShareIndex.size()));
}

_MDX_COMPONENT_END