//==========================================================================
// �r���A�[ [ImageViewer.cpp]
// author : MasyoLab
//==========================================================================
#include "ImageViewer.h"

constexpr size_t viewDataMax = 3; // �r���[�̍ő�l
constexpr size_t defaultNumCash = viewDataMax + 2; // �r���[�̍ő�l
constexpr size_t textureNumCash = viewDataMax + (50 - viewDataMax); // �e�N�X�`���̃L���b�V����
constexpr float defaultImageButtonSize = 200; // �{�^���̃T�C�Y
constexpr float defaultPopImageSize = 500; // �|�b�v�A�b�v�T�C�Y
constexpr float imageWindowSize = defaultImageButtonSize + defaultPopImageSize; // �摜window�T�C�Y
constexpr mdx_imgui::ImGuiWindowFlags_ viewerFlag = mdx_imgui::ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar | mdx_imgui::ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings;

ImageViewer::ImageViewer()
{
	SetObjectName("ImageViewer");
	m_viewData.reserve(viewDataMax);

	// �����Z���k�E�c�C�X�^�[�@�ɂ��[��������������A
	// �n�[�h�E�F�A�������V�[�h�ɂ��ď�����
	m_engine = std::mt19937(m_seed_gen());
	m_textureNumCash = defaultNumCash;
	m_updateTime = 5;
	m_MemoryOver = true;
}

ImageViewer::~ImageViewer()
{
	if (m_function.joinable())
		m_function.join();

	std::ofstream outputfile;
	outputfile.open("Assets/data.bin", std::ios::out | std::ios::binary | std::ios::trunc);
	if (!outputfile)
		return;
	
	outputfile.write((char*)&m_textureNumCash, sizeof(m_textureNumCash));
	outputfile.write((char*)&m_updateTime, sizeof(m_updateTime));
	outputfile.write((char*)&m_InitializerData, sizeof(m_InitializerData));
	outputfile.write((char*)&m_OpenMemoryMindow, sizeof(m_OpenMemoryMindow));
	outputfile.write((char*)&m_MemoryOver, sizeof(m_MemoryOver));
	outputfile.close();
}

void ImageViewer::Init()
{
	m_CheckAllFile = m_GameObject->AddComponent(new check_all_file::CheckAllFile);
	m_transform = m_GameObject->GetComponent<mdx::component::Transform>();
	m_GuiInfo = m_GameObject->AddComponent(new GuiInfo);

	std::ifstream inputfile;
	inputfile.open("Assets/data.bin", std::ios::in | std::ios::binary);
	if (inputfile)
	{
		inputfile.read((char*)&m_textureNumCash, sizeof(m_textureNumCash));
		inputfile.read((char*)&m_updateTime, sizeof(m_updateTime));
		inputfile.read((char*)&m_InitializerData, sizeof(m_InitializerData));
		inputfile.read((char*)&m_OpenMemoryMindow, sizeof(m_OpenMemoryMindow));
		inputfile.read((char*)&m_MemoryOver, sizeof(m_MemoryOver));
		inputfile.close();
	}

	if (m_InitializerData)
	{
		m_textureNumCash = defaultNumCash;
		m_updateTime = 5;
		m_OpenMemoryMindow = false;
		m_MemoryOver = true;
	}

	m_GuiInfo->SetMemoryMindowFlag(m_OpenMemoryMindow);

	FirstLoad();
}

void ImageViewer::Update()
{
	if (m_Manager == nullptr)
		return;

	if (m_MemoryOver)
	{
		// �������s���ɂȂ�Ȃ�A�L���b�V���\�Ȑ��𔼕��ɂ���
		if (m_GuiInfo->IsInsufficientMemory() && !m_RefreshMemory)
			m_textureNumCash = (int)((m_textureNumCash / 2) + 0.5f);
		m_RefreshMemory = m_GuiInfo->IsInsufficientMemory();
	}

	DeleteCash();

	if (m_updateTime < m_timeCount)
	{
		SwapData();
		ResetTransform();
		m_timeCount = 0;
	}
	GUI();
	m_timeCount += mdx::system::clock::GetDeltaTime();
}

