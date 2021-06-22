//==========================================================================
// �R���s���[�g�V�F�[�_�[�̃}�l�[�W���[ [ComputeShaderManager.cpp]
// author : MasyoLab
//==========================================================================
#include "ComputeShaderManager.h"

_MDX_SYSTEM_BEGIN

namespace common
{
	ComputeShaderManager::ComputeShaderManager(DirectXDevice device) :
		m_device(device)
	{
	}

	ComputeShaderManager::~ComputeShaderManager()
	{
	}

	ComputeShader ComputeShaderManager::CreateComputeShader(const std::string& cso_file_path)
	{
		// �V�F�[�_�[�������ς݂����`�F�b�N
		auto comShader = get(cso_file_path);
		// �V�F�[�_�[�����݂���ꍇ�I��
		if (comShader != nullptr)
			return comShader;

		ID3D11ComputeShader* pShader = nullptr;
		LoadCso load(cso_file_path);

		auto hr = m_device->CreateComputeShader(load.GetData(), load.GetSize(), nullptr, &pShader);
		assert(SUCCEEDED(hr));
		if (FAILED(hr))
			return nullptr;

		comShader.Attach(pShader);
		return set(cso_file_path, comShader);
	}

	ComputeShader ComputeShaderManager::CompileComputeShader(const std::string& filename, const std::string& entrypath)
	{
		// �V�F�[�_�[�������ς݂����`�F�b�N
		auto comShader = get(filename);
		// �V�F�[�_�[�����݂���ꍇ�I��
		if (comShader != nullptr)
			return comShader;

		ID3D11ComputeShader* pShader = nullptr;

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
		HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "cs_5_0", compileFlags, 0, &blob, &pErrorBlob);
		// �G���[�`�F�b�N.
		if (FAILED(hr))
		{
			std::string er = (char*)pErrorBlob->GetBufferPointer();
			if (er.find("entrypoint not found") == std::string::npos)
				MessageBox(nullptr, (char*)pErrorBlob->GetBufferPointer(), "", 0);
			std::cout << filename << "(" << entrypath << ") is notfound" << std::endl;
			return nullptr;
		}

		hr = m_device->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pShader);
		assert(SUCCEEDED(hr));

		comShader.Attach(pShader);
		return set(filename, comShader);
	}
}

_MDX_SYSTEM_END