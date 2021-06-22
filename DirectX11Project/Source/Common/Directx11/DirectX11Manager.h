//==========================================================================
// DirectX11のマネージャー [DirectX11Manager.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "../System.h"
#include "VertexShaderManager.h"
#include "PixelShaderManager.h"
#include "ShaderTextureManager.h"
#include "GeometryShaderManager.h"
#include "ComputeShaderManager.h"
#include "InputLayoutManager.h"

_MDX_SYSTEM_BEGIN

//==========================================================================
//
// class : DirectX11Manager 
// Content : DirectX11のマネージャー
// details : 継承禁止
//
//==========================================================================
class DirectX11Manager final
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(ImGuiInitializer, HWND, ComPtr<ID3D11Device>, ComPtr<ID3D11DeviceContext>);
private:
	HWND											m_hWnd = nullptr;
	common::SharePtr<common::VertexShaderManager>	m_VertexShaderManager;
	common::SharePtr<common::PixelShaderManager>	m_PixelShaderManager;
	common::SharePtr<common::ShaderTextureManager>	m_ShaderTextureManager;
	common::SharePtr<common::GeometryShaderManager>	m_GeometryShaderManager;
	common::SharePtr<common::ComputeShaderManager>	m_ComputeShaderManager;
	common::SharePtr<common::InputLayoutManager>	m_InputLayoutManager;

	// DX11
	structure::DirectXDevice		m_Device = nullptr; // デバイス
	ComPtr<ID3D11DeviceContext>		m_DeviceContext = nullptr; // デバイスコンテキスト
	ComPtr<IDXGISwapChain>			m_SwapChain = nullptr; // スワップチェイン
	structure::Texture2D			m_RenderTargetTexture = nullptr; // レンダーターゲット
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView = nullptr; // ビュー
	D3D11_VIEWPORT					m_Viewport = { 0,0,0,0,0,0 }; // ビューポート
	ComPtr<ID3D11RasterizerState>	m_RasterizerState = nullptr; // ラスタライズ
	ComPtr<ID3D11BlendState>		m_BlendState; // ブレンドステート

	// Zバッファ
	ComPtr<ID3D11Texture2D>			m_Texture2DDepth = nullptr; // ステンシル用テクスチャ
	ComPtr<ID3D11DepthStencilState>	m_DepthStencilState = nullptr;	// Ｚバッファ、ステンシルステート
	ComPtr<ID3D11DepthStencilView>	m_DepthStencilView = nullptr; // ビュー

	// サンプラー
	ComPtr<ID3D11SamplerState>		m_Sampler = nullptr; // 通常テクスチャ(0-1サンプリング)
public:
	ImGuiInitializer m_ImGuiInitializer;