mdx::math::Vector2 ImageViewer::SizeCorrection(size_t width, size_t height, const mdx::math::Vector2& standardSize, bool standardControl)
{
	return SizeCorrection({ width * 1.0f, height * 1.0f }, standardSize, standardControl);
}

mdx::math::Vector2 ImageViewer::SizeCorrection(const mdx::math::Vector2& size, const mdx::math::Vector2& standardSize, bool standardControl)
{
	if (standardControl)
	{
		// ��ƂȂ�T�C�Y��菬�����Ȃ�A�␳�����Ȃ�
		if (size.x < standardSize.x && size.y < standardSize.y)
			return size;
	}

	float correctionReferenceValue = 0.1f;
	mdx::math::Vector2 newSize;

	// �~���P�ʂŕ␳����
	for (auto additionalSize = size;; correctionReferenceValue *= 0.1f)
	{
		// �␳�l
		additionalSize = size * correctionReferenceValue;

		// �X�N���[�����T�C�Y�𒴂���܂�
		for (; newSize.x < standardSize.x && newSize.y < standardSize.y; newSize += additionalSize);

		// ���̎��_�Œ����Ă���̂ň�O�ɖ߂�
		newSize -= additionalSize;

		bool bIsClearX = standardSize.x - 1 < newSize.x && newSize.x < standardSize.x + 1;
		bool bIsClearY = standardSize.y - 1 < newSize.y && newSize.y < standardSize.y + 1;

		if (bIsClearX == true || bIsClearY == true)
			return newSize;
	}

	return newSize;
}

void ImageViewer::SwapData()
{
	// �f�[�^�������Ȃ�
	if (m_CheckAllFile->Length() == 0)
		return;

	// ���炷�f�[�^������
	if (m_viewData.size() == 0)
		return;

	// �擪�̃f�[�^�̃t���O
	if (m_viewData[0].cash != nullptr)
		m_viewData[0].cash->IsOpen = false;

	// �f�[�^�����炷
	for (size_t i = 1; i < m_viewData.size(); i++)
	{
		m_viewData[i - 1].texture = m_viewData[i].texture;
		m_viewData[i - 1].iterator = m_viewData[i].iterator;
		m_viewData[i - 1].cash = m_viewData[i].cash;
		m_viewData[i - 1].imageSize = m_viewData[i].imageSize;
	}

	const size_t backDataIndex = m_viewData.size() - 1; // ����Index

	// �f�[�^�̍Ō���̃f�[�^��iterator�������Ȃ�
	if (m_viewData[backDataIndex].iterator == m_CheckAllFile->GetData().end())
		m_viewData[backDataIndex].iterator = m_CheckAllFile->GetRandomIterator(m_engine);

	// ����iterator���X�V
	for (auto itr = ++m_viewData[backDataIndex].iterator;; ++itr)
	{
		if (itr == m_CheckAllFile->GetData().end())
			itr = m_CheckAllFile->GetData().begin();

		// �e�N�X�`����ǂݍ���
		m_viewData[backDataIndex].texture = LoadTexture(itr->m_str_path);

		// �ǂݍ��݂Ɏ��s�����̂ł�蒼���܂��B
		if (m_viewData[backDataIndex].texture == nullptr)
			continue;

		m_viewData[backDataIndex].iterator = itr;
		m_viewData[backDataIndex].imageSize = mdx::math::Vector2(m_viewData[backDataIndex].texture.GetImageInfo().width * 1.0f,
			m_viewData[backDataIndex].texture.GetImageInfo().height * 1.0f);

		// �x�[�X�̃T�C�Y�����ɐV�����T�C�Y�𐶐�
		auto newSize = SizeCorrection(m_viewData[backDataIndex].imageSize, mdx::shared_constant::g_ScreenSize) + 0.5f;

		// �摜�����T�C�Y
		m_viewData[backDataIndex].texture.SetImageSize(newSize.x, newSize.y);
		m_viewData[backDataIndex].cash = AddCash(m_viewData[backDataIndex].texture, m_viewData[backDataIndex].imageSize, *m_viewData[backDataIndex].iterator);
		break;
	}

	// �f�[�^���X�V
	for (auto& itr : m_viewData)
	{
		itr.canvas->SetTexture(itr.texture);
		itr.canvas->SetDisplayFlags(false);
		itr.cash->IsOpen = true;
	}

	// �L�����o�X��L��
	m_viewData[0].canvas->SetDisplayFlags(true);

	// �e�N�X�`���ɍ��킹�č��W��␳
	MakeDefaultPosition(m_viewData[0].texture);
}

