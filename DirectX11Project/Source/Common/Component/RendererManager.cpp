//==========================================================================
// レンダラーマネージャー [RendererManager.cpp]
// author : MasyoLab
//==========================================================================
#include "RendererManager.h"
#include "Scene.h"
#include "../DirectX11.h"

_MDX_COMPONENT_BEGIN
_MDX_USING_OBJECT
_MDX_USING_STRUCTURE

#pragma region Entity declaration
//==========================================================================
// 実体の宣言
//==========================================================================
std::unordered_map<Scene*, std::unordered_map<ERendererList, std::list< RendererManager*>>> RendererManager::m_Renderers;
static const math::Vector4 g_DefaultCollar(1, 1, 1, 1);
#pragma endregion

RendererManager::RendererManager() :
	Component("RendererManager")
{
}

RendererManager::~RendererManager()
{
}

void RendererManager::SetColor(const math::Vector4& color)
{
	color;
}

void RendererManager::SetColor(float r, float g, float b, float a)
{
	r; g; b; a;
}

const math::Vector4& RendererManager::GetColor() const
{
	return g_DefaultCollar;
}

void RendererManager::SetVertexShader(const VertexShader& shader)
{
	shader;
}

void RendererManager::SetPixelShader(const PixelShader& shader)
{
	shader;
}

void RendererManager::SetInputLayout(const InputLayout& layout)
{
	layout;
}

void RendererManager::RestoreDefaultShader()
{
}

void RendererManager::Draw(const math::Matrix& view, const math::Matrix& projection)
{
	view; projection;
}

void RendererManager::Draw()
{
}

void RendererManager::SetRenderer(ERendererList RendererType, RendererManager* RendererPtr, object::GameObject* ObjectPtr)
{
	m_Renderers[ObjectPtr->GetScene()][RendererType].push_back(RendererPtr);
}

void RendererManager::ReleaseRenderer(ERendererList RendererType, RendererManager* RendererPtr, object::GameObject* ObjectPtr)
{
	// 属しているシーン
	auto scenePtr = m_Renderers.find(ObjectPtr->GetScene());
	if (scenePtr == m_Renderers.end())
		return;

	// レンダラーのタイプ
	auto rendererList = scenePtr->second.find(RendererType);
	if (rendererList == scenePtr->second.end())
		return;

	// 対象となるレンダラー
	auto rendererPtr = std::find(rendererList->second.begin(), rendererList->second.end(), RendererPtr);
	if (rendererPtr == rendererList->second.end())
		return;

	rendererList->second.erase(rendererPtr);
}

void RendererManager::CreateSceneRenderer(Scene* scene)
{
	// 格納場所の作成
	for (int i = 0; i < (int)ERendererList::Max; i++)
	{
		m_Renderers[scene][(ERendererList)i];
	}
}

void RendererManager::ReleaseSceneRenderer(Scene* scene)
{
	auto itr = m_Renderers.find(scene);
	if (itr == m_Renderers.end())
		return;
	m_Renderers.erase(itr);
}

void RendererManager::DrawSceneRenderer(Scene* scene, const math::Matrix& view, const math::Matrix& projection)
{
	auto sceneItr = m_Renderers.find(scene);
	if (sceneItr == m_Renderers.end())
		return;

	for (auto& rendererType : sceneItr->second)
	{
		for (auto& itr : rendererType.second)
		{
			if (!itr->GetDisplayFlags())
				continue;

			itr->Draw(view, projection);
			itr->Draw();
		}
	}
}

_MDX_COMPONENT_END