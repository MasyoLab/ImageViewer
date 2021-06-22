//==========================================================================
// DirectX11�̃}�l�[�W���[ [DirectX11Manager.cpp]
// author : MasyoLab
//==========================================================================
#include "DirectX11Manager.h"

_MDX_SYSTEM_BEGIN
_MDX_USING_COMMON
_MDX_USING_STRUCTURE

using namespace mdx::system::common;

DirectX11Manager::DirectX11Manager()
{
}

DirectX11Manager::~DirectX11Manager()
{
}

HRESULT DirectX11Manager::Init(const std::string& strWindowName, int width, int height, DWORD style, WNDCLASSEX wcex, HINSTANCE hInstance, int cCmdShow)
{
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	RECT wr = { 0, 0, width, height }, dr;

	AdjustWindowRect(&wr, style, wcex.lpszMenuName != nullptr ? true : false);
	wr.right = (wr.right - wr.left);
	wr.bottom = (wr.bottom - wr.top);
	wr.left = 0;
	wr.top = 0;

	//�f�X�N�g�b�v�T�C�Y�K��
	GetWindowRect(GetDesktopWindow(), &dr);

	// �����ʒu�C��
	wr.left = dr.right / 2;
	wr.top = dr.bottom / 2;
	wr.left -= wr.right / 2;
	wr.top -= wr.bottom / 2;

	m_hWnd = CreateWindow(wcex.lpszClassName, strWindowName.c_str(), style,
		wr.left, wr.top, wr.right, wr.bottom,
		nullptr, nullptr, hInstance, nullptr);
	if (!m_hWnd)
		return E_FAIL;

	ShowWindow(m_hWnd, cCmdShow);
	UpdateWindow(m_hWnd);
#pragma region HardWare Check
	IDXGIFactory* factory = nullptr;
	IDXGIAdapter* adapter = nullptr;
	IDXGIOutput* adapterOutput = nullptr;
	unsigned int numModes = 0;
	size_t stringLength;
	DXGI_ADAPTER_DESC adapterDesc;

	// �O���t�B�b�N �C���^�t�F�[�X �t�@�N�g�����쐬
	auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr))
		return hr;

	int GPUNumber = 0;
	int GPUMaxMem = 0;

	// ��ԋ���GPU�A�_�v�^������
	for (int i = 0; i < 100; i++)
	{
		IDXGIAdapter* add = nullptr;
		hr = factory->EnumAdapters(i, &add);
		if (FAILED(hr))
			break;
		hr = add->GetDesc(&adapterDesc);

		char videoCardDescription[128];

		// �r�f�I�J�[�h�����擾
		int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
		if (error != 0)
			break;
		std::cout << "�r�f�I�J�[�h�� : " << videoCardDescription << std::endl;

		// �r�f�I�J�[�h���������擾�iMB�P�ʁj
		int videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
		std::cout << "�r�f�I�������[ : " << videoCardMemory << std::endl;

		// �A�E�g�v�b�g�i���j�^�[�j�ɔԍ�ID��t����
		hr = add->EnumOutputs(0, &adapterOutput);
		if (FAILED(hr))
			continue;

		// DXGI_FORMAT_R8G8B8A8_UNORM �̕\���`�������擾����
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
		if (FAILED(hr))
			continue;
		std::cout << "RBGA8_UNORM Count : " << numModes << std::endl;

		if (videoCardMemory > GPUMaxMem)
		{
			GPUMaxMem = videoCardMemory;
			GPUNumber = i;
		}
		add->Release();

		// �A�_�v�^�A�E�g�v�b�g�����
		adapterOutput->Release();
		adapterOutput = nullptr;
	}

	// �O���t�B�b�N �C���^�t�F�[�X �A�_�v�^�[���쐬
	hr = factory->EnumAdapters(GPUNumber, &adapter);
	if (FAILED(hr))
		return hr;
#pragma endregion

#pragma region DirectX11Init
	UINT cdevFlags = 0;