void ImageViewer::ResetTransform()
{
	m_transform->SetPosition(m_defaultPosition);
	m_transform->SetScale(1, 1, 1);
}

void ImageViewer::MakeDefaultPosition(const mdx::common::Texture& texture)
{
	auto position = mdx::shared_constant::g_ScreenSize * 0.5f;
	auto imageVec = mdx::math::Vector2(texture.GetImageInfo().width, texture.GetImageInfo().height) * 0.5f;

	m_defaultPosition = mdx::math::Vector3(position.x - imageVec.x, position.y - imageVec.y, 0);
}

void ImageViewer::FirstLoad()
{
	if (m_init)
		return;

	// �f�[�^�������Ȃ�
	if (m_CheckAllFile->Length() == 0)
		return;

	// �����_���ŏ����̉摜��I��
	for (auto itr = m_CheckAllFile->GetRandomIterator(m_engine); m_viewData.size() != viewDataMax; ++itr)
	{
		// ����iterator�������Ȃ�
		if (itr == m_CheckAllFile->GetData().end())
			itr = m_CheckAllFile->GetRandomIterator(m_engine);

		ObjectData data;

		data.texture = LoadTexture(itr->m_str_path);

		// �ǂݍ��݂Ɏ��s�����̂ł�蒼���܂��B
		if (data.texture == nullptr)
			continue;

		data.iterator = itr;
		m_viewData.push_back(data);
	}

	// �Z�b�g���ꂽ�f�[�^�����ɏ�����
	for (auto& itr : m_viewData)
	{
		itr.canvas = m_GameObject->AddComponent(new mdx::component::CanvasRenderer);
		itr.imageSize = mdx::math::Vector2(itr.texture.GetImageInfo().width * 1.0f, itr.texture.GetImageInfo().height * 1.0f);

		// �x�[�X�̃T�C�Y�����ɐV�����T�C�Y�𐶐�
		auto newSize = SizeCorrection(itr.imageSize, mdx::shared_constant::g_ScreenSize) + 0.5f;

		// �摜�����T�C�Y
		itr.texture.SetImageSize(newSize.x, newSize.y);

		// �f�[�^���X�V
		itr.canvas->SetTexture(itr.texture);
		itr.canvas->SetDisplayFlags(false);

		// �e�N�X�`�����L���b�V��
		itr.cash = AddCash(itr.texture, itr.imageSize, (*itr.iterator));
		itr.cash->IsOpen = true;
	}

	if (m_viewData.size() == 0)
		return;

	// �L�����o�X��L��
	m_viewData[0].canvas->SetDisplayFlags(true);

	// �e�N�X�`���ɍ��킹�č��W��␳
	MakeDefaultPosition(m_viewData[0].texture);
	ResetTransform();
	m_init = true;
}

void ImageViewer::Reset()
{
	// �C�e���[�^�[���g���Ȃ�����
	for (auto& itr : m_viewData)
		itr.iterator = m_CheckAllFile->GetData().end();

	// �����ǂݍ��݂����s
	FirstLoad();

	m_timeCount = 0;
}

