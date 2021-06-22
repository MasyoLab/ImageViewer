//==========================================================================
// �C���v�b�g���C�A�E�g [InputLayoutManager.cpp]
// author : MasyoLab
//==========================================================================
#include "InputLayoutManager.h"

_MDX_SYSTEM_BEGIN

namespace common
{
	InputLayoutManager::InputLayoutManager(DirectXDevice device) :
		m_device(device)
	{
	}

	InputLayoutManager::~InputLayoutManager()
	{
	}

	InputLayout InputLayoutManager::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& cso_file_path)
	{
		// �V�F�[�_�[�������ς݂����`�F�b�N
		auto comShader = get(cso_file_path);
		// �V�F�[�_�[�����݂���ꍇ�I��
		if (comShader != nullptr)
			return comShader;

		// �ȉ��ǂݍ��ݏ���
		ID3D11InputLayout* pShader = nullptr;
		LoadCso load(cso_file_path);

		auto hr = m_device->CreateInputLayout(layout, elem_num, load.GetData(), load.GetSize(), &pShader);
		assert(SUCCEEDED(hr));
		if (FAILED(hr))
			return nullptr;

		comShader.Attach(pShader);
		return set(cso_file_path, comShader);
	}

	InputLayout InputLayoutManager::CompileInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const std::string& filename, const std::string& entrypath)
	{
		// ���C�A�E�g�������ς݂����`�F�b�N
		auto comLayout = get(filename);
		// ���C�A�E�g�����݂���ꍇ�I��
		if (comLayout != nullptr)
			return comLayout;

		ID3D11InputLayout* pVertexLayout = nullptr;

#if defined(_DEBUG)
		// �O���t�B�b�N�f�o�b�O�c�[���ɂ��V�F�[�_�[�̃f�o�b�O��L���ɂ���
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif
		ComPtr<ID3DBlob> blob;
		wchar_t ws[512];

		setlocale(LC_CTYPE, "jpn");
		mbstowcs(ws, filename.c_str(), 512);
		ComPtr<ID3DBlob> pErrorBlob = nullptr;
		HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "vs_5_0", compileFlags, 0, &blob, &pErrorBlob);

		// �G���[�`�F�b�N
		if (FAILED(hr))
			// �G���[���b�Z�[�W���o��
			if (pErrorBlob != nullptr)
				MessageBox(nullptr, (char*)pErrorBlob->GetBufferPointer(), "", 0);

		hr = m_device->CreateInputLayout(layout, elem_num, blob->GetBufferPointer(), blob->GetBufferSize(), &pVertexLayout);
		assert(SUCCEEDED(hr));

		comLayout.Attach(pVertexLayout);
		return set(filename, comLayout);
	}
}

_MDX_SYSTEM_END