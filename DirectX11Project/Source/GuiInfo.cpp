//==========================================================================
// 情報 [GuiInfo.cpp]
// author : MasyoLab
//==========================================================================
#include "GuiInfo.h"

constexpr size_t recordingSeconds = 60; // 記録時間(秒)
constexpr float IsInsufficientMemoryParam = 0.8f; // メモリ不足の値

GuiInfo::GuiInfo()
{
	SetObjectName("GuiInfo");
	m_PhysicalMemory = std::vector<float>(recordingSeconds, 0.0f);
	m_VirtualMemory = std::vector<float>(recordingSeconds, 0.0f);
	m_UserSpace = std::vector<float>(recordingSeconds, 0.0f);
}

GuiInfo::~GuiInfo()
{
}

void GuiInfo::GUI()
{
	if (!mdx_imgui::BeginMenu("Info"))
		return;

	if (mdx_imgui::BeginMenu("Window"))
	{
		mdx_imgui::DisplayWindowsSize();
		mdx_imgui::DisplayFramerate();
		mdx_imgui::EndMenu();
	}

	if (mdx_imgui::BeginMenu("Memory info"))
	{
		MemoryGUI();
		mdx_imgui::Separator();
		mdx_imgui::Checkbox("Memory window", m_MemoryMindow);
		mdx_imgui::EndMenu();
	}

	if (m_GuiOpenSourceLicenses != nullptr)
		m_GuiOpenSourceLicenses->GUI(700);

	mdx_imgui::EndMenu();
}

bool GuiInfo::IsInsufficientMemory()
{
	return m_InsufficientMemory;
}

void GuiInfo::SetMemoryMindowFlag(bool flag)
{
	m_MemoryMindow = flag;
}

void GuiInfo::Init()
{
	m_GuiOpenSourceLicenses = m_GameObject->AddComponent(new GuiOpenSourceLicenses);
}

void GuiInfo::Update()
{
	m_time += mdx::system::clock::GetDeltaTime();
	m_UpdateTime = false;

	// 1秒より大きいなら
	for (; 1.0f < m_time; m_time--)
	{
		m_MemoryInfo = mdx::system::memory::GetMemoryInfoInGByte();

		// データを前に
		for (size_t i = 1; i < m_PhysicalMemory.size(); i++)
			m_PhysicalMemory[i - 1] = m_PhysicalMemory[i];
		m_PhysicalMemory[m_PhysicalMemory.size() - 1] = m_MemoryInfo.maxPhysicalMemoryCapacity - m_MemoryInfo.freePhysicalMemory;

		// データを前に
		for (size_t i = 1; i < m_VirtualMemory.size(); i++)
			m_VirtualMemory[i - 1] = m_VirtualMemory[i];
		m_VirtualMemory[m_VirtualMemory.size() - 1] = m_MemoryInfo.maxVirtualMemoryCapacity - m_MemoryInfo.freeVirtualMemory;

		// データを前に
		for (size_t i = 1; i < m_UserSpace.size(); i++)
			m_UserSpace[i - 1] = m_UserSpace[i];
		m_UserSpace[m_UserSpace.size() - 1] = m_MemoryInfo.maxUserSpaceCapacity - m_MemoryInfo.freeUserSpace;
		m_UpdateTime = true;
	}

	MemoryWindow();
}

void GuiInfo::MemoryGUI()
{
	mdx_imgui::PlotLines("", m_PhysicalMemory.data(), m_PhysicalMemory.size(), 0, u8"物理メモリ", 0.0f, m_MemoryInfo.maxPhysicalMemoryCapacity, { 0, 100 });
	mdx_imgui::Text(ANSI_TO_UTF8_ENCODE(mdx_imgui::MakeString("利用可能 : %.1f GB", m_MemoryInfo.freePhysicalMemory)));
	mdx_imgui::Text(ANSI_TO_UTF8_ENCODE(mdx_imgui::MakeString("使用中 : %.1f GB / %.1f GB (%lu％)",
		m_MemoryInfo.maxPhysicalMemoryCapacity - m_MemoryInfo.freePhysicalMemory, m_MemoryInfo.maxPhysicalMemoryCapacity, m_MemoryInfo.physicalMemoryUsage)));

	mdx_imgui::Separator();

	mdx_imgui::PlotLines("", m_VirtualMemory.data(), m_VirtualMemory.size(), 0, u8"仮想メモリ", 0.0f, m_MemoryInfo.maxVirtualMemoryCapacity, { 0, 100 });
	mdx_imgui::Text(ANSI_TO_UTF8_ENCODE(mdx_imgui::MakeString("利用可能 : %.1f GB", m_MemoryInfo.freeVirtualMemory)));
	mdx_imgui::Text(ANSI_TO_UTF8_ENCODE(mdx_imgui::MakeString("使用中 : %.1f GB / %.1f GB",
		m_MemoryInfo.maxVirtualMemoryCapacity - m_MemoryInfo.freeVirtualMemory, m_MemoryInfo.maxVirtualMemoryCapacity)));

	mdx_imgui::Separator();

	mdx_imgui::PlotLines("", m_UserSpace.data(), m_UserSpace.size(), 0, u8"アプリが利用できるメモリ", 0.0f, m_MemoryInfo.maxUserSpaceCapacity, { 0, 100 });
	mdx::math::Vector4 color = mdx::math::Vector4(1, 1, 1, 1);

	if (m_MemoryInfo.freeUserSpace < 1.0f)
		color = mdx::math::Vector4(1, 1, 0, 1);
	m_InsufficientMemory = m_MemoryInfo.freeUserSpace < IsInsufficientMemoryParam;
	if (m_InsufficientMemory)
		color = mdx::math::Vector4(1, 0, 0, 1);
	mdx_imgui::Text(ANSI_TO_UTF8_ENCODE(mdx_imgui::MakeString("利用可能 : %.1f GB", m_MemoryInfo.freeUserSpace)), color);
	mdx_imgui::Text(ANSI_TO_UTF8_ENCODE(mdx_imgui::MakeString("使用中 : %.1f GB / %.1f GB",
		m_MemoryInfo.maxUserSpaceCapacity - m_MemoryInfo.freeUserSpace, m_MemoryInfo.maxUserSpaceCapacity)));
}

void GuiInfo::MemoryWindow()
{
	if (!m_MemoryMindow)
		return;

	mdx_imgui::Begin("Memory window", &m_MemoryMindow, mdx_imgui::ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings);
	MemoryGUI();
	mdx_imgui::End();
}