TextureCash* ImageViewer::AddCash(const mdx::common::Texture& texture, const mdx::math::Vector2& imageSize, const check_all_file::DataInfo& imageName)
{
	// �L���b�V���\��
	auto searchCash_lambda = [&](const check_all_file::DataInfo& imageName) {
		// ���݂��邩���ׂ�
		for (auto& itr : m_textureCash)
			if (itr.imageName.m_str_path == imageName.m_str_path)
				return &itr; // �L���b�V���ł��Ȃ�
		return (TextureCash*)nullptr; // �L���b�V���ł���
	};

	auto searchPtr = searchCash_lambda(imageName);
	if (searchPtr != nullptr)
		return searchPtr;

	auto smallSize = SizeCorrection(imageSize, { defaultImageButtonSize ,defaultImageButtonSize });
	auto popSize = SizeCorrection(imageSize, { defaultPopImageSize ,defaultPopImageSize }, false);

	m_textureCash.push_back(TextureCash(texture, imageSize, smallSize, popSize, imageName));
	return &(*(--m_textureCash.end()));
}

void ImageViewer::DeleteCash()
{
	if (m_textureCash.size() == 0)
		return;

	for (size_t i = 0; i < m_textureCash.size(); i++)
	{
		if (m_textureNumCash < static_cast<int>(m_textureCash.size()))
			ReleaseTexture();
	}
}

void ImageViewer::ReleaseTexture()
{
	// �L���b�V���f�[�^��j��
	auto oldRep = m_textureCash.begin()->rep; // �Â�rep
	auto deleteItr = m_textureCash.begin();

	for (auto itr = m_textureCash.begin(); itr != m_textureCash.end(); ++itr)
	{
		if (!itr->IsDelete())
			continue;

		// ����rep���傫���Ȃ�
		if (oldRep < itr->rep)
			continue;

		oldRep = itr->rep;
		deleteItr = itr;
	}

	if (!deleteItr->IsDelete())
		return;

	m_Manager->ReleaseTexture(deleteItr->texture);
	m_textureCash.erase(deleteItr);
}

void ImageViewer::GUI()
{
	if (!m_initGuiSize)
		mdx_imgui::SetNextWindowSize(mdx_imgui::GetDisplaySize() * 0.5f);
	m_initGuiSize = true;

	mdx_imgui::Begin("Viewer IU", nullptr, viewerFlag);

	// ���j���[
	GuiMenu();

	switch (m_mode)
	{
	case Mode::ViewImageCash:
		// �摜�̃{�^��
		ViewImageCash();
		break;
	case Mode::ViewDirectory:
		ViewDirectory(m_directoryData);
		break;
	case Mode::Config:
		Config();
		break;
	default:
		break;
	}

	// �}�E�X�N���b�N�̃A�N�V����
	ClickAction();

	mdx_imgui::End();

	ImageWindow();
}

void ImageViewer::GuiMenu()
{
	// ���j���[
	if (mdx_imgui::BeginMenuBar())
	{
		GuiFile();
		mdx_imgui::TextDisabled("|");
		if (mdx_imgui::BeginMenu("Menu"))
		{
			Mode i = Mode::Begin;
			++i;
			for (; i < Mode::end; ++i)
			{
				auto strEnumName = NAMEOF_ENUM(i);
				if (mdx_imgui::MenuItem(strEnumName.data()))
					m_mode = i;
			}
			mdx_imgui::EndMenu();
		}
		mdx_imgui::TextDisabled("|");
		m_GuiInfo->GUI();
		mdx_imgui::TextDisabled("|");
		mdx_imgui::Text(mdx::system::clock::GetTimeString());
		mdx_imgui::TextDisabled("|");
		mdx_imgui::Text(mdx_imgui::MakeString("(%.1f FPS)", mdx::system::clock::GetFPS()));

		// �ʂ̃X���b�h�����s��
		if (m_sled)
		{
			mdx_imgui::TextDisabled("|");
			mdx_imgui::Text(std::to_string(folder_path::GetLength()));
			mdx_imgui::TextDisabled("|");
			mdx_imgui::Text(std::to_string(file_path::GetLength()));
		}
		mdx_imgui::EndMenuBar();
	}
}

