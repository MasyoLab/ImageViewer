//==========================================================================
// �r���A�[ [ImageViewer.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <future>
#include <random>
#include <fstream>   // ifstream, ofstream
#include <sstream>   // istringstream
#include "common.h"
#include "CheckAllFile.h"
#include "GuiInfo.h"

enum class Mode
{
	Begin = -1,
	ViewImageCash,
	ViewDirectory,
	Config,
	end
};
template<> struct mdx::common::enum_operator::calculation<Mode> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<Mode> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<Mode> : std::true_type {};

struct TextureCash
{
	mdx::common::Texture texture; // Texture
	mdx::system::clock::rep rep = mdx::system::clock::GetSystemTimeSinceEpoch();
	mdx::math::Vector2 smallViewSize; // ������view�T�C�Y
	mdx::math::Vector2 popViewSize; // �|�b�vview�T�C�Y
	mdx::math::Vector2 imageSize; // �摜�̃T�C�Y
	check_all_file::DataInfo imageName; // �摜�̖��O
	bool IsOpen = false;
	bool IsOpenWindow = false;

	TextureCash(const mdx::common::Texture& texture, const mdx::math::Vector2& imageSize, const mdx::math::Vector2& smallViewSize,
		const mdx::math::Vector2& popViewSize, const check_all_file::DataInfo& imageName) :
		texture(texture), imageSize(imageSize), smallViewSize(smallViewSize), popViewSize(popViewSize), imageName(imageName) {}

	bool IsDelete() {
		return IsOpen == false && IsOpenWindow == false;
	}
};

struct ObjectData
{
	mdx::component::CanvasRenderer* canvas = nullptr; // �L�����o�X
	mdx::common::Texture texture; // Texture
	check_all_file::DataInfoList::const_iterator iterator; // iterator
	mdx::math::Vector2 imageSize; // �摜�̃T�C�Y
	TextureCash* cash = nullptr; // �L���b�V��
};

struct ImageWindowData
{
	TextureCash* textureCashPtr = nullptr;
	bool init = false;
	mdx::math::Vector2 winSize; // �E�B���h�E�T�C�Y
	mdx::math::Vector2 imageSize; // �摜�̃T�C�Y

	ImageWindowData(TextureCash* ptr) :textureCashPtr(ptr), imageSize(ptr->imageSize) {}
};

struct DirectoryData
{
	std::unordered_map<std::wstring, DirectoryData> map; // �f�B���N�g���}�b�v
	std::list<check_all_file::DataInfo> info;
	std::list<TextureCash*> cash; // �L���b�V��

	// �L���b�V���\��
	TextureCash* SearchCash(const check_all_file::DataInfo& imageName) {
		// ���݂��邩���ׂ�
		for (auto itr : cash)
		{
			if (itr == nullptr)
				continue;
			if (itr->imageName.m_str_path == imageName.m_str_path)
				return itr; // �L���b�V���ł��Ȃ�
		}
		return (TextureCash*)nullptr; // �L���b�V���ł���
	};
	void DeleteCash(const check_all_file::DataInfo& imageName) {
		for (auto itr = cash.begin(); itr != cash.end(); )
		{
			if ((*itr) == nullptr)
			{
				itr = cash.erase(itr);
				continue;
			}
			if ((*itr)->imageName.m_str_path == imageName.m_str_path)
			{
				itr = cash.erase(itr);
				continue;
			}
			++itr;
		}
	};
};

