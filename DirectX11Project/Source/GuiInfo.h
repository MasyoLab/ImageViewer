//==========================================================================
// ��� [GuiInfo.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "common.h"
#include "GuiOpenSourceLicenses.h"

// ���
class GuiInfo :
	public mdx::component::Component
{
private:
	float m_time = 0;
	mdx::system::memory::MemoryInfo_float m_MemoryInfo;
	std::vector<float> m_PhysicalMemory; // ����������
	std::vector<float> m_VirtualMemory; // ���z������
	std::vector<float> m_UserSpace; // �A�v�������p�ł��郁����
	bool m_MemoryMindow = false; // �������E�B���h�E
	GuiOpenSourceLicenses* m_GuiOpenSourceLicenses = nullptr;
	bool m_UpdateTime = false;
	bool m_InsufficientMemory = false; // �������s��
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
	@brief ������
	*/
	void Init() override;

	/**
	@brief �X�V
	*/
	void Update() override;

	/**
	@brief ��������UI
	*/
	void MemoryGUI();

	/**
	@brief �������E�B���h�E
	*/
	void MemoryWindow();
};