void ImageViewer::GuiFile()
{
	// �ʂ̃X���b�h�����s��
	if (m_sled)
	{
		mdx_imgui::TextDisabled(" File ");
		// �O��UI���z�o�[���ꂽ��
		if (!mdx_imgui::IsItemHovered())
			return;
		mdx_imgui::BeginTooltip();
		mdx_imgui::Text(u8"���΂炭���҂����������B");
		mdx_imgui::EndTooltip();
		return;
	}

	// �ʂ̃X���b�h�͑��݂��Ȃ�
	if (!mdx_imgui::BeginMenu("File"))
		return;
	if (mdx_imgui::MenuItem("Open", "CTRL+O"))
	{
		// �o�^���Ă���X���b�h���܂����s���Ȃ�҂�
		for (; m_function.joinable() != false;)
			m_function.join();
		// �t�H���_���J��
		if (mdx::common::file_dialog::PickFolder(m_directory) == mdx::common::file_dialog::NFD_OKAY)
			m_function = std::thread(&ImageViewer::LoadDirectory, this);
	}
	mdx_imgui::EndMenu();
}

void ImageViewer::ViewImageCash()
{
	float nextPos = 0; // ����UI�̊J�n�n�_
	float itemSpace = 0; // x���̃X�y�[�X

	// �摜�̃{�^�����쐬
	for (auto& cash : m_textureCash)
		ImageButton(cash, nextPos, itemSpace);
}

void ImageViewer::ImageButton(TextureCash& cash, float& nextPos, float& itemSpace)
{
	// �e�s�̐擪�ł͂Ȃ�
	if (nextPos != 0)
	{
		// �E�B���h�E���Ɏ��܂�Ȃ�
		if (nextPos + cash.smallViewSize.x + itemSpace < mdx_imgui::GetWindowSize().x)
			mdx_imgui::SameLine();
		// ���܂�Ȃ�
		else
			nextPos = 0;
	}

	if (mdx_imgui::ImageButton(cash.texture.GetShaderTexture().Get(), cash.smallViewSize))
		MakeImageWindow(&cash);

	auto rectSize = mdx_imgui::GetItemRectSize();
	itemSpace = rectSize.x - cash.smallViewSize.x; // UI�̎���̃X���
	nextPos += rectSize.x + itemSpace; // ����UI�̊J�n�n�_

	// �O��UI���z�o�[���ꂽ��
	if (mdx_imgui::IsItemHovered())
	{
		mdx_imgui::BeginTooltip();
		mdx_imgui::Image(cash.texture.GetShaderTexture().Get(), cash.popViewSize);
		mdx_imgui::TextWrapped(WIDE_TO_UTF8_ENCODE(cash.imageName.m_str_name));
		mdx_imgui::EndTooltip();
	}
}

void ImageViewer::ViewDirectory(DirectoryData& data)
{
	for (auto& infoItr : data.info)
	{
		float nextPos = 0; // ����UI�̊J�n�n�_
		float itemSpace = 0; // x���̃X�y�[�X

			// ���̃f�B���N�g�����Ƀe�N�X�`���L���b�V�������邩�𒲂ׂ�
		auto cash = data.SearchCash(infoItr);

		if (mdx_imgui::MenuItem(WIDE_TO_UTF8_ENCODE(infoItr.m_str_name)))
		{
			MakeImageWindow(cash);
		}
		if (mdx_imgui::IsItemHovered())
		{
			// �L���b�V���������̂œǂݍ���
			if (cash == nullptr)
			{
				auto tex = LoadTexture(infoItr.m_str_path);
				cash = AddCash(tex, { tex.GetImageInfo().width * 1.0f,tex.GetImageInfo().height * 1.0f }, infoItr);
				data.cash.push_back(cash);
			}
			mdx_imgui::BeginTooltip();
			mdx_imgui::Image(cash->texture.GetShaderTexture().Get(), cash->popViewSize);
			mdx_imgui::EndTooltip();
			cash->rep = mdx::system::clock::GetSystemTimeSinceEpoch();
			cash->IsOpen = true;
		}
		else
		{
			// �L���V��������Ȃ�j��
			if (cash != nullptr)
			{
				cash->IsOpen = false;
				data.DeleteCash(infoItr);
			}
		}
	}

	// �f�B���N�g��������Ȃ�
	for (auto& mapItr : data.map)
	{
		bool bKey = false;
		mdx_imgui::Separator();
		if (mdx_imgui::NewTreeNode(WIDE_TO_UTF8_ENCODE(mapItr.first), bKey))
		{
			// �ċA�I�Ɏ��s
			ViewDirectory(mapItr.second);
			mdx_imgui::EndTreeNode();
		}
		else
		{
			// ��ł͂Ȃ��̂Ȃ�
			if (mapItr.second.cash.size() != 0)
			{
				for (auto cash : mapItr.second.cash)
					if (cash != nullptr)
						cash->IsOpen = false;
				mapItr.second.cash.clear();
			}
		}
	}
}