public:
	DirectX11Manager();
	~DirectX11Manager();
	/**
	@brief 初期化
	@param [in] strWindowName : ウィンドウ名
	@param [in] hInstance : Instance
	@param [in] cCmdShow : CmdShow
	@return 成功かどうか
	*/
	HRESULT Init(const std::string& strWindowName, int width, int height, DWORD style, WNDCLASSEX wcex, HINSTANCE hInstance, int cCmdShow);

	const D3D11_VIEWPORT& GetViewport() const;

	/**
	@brief バーテックスシェーダー生成
	@param [in] cso_file_path : .cosのファイルパス
	@return VertexShader
	*/
	structure::VertexShader CreateVertexShader(const std::string& cso_file_path);

	/**
	@brief ピクセルシェーダー生成
	@param [in] cso_file_path : .cosのファイルパス
	@return PixelShader
	*/
	structure::PixelShader CreatePixelShader(const std::string& cso_file_path);

	/**
	@brief ジオメトリシェーダー生成
	@param [in] cso_file_path : .cosのファイルパス
	@return GeometryShader
	*/
	structure::GeometryShader CreateGeometryShader(const std::string& cso_file_path);

	/**
	@brief コンピュートシェーダー生成
	@param [in] cso_file_path : .cosのファイルパス
	@return ComputeShader
	*/
	structure::ComputeShader CreateComputeShader(const std::string& cso_file_path);

	/**
	@brief 入力レイアウト作成
	@param [in] layout : D3D11_INPUT_ELEMENT_DESC
	@param [in] elem_num : D3D11_INPUT_ELEMENT_DESC のサイズ
	@param [in] cso_file_path : .cosのファイルパス
	@return InputLayout
	*/
	structure::InputLayout CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& cso_file_path);

	/**
	@brief コンスタントバッファを作成
	@param [in] bytesize : Byte Width
	@param [in] buffer : ID3D11Buffer
	@return 生成成功かどうか
	*/
	bool CreateConstantBuffer(unsigned int bytesize, ID3D11Buffer** buffer);

	/**
	@brief 頂点バッファ生成
	@param [in] VertexData : 頂点データ
	@param [in] VertexNum : 頂点数
	@return ID3D11Buffer*
	*/
	template<class _Ty>
	[[nodiscard]] 
	ID3D11Buffer* CreateVertexBuffer(_Ty* VertexData, UINT VertexNum)
	{
		// 頂点バッファ作成
		D3D11_BUFFER_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(bufferDesc));
		bufferDesc.ByteWidth = sizeof(_Ty) * VertexNum;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subResourceData;
		ZeroMemory(&subResourceData, sizeof(subResourceData));
		subResourceData.pSysMem = VertexData;
		//subResourceData.SysMemPitch = 0;
		//subResourceData.SysMemSlicePitch = 0;

		ID3D11Buffer* pBuffer = nullptr;
		if (FAILED(m_Device->CreateBuffer(&bufferDesc, &subResourceData, &pBuffer)))
			return nullptr;
		return pBuffer;
	}

	/**
	@brief インデックスバッファ生成
	@param [in] Index : インデックスデータ
	@param [in] IndexNum : インデック数
	@return ID3D11Buffer*
	*/
	[[nodiscard]] 
	ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

	/**
	@brief 2Dテクスチャ生成
	@param [in] Width : 幅
	@param [in] Height : 高さ
	@param [in] Format : テクスチャフォーマト
	@param [in] BindFlag :
	@param [in] Usage : デフォルトで　D3D11_USAGE_DEFAULT
	@return ID3D11Texture2D*
	*/
	[[nodiscard]] 
	ID3D11Texture2D* CreateTexture2D(UINT Width, UINT Height, DXGI_FORMAT Format, UINT BindFlag, D3D11_USAGE Usage = D3D11_USAGE_DEFAULT);

	/**
	@brief テクスチャの読み込み
	@param [in] filename : ファイルパス
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const std::string& filename);

	/**
	@brief テクスチャの読み込み
	@param [in] filename : ファイルパス
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const std::wstring& filename);

	/**
	@brief テクスチャの読み込み
	@param [in] filename : ファイルパス
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const char* filename);

	/**
	@brief テクスチャの読み込み
	@param [in] filename : ファイルパス
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const wchar_t* filename);

	/**
	@brief テクスチャの破棄
	@param [in] filename : ファイルパス
	*/
	void ReleaseTexture(const char* filename);

	/**
	@brief テクスチャの破棄
	@param [in] filename : ファイルパス
	*/
	void ReleaseTexture(const std::string& filename);

	/**
	@brief テクスチャの破棄
	@param [in] texture : テクスチャ
	*/
	void ReleaseTexture(const common::Texture& texture);

	/**
	@brief 入力レイアウト設定
	@param [in] VertexLayout : ID3D11InputLayout*
	*/
	void SetInputLayout(ID3D11InputLayout* VertexLayout);

	/**
	@brief シェーダ設定
	@param [in] vs : ID3D11VertexShader*
	*/
	void SetVertexShader(ID3D11VertexShader* vs);

	/**
	@brief シェーダ設定
	@param [in] ps : ID3D11PixelShader*
	*/
	void SetPixelShader(ID3D11PixelShader* ps);

	/**
	@brief シェーダ設定
	@param [in] gs : ID3D11PixelShader*
	*/
	void SetGeometryShader(ID3D11GeometryShader* gs);

	/**
	@brief バーテックスバッファ
	@param [in] VertexBuffer : ID3D11Buffer*
	@param [in] VertexSize : データ型のサイズ
	*/
	void SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize);

	/**
	@brief インデックスバッファ
	@param [in] IndexBuffer : ID3D11Buffer*
	*/
	void SetIndexBuffer(ID3D11Buffer* IndexBuffer);

	void VSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers);
	void GSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers);
	void PSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers);
	void CSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers);
	void SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
	void SetBlendState(const math::Vector4& blendFactor);

	/**
	@brief テクスチャの登録
	@param [in] RegisterNo : Register No
	@param [in] Texture : テクスチャ
	*/
	void SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture);

	void SetUpdateSubresource(ID3D11Buffer* buffer,
		UINT DstSubresource,
		D3D11_BOX* pDstBox,
		const void* pSrcData,
		UINT SrcRowPitch,
		UINT SrcDepthPitch);

	/**
	@brief 描画開始
	*/
	void DrawBegin();

	/**
	@brief 描画終了
	*/
	void DrawEnd();
	void Draw(UINT VertexNum);
	void DrawIndexed(UINT VertexNum);

	void ResizeBuffers(UINT lParam);
private:
	void CleanupRenderTarget();
	HRESULT CreateRenderTarget();
};

_MDX_SYSTEM_END