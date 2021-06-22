//==========================================================================
// グリッドレンダラー [GridRenderer.cpp]
// author : MasyoLab
//==========================================================================
#include "GridRenderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "../DirectX11.h"

_MDX_COMPONENT_BEGIN
_MDX_USING_STRUCTURE

#pragma region Entity declaration
//==========================================================================
// 実体の宣言
//==========================================================================
VertexShader GridRenderer::m_ShareVertexShader;
PixelShader GridRenderer::m_SharePixelShader;
InputLayout GridRenderer::m_ShareInputLayout;
ConstantBuffer GridRenderer::m_ShareConstantBuffer;
MatrixBuffer GridRenderer::m_ShareMatrixBuffer;
static D3D11_INPUT_ELEMENT_DESC g_ShareInputElementDesc[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0}
};
#pragma endregion

GridRenderer::GridRenderer(int size) :m_Size(size)
{
	SetObjectName("GridRenderer");
}

GridRenderer::~GridRenderer()
{
	// レンダラーマネージャーから解放
	ReleaseRenderer(ERendererList::GridRenderer, this, m_GameObject);
}

void GridRenderer::SetVertexShader(const VertexShader& shader)
{
	m_VertexShader = shader;
}

void GridRenderer::SetPixelShader(const PixelShader& shader)
{
	m_PixelShader = shader;
}

void GridRenderer::SetInputLayout(const InputLayout& layout)
{
	m_InputLayout = layout;
}

void GridRenderer::RestoreDefaultShader()
{
	// デフォルトシェーダを渡す
	m_VertexShader = m_ShareVertexShader;
	m_PixelShader = m_SharePixelShader;
	m_InputLayout = m_ShareInputLayout;
}

void GridRenderer::Init()
{
	int num = 4; // 十字を作るための線
	float X = (float)m_Size; // サイズの記録
	float Z = (float)m_Size; // サイズの記録

	// サイズ分の外枠の線を追加
	for (int i = 0; i < m_Size; i++)
		num += 8;

	// 線の数分を予約
	m_Vertex = std::vector<GridVertex>(num);

	int numLine = (int)(num / 2);

	for (int i = 0; i < numLine; i += 2, X--, Z--)
	{
		m_Vertex[i].position = math::Vector3(1.0f * X, 0.0f, (float)m_Size); // x座標に線
		m_Vertex[i + 1].position = math::Vector3(1.0f * X, 0.0f, -(float)m_Size); // x座標に線
		m_Vertex[numLine + i].position = math::Vector3((float)m_Size, 0.0f, 1.0f * Z); // z座標に線
		m_Vertex[numLine + i + 1].position = math::Vector3(-(float)m_Size, 0.0f, 1.0f * Z); // z座標に線

		m_Vertex[i].color = math::Vector4(1, 1, 1, 1);
		m_Vertex[i + 1].color = math::Vector4(1, 1, 1, 1);
		m_Vertex[numLine + i].color = math::Vector4(1, 1, 1, 1);
		m_Vertex[numLine + i + 1].color = math::Vector4(1, 1, 1, 1);

		if (i == (int)((float)m_Size * 2))
		{
			m_Vertex[i].color = math::Vector4(1, 0, 0, 1);
			m_Vertex[i + 1].color = math::Vector4(1, 0, 0, 1);
			m_Vertex[numLine + i].color = math::Vector4(1, 0, 0, 1);
			m_Vertex[numLine + i + 1].color = math::Vector4(1, 0, 0, 1);
		}
	}

	if (m_Manager == nullptr)
		return;

	// デフォルトのシェーダーを読み込みます
	if (m_ShareVertexShader == nullptr)
		m_ShareVertexShader = m_Manager->CreateVertexShader("Assets/cso/LineShaderVS.cso");
	if (m_SharePixelShader == nullptr)
		m_SharePixelShader = m_Manager->CreatePixelShader("Assets/cso/LineShaderPS.cso");
	if (m_ShareInputLayout == nullptr)
		m_ShareInputLayout = m_Manager->CreateInputLayout(g_ShareInputElementDesc, sizeof(g_ShareInputElementDesc) / sizeof(D3D11_INPUT_ELEMENT_DESC), "Assets/cso/LineShaderVS.cso");
	if (m_ShareConstantBuffer == nullptr)
		m_Manager->CreateConstantBuffer(sizeof(MatrixBuffer), &m_ShareConstantBuffer);
	if (m_VertexBuffer == nullptr)
		m_VertexBuffer.Attach(m_Manager->CreateVertexBuffer(m_Vertex.data(), static_cast<UINT>(m_Vertex.size())));

	// デフォルトシェーダーを登録
	RestoreDefaultShader();

	// レンダラーマネージャーに登録
	SetRenderer(ERendererList::GridRenderer, this, m_GameObject);
}

void GridRenderer::Draw(const math::Matrix& view, const math::Matrix& projection)
{
	if (m_Manager == nullptr)
		return;
	auto transform = m_GameObject->GetComponent<Transform>();
	if (transform == nullptr)
		return;

	// ポリゴンを書くための各種パラメータセット
	m_Manager->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_Manager->SetVertexShader(m_VertexShader.Get());
	m_Manager->SetPixelShader(m_PixelShader.Get());
	m_Manager->SetInputLayout(m_InputLayout.Get());
	m_Manager->SetVertexBuffer(m_VertexBuffer.Get(), sizeof(GridVertex));

	m_ShareMatrixBuffer.mat = transform->GetWorldMatrix() * view * projection;

	// マトリックスバッファの設定
	m_Manager->SetUpdateSubresource(m_ShareConstantBuffer.Get(), 0, nullptr, &m_ShareMatrixBuffer, 0, 0);
	m_Manager->VSSetConstantBuffers(m_ShareConstantBuffer.Get());

	// DrawCall
	m_Manager->Draw(m_Vertex.size());
	m_Manager->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

_MDX_COMPONENT_END