void ImageViewer::MakeDirectory()
{
	// �s�v�ȕ�������j������
	auto ConvertToRelativePath = [&](const std::wstring& imageName, size_t count) {
		auto copy = imageName;
		copy.erase(0, count);
		return copy;
	};

	auto directoryCopy = m_directory;
	auto isHierarchy = std::wstring(L"/");

	// �e�f�B���N�g������]�v�ȕ������j��
	std::replace(directoryCopy.begin(), directoryCopy.end(), '\\', '/');
	directoryCopy += isHierarchy;

	m_directoryData.info.clear();
	m_directoryData.map.clear();

	for (auto& itr : m_CheckAllFile->GetData())
		MakeDirectoryData(ConvertToRelativePath(itr.m_str_path, directoryCopy.size()), m_directoryData, itr, isHierarchy);
}

void ImageViewer::MakeDirectoryData(std::wstring str_path, DirectoryData& data, const check_all_file::DataInfo& dataInfo, const std::wstring& isHierarchy)
{
	auto npos = str_path.find(isHierarchy.c_str());

	if (npos == std::wstring::npos)
	{
		data.info.push_back(dataInfo);
	}
	else
	{
		std::wstring wstrPass = str_path;

		// �ۑ��p�X
		wstrPass.erase(npos, wstrPass.size());

		// ���̃p�X
		str_path.erase(0, (wstrPass + isHierarchy).size());

		auto dirItr = data.map.find(wstrPass);
		// �f�[�^������
		if (dirItr == data.map.end())
		{
			data.map[wstrPass];
			dirItr = data.map.find(wstrPass);
		}
		MakeDirectoryData(str_path, dirItr->second, dataInfo, isHierarchy);
	}
}

void ImageViewer::ImageWindow()
{
	// �E�B���h�E�̕\��
	for (auto& window : m_imageWindow)
	{
		if (window.textureCashPtr == nullptr)
			continue;

		if (!window.init)
		{
			auto nextWindowSize = SizeCorrection(window.textureCashPtr->imageSize, { imageWindowSize ,imageWindowSize });
			nextWindowSize.y += mdx_imgui::GetTitleBarHeight();
			mdx_imgui::SetNextWindowSize(nextWindowSize);
			window.textureCashPtr->IsOpenWindow = true;
		}

		mdx_imgui::Begin(WIDE_TO_UTF8_ENCODE(window.textureCashPtr->imageName.m_str_path), &window.textureCashPtr->IsOpenWindow,
			mdx_imgui::ImGuiWindowFlags_::ImGuiWindowFlags_NoSavedSettings);

		// �O�t���[���̃E�B���h�E�T�C�Y�ƍ��̃T�C�Y���Ⴄ�Ȃ�
		if (window.winSize != mdx_imgui::GetWindowSize() && window.init)
		{
			window.winSize = mdx_imgui::GetWindowSize();
			window.imageSize = SizeCorrection(window.textureCashPtr->imageSize, window.winSize);
		}

		// �X�V
		window.textureCashPtr->rep = mdx::system::clock::GetSystemTimeSinceEpoch();

		// �`��
		mdx_imgui::Image(window.textureCashPtr->texture.GetShaderTexture().Get(), window.imageSize);

		mdx_imgui::End();

		// ������
		if (!window.init)
			window.init = true;
	}

	for (auto itr = m_imageWindow.begin(); itr != m_imageWindow.end(); )
	{
		if (itr->textureCashPtr == nullptr)
			continue;

		if (itr->textureCashPtr->IsOpenWindow)
		{
			++itr;
			continue;
		}

		// �\���������ɂȂ�����
		itr = m_imageWindow.erase(itr);
	}
}