class ImageViewer :
	public mdx::component::Component
{
private:
	mdx::component::Transform* m_transform = nullptr;
	mdx::math::Vector3 m_defaultPosition; // �Œ���W
	mdx::math::Vector3 m_position; // �{�̂̍��W
	std::vector<ObjectData> m_viewData; // �r���[���
	std::list<TextureCash> m_textureCash; // �e�N�X�`���̃L���b�V��
	std::list<ImageWindowData> m_imageWindow; // �摜�p�E�B���h�E
	std::random_device m_seed_gen; // �V�[�h�l
	std::wstring m_directory; // �f�B���N�g��
	std::wstring m_oldDirectory; // �f�B���N�g��
	std::mt19937 m_engine; // ����
	std::thread m_function; // �֐��|�C���^
	check_all_file::CheckAllFile* m_CheckAllFile = nullptr;
	DirectoryData m_directoryData; // �f�B���N�g���}�b�v
	GuiInfo* m_GuiInfo = nullptr; // info��Gui
	Mode m_mode = Mode::ViewImageCash; // ���[�h
	float m_timeCount = 0; // �^�C���̃J�E���g
	float m_updateTime = 0; // �X�V����
	bool m_init = false; // ���������ꂽ��
	bool m_initGuiSize = false; // gui�T�C�Y�̕ύX
	bool m_reset = false; // ���Z�b�g�t���O
	bool m_sled = false; // �X���b�h
	bool m_InitializerData = false; // �������f�[�^���g��
	bool m_OpenMemoryMindow = false; // �������E�B���h�E���J��
	bool m_MemoryOver = false; // �������𒴂�������
	bool m_RefreshMemory = false; // �������̕��ׂ�����
	int m_textureNumCash = 0; // �e�N�X�`���̃L���b�V�����
public:
	ImageViewer();
	virtual ~ImageViewer();

private:
	/**
	@brief ������
	*/
	void Init() override;

	/**
	@brief �X�V
	*/
	void Update() override;

	/**
	@brief �T�C�Y�␳
	*/
	mdx::math::Vector2 SizeCorrection(size_t width, size_t height, const mdx::math::Vector2& standardSize, bool standardControl = true);

	/**
	@brief �T�C�Y�␳
	*/
	mdx::math::Vector2 SizeCorrection(const mdx::math::Vector2& size, const mdx::math::Vector2& standardSize, bool standardControl = true);

	/**
	@brief view�f�[�^�̍X�V
	*/
	void SwapData();

	/**
	@brief Transform�̏�����
	*/
	void ResetTransform();

	/**
	@brief �������W�̐���
	*/
	void MakeDefaultPosition(const mdx::common::Texture& texture);

	/**
	@brief �ŏ��̓ǂݍ���
	*/
	void FirstLoad();

	/**
	@brief view���e�̃��Z�b�g
	*/
	void Reset();

	/**
	@brief �L���b�V���ɓo�^
	*/
	TextureCash* AddCash(const mdx::common::Texture& texture, const mdx::math::Vector2& imageSize, const check_all_file::DataInfo& imageName);

	/**
	@brief �L���b�V���̔j��
	*/
	void DeleteCash();

	/**
	@brief �L���b�V���̔j��
	*/
	void ReleaseTexture();

	/**
	@brief UI
	*/
	void GUI();

	/**
	@brief ���j���[
	*/
	void GuiMenu();

	/**
	@brief �t�@�C���n�̏���
	*/
	void GuiFile();

	/**
	@brief �摜�̃L���b�V����\��
	*/
	void ViewImageCash();

	/**
	@brief �摜�̃{�^��
	*/
	void ImageButton(TextureCash& cash, float& nextPos, float& itemSpace);

	/**
	@brief �f�B���N�g����\��
	*/
	void ViewDirectory(DirectoryData& data);

	/**
	@brief �f�B���N�g�����쐬
	*/
	void MakeDirectory();

	/**
	@brief �f�B���N�g���̃f�[�^���쐬
	*/
	void MakeDirectoryData(std::wstring str_path, DirectoryData& data, const check_all_file::DataInfo& dataInfo, const std::wstring& isHierarchy);

	/**
	@brief �摜��\�����邽�߂̃E�B���h�E
	*/
	void ImageWindow();

	/**
	@brief �摜��\�����邽�߂̃E�B���h�E���쐬
	*/
	bool MakeImageWindow(TextureCash* cash);

	/**
	@brief �}�E�X�N���b�N�̃A�N�V����
	*/
	void ClickAction();

	/**
	@brief �f�B���N�g���̓ǂݍ���
	*/
	void LoadDirectory();

	/**
	@brief �e�N�X�`���̓ǂݍ���
	*/
	mdx::common::Texture LoadTexture(const std::wstring& filename);

	void Config();
};