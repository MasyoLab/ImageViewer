//==========================================================================
// ピクセルシェーダーのマネージャー [PixelShaderManager.cpp]
// author : MasyoLab
//==========================================================================
#include "PixelShaderManager.h"

_MDX_SYSTEM_BEGIN

namespace common
{
	PixelShaderManager::PixelShaderManager(DirectXDevice device) :
		m_device(device)
	{
	}

	PixelShaderManager::~PixelShaderManager()
	{
	}

	PixelShader PixelShaderManager::CreatePixelShader(const std::string& cso_file_path)
	{
		// シェーダーが生成済みかをチェック
		auto comShader = get(cso_file_path);
		// シェーダーが存在する場合終了
		if (comShader != nullptr)
			return comShader;

		// 以下読み込み処理
		ID3D11PixelShader* pShader = nullptr;
		LoadCso load(cso_file_path);

		auto hr = m_device->CreatePixelShader(load.GetData(), load.GetSize(), nullptr, &pShader);
		assert(SUCCEEDED(hr));
		if (FAILED(hr))
			return nullptr;

		comShader.Attach(pShader);
		return set(cso_file_path, comShader);
	}

	PixelShader PixelShaderManager::CompilePixelShader(const std::string& filename, const std::string& entrypath, bool erorr)
	{
		// シェーダーが生成済みかをチェック
		auto comShader = get(filename);
		// シェーダーが存在する場合終了
		if (comShader != nullptr)
			return comShader;

		ID3D11PixelShader* pShader = nullptr;

#if defined(_DEBUG)
		// グラフィックデバッグツールによるシェーダーのデバッグを有効にする
		UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
		UINT compileFlags = 0;
#endif
		ComPtr<ID3DBlob> blob;
		wchar_t ws[512];

		setlocale(LC_CTYPE, "jpn");
		mbstowcs(ws, filename.c_str(), 512);
		ComPtr<ID3DBlob> pErrorBlob = nullptr;
		HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entrypath.c_str(), "ps_5_0", compileFlags, 0, &blob, &pErrorBlob);

		// エラーチェック
		if (FAILED(hr))
		{
			if (erorr)
			{
				// エラーメッセージを出力
				if (pErrorBlob != nullptr && erorr)
				{
					MessageBox(nullptr, (char*)pErrorBlob->GetBufferPointer(), "", 0);
					return nullptr;
				}
			}
			else
			{
				std::string er = (char*)pErrorBlob->GetBufferPointer();
				if (er.find("entrypoint not found") == std::string::npos)
					MessageBox(nullptr, (char*)pErrorBlob->GetBufferPointer(), "", 0);
				std::cout << filename << "(" << entrypath << ") is notfound" << std::endl;
				return nullptr;
			}
		}

		hr = m_device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pShader);
		assert(SUCCEEDED(hr));

		comShader.Attach(pShader);
		return set(filename, comShader);
	}
}

_MDX_SYSTEM_END