#ifdef _DEBUG
	cdevFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	// �X���b�v�`�F�C���ݒ�
	DXGI_SWAP_CHAIN_DESC swapChain;
	ZeroMemory(&swapChain, sizeof(swapChain));
	swapChain.BufferCount = 1; // �o�b�t�@��
	swapChain.BufferDesc.Width = static_cast<UINT>(width); // �𑜓x��
	swapChain.BufferDesc.Height = static_cast<UINT>(height); // �𑜓x����
	swapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �\���t�H�[�}�b�g�@4�v�f��������32�r�b�g
	swapChain.BufferDesc.RefreshRate.Numerator = 1000; // ���t���b�V�����[�g�̍ő�L�����@�ύX�\�ȏꍇ�̂݉�ʂ̃��t���b�V�����[�g�����̒l�ɕύX����
	swapChain.BufferDesc.RefreshRate.Denominator = 1;	// 1/60 = 60fps // ���t���b�V�����[�g�̍ŏ��L����
	swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // �o�b�N�o�b�t�@�̃T�[�t�F�X�g�p�@CPU�A�N�Z�X�I�v�V������ݒ肷��@�o�͂Ŏg���悤�ɂ���
	swapChain.OutputWindow = m_hWnd; // �o�͂���E�B���h�E�̃n���h��
	swapChain.SampleDesc.Count = 1; // �s�N�Z���P�ʂ̃T���v�����O��
	swapChain.SampleDesc.Quality = 0; // �C���[�W�i���@-1�`0�܂Ŏw��ł���
	swapChain.Windowed = true; // �E�B���h�E���[�h�ŋN������
	swapChain.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
	};

	// DirectX11�f�o�C�X�ƃX���b�v�`�F�C���쐬
	hr = D3D11CreateDeviceAndSwapChain(
		adapter,					// �r�f�I�A�_�v�^�w��(nullptr�͊���)
		D3D_DRIVER_TYPE_UNKNOWN,	// �h���C�o�̃^�C�v
		nullptr,					// D3D_DRIVER_TYPE_SOFTWARE�w�莞�Ɏg�p
		cdevFlags,					// �t���O�w��
		featureLevels,				// D3D_FEATURE_LEVEL�w��Ŏ����Œ�`�����z����w��\
		1,							// ���D3D_FEATURE_LEVEL�z��̗v�f��
		D3D11_SDK_VERSION,			// SDK�o�[�W����
		&swapChain,					// DXGI_SWAP_CHAIN_DESC
		&m_SwapChain,				// �֐���������SwapChain�̏o�͐�
		&m_Device,					// �֐���������Device�̏o�͐�
		nullptr,					// ��������D3D_FEATURE_LEVEL�̏o�͐�
		&m_DeviceContext			// �֐���������Context�̏o�͐�
	);			
	if (FAILED(hr))
		return hr;

	// �A�_�v�^�����
	adapter->Release();
	adapter = nullptr;

	// �t�@�N�g�������
	factory->Release();
	factory = nullptr;

	// �X�e���V���p�e�N�X�`���[�̐ݒ�i�[�w�o�b�t�@�j
	D3D11_TEXTURE2D_DESC texture2dDesc;
	ZeroMemory(&texture2dDesc, sizeof(texture2dDesc));
	texture2dDesc.Width = static_cast<UINT>(width);
	texture2dDesc.Height = static_cast<UINT>(height);
	texture2dDesc.MipLevels = 1; // �~�b�v�}�b�v�̃��x���w��
	texture2dDesc.ArraySize = 1; // �e�N�X�`���z��̃T�C�Y�w��
	texture2dDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT; // �e�N�X�`���̃t�H�[�}�b�g
	texture2dDesc.SampleDesc = swapChain.SampleDesc; // �}���`�T���v�����O�ݒ�
	texture2dDesc.Usage = D3D11_USAGE_DEFAULT;
	texture2dDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	texture2dDesc.CPUAccessFlags = 0; // ���\�[�X�ւ�CPU�̃A�N�Z�X�����ɂ��Ă̐ݒ�
	texture2dDesc.MiscFlags = 0; // ���\�[�X�I�v�V�����̃t���O

	// �X�e���V���p�e�N�X�`���̍쐬�i�[�w�o�b�t�@�j
	hr = m_Device->CreateTexture2D(&texture2dDesc, nullptr, &m_Texture2DDepth);
	if (FAILED(hr))
		return hr;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	// �X�e���V���X�e�[�g�̏����� (3D�p)
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

	// �X�e���V���X�e�[�g�ݒ�
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// �X�e���V���X�e�[�g�쐬
	hr = m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);
	if (FAILED(hr))
		return hr;

	// �X�e���V���^�[�Q�b�g�쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = texture2dDesc.Format;

	/*
		DSV���������ł��邩��Texture�̎�ނ�ݒ肷��l
		D3D11_DSV_DIMENSION_TEXTURE2D
		D3D11_DSV_DIMENSION_TEXTURE1D
		D3D11_DSV_DIMENSION_TEXTURE2D_ARRAY
		D3D11_DSV_DIMENSION_TEXTURE2DMS
	*/
	//depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	// �ŏ��Ɏg�p����~�b�v�}�b�v�̃��x�����w�� 
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	depthStencilViewDesc.Flags = 0;
	hr = m_Device->CreateDepthStencilView(m_Texture2DDepth.Get(), &depthStencilViewDesc, &m_DepthStencilView);
	if (FAILED(hr))
		return hr;

	// �����_�[�^�[�Q�b�g�̍쐬
	hr = CreateRenderTarget();
	if (FAILED(hr))
		return hr;

	// viewport
	m_Viewport.Width = static_cast<FLOAT>(width);
	m_Viewport.Height = static_cast<FLOAT>(height);
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;

	// ���X�^���C�U�ݒ�
	D3D11_RASTERIZER_DESC rasterizerDesc = {
		D3D11_FILL_SOLID, // 3�̒��_������ŏo�����O�p�`��h��Ԃ�
		D3D11_CULL_NONE, // �\�ʂƗ��ʂ̗�����`�悷��
		FALSE,
		0,
		0.0f,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE
	};
	hr = m_Device->CreateRasterizerState(&rasterizerDesc, &m_RasterizerState);
	if (FAILED(hr))
		return hr;

	// �T���v���[�쐬
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampDesc.MipLODBias = 0.0f;
	sampDesc.MaxAnisotropy = 1;
	//sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.BorderColor[0] = 0;
	sampDesc.BorderColor[1] = 0;
	sampDesc.BorderColor[2] = 0;
	sampDesc.BorderColor[3] = 0;
	sampDesc.MinLOD = FLT_MIN;
	sampDesc.MaxLOD = FLT_MAX;
	hr = m_Device->CreateSamplerState(&sampDesc, &m_Sampler);
	if (FAILED(hr))
		return hr;

	// �f�t�H���g�̃u�����h�ݒ�
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = true; // �摜�̎���̓����𖳌���
	BlendDesc.IndependentBlendEnable = false; // 
	BlendDesc.RenderTarget[0].BlendEnable = true;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = m_Device->CreateBlendState(&BlendDesc, &m_BlendState);

	if (FAILED(hr))
		return hr;
