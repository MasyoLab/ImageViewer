//==========================================================================
// メッシュレンダラー [MeshRenderer.cpp]
// author : MasyoLab
//==========================================================================
#include "MeshRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "../DirectX11.h"

_MDX_COMPONENT_BEGIN
_MDX_USING_STRUCTURE

#pragma region Entity declaration
//==========================================================================
// 実体の宣言
//==========================================================================
VertexShader MeshRenderer::m_ShareVertexShader;
PixelShader MeshRenderer::m_SharePixelShader;
InputLayout MeshRenderer::m_ShareInputLayout;
VertexBuffer MeshRenderer::m_ShareVertexBuffer;
ConstantBuffer MeshRenderer::m_ShareConstantBuffer;
std::vector<Vertex> MeshRenderer::m_ShareVertex = std::vector<Vertex>({
	 {math::Vector3(-0.5f, 0.5f, 0.0f)},
	 {math::Vector3(-0.5f, -0.5f, 0.0f)},
	 {math::Vector3(0.5f, 0.5f, 0.0f)},
	 {math::Vector3(0.5f, -0.5f, 0.0f)}
	});
D3D11_INPUT_ELEMENT_DESC MeshRenderer::m_ShareInputElementDesc[1] = {
	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0} };
#pragma endregion

MeshRenderer::MeshRenderer()
{
	SetObjectName("MeshRenderer");
}

MeshRenderer::~MeshRenderer()
{
	// レンダラーマネージャーから解放
	ReleaseRenderer(ERendererList::MeshRenderer, this, m_GameObject);
}

void MeshRenderer::SetColor(const math::Vector4& color)
{
	m_MatrixBuffer.color = color;
}

void MeshRenderer::SetColor(float r, float g, float b, float a)
{
	m_MatrixBuffer.color = math::Vector4(r, g, b, a);
}

const math::Vector4& MeshRenderer::GetColor() const
{
	return m_MatrixBuffer.color;
}

void MeshRenderer::SetVertexShader(const VertexShader& shader)
{
	m_VertexShader = shader;
}

void MeshRenderer::SetPixelShader(const PixelShader& shader)
{
	m_PixelShader = shader;
}

void MeshRenderer::SetInputLayout(const InputLayout& layout)
{
	m_InputLayout = layout;
}

void MeshRenderer::RestoreDefaultShader()
{
	// デフォルトシェーダを渡す
	m_VertexShader = m_ShareVertexShader;
	m_PixelShader = m_SharePixelShader;
	m_InputLayout = m_ShareInputLayout;
}

void MeshRenderer::Init()
{
	if (m_Manager == nullptr)
		return;

	// デフォルトのシェーダーを読み込みます
	if (m_ShareVertexShader == nullptr)
		m_ShareVertexShader = m_Manager->CreateVertexShader("Assets/cso/3DDefaultShaderVS.cso");
	if (m_SharePixelShader == nullptr)
		m_SharePixelShader = m_Manager->CreatePixelShader("Assets/cso/3DDefaultShaderPS.cso");
	if (m_ShareInputLayout == nullptr)
		m_ShareInputLayout = m_Manager->CreateInputLayout(m_ShareInputElementDesc, sizeof(m_ShareInputElementDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC), "Assets/cso/3DDefaultShaderVS.cso");
	if (m_ShareVertexBuffer == nullptr)
		m_ShareVertexBuffer.Attach(m_Manager->CreateVertexBuffer(m_ShareVertex.data(), static_cast<UINT>(m_ShareVertex.size())));
	if (m_ShareConstantBuffer == nullptr)
		m_Manager->CreateConstantBuffer(sizeof(SpriteMatrixBuffer), &m_ShareConstantBuffer);

	// デフォルトシェーダーを登録
	RestoreDefaultShader();

	// レンダラーマネージャーに登録
	SetRenderer(ERendererList::MeshRenderer, this, m_GameObject);
}

void MeshRenderer::Draw(const math::Matrix& view, const math::Matrix& projection)
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

	m_MatrixBuffer.mat = transform->GetWorldMatrix() * view * projection;

	// マトリックスバッファの設定
	m_Manager->SetUpdateSubresource(m_ShareConstantBuffer.Get(), 0, nullptr, &m_MatrixBuffer, 0, 0);
	m_Manager->VSSetConstantBuffers(m_ShareConstantBuffer.Get());

	// DrawCall
	m_Manager->Draw(4);
}

_MDX_COMPONENT_END