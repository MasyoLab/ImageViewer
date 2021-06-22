//==========================================================================
// 共通include [dx11afx.h]
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
#include <chrono> // c++ 時間演算
#include <codecvt> // c++ 文字コード変換
#include <cstdlib> // c++ 数値変換
#include <locale> // c++ 文字の判定
#include <system_error> // c++ OSエラー
#include <vector> // c++ 動的構造体
#include <list> // c++ 双方向list
#include <map> // c++ 平衡二分木 ソート機能付き
#include <unordered_map> // c++ 平衡二分木 ソート機能無し
#include <iomanip> // c++ 時間
#include <string> // c++ char
#include <random> // c++ rand
#include <fstream> // ifstream, ofstream
#include <sstream> // istringstream
#include <type_traits> // c++ メタ関数
#include <algorithm> // c++ アルゴリズム
#include <memory> // c++ メモリ
#include <iterator>
#include <cstdio> // 
#include <limits> // 型の最大値を返す
#include <stdio.h>
#include <typeinfo> // typeidを使うために必要
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
using Microsoft::WRL::ComPtr; //ComPtr(DirectX版のスマートポインタ)
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
// 一つの頂点情報を格納する構造体
struct Vertex
{
	math::Vector3 position; // 頂点座標
};

// マトリクスバッファ
struct MatrixBuffer
{
	math::Matrix mat; // 計算済み行列
};

// 頂点情報を格納する構造体
struct Vertex2D
{
	math::Vector3 position; // 頂点座標
	math::Vector4 color = math::Vector4(1, 1, 1, 1); // 色
	math::Vector2 uv; // UV座標
};

struct SpriteMatrixBuffer
{
	math::Matrix mat; // 計算済み行列
	math::Vector4 color = math::Vector4(1, 1, 1, 1); // 色
};

#pragma endregion
_MDX_STRUCTURE_END

_MDX_SHARED_CONSTANT_BEGIN
#pragma region Shared constant
static const math::Vector2 g_ScreenSize(1920, 1080); // Full HD スクリーンのサイズ
static const math::Vector2 g_AspectRatio(16, 9); // アスペクト比

// 2D座標変換行列
static const math::Matrix g_TransformationMatrix2D(
	2.0f / g_ScreenSize.x, 0.0f, 0.0f, 0.0f,
	0.0f, -2.0f / g_ScreenSize.y, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	-1.0f, 1.0f, 0.0f, 1.0f
);
#pragma endregion
_MDX_SHARED_CONSTANT_END