//==========================================================================
// キャンバスレンダラー [CanvasRenderer.cpp]
// author : MasyoLab
//==========================================================================
#include "CanvasRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "../DirectX11.h"

_MDX_COMPONENT_BEGIN
_MDX_USING_STRUCTURE
_MDX_USING_SHARED_CONSTANT
_MDX_USING_COMMON

#pragma region Entity declaration
//==========================================================================
// 実体の宣言
//==========================================================================
VertexShader CanvasRenderer::m_ShareVertexShader;
PixelShader CanvasRenderer::m_SharePixelShader;
InputLayout CanvasRenderer::m_ShareInputLayout;
VertexBuffer CanvasRenderer::m_ShareVertexBuffer;
IndexBuffer CanvasRenderer::m_ShareIndexBuffer;
ConstantBuffer CanvasRenderer::m_ShareConstantBuffer;
std::vector<Vertex2D> CanvasRenderer::m_ShareVertex = std::vector<Vertex2D>({
	{ math::Vector3(0.0f, 0.0f, 0.0f),math::Vector4(1.0f,1.0f,1.0f,1.0f),math::Vector2(0.0f, 0.0f)},
	{ math::Vector3(1.0f, 0.0f, 0.0f),math::Vector4(1.0f,1.0f,1.0f,1.0f),math::Vector2(1.0f, 0.0f)},
	{ math::Vector3(1.0f, 1.0f, 0.0f),math::Vector4(1.0f,1.0f,1.0f,1.0f),math::Vector2(1.0f, 1.0f)},
	{ math::Vector3(0.0f, 1.0f, 0.0f),math::Vector4(1.0f,1.0f,1.0f,1.0f),math::Vector2(0.0f, 1.0f)} });
std::vector<UINT> CanvasRenderer::m_ShareIndex = std::vector<UINT>({ 0,1,2,0,2,3 });
D3D11_INPUT_ELEMENT_DESC CanvasRenderer::m_ShareInputElementDesc[3] = {
	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0},
	{ "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0},
	{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	28,	D3D11_INPUT_PER_VERTEX_DATA,	0}, };
#pragma endregion

CanvasRenderer::CanvasRenderer()
{
	SetObjectName("CanvasRenderer");
}

CanvasRenderer::~CanvasRenderer()
{
	// レンダラーマネージャーから解放
	ReleaseRenderer(ERendererList::CanvasRenderer, this, m_GameObject);
}

void CanvasRenderer::SetTexture(const Texture& texture, bool offset)
{
	m_Texture = texture;
	auto& info = m_Texture.GetImageInfo();
	m_Polygon = math::Vector3((float)info.width, (float)info.height, 0);
	m_PolygonMatrix = math::Matrix::MakeScaling(m_Polygon);

	// ピボット分オフセット
	if(offset)
	{
		m_PolygonMatrix.m41 -= m_Polygon.x * 0.5f;
		m_PolygonMatrix.m42 -= m_Polygon.y * 0.5f;
	}
	else
	{
		m_PolygonMatrix.m41 -= m_Polygon.x;
		m_PolygonMatrix.m42 -= m_Polygon.y;
	}
}

void CanvasRenderer::SetColor(const math::Vector4& color)
{
	m_MatrixBuffer.color = color;
}

void CanvasRenderer::SetColor(float r, float g, float b, float a)
{
	m_MatrixBuffer.color = math::Vector4(r, g, b, a);
}

const math::Vector4& CanvasRenderer::GetColor() const
{
	return m_MatrixBuffer.color;
}

void CanvasRenderer::SetVertexShader(const VertexShader& shader)
{
	m_VertexShader = shader;
}

void CanvasRenderer::SetPixelShader(const PixelShader& shader)
{
	m_PixelShader = shader;
}

void CanvasRenderer::SetInputLayout(const InputLayout& layout)
{
	m_InputLayout = layout;
}

void CanvasRenderer::RestoreDefaultShader()
{
	// デフォルトシェーダを渡す
	m_VertexShader = m_ShareVertexShader;
	m_PixelShader = m_SharePixelShader;
	m_InputLayout = m_ShareInputLayout;
}

void CanvasRenderer::Init()
{
	if (m_Manager == nullptr)
		return;

	// デフォルトのシェーダーを読み込みます
	if (m_ShareVertexShader == nullptr)
		m_ShareVertexShader = m_Manager->CreateVertexShader("Assets/cso/2DDefaultShaderVS.cso");
	if (m_SharePixelShader == nullptr)
		m_SharePixelShader = m_Manager->CreatePixelShader("Assets/cso/2DDefaultShaderPS.cso");
	if (m_ShareInputLayout == nullptr)
		m_ShareInputLayout = m_Manager->CreateInputLayout(m_ShareInputElementDesc, sizeof(m_ShareInputElementDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC), "Assets/cso/2DDefaultShaderVS.cso");
	if (m_ShareVertexBuffer == nullptr)
		m_ShareVertexBuffer.Attach(m_Manager->CreateVertexBuffer(m_ShareVertex.data(), static_cast<UINT>(m_ShareVertex.size())));
	if (m_ShareIndexBuffer == nullptr)
		m_ShareIndexBuffer.Attach(m_Manager->CreateIndexBuffer(m_ShareIndex.data(), static_cast<UINT>(m_ShareIndex.size())));
	if (m_ShareConstantBuffer == nullptr)
		m_Manager->CreateConstantBuffer(sizeof(SpriteMatrixBuffer), &m_ShareConstantBuffer);

	// デフォルトシェーダーを登録
	RestoreDefaultShader();

	// レンダラーマネージャーに登録
	SetRenderer(ERendererList::CanvasRenderer, this, m_GameObject);
}

void CanvasRenderer::Draw()
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
	m_Manager->SetVertexBuffer(m_ShareVertexBuffer.Get(), sizeof(Vertex2D));
	m_Manager->SetIndexBuffer(m_ShareIndexBuffer.Get());
	m_Manager->SetTexture2D(0, m_Texture.GetShaderTexture().Get());

	// ワールド行列を更新、ポリゴンと合成します。
	m_MatrixBuffer.mat = (m_PolygonMatrix * transform->GetWorldMatrix());

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