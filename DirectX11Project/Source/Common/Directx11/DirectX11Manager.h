//==========================================================================
// DirectX11�̃}�l�[�W���[ [DirectX11Manager.h]
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
// Content : DirectX11�̃}�l�[�W���[
// details : �p���֎~
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
	structure::DirectXDevice		m_Device = nullptr; // �f�o�C�X
	ComPtr<ID3D11DeviceContext>		m_DeviceContext = nullptr; // �f�o�C�X�R���e�L�X�g
	ComPtr<IDXGISwapChain>			m_SwapChain = nullptr; // �X���b�v�`�F�C��
	structure::Texture2D			m_RenderTargetTexture = nullptr; // �����_�[�^�[�Q�b�g
	ComPtr<ID3D11RenderTargetView>	m_RenderTargetView = nullptr; // �r���[
	D3D11_VIEWPORT					m_Viewport = { 0,0,0,0,0,0 }; // �r���[�|�[�g
	ComPtr<ID3D11RasterizerState>	m_RasterizerState = nullptr; // ���X�^���C�Y
	ComPtr<ID3D11BlendState>		m_BlendState; // �u�����h�X�e�[�g

	// Z�o�b�t�@
	ComPtr<ID3D11Texture2D>			m_Texture2DDepth = nullptr; // �X�e���V���p�e�N�X�`��
	ComPtr<ID3D11DepthStencilState>	m_DepthStencilState = nullptr;	// �y�o�b�t�@�A�X�e���V���X�e�[�g
	ComPtr<ID3D11DepthStencilView>	m_DepthStencilView = nullptr; // �r���[

	// �T���v���[
	ComPtr<ID3D11SamplerState>		m_Sampler = nullptr; // �ʏ�e�N�X�`��(0-1�T���v�����O)
public:
	ImGuiInitializer m_ImGuiInitializer;