#pragma endregion

	m_ImGuiInitializer.Broadcast(m_hWnd, m_Device, m_DeviceContext);

	return hr;
}

const D3D11_VIEWPORT& DirectX11Manager::GetViewport() const
{
	return m_Viewport;
}

VertexShader DirectX11Manager::CreateVertexShader(const std::string& cso_file_path)
{
	if (m_VertexShaderManager == nullptr)
		m_VertexShaderManager = new VertexShaderManager(m_Device);
	return m_VertexShaderManager->CreateVertexShader(cso_file_path);
}

PixelShader DirectX11Manager::CreatePixelShader(const std::string& cso_file_path)
{
	if (m_PixelShaderManager == nullptr)
		m_PixelShaderManager = new PixelShaderManager(m_Device);
	return m_PixelShaderManager->CreatePixelShader(cso_file_path);
}

GeometryShader DirectX11Manager::CreateGeometryShader(const std::string& cso_file_path)
{
	if (m_GeometryShaderManager == nullptr)
		m_GeometryShaderManager = new GeometryShaderManager(m_Device);
	return m_GeometryShaderManager->CreateGeometryShader(cso_file_path);
}

ComputeShader DirectX11Manager::CreateComputeShader(const std::string& cso_file_path)
{
	if (m_ComputeShaderManager == nullptr)
		m_ComputeShaderManager = new ComputeShaderManager(m_Device);
	return m_ComputeShaderManager->CreateComputeShader(cso_file_path);
}

InputLayout DirectX11Manager::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& cso_file_path)
{
	if (m_InputLayoutManager == nullptr)
		m_InputLayoutManager = new InputLayoutManager(m_Device);
	return m_InputLayoutManager->CreateInputLayout(layout, elem_num, cso_file_path);
}

