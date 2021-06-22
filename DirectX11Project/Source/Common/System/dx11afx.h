//==========================================================================
// ����include [dx11afx.h]
// author : MasyoLab
//==========================================================================
#pragma once

#pragma region WindowsDirectX
#include <windows.h>
#include <d3d11.h>
#include <LuminoMath.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include <DirectXMath.h>
#include <DirectXTex.h>
#pragma endregion

#pragma region std include
#include <iostream>
#include <chrono> // c++ ���ԉ��Z
#include <codecvt> // c++ �����R�[�h�ϊ�
#include <cstdlib> // c++ ���l�ϊ�
#include <locale> // c++ �����̔���
#include <system_error> // c++ OS�G���[
#include <vector> // c++ ���I�\����
#include <list> // c++ �o����list
#include <map> // c++ ���t�񕪖� �\�[�g�@�\�t��
#include <unordered_map> // c++ ���t�񕪖� �\�[�g�@�\����
#include <iomanip> // c++ ����
#include <string> // c++ char
#include <random> // c++ rand
#include <fstream> // ifstream, ofstream
#include <sstream> // istringstream
#include <type_traits> // c++ ���^�֐�
#include <algorithm> // c++ �A���S���Y��
#include <memory> // c++ ������
#include <iterator>
#include <cstdio> // 
#include <limits> // �^�̍ő�l��Ԃ�
#include <stdio.h>
#include <typeinfo> // typeid���g�����߂ɕK�v
#pragma endregion

#pragma region common
#include "mdx.h"
#include "SharePtr.h"
#include "math.h"
#pragma endregion

#pragma region API
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
#pragma endregion

#pragma region using
using Microsoft::WRL::ComPtr; //ComPtr(DirectX�ł̃X�}�[�g�|�C���^)
using namespace DirectX;
#pragma endregion

_MDX_STRUCTURE_BEGIN
#pragma region Smart pointer definition
typedef ComPtr<ID3D11Buffer> ConstantBuffer, VertexBuffer, IndexBuffer, StructuredBuffer;
typedef ComPtr<ID3D11InputLayout> InputLayout;
typedef ComPtr<ID3D11VertexShader> VertexShader;
typedef ComPtr<ID3D11GeometryShader> GeometryShader;
typedef ComPtr<ID3D11PixelShader> PixelShader;
typedef ComPtr<ID3D11ComputeShader> ComputeShader;
typedef ComPtr<ID3D11Texture2D> Texture2D;
typedef ComPtr<ID3D11ShaderResourceView> ShaderTexture;
typedef ComPtr<ID3D11UnorderedAccessView> ComputeOutputView;
typedef ComPtr<ID3D11Device> DirectXDevice;
#pragma endregion

#pragma region Structure
// ��̒��_�����i�[����\����
struct Vertex
{
	math::Vector3 position; // ���_���W
};

// �}�g���N�X�o�b�t�@
struct MatrixBuffer
{
	math::Matrix mat; // �v�Z�ςݍs��
};

// ���_�����i�[����\����
struct Vertex2D
{
	math::Vector3 position; // ���_���W
	math::Vector4 color = math::Vector4(1, 1, 1, 1); // �F
	math::Vector2 uv; // UV���W
};

struct SpriteMatrixBuffer
{
	math::Matrix mat; // �v�Z�ςݍs��
	math::Vector4 color = math::Vector4(1, 1, 1, 1); // �F
};

#pragma endregion
_MDX_STRUCTURE_END

_MDX_SHARED_CONSTANT_BEGIN
#pragma region Shared constant
static const math::Vector2 g_ScreenSize(1920, 1080); // Full HD �X�N���[���̃T�C�Y
static const math::Vector2 g_AspectRatio(16, 9); // �A�X�y�N�g��

// 2D���W�ϊ��s��
static const math::Matrix g_TransformationMatrix2D(
	2.0f / g_ScreenSize.x, 0.0f, 0.0f, 0.0f,
	0.0f, -2.0f / g_ScreenSize.y, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 1.0f
);
#pragma endregion
_MDX_SHARED_CONSTANT_END