public:
	DirectX11Manager();
	~DirectX11Manager();
	/**
	@brief ������
	@param [in] strWindowName : �E�B���h�E��
	@param [in] hInstance : Instance
	@param [in] cCmdShow : CmdShow
	@return �������ǂ���
	*/
	HRESULT Init(const std::string& strWindowName, int width, int height, DWORD style, WNDCLASSEX wcex, HINSTANCE hInstance, int cCmdShow);

	const D3D11_VIEWPORT& GetViewport() const;

	/**
	@brief �o�[�e�b�N�X�V�F�[�_�[����
	@param [in] cso_file_path : .cos�̃t�@�C���p�X
	@return VertexShader
	*/
	structure::VertexShader CreateVertexShader(const std::string& cso_file_path);

	/**
	@brief �s�N�Z���V�F�[�_�[����
	@param [in] cso_file_path : .cos�̃t�@�C���p�X
	@return PixelShader
	*/
	structure::PixelShader CreatePixelShader(const std::string& cso_file_path);

	/**
	@brief �W�I���g���V�F�[�_�[����
	@param [in] cso_file_path : .cos�̃t�@�C���p�X
	@return GeometryShader
	*/
	structure::GeometryShader CreateGeometryShader(const std::string& cso_file_path);

	/**
	@brief �R���s���[�g�V�F�[�_�[����
	@param [in] cso_file_path : .cos�̃t�@�C���p�X
	@return ComputeShader
	*/
	structure::ComputeShader CreateComputeShader(const std::string& cso_file_path);

	/**
	@brief ���̓��C�A�E�g�쐬
	@param [in] layout : D3D11_INPUT_ELEMENT_DESC
	@param [in] elem_num : D3D11_INPUT_ELEMENT_DESC �̃T�C�Y
	@param [in] cso_file_path : .cos�̃t�@�C���p�X
	@return InputLayout
	*/
	structure::InputLayout CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& cso_file_path);

	/**
	@brief �R���X�^���g�o�b�t�@���쐬
	@param [in] bytesize : Byte Width
	@param [in] buffer : ID3D11Buffer
	@return �����������ǂ���
	*/
	bool CreateConstantBuffer(unsigned int bytesize, ID3D11Buffer** buffer);

	/**
	@brief ���_�o�b�t�@����
	@param [in] VertexData : ���_�f�[�^
	@param [in] VertexNum : ���_��
	@return ID3D11Buffer*
	*/
	template<class _Ty>
	[[nodiscard]] 
	ID3D11Buffer* CreateVertexBuffer(_Ty* VertexData, UINT VertexNum)
	{
		// ���_�o�b�t�@�쐬
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
	@brief �C���f�b�N�X�o�b�t�@����
	@param [in] Index : �C���f�b�N�X�f�[�^
	@param [in] IndexNum : �C���f�b�N��
	@return ID3D11Buffer*
	*/
	[[nodiscard]] 
	ID3D11Buffer* CreateIndexBuffer(UINT* Index, UINT IndexNum);

	/**
	@brief 2D�e�N�X�`������
	@param [in] Width : ��
	@param [in] Height : ����
	@param [in] Format : �e�N�X�`���t�H�[�}�g
	@param [in] BindFlag :
	@param [in] Usage : �f�t�H���g�Ł@D3D11_USAGE_DEFAULT
	@return ID3D11Texture2D*
	*/
	[[nodiscard]] 
	ID3D11Texture2D* CreateTexture2D(UINT Width, UINT Height, DXGI_FORMAT Format, UINT BindFlag, D3D11_USAGE Usage = D3D11_USAGE_DEFAULT);

	/**
	@brief �e�N�X�`���̓ǂݍ���
	@param [in] filename : �t�@�C���p�X
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const std::string& filename);

	/**
	@brief �e�N�X�`���̓ǂݍ���
	@param [in] filename : �t�@�C���p�X
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const std::wstring& filename);

	/**
	@brief �e�N�X�`���̓ǂݍ���
	@param [in] filename : �t�@�C���p�X
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const char* filename);

	/**
	@brief �e�N�X�`���̓ǂݍ���
	@param [in] filename : �t�@�C���p�X
	@return Texture
	*/
	common::Texture CreateTextureFromFile(const wchar_t* filename);

	/**
	@brief �e�N�X�`���̔j��
	@param [in] filename : �t�@�C���p�X
	*/
	void ReleaseTexture(const char* filename);

	/**
	@brief �e�N�X�`���̔j��
	@param [in] filename : �t�@�C���p�X
	*/
	void ReleaseTexture(const std::string& filename);

	/**
	@brief �e�N�X�`���̔j��
	@param [in] texture : �e�N�X�`��
	*/
	void ReleaseTexture(const common::Texture& texture);

	/**
	@brief ���̓��C�A�E�g�ݒ�
	@param [in] VertexLayout : ID3D11InputLayout*
	*/
	void SetInputLayout(ID3D11InputLayout* VertexLayout);

	/**
	@brief �V�F�[�_�ݒ�
	@param [in] vs : ID3D11VertexShader*
	*/
	void SetVertexShader(ID3D11VertexShader* vs);

	/**
	@brief �V�F�[�_�ݒ�
	@param [in] ps : ID3D11PixelShader*
	*/
	void SetPixelShader(ID3D11PixelShader* ps);

	/**
	@brief �V�F�[�_�ݒ�
	@param [in] gs : ID3D11PixelShader*
	*/
	void SetGeometryShader(ID3D11GeometryShader* gs);

	/**
	@brief �o�[�e�b�N�X�o�b�t�@
	@param [in] VertexBuffer : ID3D11Buffer*
	@param [in] VertexSize : �f�[�^�^�̃T�C�Y
	*/
	void SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize);

	/**
	@brief �C���f�b�N�X�o�b�t�@
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
	@brief �e�N�X�`���̓o�^
	@param [in] RegisterNo : Register No
	@param [in] Texture : �e�N�X�`��
	*/
	void SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture);

	void SetUpdateSubresource(ID3D11Buffer* buffer,
		UINT DstSubresource,
		D3D11_BOX* pDstBox,
		const void* pSrcData,
		UINT SrcRowPitch,
		UINT SrcDepthPitch);

	/**
	@brief �`��J�n
	*/
	void DrawBegin();

	/**
	@brief �`��I��
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