bool DirectX11Manager::CreateConstantBuffer(unsigned int bytesize, ID3D11Buffer** buffer) {
	// �R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;

	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = bytesize;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	HRESULT hr = m_Device->CreateBuffer(&bd, nullptr, buffer);
	if (FAILED(hr))
	{
		MessageBox(nullptr, "CreateBuffer(constant buffer) error", "Error", MB_OK);
		return false;
	}

	return true;
}

ID3D11Buffer* DirectX11Manager::CreateIndexBuffer(UINT* Index, UINT IndexNum)
{
	//�C���f�b�N�X�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = sizeof(UINT) * IndexNum;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	//bufferDesc.MiscFlags = 0;
	//bufferDesc.StructureByteStride = sizeof(UINT);

	D3D11_SUBRESOURCE_DATA subResourceData;
	ZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem = Index;
	//hSubResourceData.SysMemPitch = 0;
	//hSubResourceData.SysMemSlicePitch = 0;

	ID3D11Buffer* pBuffer = nullptr;
	if (FAILED(m_Device->CreateBuffer(&bufferDesc, &subResourceData, &pBuffer)))
		return nullptr;
	return pBuffer;
}

ID3D11Texture2D* DirectX11Manager::CreateTexture2D(UINT Width, UINT Height, DXGI_FORMAT Format, UINT BindFlag, D3D11_USAGE Usage)
{
	ID3D11Texture2D* texture = nullptr;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = Width;
	desc.Height = Height;
	desc.MipLevels = 1;
	desc.Format = Format;
	desc.Usage = Usage;
	desc.BindFlags = BindFlag;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	HRESULT hr = m_Device->CreateTexture2D(&desc, nullptr, &texture);
	if (FAILED(hr))
		return nullptr;
	return texture;
}

Texture DirectX11Manager::CreateTextureFromFile(const std::string& filename)
{
	if (m_ShaderTextureManager == nullptr)
		m_ShaderTextureManager = new ShaderTextureManager(m_Device);
	return m_ShaderTextureManager->CreateTextureFromFile(filename);
}

common::Texture DirectX11Manager::CreateTextureFromFile(const std::wstring& filename)
{
	if (m_ShaderTextureManager == nullptr)
		m_ShaderTextureManager = new ShaderTextureManager(m_Device);
	return m_ShaderTextureManager->CreateTextureFromFile(filename);
}

Texture DirectX11Manager::CreateTextureFromFile(const char* filename)
{
	if (m_ShaderTextureManager == nullptr)
		m_ShaderTextureManager = new ShaderTextureManager(m_Device);
	return m_ShaderTextureManager->CreateTextureFromFile(filename);
}

Texture DirectX11Manager::CreateTextureFromFile(const wchar_t* filename)
{
	if (m_ShaderTextureManager == nullptr)
		m_ShaderTextureManager = new ShaderTextureManager(m_Device);
	return m_ShaderTextureManager->CreateTextureFromFile(filename);
}

void DirectX11Manager::ReleaseTexture(const char* filename)
{
	if (m_ShaderTextureManager == nullptr)
		m_ShaderTextureManager->destroy(filename);
}

void DirectX11Manager::ReleaseTexture(const std::string& filename)
{
	if (m_ShaderTextureManager == nullptr)
		m_ShaderTextureManager->destroy(filename);
}

void DirectX11Manager::ReleaseTexture(const common::Texture& texture)
{
	if (m_ShaderTextureManager == nullptr)
		m_ShaderTextureManager->destroy(texture);
}

void DirectX11Manager::SetInputLayout(ID3D11InputLayout* VertexLayout)
{
	m_DeviceContext->IASetInputLayout(VertexLayout);
}

void DirectX11Manager::SetVertexShader(ID3D11VertexShader* vs)
{
	m_DeviceContext->VSSetShader(vs, nullptr, 0);
}

void DirectX11Manager::SetPixelShader(ID3D11PixelShader* ps)
{
	m_DeviceContext->PSSetShader(ps, nullptr, 0);
}

void DirectX11Manager::SetGeometryShader(ID3D11GeometryShader* gs)
{
	m_DeviceContext->GSSetShader(gs, nullptr, 0);
}

void DirectX11Manager::SetVertexBuffer(ID3D11Buffer* VertexBuffer, UINT VertexSize)
{
	UINT hOffsets = 0;
	m_DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexSize, &hOffsets);
}

