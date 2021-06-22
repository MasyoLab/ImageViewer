//==========================================================================
// ���C�� [main.cpp]
// author : MasyoLab
//==========================================================================
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define _GLIBCXX_DEBUG
#include "Source/common.h"
#include "Source/ImageViewer.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(WindowResizeFunctions, UINT);

constexpr float g_AspectX = 16.0f;
constexpr float g_AspectY = 9.0f;
constexpr DWORD g_WindowStyle = (WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX));
WindowResizeFunctions g_WindowResizeFunctions;

void CheckSize(WPARAM wParam, LPARAM lParam);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
			g_WindowResizeFunctions.Broadcast(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZING:
		CheckSize(wParam, lParam);
		return TRUE;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			if (MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1) == IDYES)
				PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		SetFocus(hWnd);
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1) == IDYES)
			PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	int width = 1270;
	int height = 714;
	MSG msg = { 0 };
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),				// �\���̂̃T�C�Y
		CS_VREDRAW | CS_HREDRAW,		// �E�C���h�E�X�^�C��
		WndProc,						// ���̃E�C���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐��ւ̃|�C���^
		0L,								// �E�C���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�o�C�g���D����0�D
		0L,								// �E�C���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�⑫�o�C�g���D����0�D
		hInstance, 						// ���̃N���X�̂��߂̃E�C���h�E�v���V�[�W��������C���X�^���X�n��
		LoadIcon(hInstance, nullptr), 	// �A�C�R���̃n���h��
		LoadCursor(nullptr, IDC_ARROW), // �}�E�X�J�[�\���̃n���h���DLoadCursor(nullptr, IDC_ARROW )�Ƃ�
		(HBRUSH)(COLOR_WINDOW + 1), 	// �E�C���h�E�w�i�F(�w�i�`��p�u���V�̃n���h��)�D
		nullptr,						// �f�t�H���g���j���[��(MAKEINTRESOURCE(���j���[ID))
		"ImageViewer",					// ���̃E�C���h�E�N���X�ɂ��閼�O
		LoadIcon(hInstance, nullptr)	// 16�~16�̏������T�C�Y�̃A�C�R��
	};

#if defined(_DEBUG)
	// �R���\�[���f�o�b�O
	mdx::system::d3dx11debug::DebugConsoleBegin();
#endif
	
	mdx::system::clock::SetFps(60);

	// �}�l�[�W���[
	mdx::system::DirectX11Manager manager;
	g_WindowResizeFunctions.AddDynamic1(&mdx::system::DirectX11Manager::ResizeBuffers, &manager);

	mdx_imgui::Setting();
	mdx_imgui::SetFont("Assets/Font/Meiryo/meiryo.ttc");
	manager.m_ImGuiInitializer.__Internal_AddDynamic(&mdx_imgui::Init);

	if (FAILED(manager.Init("ImageViewer", width, height, g_WindowStyle, wcex, hInstance, nCmdShow)))
		return -1;

	// �V�[��
	mdx::object::Scene myScene(&manager);

	// 2DObject
	auto my2DObject = myScene.AddGameObject("2DObject");
	my2DObject->AddComponent(new ImageViewer);
	manager.SetBlendState({ 0, 0, 0, 0 });

	for (;;)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		if (!mdx::system::clock::FpsFixed())
			continue;

		mdx_imgui::NewFrame();
		myScene.Update();
		mdx_imgui::EndFrame();

		// Draw 
		manager.DrawBegin();
		myScene.Draw();
		mdx_imgui::Draw();
		manager.DrawEnd();
	}

	mdx_imgui::Uninit();
#if defined(_DEBUG)
	// �R���\�[���f�o�b�O�I��
	mdx::system::d3dx11debug::DebugConsoleEnd();
#endif

	return 0;
}

void CheckSize(WPARAM wParam, LPARAM lParam)
{
	RECT* rc;
	int width, height;
	int minimumwidth;

	minimumwidth = GetSystemMetrics(SM_CXMINTRACK);
	rc = (RECT*)lParam;
	width = rc->right - rc->left;
	height = rc->bottom - rc->top;
	switch (wParam)
	{
	case WMSZ_TOP:
		width = (int)(height * (g_AspectX / g_AspectY));
		if (((double)width / (double)height) < (g_AspectX / g_AspectY))
			rc->right = rc->left + (int)(height * (g_AspectX / g_AspectY));
		else
			rc->top = rc->bottom - (int)(width * (g_AspectY / g_AspectX));
		break;
	case WMSZ_BOTTOM:
		width = (int)(height * (g_AspectX / g_AspectY));
		if (((double)width / (double)height) < (g_AspectX / g_AspectY))
			rc->right = rc->left + (int)(height * (g_AspectX / g_AspectY));
		else
			rc->bottom = rc->top + (int)(width * (g_AspectY / g_AspectX));
		break;
	case WMSZ_LEFT:
	case WMSZ_RIGHT:
		rc->bottom = rc->top + (int)(width * (g_AspectY / g_AspectX));
		break;
	case WMSZ_TOPLEFT:
		if (((double)width / (double)height) < (g_AspectX / g_AspectY))
			rc->left = rc->right - (int)(height * (g_AspectX / g_AspectY));
		else
			rc->top = rc->bottom - (int)(width * (g_AspectY / g_AspectX));
		break;
	case WMSZ_TOPRIGHT:
		if (((double)width / (double)height) < (g_AspectX / g_AspectY))
			rc->right = rc->left + (int)(height * (g_AspectX / g_AspectY));
		else
			rc->top = rc->bottom - (int)(width * (g_AspectY / g_AspectX));
		break;
	case WMSZ_BOTTOMLEFT:
		if (((double)width / (double)height) < (g_AspectX / g_AspectY))
			rc->left = rc->right - (int)(height * (g_AspectX / g_AspectY));
		else
			rc->bottom = rc->top + (int)(width * (g_AspectY / g_AspectX));
		break;
	case WMSZ_BOTTOMRIGHT:
		if (((double)width / (double)height) < (g_AspectX / g_AspectY))
			rc->right = rc->left + (int)(height * (g_AspectX / g_AspectY));
		else
			rc->bottom = rc->top + (int)(width * (g_AspectY / g_AspectX));
		break;
	}
}
