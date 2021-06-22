//==========================================================================
// �V�F�[�_�[�e�N�X�`�� [ShaderTextureManager.cpp]
// author : MasyoLab
//==========================================================================
#include "ShaderTextureManager.h"

_MDX_SYSTEM_BEGIN

namespace common
{
	constexpr int string_size = 2048;

	ShaderTextureManager::ShaderTextureManager(DirectXDevice device) :
		m_device(device)
	{
	}

	ShaderTextureManager::~ShaderTextureManager()
	{
	}

	Texture ShaderTextureManager::CreateTextureFromFile(const std::wstring& filename)
	{
		if (filename.empty())
			return nullptr;
		return CreateTextureFromFile(filename.c_str());
	}

	Texture ShaderTextureManager::CreateTextureFromFile(const wchar_t* filename)
	{
		ID3D11ShaderResourceView* shaderResView = nullptr;

		char ms[string_size];
		setlocale(LC_CTYPE, "jpn");
		wcstombs(ms, filename, string_size);
		char* extension = strstr(ms, "."); // �g���q�`�F�b�N

		if (extension == nullptr)
			return nullptr;

		if (strcmp(extension, ".tga") == 0 || strcmp(extension, ".TGA") == 0)
		{
			TexMetadata meta;
			GetMetadataFromTGAFile(filename, meta);

			std::unique_ptr<ScratchImage> image(new ScratchImage);
			HRESULT hr = LoadFromTGAFile(filename, &meta, *image);
			if (FAILED(hr))
				return nullptr;
			hr = CreateShaderResourceView(m_device.Get(), image->GetImages(), image->GetImageCount(), meta, &shaderResView);
			if (FAILED(hr))
				return nullptr;
			return Texture(*image->GetImages(), shaderResView);
		}
		else if (strcmp(extension, ".dds") == 0 || strcmp(extension, ".DDS") == 0)
		{
			TexMetadata meta;
			GetMetadataFromDDSFile(filename, 0, meta);

			std::unique_ptr<ScratchImage> image(new ScratchImage);
			HRESULT hr = LoadFromDDSFile(filename, 0, &meta, *image);
			if (FAILED(hr))
				return nullptr;
			hr = CreateShaderResourceView(m_device.Get(), image->GetImages(), image->GetImageCount(), meta, &shaderResView);
			if (FAILED(hr))
				return nullptr;
			return Texture(*image->GetImages(), shaderResView);
		}
		else
		{
			TexMetadata meta;
			GetMetadataFromWICFile(filename, 0, meta);

			std::unique_ptr<ScratchImage> image(new ScratchImage);
			HRESULT hr = LoadFromWICFile(filename, 0, &meta, *image);
			if (FAILED(hr))
				return nullptr;
			hr = CreateShaderResourceView(m_device.Get(), image->GetImages(), image->GetImageCount(), meta, &shaderResView);
			if (FAILED(hr))
				return nullptr;
			return Texture(*image->GetImages(), shaderResView);
		}
	}

	Texture ShaderTextureManager::CreateTextureFromFile(const std::string& filename)
	{
		if (filename.empty())
			return nullptr;
		return CreateTextureFromFile(filename.c_str());
	}

	Texture ShaderTextureManager::CreateTextureFromFile(const char* filename)
	{
		// �e�N�X�`���������ς݂����`�F�b�N
		auto comTexture = get(filename);
		// �e�N�X�`�������݂���ꍇ�I��
		if (comTexture != nullptr)
			return comTexture;

		wchar_t ws[string_size];
		setlocale(LC_CTYPE, "jpn");
		mbstowcs(ws, filename, string_size);
		return set(filename, CreateTextureFromFile(ws));
	}
}

_MDX_SYSTEM_END