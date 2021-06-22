//==========================================================================
// 情報 [GuiInfo.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "common.h"
#include "GuiOpenSourceLicenses.h"

// 情報
class GuiInfo :
	public mdx::component::Component
{
private:
	float m_time = 0;
	mdx::system::memory::MemoryInfo_float m_MemoryInfo;
	std::vector<float> m_PhysicalMemory; // 物理メモリ
	std::vector<float> m_VirtualMemory; // 仮想メモリ
	std::vector<float> m_UserSpace; // アプリが利用できるメモリ
	bool m_MemoryMindow = false; // メモリウィンドウ
	GuiOpenSourceLicenses* m_GuiOpenSourceLicenses = nullptr;
	bool m_UpdateTime = false;
	bool m_InsufficientMemory = false; // メモリ不足
public:
	GuiInfo();
	~GuiInfo();

	/**
	@brief GUI
	*/
	void GUI();

	bool IsInsufficientMemory();

	void SetMemoryMindowFlag(bool flag);
private:
	/**
	@brief 初期化
	*/
	void Init() override;

	/**
	@brief 更新
	*/
	void Update() override;

	/**
	@brief メモリのUI
	*/
	void MemoryGUI();

	/**
	@brief メモリウィンドウ
	*/
	void MemoryWindow();
};
