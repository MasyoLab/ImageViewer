//==========================================================================
// ビュアー [ImageViewer.h]
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
	mdx::math::Vector2 smallViewSize; // 小さなviewサイズ
	mdx::math::Vector2 popViewSize; // ポップviewサイズ
	mdx::math::Vector2 imageSize; // 画像のサイズ
	check_all_file::DataInfo imageName; // 画像の名前
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
	mdx::component::CanvasRenderer* canvas = nullptr; // キャンバス
	mdx::common::Texture texture; // Texture
	check_all_file::DataInfoList::const_iterator iterator; // iterator
	mdx::math::Vector2 imageSize; // 画像のサイズ
	TextureCash* cash = nullptr; // キャッシュ
};

struct ImageWindowData
{
	TextureCash* textureCashPtr = nullptr;
	bool init = false;
	mdx::math::Vector2 winSize; // ウィンドウサイズ
	mdx::math::Vector2 imageSize; // 画像のサイズ

	ImageWindowData(TextureCash* ptr) :textureCashPtr(ptr), imageSize(ptr->imageSize) {}
};

struct DirectoryData
{
	std::unordered_map<std::wstring, DirectoryData> map; // ディレクトリマップ
	std::list<check_all_file::DataInfo> info;
	std::list<TextureCash*> cash; // キャッシュ

	// キャッシュ可能か
	TextureCash* SearchCash(const check_all_file::DataInfo& imageName) {
		// 存在するか調べる
		for (auto itr : cash)
		{
			if (itr == nullptr)
				continue;
			if (itr->imageName.m_str_path == imageName.m_str_path)
				return itr; // キャッシュできない
		}
		return (TextureCash*)nullptr; // キャッシュできる
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
	mdx::math::Vector3 m_defaultPosition; // 固定座標
	mdx::math::Vector3 m_position; // 本体の座標
	std::vector<ObjectData> m_viewData; // ビュー情報
	std::list<TextureCash> m_textureCash; // テクスチャのキャッシュ
	std::list<ImageWindowData> m_imageWindow; // 画像用ウィンドウ
	std::random_device m_seed_gen; // シード値
	std::wstring m_directory; // ディレクトリ
	std::wstring m_oldDirectory; // ディレクトリ
	std::mt19937 m_engine; // 乱数
	std::thread m_function; // 関数ポインタ
	check_all_file::CheckAllFile* m_CheckAllFile = nullptr;
	DirectoryData m_directoryData; // ディレクトリマップ
	GuiInfo* m_GuiInfo = nullptr; // infoのGui
	Mode m_mode = Mode::ViewImageCash; // モード
	float m_timeCount = 0; // タイムのカウント
	float m_updateTime = 0; // 更新時間
	bool m_init = false; // 初期化されたか
	bool m_initGuiSize = false; // guiサイズの変更
	bool m_reset = false; // リセットフラグ
	bool m_sled = false; // スレッド
	bool m_InitializerData = false; // 初期化データを使う
	bool m_OpenMemoryMindow = false; // メモリウィンドウを開く
	bool m_MemoryOver = false; // メモリを超えたら解放
	bool m_RefreshMemory = false; // メモリの負荷を解消
	int m_textureNumCash = 0; // テクスチャのキャッシュ上限
public:
	ImageViewer();
	virtual ~ImageViewer();

private:
	/**
	@brief 初期化
	*/
	void Init() override;

	/**
	@brief 更新
	*/
	void Update() override;

	/**
	@brief サイズ補正
	*/
	mdx::math::Vector2 SizeCorrection(size_t width, size_t height, const mdx::math::Vector2& standardSize, bool standardControl = true);

	/**
	@brief サイズ補正
	*/
	mdx::math::Vector2 SizeCorrection(const mdx::math::Vector2& size, const mdx::math::Vector2& standardSize, bool standardControl = true);

	/**
	@brief viewデータの更新
	*/
	void SwapData();

	/**
	@brief Transformの初期化
	*/
	void ResetTransform();

	/**
	@brief 初期座標の生成
	*/
	void MakeDefaultPosition(const mdx::common::Texture& texture);

	/**
	@brief 最初の読み込み
	*/
	void FirstLoad();

	/**
	@brief view内容のリセット
	*/
	void Reset();

	/**
	@brief キャッシュに登録
	*/
	TextureCash* AddCash(const mdx::common::Texture& texture, const mdx::math::Vector2& imageSize, const check_all_file::DataInfo& imageName);

	/**
	@brief キャッシュの破棄
	*/
	void DeleteCash();

	/**
	@brief キャッシュの破棄
	*/
	void ReleaseTexture();

	/**
	@brief UI
	*/
	void GUI();

	/**
	@brief メニュー
	*/
	void GuiMenu();

	/**
	@brief ファイル系の処理
	*/
	void GuiFile();

	/**
	@brief 画像のキャッシュを表示
	*/
	void ViewImageCash();

	/**
	@brief 画像のボタン
	*/
	void ImageButton(TextureCash& cash, float& nextPos, float& itemSpace);

	/**
	@brief ディレクトリを表示
	*/
	void ViewDirectory(DirectoryData& data);

	/**
	@brief ディレクトリを作成
	*/
	void MakeDirectory();

	/**
	@brief ディレクトリのデータを作成
	*/
	void MakeDirectoryData(std::wstring str_path, DirectoryData& data, const check_all_file::DataInfo& dataInfo, const std::wstring& isHierarchy);

	/**
	@brief 画像を表示するためのウィンドウ
	*/
	void ImageWindow();

	/**
	@brief 画像を表示するためのウィンドウを作成
	*/
	bool MakeImageWindow(TextureCash* cash);

	/**
	@brief マウスクリックのアクション
	*/
	void ClickAction();

	/**
	@brief ディレクトリの読み込み
	*/
	void LoadDirectory();

	/**
	@brief テクスチャの読み込み
	*/
	mdx::common::Texture LoadTexture(const std::wstring& filename);

	void Config();
};