bool ImageViewer::MakeImageWindow(TextureCash* cash)
{
	if (cash == nullptr)
		return false;

	bool bPush = true;

	// �E�B���h�E������Ă��邩�𒲂ׂ�
	for (auto& itr : m_imageWindow)
	{
		if (itr.textureCashPtr == nullptr)
			continue;

		// �E�B���h�E������Ă���
		if (itr.textureCashPtr == cash)
		{
			// �J���Ă����ꍇ����
			itr.textureCashPtr->IsOpenWindow = false;
			bPush = false;
			break;
		}
	}

	// �L���b�V����o�^
	if (bPush)
	{
		cash->IsOpenWindow = true;
		m_imageWindow.push_back(ImageWindowData(cash));
	}

	return bPush;
}

void ImageViewer::ClickAction()
{
	// �N���b�N��������W���L�^
	if (mdx_imgui::IsMouseClicked(mdx_imgui::ImGuiMouseButton_::ImGuiMouseButton_Right))
	{
		m_position = m_transform->GetPosition();
	}
	// �N���b�N���Ă���Ԃ͎��s
	if (mdx_imgui::IsMouseDown(mdx_imgui::ImGuiMouseButton_::ImGuiMouseButton_Right))
	{
		auto vec = mdx_imgui::GetMouseDragDelta(mdx_imgui::ImGuiMouseButton_::ImGuiMouseButton_Right);
		m_transform->SetPosition(vec.x + m_position.x, vec.y + m_position.y, 0);
	}
}

void ImageViewer::LoadDirectory()
{
	m_sled = true;

	// �e�̃f�B���N�g��������
	if (m_oldDirectory == m_directory)
	{
		Reset();
		m_sled = false;
		return;
	}
	folder_path::SetLength(0);
	file_path::SetLength(0);
	m_CheckAllFile->LoadDirectory(m_directory);
	Reset();
	MakeDirectory();
	m_oldDirectory = m_directory;
	m_sled = false;
}

mdx::common::Texture ImageViewer::LoadTexture(const std::wstring& filename)
{
	// �e�N�X�`����ǂݍ���
	mdx::common::Texture texture = m_Manager->CreateTextureFromFile(filename);

	// �ǂݍ��݂Ɏ��s�����̂ł�蒼���܂��B
	if (texture == nullptr || texture.GetImageInfo().width == 0 || texture.GetImageInfo().height == 0)
		return nullptr;

	return texture;
}

void ImageViewer::Config()
{
	mdx_imgui::Checkbox(u8"�N�����ɐݒ������������", m_InitializerData);
	mdx_imgui::SliderInt(u8"�L���b�V�����", &m_textureNumCash, static_cast<int>(viewDataMax), static_cast<int>(textureNumCash));
	if (mdx_imgui::InputFloat(u8"�X�V����(�b)", &m_updateTime, 0.1f, 100))
		if (m_updateTime <= 0)
			m_updateTime = 1;
	mdx_imgui::Checkbox(u8"�N�����Ƀ������E�B���h�E��\������", m_OpenMemoryMindow);
	mdx_imgui::Checkbox(u8"�A�v���P�[�V�����Ŏg���郁���������Ȃ��Ȃ�����L���b�V����j������", m_MemoryOver);
}