void DirectX11Manager::SetIndexBuffer(ID3D11Buffer* IndexBuffer)
{
	m_DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

void DirectX11Manager::VSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers)
{
	m_DeviceContext->VSSetConstantBuffers(0, 1, &ppConstantBuffers);
}

void DirectX11Manager::GSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers)
{
	m_DeviceContext->GSSetConstantBuffers(0, 1, &ppConstantBuffers);
}

void DirectX11Manager::PSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers)
{
	m_DeviceContext->PSSetConstantBuffers(0, 1, &ppConstantBuffers);
}

void DirectX11Manager::CSSetConstantBuffers(ID3D11Buffer* ppConstantBuffers)
{
	m_DeviceContext->CSSetConstantBuffers(0, 1, &ppConstantBuffers);
}

void DirectX11Manager::SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
{
	m_DeviceContext->IASetPrimitiveTopology(Topology);
}

void DirectX11Manager::SetBlendState(const math::Vector4& blendFactor)
{
	float fblendFactor[4] = { blendFactor.x,blendFactor.y,blendFactor.z,blendFactor.w };
	m_DeviceContext->OMSetBlendState(m_BlendState.Get(), fblendFactor, 0xffffffff);
}

void DirectX11Manager::SetTexture2D(UINT RegisterNo, ID3D11ShaderResourceView* Texture)
{
	m_DeviceContext->PSSetShaderResources(RegisterNo, 1, &Texture);
}

void DirectX11Manager::SetUpdateSubresource(ID3D11Buffer* buffer,
	UINT DstSubresource,
	D3D11_BOX* pDstBox,
	const void* pSrcData,
	UINT SrcRowPitch,
	UINT SrcDepthPitch)
{
	m_DeviceContext->UpdateSubresource(buffer, DstSubresource, pDstBox, pSrcData, SrcRowPitch, SrcDepthPitch);
}

void DirectX11Manager::DrawBegin()
{
	//�|���S���̐������@�̎w��
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �w��F�ŉ�ʃN���A
	float clearColor[4] = { 0.1f, 0.1f, 0.1f, 1.f }; //red,green,blue,alpha
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
	float cloar[4] = { 0,0,0,1 };
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_DeviceContext->RSSetViewports(1, &m_Viewport);
	//���X�^���C�U�[���R���e�L�X�g�ɐݒ�
	m_DeviceContext->RSSetState(m_RasterizerState.Get());
	//�f�o�C�X�R���e�L�X�g�ɃZ�b�g����
	m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState.Get(), 1);

	//�T���v���[���Z�b�g
	ID3D11SamplerState* sampler = m_Sampler.Get();
	m_DeviceContext->PSSetSamplers(0, 1, &sampler);

	//RenderTarget���o�b�N�o�b�t�@
	ID3D11RenderTargetView* rtv[1] = { m_RenderTargetView.Get() };
	m_DeviceContext->OMSetRenderTargets(1, rtv, m_DepthStencilView.Get());
}

void DirectX11Manager::DrawEnd()
{
	m_SwapChain->Present(0, 0);
}

void DirectX11Manager::Draw(UINT VertexNum)
{
	m_DeviceContext->Draw(VertexNum, 0);
}

void DirectX11Manager::DrawIndexed(UINT VertexNum)
{
	m_DeviceContext->DrawIndexed(VertexNum, 0, 0);
}

void DirectX11Manager::ResizeBuffers(UINT lParam)
{
	if (m_Device == nullptr)
		return;
	CleanupRenderTarget();
	m_SwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
	CreateRenderTarget();
}

void DirectX11Manager::CleanupRenderTarget()
{
	m_RenderTargetView.Reset();
	m_RenderTargetTexture.Reset();
}

HRESULT DirectX11Manager::CreateRenderTarget()
{
	// �X���b�v�`�F�C���ɗp�ӂ��ꂽ�o�b�t�@ (2D�e�N�X�`��) ���擾
	HRESULT hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_RenderTargetTexture));
	if (FAILED(hr))
		return hr;

	// �����_�[�^�[�Q�b�gView�쐬
	return m_Device->CreateRenderTargetView(m_RenderTargetTexture.Get(), nullptr, &m_RenderTargetView);
}

_MDX_SYSTEM_END