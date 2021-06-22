//==========================================================================
// Dear ImGui のラッパー [mdx_imgui.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include <Windows.h>
#include <memory>
#include <string>
#include <cstdio>
#include "dx11afx.h"
#include "enum_operator.hpp"

namespace mdx_imgui
{
	using namespace mdx::math;
#pragma region Flags & Enumerations

	//-----------------------------------------------------------------------------
	// Flags & Enumerations
	//-----------------------------------------------------------------------------

	// Flags for Begin()
	enum class ImGuiWindowFlags_
	{
		ImGuiWindowFlags_None = 0,
		ImGuiWindowFlags_NoTitleBar = 1 << 0,  // タイトルバーを無効にする
		ImGuiWindowFlags_NoResize = 1 << 1,  // 右下のグリップでユーザーのサイズ変更を無効にします
		ImGuiWindowFlags_NoMove = 1 << 2,  // ユーザーがウィンドウを移動できないようにする
		ImGuiWindowFlags_NoScrollbar = 1 << 3,  // スクロールバーを無効にします(ウィンドウはマウスまたはプログラムでスクロールできます)
		ImGuiWindowFlags_NoScrollWithMouse = 1 << 4,  // ユーザーがマウスホイールで垂直にスクロールできないようにします。子ウィンドウでは、NoScrollbarも設定されていない限り、マウスホイールは親に転送されます。
		ImGuiWindowFlags_NoCollapse = 1 << 5,  // ユーザー折りたたみウィンドウをダブルクリックして無効にします。ドッキングノード内の「ウィンドウメニューボタン」とも呼ばれます。
		ImGuiWindowFlags_AlwaysAutoResize = 1 << 6,  // すべてのウィンドウのサイズをすべてのフレームのコンテンツに変更します
		ImGuiWindowFlags_NoBackground = 1 << 7,  // 描画背景色(WindowBgなど)および外枠を無効にします。 SetNextWindowBgAlpha(0.0f) を使用する場合と同様です。
		ImGuiWindowFlags_NoSavedSettings = 1 << 8,  // .iniファイルの設定をロード/保存しない
		ImGuiWindowFlags_NoMouseInputs = 1 << 9,  // パススルーでテストをホバリング、マウスのキャッチを無効にします。
		ImGuiWindowFlags_MenuBar = 1 << 10, // メニューバーがあります
		ImGuiWindowFlags_HorizontalScrollbar = 1 << 11, // 水平スクロールバーの表示を許可します(デフォルトではオフ)。 SetNextWindowContentSize(ImVec2(width、0.0f)); を使用できます。 Begin() を呼び出して幅を指定する前に。 「水平スクロール」セクションのimgui_demoのコードを読んでください。
		ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12, // 非表示から表示状態に移行するときにフォーカスを取得できないようにします
		ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13, // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
		ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14, // フォーカスを取得するときにウィンドウを前面に移動することを無効にします(たとえば、クリックするか、プログラムでフォーカスを設定します)
		ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15, // 常に水平スクロールバーを表示します(ContentSize.x <Size.xであっても)
		ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16, // 境界線のない子ウィンドウがstyle.WindowPaddingを使用するようにします(境界線のない子ウィンドウではデフォルトで無視されるため、より便利です)
		ImGuiWindowFlags_NoNavInputs = 1 << 18, // ウィンドウ内にゲームパッド/キーボードナビゲーションはありません
		ImGuiWindowFlags_NoNavFocus = 1 << 19, // ゲームパッド/キーボードナビゲーションでこのウィンドウに焦点を合わせない(たとえば、CTRL + TABでスキップ)
		ImGuiWindowFlags_UnsavedDocument = 1 << 20, // ###演算子の使用を避けるために、IDに影響を与えずにタイトルに「*」を追加します。タブ/ドッキングコンテキストで使用すると、クロージャーでタブが選択され、クロージャーが1フレーム延期されて、コードがちらつきのない(確認ポップアップなどで)クロージャーをキャンセルできるようになります。
		ImGuiWindowFlags_NoDocking = 1 << 21, // このウィンドウのドッキングを無効にします

		ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
		ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
		ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
	};

	// Flags for InputText()
	enum class ImGuiInputTextFlags_
	{
		ImGuiInputTextFlags_None = 0,
		ImGuiInputTextFlags_CharsDecimal = 1 << 0,  // 0123456789.+-* を許可/
		ImGuiInputTextFlags_CharsHexadecimal = 1 << 1,  // 0123456789ABCDEFabcdef を許可
		ImGuiInputTextFlags_CharsUppercase = 1 << 2,  // a..zをA..Zに変える
		ImGuiInputTextFlags_CharsNoBlank = 1 << 3,  // スペース、タブを除外する
		ImGuiInputTextFlags_AutoSelectAll = 1 << 4,  // 最初にマウスフォーカスを取るときにテキスト全体を選択する
		ImGuiInputTextFlags_EnterReturnsTrue = 1 << 5,  // (値が変更されるたびにではなく)Enterが押されたときに「true」を返します。 IsItemDeactivatedAfterEdit() 関数を調べることを検討してください。
		ImGuiInputTextFlags_CallbackCompletion = 1 << 6,  // Tabキーを押したときのコールバック(完了処理のため)
		ImGuiInputTextFlags_CallbackHistory = 1 << 7,  // 上/下矢印を押すとコールバック(履歴処理用)
		ImGuiInputTextFlags_CallbackAlways = 1 << 8,  // 各反復でのコールバック。ユーザーコードはカーソル位置を照会し、テキストバッファを変更できます。
		ImGuiInputTextFlags_CallbackCharFilter = 1 << 9,  // 置換または破棄する文字入力のコールバック。 'EventChar'を変更して置換または破棄するか、コールバックで1を返して破棄します。
		ImGuiInputTextFlags_AllowTabInput = 1 << 10, // Tabキーを押すと、テキストフィールドに「\ t」文字が入力されます
		ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11, // 複数行モードでは、Enterでフォーカスを解除し、Ctrl + Enterで新しい行を追加します(デフォルトは反対です : Ctrl + Enterでフォーカスを解除し、Enterで行を追加します)。
		ImGuiInputTextFlags_NoHorizontalScroll = 1 << 12, // カーソルの水平方向のフォローを無効にする
		ImGuiInputTextFlags_AlwaysInsertMode = 1 << 13, // 挿入モード
		ImGuiInputTextFlags_ReadOnly = 1 << 14, // 読み取り専用モード
		ImGuiInputTextFlags_Password = 1 << 15, // パスワードモード、すべての文字を「*」として表示
		ImGuiInputTextFlags_NoUndoRedo = 1 << 16, // 元に戻す/やり直しを無効にします。アクティブな間は入力テキストがテキストデータを所有していることに注意してください。独自の元に戻す/やり直しスタックを提供する場合は、たとえばClearActiveID() を呼び出します。
		ImGuiInputTextFlags_CharsScientific = 1 << 17, // 0123456789。+-*/eE(科学表記法の入力)を許可
		ImGuiInputTextFlags_CallbackResize = 1 << 18, // バッファ容量のコールバックはリクエストを変更し(「buf_size」パラメータ値を超えて)、文字列を大きくすることができます。文字列のサイズを変更する必要がある場合に通知します(サイズのキャッシュを保持する文字列タイプの場合)。コールバックで新しいBufSizeが提供され、それを尊重する必要があります。 (これの使用例については、misc/cpp/imgui_stdlib.hを参照してください)
	};

	// Flags for TreeNodeEx(), CollapsingHeader*()
	enum class ImGuiTreeNodeFlags_
	{
		ImGuiTreeNodeFlags_None = 0,
		ImGuiTreeNodeFlags_Selected = 1 << 0,  // 選択されたとおりに描く
		ImGuiTreeNodeFlags_Framed = 1 << 1,  // フルカラーフレーム(CollapsingHeaderなど)
		ImGuiTreeNodeFlags_AllowItemOverlap = 1 << 2,  // テストをヒットして、後続のウィジェットがこのウィジェットとオーバーラップできるようにします
		ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3,  // 開いているときにTreePush() を実行しない(例 : CollapsingHeaderの場合)=追加のインデントもIDスタックのプッシュも行わない
		ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4,  // ロギングがアクティブなときにノードを自動的に一時的に開かないでください(デフォルトでは、ロギングは自動的にツリーノードを開きます)
		ImGuiTreeNodeFlags_DefaultOpen = 1 << 5,  // 開くデフォルトのノード
		ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6,  // ノードを開くにはダブルクリックが必要です
		ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7,  // 矢印部分をクリックしたときにのみ開きます。 ImGuiTreeNodeFlags_OpenOnDoubleClickも設定されている場合、矢印をシングルクリックするか、すべてのボックスをダブルクリックして開きます。
		ImGuiTreeNodeFlags_Leaf = 1 << 8,  // 折りたたみも矢印もありません(リーフノードの利便性として使用)。
		ImGuiTreeNodeFlags_Bullet = 1 << 9,  // 矢印の代わりに弾丸を表示する
		ImGuiTreeNodeFlags_FramePadding = 1 << 10, // FramePaddingを使用して(フレーム化されていないテキストノードの場合でも)、テキストのベースラインを通常のウィジェットの高さに垂直に揃えます。 AlignTextToFramePadding() の呼び出しと同等です。
		ImGuiTreeNodeFlags_SpanAvailWidth = 1 << 11, // ヒットボックスを右端まで拡張します(フレーム化されていない場合でも)。これは、同じ行に他のアイテムを追加できるようにするためのデフォルトではありません。将来的には、ヒットシステムを前面から背面にリファクタリングして、自然なオーバーラップを可能にし、これがデフォルトになる可能性があります。
		ImGuiTreeNodeFlags_SpanFullWidth = 1 << 12, // ヒットボックスを左端と右端に拡張します(インデントされた領域をバイパスします)。
		ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 13, // (WIP)Nav : 左方向は、その子(TreeNodeとTreePopの間で送信されたアイテム)からこのTreeNode() に移動できます
		//ImGuiTreeNodeFlags_NoScrollOnOpen     = 1 << 14, // FIXME : TODO : ノードが開いたばかりで内容が表示されない場合、TreePop() の自動スクロールを無効にします
		ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog
	};

	// Flags for Selectable()
	enum class ImGuiSelectableFlags_
	{
		ImGuiSelectableFlags_None = 0,
		ImGuiSelectableFlags_DontClosePopups = 1 << 0,  // これをクリックしても、親ポップアップウィンドウは閉じません。
		ImGuiSelectableFlags_SpanAllColumns = 1 << 1,  // 選択可能なフレームはすべての列にまたがることができます(テキストは現在の列に収まります)
		ImGuiSelectableFlags_AllowDoubleClick = 1 << 2,  // ダブルクリックでもプレスイベントを生成
		ImGuiSelectableFlags_Disabled = 1 << 3,  // 選択できません、グレー表示されたテキストを表示します
		ImGuiSelectableFlags_AllowItemOverlap = 1 << 4   // (WIP)ヒットテストにより、後続のウィジェットがこのウィジェットとオーバーラップできるようにします
	};

	// Flags for BeginCombo()
	enum class ImGuiComboFlags_
	{
		ImGuiComboFlags_None = 0,
		ImGuiComboFlags_PopupAlignLeft = 1 << 0,  // デフォルトでポップアップを左に揃える
		ImGuiComboFlags_HeightSmall = 1 << 1,  // 最大4個のアイテムが表示されます。ヒント : コンボポップアップを特定のサイズにするには、BeginCombo() を呼び出す前にSetNextWindowSizeConstraints() を使用できます。
		ImGuiComboFlags_HeightRegular = 1 << 2,  // 最大8個のアイテムが表示されます(デフォルト)
		ImGuiComboFlags_HeightLarge = 1 << 3,  // 最大20個のアイテムが表示されます
		ImGuiComboFlags_HeightLargest = 1 << 4,  // できるだけ多くのフィッティングアイテム
		ImGuiComboFlags_NoArrowButton = 1 << 5,  // 四角い矢印ボタンなしでプレビューボックスに表示する
		ImGuiComboFlags_NoPreview = 1 << 6,  // 四角い矢印ボタンのみを表示する
		ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest
	};

	// Flags for BeginTabBar()
	enum class ImGuiTabBarFlags_
	{
		ImGuiTabBarFlags_None = 0,
		ImGuiTabBarFlags_Reorderable = 1 << 0,  // タブを手動でドラッグして並べ替えることができます+リストの最後に新しいタブが追加されます
		ImGuiTabBarFlags_AutoSelectNewTabs = 1 << 1,  // 新しいタブが表示されたら自動的に選択する
		ImGuiTabBarFlags_TabListPopupButton = 1 << 2,  // ボタンを無効にしてタブリストポップアップを開きます
		ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 1 << 3,  // マウスの中ボタンでタブを閉じる(p_open！= nullptrで送信される)動作を無効にします。if(IsItemHovered() && IsMouseClicked(2))* p_open = falseを使用すると、ユーザー側でこの動作を再現できます。
		ImGuiTabBarFlags_NoTabListScrollingButtons = 1 << 4,  // スクロールボタンを無効にする(フィッティングポリシーがImGuiTabBarFlags_FittingPolicyScrollの場合に適用)
		ImGuiTabBarFlags_NoTooltip = 1 << 5,  // タブをホバーするときにツールチップを無効にする
		ImGuiTabBarFlags_FittingPolicyResizeDown = 1 << 6,  // 収まらないタブのサイズを変更する
		ImGuiTabBarFlags_FittingPolicyScroll = 1 << 7,  // タブが収まらない場合にスクロールボタンを追加する
		ImGuiTabBarFlags_FittingPolicyMask_ = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
		ImGuiTabBarFlags_FittingPolicyDefault_ = ImGuiTabBarFlags_FittingPolicyResizeDown
	};

	// Flags for BeginTabItem()
	enum class ImGuiTabItemFlags_
	{
		ImGuiTabItemFlags_None = 0,
		ImGuiTabItemFlags_UnsavedDocument = 1 << 0,  // ###演算子の使用を避けるために、IDに影響を与えずにタイトルに「*」を追加します。また、クロージャーでタブが選択され、クロージャーは1フレーム延期され、フリッカーなしでコードを元に戻すことができます。
		ImGuiTabItemFlags_SetSelected = 1 << 1,  // BeginTabItem() の呼び出し時にプログラムでタブを選択するためのトリガーフラグ
		ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2,  // マウスの中ボタンでタブを閉じる(p_open！= nullptrで送信される)動作を無効にします。if(IsItemHovered() && IsMouseClicked(2))* p_open = falseを使用すると、ユーザー側でこの動作を再現できます。
		ImGuiTabItemFlags_NoPushId = 1 << 3   // BeginTabItem()/EndTabItem() でPushID(tab-> ID)/ PopID() を呼び出さないでください
	};

	// Flags for IsWindowFocused()
	enum class ImGuiFocusedFlags_
	{
		ImGuiFocusedFlags_None = 0,
		ImGuiFocusedFlags_ChildWindows = 1 << 0,  // IsWindowFocused() : ウィンドウのいずれかの子がフォーカスされている場合にtrueを返します
		ImGuiFocusedFlags_RootWindow = 1 << 1,  // IsWindowFocused() : ルートウィンドウからテスト(現在の階層の最上位の親)
		ImGuiFocusedFlags_AnyWindow = 1 << 2,  // IsWindowFocused() : ウィンドウがフォーカスされている場合はtrueを返します。重要 : 低レベルの入力をディスパッチする方法を伝えようとしている場合は、これを使用しないでください。代わりにGetIO() 。WantCaptureMouseを使用してください。
		ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows
	};

	// IsItemHovered() 、IsWindowHovered() のフラグ
	// 注 : マウスをimguiまたはアプリにディスパッチする必要があるかどうかを確認しようとしている場合は、 'io.WantCaptureMouse'ブール値を使用する必要があります。 FAQを読んでください！
	// 注 : ImGuiWindowFlags_NoInputsフラグを持つウィンドウは、IsWindowHovered() 呼び出しによって無視されます。
	enum class ImGuiHoveredFlags_
	{
		ImGuiHoveredFlags_None = 0,       // アイテム/ウィンドウのすぐ上で、別のウィンドウで遮られていない場合、またはアクティブなポップアップやモーダルブロック入力で遮られていない場合、trueを返します。
		ImGuiHoveredFlags_ChildWindows = 1 << 0,  // IsWindowHovered() only : ウィンドウのいずれかの子がホバーされている場合はtrueを返します
		ImGuiHoveredFlags_RootWindow = 1 << 1,  // IsWindowHovered() only : ルートウィンドウ(現在の階層の最上位の親)からテストする
		ImGuiHoveredFlags_AnyWindow = 1 << 2,  // IsWindowHovered() only : ウィンドウがホバーされている場合はtrueを返します
		ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 3,  // ポップアップウィンドウがこのアイテム/ウィンドウへのアクセスを通常ブロックしている場合でもtrueを返します
		//ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 4,  // モーダルポップアップウィンドウがこのアイテム/ウィンドウへのアクセスを通常ブロックしている場合でもtrueを返します。 FIXME-TODO : まだ利用できません。
		ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 5,  // アクティブなアイテムがこのアイテム/ウィンドウへのアクセスをブロックしている場合でもtrueを返します。ドラッグアンドドロップパターンに役立ちます。
		ImGuiHoveredFlags_AllowWhenOverlapped = 1 << 6,  // 位置が他のウィンドウによって遮られたり、重なっている場合でもtrueを返します
		ImGuiHoveredFlags_AllowWhenDisabled = 1 << 7,  // アイテムが無効になっていてもtrueを返します
		ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
		ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows
	};

	// 子ノードによって共有/継承されるDockSpace() のフラグ。
	// (一部のフラグは個々のノードに直接適用できます)
	// FIXME-DOCK : また、WIPおよび内部DockBuilder APIの使用を伴う可能性があるImGuiDockNodeFlagsPrivate_も参照してください。
	enum class ImGuiDockNodeFlags_
	{
		ImGuiDockNodeFlags_None = 0,
		ImGuiDockNodeFlags_KeepAliveOnly = 1 << 0,  // 共有      // ドックスペースノードを表示しないで、そのままにしてください。このドックスペースノードにドッキングされたWindowsは、ドッキング解除されません。
		//ImGuiDockNodeFlags_NoCentralNode          = 1 << 1,  // 共有      // セントラルノード(空のままにできるノード)を無効にする
		ImGuiDockNodeFlags_NoDockingInCentralNode = 1 << 2,  // 共有      // 常に空のままになるセントラルノード内のドッキングを無効にします。
		ImGuiDockNodeFlags_PassthruCentralNode = 1 << 3,  // 共有      // パススルードックスペースを有効にします。1)DockSpace() は、空のときにセントラルノードを除くすべてをカバーするImGuiCol_WindowBgバックグラウンドをレンダリングします。これを使用する場合、ホストウィンドウの意味は、おそらくBegin() の前にSetNextWindowBgAlpha(0.0f)を使用する必要があります。 2)セントラルノードが空の場合 : 入力パススルー+ DockingEmptyBgバックグラウンドを表示しません。詳細については、デモをご覧ください。
		ImGuiDockNodeFlags_NoSplit = 1 << 4,  // 共有/ローカル // ノードを小さなノードに分割することを無効にします。便利な例メインのルート1にドックスペースを埋め込む場合(ルート1では混乱を避けるために分割が無効になっている場合があります)。注 : オフにすると、既存の分割が保持されます。
		ImGuiDockNodeFlags_NoResize = 1 << 5,  // 共有/ローカル // スプリッター/セパレーターを使用してノードのサイズ変更を無効にします。プログラムでセットアップされたドックスペースで役立ちます。
		ImGuiDockNodeFlags_AutoHideTabBar = 1 << 6   // 共有/ローカル // ドックノードに単一のウィンドウがある場合、タブバーは自動的に非表示になります。
	};

	// BeginDragDropSource(), AcceptDragDropPayload() のフラグ
	enum class ImGuiDragDropFlags_
	{
		ImGuiDragDropFlags_None = 0,
		// BeginDragDropSource() flags
		ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0,  // デフォルトでは、BeginDragDropSourceを正常に呼び出すとツールチップが開き、ソースコンテンツのプレビューまたは説明を表示できます。このフラグはこの動作を無効にします。
		ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1,  // デフォルトでは、ドラッグするときにデータをクリアして、IsItemHovered() がfalseを返すようにして、後続のユーザーコードがツールチップを送信しないようにします。このフラグはこの動作を無効にするため、ソースアイテムでIsItemHovered() を呼び出すことができます。
		ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2,  // ソースノードをドラッグしているときにツリーノードを保持してヘッダーを折りたたむことができる動作を無効にします。
		ImGuiDragDropFlags_SourceAllowNullID = 1 << 3,  // ウィンドウに相対的な位置に基づいて一時的な識別子を作成することにより、一意の識別子を持たないText() 、Image() などのアイテムをドラッグソースとして使用できるようにします。これは、親愛なるimguiエコシステム内では非常に珍しいことなので、明確にしました。
		ImGuiDragDropFlags_SourceExtern = 1 << 4,  // 外部ソース(親愛なるimguiの外部から)、現在のアイテム/ウィンドウ情報を読み取ろうとしません。常にtrueを返します。同時にアクティブにできる外部ソースは1つだけです。
		ImGuiDragDropFlags_SourceAutoExpirePayload = 1 << 5,  // ソースの送信が停止した場合、ペイロードを自動的に期限切れにします(それ以外の場合、ペイロードはドラッグ中に保持されます)
		// AcceptDragDropPayload() flags
		ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10, // AcceptDragDropPayload() は、マウスボタンが離される前でもtrueを返します。その後、IsDelivery() を呼び出して、ペイロードを配信する必要があるかどうかをテストできます。
		ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11, // ターゲットにカーソルを合わせたときにデフォルトのハイライト長方形を描画しないでください。
		ImGuiDragDropFlags_AcceptNoPreviewTooltip = 1 << 12, // BeginDragDropSourceサイトからBeginDragDropSourceツールチップを非表示にすることを要求します。
		ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect // 配送前に先を覗いてペイロードを検査します。
	};

	// プライマリデータタイプ
	enum class ImGuiDataType_
	{
		ImGuiDataType_S8,      // signed char/char(賢明なコンパイラを使用)
		ImGuiDataType_U8,      // unsigned char
		ImGuiDataType_S16,     // short
		ImGuiDataType_U16,     // unsigned short
		ImGuiDataType_S32,     // int
		ImGuiDataType_U32,     // unsigned int
		ImGuiDataType_S64,     // long long/__int64
		ImGuiDataType_U64,     // unsigned long long/unsigned __int64
		ImGuiDataType_Float,   // float
		ImGuiDataType_Double,  // double
		ImGuiDataType_COUNT
	};

	// 基本的な方向
	enum class ImGuiDir_
	{
		ImGuiDir_None = -1,
		ImGuiDir_Left = 0,
		ImGuiDir_Right = 1,
		ImGuiDir_Up = 2,
		ImGuiDir_Down = 3,
		ImGuiDir_COUNT
	};

	// ユーザーはImGuiIO.KeyMap[] 配列にImGuiIO.KeysDown[512] 配列へのインデックスを入力します
	enum class ImGuiKey_
	{
		ImGuiKey_Tab,
		ImGuiKey_LeftArrow,
		ImGuiKey_RightArrow,
		ImGuiKey_UpArrow,
		ImGuiKey_DownArrow,
		ImGuiKey_PageUp,
		ImGuiKey_PageDown,
		ImGuiKey_Home,
		ImGuiKey_End,
		ImGuiKey_Insert,
		ImGuiKey_Delete,
		ImGuiKey_Backspace,
		ImGuiKey_Space,
		ImGuiKey_Enter,
		ImGuiKey_Escape,
		ImGuiKey_KeyPadEnter,
		ImGuiKey_A,                // for text edit CTRL+A : select all
		ImGuiKey_C,                // for text edit CTRL+C : copy
		ImGuiKey_V,                // for text edit CTRL+V : paste
		ImGuiKey_X,                // for text edit CTRL+X : cut
		ImGuiKey_Y,                // for text edit CTRL+Y : redo
		ImGuiKey_Z,                // for text edit CTRL+Z : undo
		ImGuiKey_COUNT
	};

	// ゲームパッド/キーボードの方向ナビゲーション
	// キーボード : io.ConfigFlags!=ImGuiConfigFlags_NavEnableKeyboardを有効に設定します。 NewFrame() は、io.KeysDown[] + io.KeyMap[]配列に基づいてio.NavInputs[] を自動的に埋めます。
	// ゲームパッド : io.ConfigFlags!=ImGuiConfigFlags_NavEnableGamepadを有効に設定します。バックエンド : ImGuiBackendFlags_HasGamepadを設定し、NewFrame() を呼び出す前にio.NavInputs[]フィールドを埋めます。 io.NavInputs[] はEndFrame() によってクリアされることに注意してください。
	// 詳細については、imgui.cppの手順を参照してください。 http://goo.gl/9LgVZWでPNG/PSDをダウンロードします。
	enum class ImGuiNavInput_
	{
		// ゲームパッドマッピング
		ImGuiNavInput_Activate,     // 値を有効化/開く/切り替える/微調整する      // 例えばクロス(PS4)、A(Xbox)、A(スイッチ)、スペース(キーボード)
		ImGuiNavInput_Cancel,       // キャンセル/閉じる/終了                       // 例えばサークル(PS4)、B(Xbox)、B(スイッチ)、エスケープ(キーボード)
		ImGuiNavInput_Input,        // テキスト入力/スクリーンキーボード             // 例えば三角形(PS4)、Y(Xbox)、X(スイッチ)、リターン(キーボード)
		ImGuiNavInput_Menu,         // タップ : メニューの切り替え/ホールド : フォーカス、移動、サイズ変更 // 例えば正方形(PS4)、X(Xbox)、Y(スイッチ)、Alt(キーボード)
		ImGuiNavInput_DpadLeft,     // ウィンドウの移動/調整/サイズ変更(w/PadMenu)   // 例えばD-pad左/右/上/下(ゲームパッド)、矢印キー（キーボード)
		ImGuiNavInput_DpadRight,    //
		ImGuiNavInput_DpadUp,       //
		ImGuiNavInput_DpadDown,     //
		ImGuiNavInput_LStickLeft,   // ウィンドウのスクロール/移動(PadMenu付き)           // 例えば左アナログスティック左/右/上/下
		ImGuiNavInput_LStickRight,  //
		ImGuiNavInput_LStickUp,     //
		ImGuiNavInput_LStickDown,   //
		ImGuiNavInput_FocusPrev,    // 次のウィンドウ(PadMenu付き)              // 例えばL1またはL2(PS4)、LBまたはLT(Xbox)、LまたはZL(スイッチ)s
		ImGuiNavInput_FocusNext,    // 前のウィンドウ(w/PadMenu)              // 例えばR1またはR2(PS4)、RBまたはRT(Xbox)、RまたはZL(スイッチ)
		ImGuiNavInput_TweakSlow,    // より遅い調整                               // 例えばL1またはL2(PS4)、LBまたはLT(Xbox)、LまたはZL(スイッチ)
		ImGuiNavInput_TweakFast,    // より速い調整                               // 例えばR1またはR2(PS4)、RBまたはRT(Xbox)、RまたはZL(スイッチ)
	};

	// io.ConfigFlagsに保存されている構成フラグ。ユーザー/アプリケーションによって設定されます。
	enum class ImGuiConfigFlags_
	{
		ImGuiConfigFlags_None = 0,
		ImGuiConfigFlags_NavEnableKeyboard = 1 << 0,  // マスターキーボードナビゲーション有効化フラグ。 NewFrame() は、io.KeysDown[] に基づいてio.NavInputs[] を自動的に埋めます。
		ImGuiConfigFlags_NavEnableGamepad = 1 << 1,  // マスターゲームパッドナビゲーション有効化フラグ。これは主に、imguiバックエンドにio.NavInputs[] を埋めるように指示するためのものです。バックエンドもImGuiBackendFlags_HasGamepadを設定する必要があります。
		ImGuiConfigFlags_NavEnableSetMousePos = 1 << 2,  // ナビゲーションにマウスカーソルを移動するよう指示します。仮想マウスの移動が厄介なテレビ/コンソールシステムで役立つ場合があります。 io.MousePosを更新し、io.WantSetMousePos = trueを設定します。有効にした場合、バインディングでio.WantSetMousePosリクエストを尊重する必要があります。そうしないと、ImGuiはマウスが前後にジャンプしているように反応します。
		ImGuiConfigFlags_NavNoCaptureKeyboard = 1 << 3,  // io.NavActiveが設定されている場合、io.WantCaptureKeyboardフラグを設定しないようにナビゲーションに指示します。
		ImGuiConfigFlags_NoMouse = 1 << 4,  // NewFrame() でマウスの位置/ボタンをクリアするようにimguiに指示します。これにより、バックエンドによって設定されたマウス情報を無視できます。
		ImGuiConfigFlags_NoMouseCursorChange = 1 << 5,  // マウスカーソルの形状と可視性を変更しないようにバックエンドに指示します。バックエンドカーソルの変更があなたの邪魔になり、マウスカーソルの変更にSetMouseCursor() を使用したくない場合に使用します。代わりに、自分でGetMouseCursor() を読むことにより、imguiからのリクエストを尊重することができます。

		// [BETA] Docking
		ImGuiConfigFlags_DockingEnable = 1 << 6,  // ドッキングイネーブルフラグ。

		// [BETA] ビューポート
		// ビューポートを使用する場合、ImGuiCol_WindowBgのデフォルト値を不透明(Alpha = 1.0)にして、ビューポートへの移行が目立たないようにすることをお勧めします。
		ImGuiConfigFlags_ViewportsEnable = 1 << 10, // ビューポート有効化フラグ(ImGuiConfigFlags_PlatformHasViewports +それぞれのバックエンドによって設定されるImGuiConfigFlags_RendererHasViewportsの両方が必要です)

		// ユーザーストレージ(バックエンド/エンジンが複数のプロジェクト間で共有されるコードと通信できるようにします。これらのフラグはコアDear ImGuiでは使用されません)
		ImGuiConfigFlags_IsSRGB = 1 << 20, // アプリケーションはSRGB対応です。
		ImGuiConfigFlags_IsTouchScreen = 1 << 21  // アプリケーションは、マウスの代わりにタッチスクリーンを使用しています。
	};

	// io.BackendFlagsに保存されているバックエンド機能フラグ。 imgui_impl_xxxまたはカスタムバックエンドによって設定されます。
	enum class ImGuiBackendFlags_
	{
		ImGuiBackendFlags_None = 0,
		ImGuiBackendFlags_HasGamepad = 1 << 0,  // バックエンドプラットフォームはゲームパッドをサポートし、現在接続されています。
		ImGuiBackendFlags_HasMouseCursors = 1 << 1,  // バックエンドプラットフォームは、OSカーソルの形状を変更するためにGetMouseCursor() 値を尊重することをサポートしています。
		ImGuiBackendFlags_HasSetMousePos = 1 << 2,  // バックエンドプラットフォームはio.WantSetMousePos要求をサポートして、OSマウスの位置を変更します(ImGuiConfigFlags_NavEnableSetMousePosが設定されている場合にのみ使用されます)。
		ImGuiBackendFlags_RendererHasVtxOffset = 1 << 3,  // バックエンドレンダラーはImDrawCmd::VtxOffsetをサポートします。これにより、16ビットインデックスを使用しながら、大きなメッシュ(64K +頂点)の出力が可能になります。

		// [BETA] ビューポート
		ImGuiBackendFlags_PlatformHasViewports = 1 << 10, // バックエンドプラットフォームは複数のビューポートをサポートしています。
		ImGuiBackendFlags_HasMouseHoveredViewport = 1 << 11, // バックエンドプラットフォームは、ImGuiViewportFlags_NoInputsフラグと、別のビューポートがフォーカスされているか、マウスをキャプチャしている可能性があるかを示す_REGARDLESS_を使用して、マウス_IGNORING_ビューポートの直下のビューポートにio。この情報は、ほとんどの高レベルのエンジンで正しく提供するために_簡単ではありません！例/バックエンドがそれをどのように扱うかを研究せずにこれを設定しないでください！
		ImGuiBackendFlags_RendererHasViewports = 1 << 12  // バックエンドレンダラーは複数のビューポートをサポートしています。
	};

	// PushStyleColor()/PopStyleColor() の列挙体
	enum class ImGuiCol_
	{
		ImGuiCol_Text,
		ImGuiCol_TextDisabled,
		ImGuiCol_WindowBg,             // 通常のウィンドウの背景
		ImGuiCol_ChildBg,              // 子ウィンドウの背景
		ImGuiCol_PopupBg,              // ポップアップ、メニュー、ツールチップウィンドウの背景
		ImGuiCol_Border,
		ImGuiCol_BorderShadow,
		ImGuiCol_FrameBg,              // チェックボックス、ラジオボタン、プロット、スライダー、テキスト入力の背景
		ImGuiCol_FrameBgHovered,
		ImGuiCol_FrameBgActive,
		ImGuiCol_TitleBg,
		ImGuiCol_TitleBgActive,
		ImGuiCol_TitleBgCollapsed,
		ImGuiCol_MenuBarBg,
		ImGuiCol_ScrollbarBg,
		ImGuiCol_ScrollbarGrab,
		ImGuiCol_ScrollbarGrabHovered,
		ImGuiCol_ScrollbarGrabActive,
		ImGuiCol_CheckMark,
		ImGuiCol_SliderGrab,
		ImGuiCol_SliderGrabActive,
		ImGuiCol_Button,
		ImGuiCol_ButtonHovered,
		ImGuiCol_ButtonActive,
		ImGuiCol_Header,               // ヘッダー*の色は、CollapsingHeader、TreeNode、Selectable、MenuItemに使用されます
		ImGuiCol_HeaderHovered,
		ImGuiCol_HeaderActive,
		ImGuiCol_Separator,
		ImGuiCol_SeparatorHovered,
		ImGuiCol_SeparatorActive,
		ImGuiCol_ResizeGrip,
		ImGuiCol_ResizeGripHovered,
		ImGuiCol_ResizeGripActive,
		ImGuiCol_Tab,
		ImGuiCol_TabHovered,
		ImGuiCol_TabActive,
		ImGuiCol_TabUnfocused,
		ImGuiCol_TabUnfocusedActive,
		ImGuiCol_DockingPreview,
		ImGuiCol_DockingEmptyBg,       // 空のノードの背景色(ウィンドウがドッキングされていないCentralNodeなど)
		ImGuiCol_PlotLines,
		ImGuiCol_PlotLinesHovered,
		ImGuiCol_PlotHistogram,
		ImGuiCol_PlotHistogramHovered,
		ImGuiCol_TextSelectedBg,
		ImGuiCol_DragDropTarget,
		ImGuiCol_NavHighlight,         // ゲームパッド/キーボード : 現在ハイライトされているアイテム
		ImGuiCol_NavWindowingHighlight, // Ctrl + Tabキーを使用するときにウィンドウを強調表示する
		ImGuiCol_NavWindowingDimBg,    // アクティブな場合、CTRL + TABウィンドウリストの背後にある画面全体を暗くする/色付けする
		ImGuiCol_ModalWindowDimBg,     // アクティブな場合、モーダルウィンドウの背後の画面全体を暗く/色付けする
		ImGuiCol_COUNT
	};

	// ImGuiStyle構造を一時的に変更するためのPushStyleVar()/PopStyleVar() の列挙体。
	// NB : 列挙型は、UIコード内でプッシュ/ポップする意味があるImGuiStyleのフィールドのみを参照します。初期化中に、ImGuiStyleに直接突っ込んでください。
	// NB : この列挙型を変更する場合、関連する内部テーブルGStyleVarInfo[]を適宜更新する必要があります。これは、列挙値をメンバーのオフセット/タイプにリンクする場所です。
	enum class ImGuiStyleVar_
	{
		// Enum name --------------------- // ImGuiStyle構造体のメンバー（説明についてはImGuiStyleを参照)
		ImGuiStyleVar_Alpha,              // float     Alpha
		ImGuiStyleVar_WindowPadding,      // ImVec2    Window Padding
		ImGuiStyleVar_WindowRounding,     // float     Window Rounding
		ImGuiStyleVar_WindowBorderSize,   // float     WindowBorderSize
		ImGuiStyleVar_WindowMinSize,      // ImVec2    WindowMinSize
		ImGuiStyleVar_WindowTitleAlign,   // ImVec2    WindowTitleAlign
		ImGuiStyleVar_ChildRounding,      // float     Child 外枠を角丸に
		ImGuiStyleVar_ChildBorderSize,    // float     Child 外枠の太さ
		ImGuiStyleVar_PopupRounding,      // float     Popup 外枠を角丸に
		ImGuiStyleVar_PopupBorderSize,    // float     Popup 外枠の太さ
		ImGuiStyleVar_FramePadding,       // ImVec2    FramePadding
		ImGuiStyleVar_FrameRounding,      // float     FrameRounding
		ImGuiStyleVar_FrameBorderSize,    // float     FrameBorderSize
		ImGuiStyleVar_ItemSpacing,        // ImVec2    ItemSpacing
		ImGuiStyleVar_ItemInnerSpacing,   // ImVec2    ItemInnerSpacing
		ImGuiStyleVar_IndentSpacing,      // float     IndentSpacing
		ImGuiStyleVar_ScrollbarSize,      // float     ScrollbarSize
		ImGuiStyleVar_ScrollbarRounding,  // float     ScrollbarRounding
		ImGuiStyleVar_GrabMinSize,        // float     GrabMinSize
		ImGuiStyleVar_GrabRounding,       // float     GrabRounding
		ImGuiStyleVar_TabRounding,        // float     TabRounding
		ImGuiStyleVar_ButtonTextAlign,    // ImVec2    ButtonTextAlign
		ImGuiStyleVar_SelectableTextAlign, // ImVec2    SelectableTextAlign
		ImGuiStyleVar_COUNT
	};

	// ColorEdit3()/ColorEdit4()/ColorPicker3()/ColorPicker4()/ColorButton() のフラグ
	enum class ImGuiColorEditFlags_
	{
		ImGuiColorEditFlags_None = 0,
		ImGuiColorEditFlags_NoAlpha = 1 << 1,  //             // ColorEdit, ColorPicker, ColorButton : Alphaコンポーネントを無視します(入力ポインターから3つのコンポーネントのみを読み取ります)。
		ImGuiColorEditFlags_NoPicker = 1 << 2,  //             // ColorEdit : 色付きの四角形をクリックしたときにピッカーを無効にします。
		ImGuiColorEditFlags_NoOptions = 1 << 3,  //             // ColorEdit : 入力/小さなプレビューを右クリックしたときのオプションメニューの切り替えを無効にします。
		ImGuiColorEditFlags_NoSmallPreview = 1 << 4,  //             // ColorEdit, ColorPicker : 入力の横にある色付きの正方形プレビューを無効にします。 (例 : 入力のみを表示する)
		ImGuiColorEditFlags_NoInputs = 1 << 5,  //             // ColorEdit, ColorPicker : 入力スライダー/テキストウィジェットを無効にします(たとえば、小さなプレビューの色付きの四角形のみを表示します)。
		ImGuiColorEditFlags_NoTooltip = 1 << 6,  //             // ColorEdit, ColorPicker, ColorButton : プレビューをホバーするときにツールチップを無効にします。
		ImGuiColorEditFlags_NoLabel = 1 << 7,  //             // ColorEdit, ColorPicker : インラインテキストラベルの表示を無効にします(ラベルは引き続きツールチップとピッカーに転送されます)。
		ImGuiColorEditFlags_NoSidePreview = 1 << 8,  //             // ColorPicker : ピッカーの右側で大きな色のプレビューを無効にし、代わりに小さな色の正方形のプレビューを使用します。
		ImGuiColorEditFlags_NoDragDrop = 1 << 9,  //             // ColorEdit : ドラッグアンドドロップターゲットを無効にします。 ColorButton : ドラッグアンドドロップソースを無効にします。

		// ユーザーオプション(ウィジェットを右クリックして、それらの一部を変更します)。
		ImGuiColorEditFlags_AlphaBar = 1 << 16, //             // ColorEdit, ColorPicker : ピッカーに垂直アルファバー/グラデーションを表示します。
		ImGuiColorEditFlags_AlphaPreview = 1 << 17, //             // ColorEdit, ColorPicker, ColorButton : プレビューを不透明ではなく、チェッカーボード上の透明色として表示します。
		ImGuiColorEditFlags_AlphaPreviewHalf = 1 << 18, //             // ColorEdit,ColorPicker,ColorButton : 不透明ではなく、半不透明/半市松模様を表示します。
		ImGuiColorEditFlags_HDR = 1 << 19, //             // (WIP) ColorEdit : 現在、RGBAエディションでは0.0f..1.0fの制限のみを無効にします(注 : おそらくImGuiColorEditFlags_Floatフラグも使用したいでしょう)。
		ImGuiColorEditFlags_DisplayRGB = 1 << 20, // [Display]   // ColorEdit : RGB/HSV/Hex間で_display_タイプをオーバーライドします。 ColorPicker : 1つ以上のRGB/HSV/Hexを使用して任意の組み合わせを選択します。
		ImGuiColorEditFlags_DisplayHSV = 1 << 21, // [Display]   // "
		ImGuiColorEditFlags_DisplayHex = 1 << 22, // [Display]   // "
		ImGuiColorEditFlags_Uint8 = 1 << 23, // [DataType]  // ColorEdit,ColorPicker,ColorButton : 0..255としてフォーマットされた_display_値。
		ImGuiColorEditFlags_Float = 1 << 24, // [DataType]  // ColorEdit,ColorPicker,ColorButton : _display_値は、0..255整数ではなく0.0f..1.0f浮動小数点としてフォーマットされます。整数による値の往復はありません。
		ImGuiColorEditFlags_PickerHueBar = 1 << 25, // [Picker]    // ColorPicker : Hueのバー、Sat/Valueの長方形。
		ImGuiColorEditFlags_PickerHueWheel = 1 << 26, // [Picker]    // ColorPicker : Hueのホイール、Sat/Valueの三角形。
		ImGuiColorEditFlags_InputRGB = 1 << 27, // [Input]     // ColorEdit,ColorPicker : RGB形式の入出力データ。
		ImGuiColorEditFlags_InputHSV = 1 << 28, // [Input]     // ColorEdit,ColorPicker : HSV形式の入出力データ。

		// デフォルトオプション。 SetColorEditOptions() を使用して、アプリケーションのデフォルトを設定できます。意図はおそらくあなたがしたくないことです
		// ほとんどの呼び出しでそれらをオーバーライドします。ユーザーがオプションメニューから選択できるようにするか、起動時にSetColorEditOptions() を1回呼び出します。
		ImGuiColorEditFlags__OptionsDefault = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,
	};

	// マウスボタンを識別します。 
	// これらの値は安定していることが保証されており、頻繁に0/1を直接使用します。便宜上、名前付き列挙型が提供されます。
	enum class ImGuiMouseButton_
	{
		ImGuiMouseButton_Left = 0,
		ImGuiMouseButton_Right = 1,
		ImGuiMouseButton_Middle = 2,
		ImGuiMouseButton_COUNT = 5
	};

	// GetMouseCursor() の列挙
	// ユーザーコードは、SetMouseCursor() を呼び出すことにより、指定されたカーソルを表示するためのバインディングを要求する場合があります。これが、ここで未使用とマークされたカーソルがある理由です。
	enum class ImGuiMouseCursor_
	{
		ImGuiMouseCursor_None = -1,
		ImGuiMouseCursor_Arrow = 0,
		ImGuiMouseCursor_TextInput,       // InputTextなどにカーソルを合わせると
		ImGuiMouseCursor_ResizeAll,       // (Dear ImGui関数では使用されません)
		ImGuiMouseCursor_ResizeNS,        // 水平の境界線上にマウスを移動するとき
		ImGuiMouseCursor_ResizeEW,        // 垂直の境界線または列の上にホバーするとき
		ImGuiMouseCursor_ResizeNESW,      // ウィンドウの左下隅にカーソルを合わせると
		ImGuiMouseCursor_ResizeNWSE,      // ウィンドウの右下隅にカーソルを合わせると
		ImGuiMouseCursor_Hand,            // (親愛なるImGui関数では使用されません。使用例ハイパーリンク)
		ImGuiMouseCursor_NotAllowed,      // 許可されていない操作で何かをホバーするとき。通常、交差した円。
		ImGuiMouseCursor_COUNT
	};

	// SetWindow***(),SetNextWindow***(),SetNextItem***() functions の列挙
	// 条件を表します。
	// 重要 : 通常の列挙型として扱います！二項演算子を使用して複数の値を結合しないでください！上記のすべての関数は、0をImGuiCond_Alwaysへのショートカットとして扱います。
	enum class ImGuiCond_
	{
		ImGuiCond_Always = 1 << 0, // 変数を設定する
		ImGuiCond_Once = 1 << 1, // ランタイムセッションごとに変数を1回設定します(成功した最初の呼び出しのみ)
		ImGuiCond_FirstUseEver = 1 << 2, // オブジェクト/ウィンドウに永続的に保存されたデータがない場合(.iniファイルにエントリがない場合)、変数を設定します
		ImGuiCond_Appearing = 1 << 3  // オブジェクト/ウィンドウが非表示/非アクティブになってから(または最初に)表示される場合は、変数を設定します
	};

#pragma endregion

	/**
	@brief stringの生成
	@param [in] format 入力文字列
	@param [in] args 表示させたい値
	@return string テキスト
	*/
	template<typename ... Args>
	const std::string MakeString(const std::string& format, const Args& ... args)
	{
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
		std::unique_ptr<char[]> buf(new char[size]);
		snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
	}

	LRESULT WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	@brief 初期化
	*/
	void Init(HWND hWnd, ComPtr<ID3D11Device> Device, ComPtr<ID3D11DeviceContext> DeviceContext);

	/**
	@brief 設定
	*/
	void Setting();

	/**
	@brief フォントの設定
	*/
	void SetFont(const char* font_str);

	/**
	@brief アイコンの追加
	*/
	void SetIcon(const char* icon_str, float size_icon, unsigned short icon_ranges_min, unsigned short icon_ranges_max);

	/**
	@brief 終了処理
	*/
	void Uninit();

	/**
	@brief 描画
	*/
	void Draw();

	/**
	@brief ディスプレイのサイズ
	*/
	Vector2 GetDisplaySize();

	/**
	@brief 経過時間を表示する
	*/
	void DisplayElapsedTime();

	/**
	@brief フレームレートを表示する
	*/
	void DisplayFramerate();

	/**
	@brief ウィンドウサイズを表示する
	*/
	void DisplayWindowsSize();

	/**
	@brief 表示フレーム開始
	*/
	void NewFrame();

	/**
	@brief 表示フレーム開始終わり
	*/
	void EndFrame();

	/**
	@brief NewFrame が呼ばれた
	*/
	bool IsCheckCallNewFrame();

#pragma region Windows

	/*
    // - Begin() =ウィンドウをスタックにプッシュし、追加を開始します。 End() =スタックからウィンドウをポップします。
    // - 同じフレーム中に同じウィンドウに複数回追加できます。
    // - 'bool * p_open！= nullptr'を渡すと、ウィンドウの右上隅にウィンドウを閉じるウィジェットが表示され、
    //   クリックするとブール値がfalseに設定されます。
    // - Begin() はfalseを返し、ウィンドウが折りたたまれているか完全にクリップされていることを示します。
    //   ウィンドウに何でも。戻り値に関係なく、Begin() 呼び出しごとに常に一致するEnd() を呼び出します！
    //   [重要：従来の理由により、これはBeginMenu / EndMenuなどの他のほとんどの機能と矛盾しています。
    //    BeginPopup / EndPopupなど。EndXXX呼び出しは、対応するBeginXXX関数が
    //    trueを返しました。 BeginとBeginChildが唯一の奇妙なものです。将来のアップデートで修正される予定です。]
    // - ウィンドウスタックの下部には、常に「デバッグ」と呼ばれるウィンドウが含まれていることに注意してください。
	*/

	/**
	@brief 新しいウィンドウ開始
	@param [in] p_open falseで開けない/trueで開ける
	*/
	bool Begin(const std::string& label, bool* p_open = nullptr, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);

	/**
	@brief ウィンドウ終了
	*/
	void End();

#pragma endregion

#pragma region Child Windows

	// - 子ウィンドウを使用して、ホストウィンドウ内の独立した独立したスクロール/クリッピング領域を開始します。子ウィンドウは自分の子を埋め込むことができます。
	// - 「サイズ」の各独立軸について：== 0.0f：残りのホストウィンドウサイズを使用/> 0.0f：固定サイズ/ <0.0f：残りのウィンドウサイズからabs（size）を引いたものを使用/各軸は異なるモードを使用できます。 ImVec2（0,400）。
	// - BeginChild() はfalseを返し、ウィンドウが折りたたまれているか完全にクリップされていることを示します。そのため、ウィンドウに何かを送信することを早めに省略できます。
	//   戻り値に関係なく、BeginChild() 呼び出しごとに常に一致するEndChild() を呼び出します（Beginと同様：これは、従来の理由によるもので、BeginChild() のように動作する通常のBegin() 以外のほとんどのBeginXXX関数と矛盾します） ]
	
	/**
	@brief 新しい子ウィンドウ開始
	@param [in] border falseで開けない/trueで開ける
	*/
	bool BeginChild(const char* str_id, const Vector2& size = Vector2(0, 0), bool border = true, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);
	
	/**
	@brief 新しい子ウィンドウ開始
	@param [in] border falseで開けない/trueで開ける
	*/
	bool BeginChild(unsigned int id, const Vector2& size = Vector2(0, 0), bool border = true, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);
	
	/**
	@brief 子ウィンドウ終了
	*/
	void EndChild();

#pragma endregion

#pragma region Windows Utilities

	// - 「現在のウィンドウ」= Begin() / End() ブロック内にある間に追加するウィンドウ。 'next window' = Begin() する次のウィンドウ。

	/**
	@brief 画面スペースの現在のウィンドウ位置を取得します（DrawList APIを介して独自の描画を行いたい場合に便利です）
	*/
	Vector2 GetWindowPos();

	/**
	@brief 現在のウィンドウサイズを取得
	*/
	Vector2 GetWindowSize();

	/**
	@brief 現在のウィンドウの幅を取得します（GetWindowSize() 。xのショートカット）
	*/
	float GetWindowWidth();

	/**
	@brief 現在のウィンドウの高さを取得する（GetWindowSize() 。yのショートカット）
	*/
	float GetWindowHeight();

	/**
	@brief 現在のウィンドウのタイトルバーの高さを取得
	*/
	float GetTitleBarHeight();
#pragma endregion

#pragma region Prefer using SetNextXXX functions(before Begin) rather that SetXXX functions(after Begin).

	/**
	@brief 次のウィンドウの位置を設定する。Begin() の前に呼び出します。
	@param [in] pos ウィンドウの位置
	@param [in] cond
	@param [in] pivot 与えられた点などを中心に
	*/
	void SetNextWindowPos(const Vector2& pos, ImGuiCond_ cond = (ImGuiCond_)0, const Vector2& pivot = Vector2(0, 0));

	/**
	@brief 次のウィンドウのサイズを設定する。Begin() の前に呼び出します。
	@param [in] size ウィンドウのサイズ
	@param [in] cond
	*/
	void SetNextWindowSize(const Vector2& size, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief 次のウィンドウのサイズ制限を設定
	*/
	void SetNextWindowSizeConstraints(const Vector2& size_min, const Vector2& size_max, void* custom_callback = nullptr, void* custom_callback_data = nullptr);
	
	/**
	@brief 次のウィンドウのコンテンツサイズを設定
	*/
	void SetNextWindowContentSize(const Vector2& size);
	
	/**
	@brief 次のウィンドウの折りたたみ状態を設定
	*/
	void SetNextWindowCollapsed(bool collapsed, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief 次のウィンドウをフォーカス / 一番上に設定
	*/
	void SetNextWindowFocus();

	/**
	@brief 次のウィンドウの背景色のアルファ値を設定
	*/
	void SetNextWindowBgAlpha(float alpha);
	
	/**
	@brief 次のウィンドウのビューポートを設定
	*/
	void SetNextWindowViewport(unsigned int viewport_id);

	/**
	@brief フォントスケールを設定
	*/
	void SetWindowFontScale(float scale);
	
	/**
	@brief ウィンドウ名を指定して位置を指定
	*/
	void SetWindowPos(const char* name, const Vector2& pos, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief ウィンドウ名を指定してサイズを指定
	*/
	void SetWindowSize(const char* name, const Vector2& size, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief ウィンドウ名を指定して折りたたみ状態を指定
	*/
	void SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief 名前付きウィンドウをフォーカス/一番上に設定 NULLを使用してフォーカスを削除
	*/
	void SetWindowFocus(const char* name);

#pragma endregion

#pragma region Content region

	// - これらの関数はすぐに再設計されることになっています（混乱を招きますが、ローカルウィンドウ座標の値が混乱し、不完全で、戻り値です）
	
	/**
	@brief ウィンドウ座標の現在のコンテンツ境界
	*/
	Vector2 GetContentRegionMax();
	
	/**
	@brief GetContentRegionMax() - GetCursorPos()
	*/
	Vector2 GetContentRegionAvail();

	/**
	@brief コンテンツの境界の最小値
	*/
	Vector2 GetWindowContentRegionMin();

	/**
	@brief ウィンドウの座標で、SetNextWindowContentSize（）でサイズをオーバーライドできるコンテンツ境界の最大値（おおよそ（0,0）+ Size-Scroll）
	*/
	Vector2 GetWindowContentRegionMax();
	
	float GetWindowContentRegionWidth();

#pragma endregion

#pragma region Windows Scrolling

	/**
	@brief スクロール量を取得
	*/
	float GetScrollX();

	/**
	@brief スクロール量を取得
	*/
	float GetScrollY();
	
	/**
	@brief 最大スクロール量を取得
	*/
	float GetScrollMaxX();

	/**
	@brief 最大スクロール量を取得
	*/
	float GetScrollMaxY();

	/**
	@brief スクロール量を設定する
	*/
	void SetScrollX(float scroll_x);

	/**
	@brief スクロール量を設定する
	*/
	void SetScrollY(float scroll_y);

	/**
	@brief 現在のカーソル位置が見えるようにスクロール量を調整します。
	*/
	void SetScrollHereX(float center_x_ratio = 0.5f);

	/**
	@brief 現在のカーソル位置が見えるようにスクロール量を調整します。
	*/
	void SetScrollHereY(float center_y_ratio = 0.5f);

	/**
	@brief 特定の位置が見えるようにスクロール量を調整します。
	*/
	void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
	
	/**
	@brief 特定の位置が見えるようにスクロール量を調整します。
	*/
	void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);

#pragma endregion

#pragma region Parameters stacks (shared)

	/**
	@brief 次のUIの色を設定
	@param [in] idx UIの種類の指定
	@param [in] col 色
	*/
	void PushStyleColor(ImGuiCol_ idx, unsigned int col);

	/**
	@brief UIの色を設定
	@param [in] idx UIの種類の指定
	@param [in] col 色
	*/
	void PushStyleColor(ImGuiCol_ idx, const Vector4& col);

	/**
	@brief UIの色変更を終了
	*/
	void PopStyleColor(int count = 1);

	/**
	@brief UIのスタイルを変更
	*/
	void PushStyleVar(ImGuiStyleVar_ idx, float val);

	/**
	@brief UIのスタイルを変更
	*/
	void PushStyleVar(ImGuiStyleVar_ idx, const Vector2& val);

	/**
	@brief UIのスタイルの変更を終了
	*/
	void PopStyleVar(int count = 1);

	/**
	@brief UIの色を取得
	*/
	Vector4 GetStyleColorVec4(ImGuiCol_ idx);

	/**
	@brief フォントサイズを取得
	*/
	float GetFontSize();

	/**
	@brief ピクセルのUV座標を取得
		ImDrawListAPIを介してカスタムシェイプを描画するのに役立ちます
	*/
	Vector2 GetFontTexUvWhitePixel();

	/**
	@brief UIの色を取得
	*/
	unsigned int GetColorU32(ImGuiCol_ idx, float alpha_mul = 1.0f);

	/**
	@brief UIの色を取得
	*/
	unsigned int GetColorU32(const Vector4& col);

	/**
	@brief UIの色を取得
	*/
	unsigned int GetColorU32(unsigned int col);

#pragma endregion

#pragma region Parameters stacks (current window)

	/**
	@brief これから先のUIパーツの幅を指定
	*/
	void PushItemWidth(float item_width);

	/**
	@brief UIパーツの幅の指定の終わり
	*/
	void PopItemWidth();

	/**
	@brief 折り返しさせる幅を指定します
	*/
	void PushTextWrapPos(float wrap_local_pos_x = 0.0f);

	/**
	@brief 折り返し終わり
	*/
	void PopTextWrapPos();

	/**
	@brief 次のUIパーツの幅を設定
	*/
	void SetNextItemWidth(float item_width);

	/**
	@brief ボタンの長押しを可能にする
	*/
	void PushButtonRepeat(bool repeat);

	/**
	@brief ボタンの長押しを終わりにする
	*/
	void PopButtonRepeat();

#pragma endregion

#pragma region Cursor / Layout

	// - 「カーソル」とは、現在の出力位置を意味します。
	// - ウィジェットの一般的な動作は、現在のカーソル位置で自分自身を出力し、カーソルを1行下に移動することです。
	// - ウィジェット間でSameLine() を呼び出して、直前の復帰と元のウィジェットの右側の出力を取り消すことができます。

	/**
	@brief 線を引く
	*/
	void Separator();

	/**
	@brief ウィジェットまたはグループ間で呼び出して、それらを水平にレイアウトします。
	@param [in] offset_from_start_x ウィンドウ座標で与えられるX位置
	*/
	void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);

	/**
	@brief 空白行を追加
	*/
	void NewLine();

	/**
	@brief 垂直方向の間隔を追加
	*/
	void Spacing();

	/**
	@brief 指定されたサイズのダミーアイテムを追加します。
	*/
	void Dummy(const Vector2& size);

	/**
	@brief コンテンツの位置を右に移動します
	*/
	void Indent(float indent_w = 0.0f);

	/**
	@brief コンテンツの位置を左に戻す
	*/
	void Unindent(float indent_w = 0.0f);

	/**
	@brief 水平開始位置をロック
	*/
	void BeginGroup();

	/**
	@brief 水平方向の開始位置のロック解除+グループの境界ボックス全体を1つの「アイテム」にキャプチャします
		（したがって、IsItemHovered（）またはグループ全体でSameLine() などのレイアウトプリミティブを使用できます）。
	*/
	void EndGroup();

	/**
	@brief ウィンドウ座標でのカーソル位置（ウィンドウ位置に相対的）
	*/
	Vector2 GetCursorPos();

	/**
	@brief ウィンドウ座標でのカーソル位置 X
	*/
	float GetCursorPosX();

	/**
	@brief ウィンドウ座標でのカーソル位置 Y
	*/
	float GetCursorPosY();

	/**
	@brief ウィンドウ座標でのカーソル位置 メインの絶対座標系を使用しています。
	*/
	void SetCursorPos(const Vector2& local_pos);

	/**
	@brief ウィンドウ座標でのカーソル位置 メインの絶対座標系を使用しています。
		GetWindowPos() + GetCursorPos() == GetCursorScreenPos() etc.)
	*/
	void SetCursorPosX(float local_x);

	/**
	@brief ウィンドウ座標でのカーソル位置 メインの絶対座標系を使用しています。
		GetWindowPos() + GetCursorPos() == GetCursorScreenPos() etc.)
	*/
	void SetCursorPosY(float local_y);

	/**
	@brief ウィンドウ座標での初期カーソル位置
	*/
	Vector2 GetCursorStartPos();

	/**
	@brief 複数のビューポートを使用する場合の絶対画面座標
		（0..io.DisplaySize）または自然OS座標でのカーソル位置。 ImDrawList APIを使用すると便利です。
	*/
	Vector2 GetCursorScreenPos();

	/**
	@brief 複数のビューポートを使用する場合の絶対画面座標
		（0..io.DisplaySize）または自然OS座標でのカーソル位置。
	*/
	void SetCursorScreenPos(const Vector2& pos);

	/**
	@brief 今後のテキストベースラインをFramePadding.yに垂直に揃えて、定期的にフレーム化されたアイテムに適切に揃えます
		（フレーム化されたアイテムの前の行にテキストがある場合に呼び出します）
	*/
	void AlignTextToFramePadding();

	/**
	@brief FontSize
	*/
	float GetTextLineHeight();

	/**
	@brief FontSize + style.ItemSpacing.y（2つの連続したテキスト行の間のピクセル単位の距離）
	*/
	float GetTextLineHeightWithSpacing();

	/**
	@brief FontSize + style.FramePadding.y * 2
	*/
	float GetFrameHeight();

	/**
	@brief FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y
		（フレーム化されたウィジェットの2つの連続した行の間のピクセル単位の距離）
	*/
	float GetFrameHeightWithSpacing();

#pragma endregion

#pragma region Widgets: Trees

	/**
	@brief ツリーノード
	@param [in] is_open false デフォルトで閉じています/true デフォルトで開いています
	*/
	bool NewTreeNode(const std::string& label, bool& is_open);

	/**
	@brief ツリーノード終わり
	*/
	void EndTreeNode();

	/**
	@brief ツリーノード
	*/
	bool TreeNode(const std::string& label);

	/**
	@brief ツリーノード終わり
	*/
	void TreePop();

	/**
	@brief 開閉可能なフィールド
	*/
	bool CollapsingHeader(const std::string& label, ImGuiTreeNodeFlags_ flags = (ImGuiTreeNodeFlags_)0);

	/**
	@brief 開閉可能なフィールド
	*/
	bool CollapsingHeader(const std::string& label, bool& is_open, ImGuiTreeNodeFlags_ flags = (ImGuiTreeNodeFlags_)0);

	/**
	@brief 次のツリーノードを開いた状態にします
	*/
	void SetNextItemOpen(bool is_open, ImGuiCond_ cond = (ImGuiCond_)0);

#pragma endregion

#pragma region Widgets: Selectables

	// - ホバーすると選択可能なハイライトが表示され、選択すると別の色を表示できます。
	// - 選択可能な隣人は、彼らの間に隙間を残さないために、ハイライトの境界を拡張します。これは、選択された一連のSelectableが連続して表示されるためです。
	
	//複数選択項目

	/**
	@brief 複数選択項目
	*/
	bool Selectable(const std::string& label, bool selected = false, ImGuiSelectableFlags_ flags = (ImGuiSelectableFlags_)0, const Vector2& size = Vector2(0, 0));  // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
	
	/**
	@brief 複数選択項目
	*/
	bool Selectable(const std::string& label, bool* p_selected, ImGuiSelectableFlags_ flags = (ImGuiSelectableFlags_)0, const Vector2& size = Vector2(0, 0));       // "bool* p_selected" point to the selection state (read-write), as a convenient helper.

#pragma endregion

#pragma region Widgets: List Boxes

	// - FIXME：すべての新しいAPIとの一貫性を保つため、ListBoxHeader / ListBoxFooterは実際にはBeginListBox / EndListBoxと呼ばれるべきです。それらの名前を変更します。
	
	/**
	@brief リストボックス
	@param [out] current_item 選んだアイテムIndex
	@param [in] items アイテムリスト
	@param [in] items_count アイテムの数
	*/
	bool ListBox(const std::string& label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
	
	bool ListBoxHeader(const std::string& label, const Vector2& size = Vector2(0, 0)); // use if you want to reimplement ListBox() will custom data or interactions. if the function return true, you can output elements then call ListBoxFooter() afterwards.
	bool ListBoxHeader(const std::string& label, int items_count, int height_in_items = -1); // "
	void ListBoxFooter(); // terminate the scrolling region. only call ListBoxFooter() if ListBoxHeader() returned true!

#pragma endregion

#pragma region Widgets: Data Plotting

	/**
	@brief 折れ線グラフ (プロットライン)
	@param [in] values データ
	@param [in] values_count データの数
	@param [in] overlay_text タイトル
	@param [in] scale_min 最小値
	@param [in] scale_max 最大値
	@param [in] graph_size グラフサイズ Vector2(0, 0)の場合は幅高さは自動です
	*/
	void PlotLines(const std::string& label, const float* values, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0), int stride = sizeof(float));
	
	/**
	@brief 折れ線グラフ (プロットライン)
	@param [in] values_getter 関数ポインタ
	@param [in] data データ
	@param [in] values_count データの数
	@param [in] overlay_text タイトル
	@param [in] scale_min 最小値
	@param [in] scale_max 最大値
	@param [in] graph_size グラフサイズ Vector2(0, 0)の場合は幅高さは自動です
	*/
	void PlotLines(const std::string& label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0));
	
	/**
	@brief ヒストグラム
	@param [in] values データ
	@param [in] values_count データの数
	@param [in] overlay_text タイトル
	@param [in] scale_min 最小値
	@param [in] scale_max 最大値
	@param [in] graph_size グラフサイズ Vector2(0, 0)の場合は幅高さは自動です
	*/
	void PlotHistogram(const std::string& label, const float* values, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0), int stride = sizeof(float));
	
	/**
	@brief ヒストグラム
	@param [in] values_getter 関数ポインタ
	@param [in] data データ
	@param [in] values_count データの数
	@param [in] overlay_text タイトル
	@param [in] scale_min 最小値
	@param [in] scale_max 最大値
	@param [in] graph_size グラフサイズ Vector2(0, 0)の場合は幅高さは自動です
	*/
	void PlotHistogram(const std::string& label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0));

#pragma endregion

#pragma region Widgets: Menus

	// - ウィンドウImGuiWindowFlags_MenuBarでBeginMenuBar（）を使用して、メニューバーに追加します。
	// - BeginMainMenuBar（）を使用して、画面上部にメニューバーを作成します。

	/**
	@brief メニューバーの開始
	*/
	bool BeginMenuBar();

	/**
	@brief メニューバーの終わり 
		BeginMenuBar() がtrueのときのみ
	*/
	void EndMenuBar();

	/**
	@brief 全画面メニューバーの開始
	*/
	bool BeginMainMenuBar();

	/**
	@brief 全画面メニューバーの終わり 
		BeginMainMenuBar() がtrueのときのみ
	*/
	void EndMainMenuBar();

	/**
	@brief メニューの開始
	*/
	bool BeginMenu(const std::string& label, bool enabled = true);

	/**
	@brief メニューの終わり
		BeginMenu() がtrueのときのみ
	*/
	void EndMenu();

	/**
	@brief メニューのアイテム
	*/
	bool MenuItem(const std::string& label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);

	/**
	@brief メニューのアイテム
	*/
	bool MenuItem(const std::string& label, const char* shortcut, bool* p_selected, bool enabled = true);

#pragma endregion

#pragma region Widgets: Trees Tooltips

	// - ツールチップはマウスに続くウィンドウで、フォーカスを奪いません。

	/**
	@brief ツールチップウィンドウを開始/追加します。
		（あらゆる種類のアイテムを含む）フル機能のツールチップを作成します。
	*/
	void BeginTooltip();

	/**
	@brief ツールチップウィンドウを終了
	*/
	void EndTooltip();

	/**
	@brief テキストのみのツールチップを設定します。
	通常はImGui::IsItemHovered() で使用します。 SetTooltip() への以前の呼び出しをオーバーライドします。
	*/
	void SetTooltip(const std::string& label);

#pragma endregion

#pragma region Popups, Modals

	// ポップアップウィンドウのプロパティは次のとおりです。
	// - それらは、通常のマウスホバリング検出をブロックします。
	// - モーダルでない限り、それらの外側のどこかをクリックするか、ESCAPEを押すことで閉じることができます。
	// - それらの可視性状態（bool）は、通常のBegin（）呼び出しで慣れているプログラマーによって保持されるのではなく、imguiによって内部的に保持されます。
	//   ユーザーは、OpenPopup（）を呼び出すことにより、可視性状態を操作できます。
	// - Popup Context関数には、デフォルトで右マウス（ImGuiMouseButton_Right = 1）を使用します。
	// IsItemHovered（ImGuiHoveredFlags_AllowWhenBlockedByPopup）を使用して、それをバイパスし、ポップアップによって通常ブロックされている場合でもホバリングを検出できます。
	// これらの3つのプロパティは接続されています。ライブラリはいつでもポップアップを閉じることができるため、可視性状態を保持する必要があります。
	
	/**
	@brief IDを指定してポップアップさせます 
	@param [in] str_id ポップアップID
		BeginPopup(),EndPopup() との併用
	*/
	void OpenPopup(const char* str_id);

	/**
	@brief ポップアップの開始
	@param [in] str_id ポップアップID
		ポップアップが開いている場合はtrueを返し、出力を開始できます。 BeginPopup（）がtrueを返す場合にのみEndPopup（）を呼び出してください！
	*/
	bool BeginPopup(const char* str_id, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0); 
	
	/**
	@brief アイテムをクリック時にポップアップの開始
	@param [in] str_id ポップアップID
	@param [in] mouse_button マウスのボタン デフォルトは右クリック
	*/
	bool BeginPopupContextItem(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1);

	/**
	@brief ImGuiウィンドウをクリック時にポップアップの開始
	@param [in] str_id ポップアップID
	@param [in] mouse_button マウスのボタン デフォルトは右クリック
	*/
	bool BeginPopupContextWindow(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1, bool also_over_items = true);

	/**
	@brief imguiウィンドウがない場合でのクリック時にポップアップの開始 
	@param [in] str_id ポップアップID
	@param [in] mouse_button マウスのボタン デフォルトは右クリック
	*/
	bool BeginPopupContextVoid(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1);
	
	/**
	@brief モーダルダイアログをクリック時にポップアップの開始
	*/
	bool BeginPopupModal(const char* name, bool* p_open = nullptr, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);

	/**
	@brief ポップアップの終了
		BeginPopupXXX() がtrueを返す場合にのみEndPopup() を呼び出してください！
	*/
	void EndPopup();

	/**
	@brief 項目をクリックしたときにポップアップの開始 
	@param [in] str_id ポップアップID
	@param [in] mouse_button マウスのボタン デフォルトは右クリック
	*/
	bool OpenPopupOnItemClick(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1);
	
	/**
	@brief 指定ポップアップIDが現在はポップアップしています
	*/
	bool IsPopupOpen(const char* str_id);

	/**
	@brief ポップアップを閉じます
		MenuItemまたはSelectableをクリックすると、ポップアップは自動的に閉じます。
	*/
	void CloseCurrentPopup();

#pragma endregion

#pragma region ID stack / scopes

	// - DearImGuiでのIDの処理方法の詳細については、FAQを参照してください。ループ内でウィジェットを作成している場合は、
	//   一意の識別子（オブジェクトポインター、ループインデックスなど）をプッシュして、一意に区別したい場合があります。
	// - 結果のIDは、スタック全体のハッシュです。
	// - また、ウィジェットラベル内で「Label ## foobar」構文を使用して、それらを互いに区別することもできます。
	// - このヘッダーファイルでは、「ラベル」/「名前」という用語を使用して、IDとして表示および使用される文字列を示します。
	//   「str_id」は、IDとしてのみ使用され、通常は表示されない文字列を示します。

	/**
	@brief IDスタックに文字列をプッシュします（文字列をハッシュします）
	*/
	void PushID(const char* str_id);

	/**
	@brief IDスタックに文字列をプッシュします（文字列をハッシュします）
	*/
	void PushID(const char* str_id_begin, const char* str_id_end); 

	/**
	@brief IDスタックにポインターをプッシュします（ポインターをハッシュします）
	*/
	void PushID(const void* ptr_id);

	/**
	@brief IDスタックに整数をプッシュします（整数をハッシュします）。
	*/
	void PushID(int int_id);

	/**
	@brief IDスタックからポップします。
	*/
	void PopID();

#pragma endregion

#pragma region Widgets: Text

	/**
	@brief 高速な文字表示
	@param [in] text 表示内容
		書式なしの生テキスト、メモリコピーや文字コード変換がないので高速です
	*/
	void TextUnformatted(const char* text, const char* text_end = nullptr);

	/**
	@brief 文字表示
	@param [in] fmt 表示内容
	*/
	void Text(const std::string& fmt);

	/**
	@brief 色付き文字表示
	@param [in] fmt 表示内容
	@param [in] collar 色
	*/
	void Text(const std::string& fmt, const Vector4& collar);

	/**
	@brief Bullet付き文字表示
	@param [in] fmt 表示内容
	*/
	void BulletText(const std::string& fmt);

	/**
	@brief 無効な文字 グレーで表示
	@param [in] fmt 表示内容
	*/
	void TextDisabled(const std::string& fmt);

	/**
	@brief 自動的に折り返して次の行に表示
	@param [in] fmt 表示内容
	*/
	void TextWrapped(const std::string& fmt);

	/**
	@brief value + labelウィジェットと同じ方法で整列されたtext + labelを表示します
	@param [in] label ラベル
	@param [in] fmt 値
	*/
	void LabelText(const std::string& label, const std::string& fmt);

#pragma endregion

#pragma region Widgets: Color Editor/Picker

	// ウィジェット：カラーエディター/ピッカー（ヒント：ColorEdit *関数には、小さな色のプレビュー四角形があり、左クリックしてピッカーを開き、右クリックしてオプションメニューを開くことができます。）
	// - C ++では、「float v [X]」関数の引数は「float * v」と同じであることに注意してください。配列構文は、アクセス可能な要素の数を文書化する方法にすぎません。
	// - 連続する構造体から最初のフロート要素のアドレスを渡すことができます。 ＆myvector.x

	/**
	@brief RGB値
	*/
	bool ColorEdit3(const std::string& label, float col[3], ImGuiColorEditFlags_ flags = (ImGuiColorEditFlags_)0);

	/**
	@brief RGBA
	*/
	bool ColorEdit4(const std::string& label, float col[4], ImGuiColorEditFlags_ flags = (ImGuiColorEditFlags_)0);

	bool ColorPicker3(const std::string& label, float col[3], ImGuiColorEditFlags_ flags = (ImGuiColorEditFlags_)0);
	bool ColorPicker4(const std::string& label, float col[4], ImGuiColorEditFlags_ flags = (ImGuiColorEditFlags_)0, const float* ref_col = nullptr);
	bool ColorButton(const char* desc_id, const Vector4& col, ImGuiColorEditFlags_ flags = (ImGuiColorEditFlags_)0, Vector2 size = Vector2(0, 0));  // display a colored square/button, hover for details, return true when pressed.
	void SetColorEditOptions(ImGuiColorEditFlags_ flags);                     // initialize current options (generally on application startup) if you want to select a default format, picker type, etc. User will be able to change many settings, unless you pass the _NoOptions flag to your calls.

#pragma endregion

#pragma region Widgets: Sliders

	// - Ctrlキーを押しながらスライダーをクリックして、入力ボックスに変換します。手動で入力した値は固定されず、範囲外になる可能性があります。
	// - 書式文字列を調整して、値をプレフィックス、サフィックスで装飾するか、編集と表示の精度を調整します。 "％.3f"-> 1.234; 「％5.2f秒」-> 01.23秒。 "ビスケット：％.0f"->ビスケット：1;等
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderFloat(const std::string& label, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);     // スライダー内ラベルまたはユニット表示のプレフィックスまたはサフィックスで値を修飾するようにフォーマットを調整します。 power！= 1.0をパワーカーブスライダーに使用します
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderFloat2(const std::string& label, float v[2], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderFloat3(const std::string& label, float v[3], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderFloat4(const std::string& label, float v[4], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief スクロールバー 角度
	@param [in/out] v 操作対象
	*/
	bool SliderAngle(const std::string& label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg");
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderInt(const std::string& label, int* v, int v_min, int v_max, const char* format = "%d");
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderInt2(const std::string& label, int v[2], int v_min, int v_max, const char* format = "%d");
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderInt3(const std::string& label, int v[3], int v_min, int v_max, const char* format = "%d");
	
	/**
	@brief スクロールバー
	@param [in/out] v 操作対象
	*/
	bool SliderInt4(const std::string& label, int v[4], int v_min, int v_max, const char* format = "%d");
	
	bool SliderScalar(const std::string& label, ImGuiDataType_ data_type, void* p_data, const void* p_min, const void* p_max, const char* format = nullptr, float power = 1.0f);
	bool SliderScalarN(const std::string& label, ImGuiDataType_ data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = nullptr, float power = 1.0f);
	bool VSliderFloat(const std::string& label, const Vector2& size, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	bool VSliderInt(const std::string& label, const Vector2& size, int* v, int v_min, int v_max, const char* format = "%d");
	bool VSliderScalar(const std::string& label, const Vector2& size, ImGuiDataType_ data_type, void* p_data, const void* p_min, const void* p_max, const char* format = nullptr, float power = 1.0f);

#pragma endregion

#pragma region Widgets: Input with Keyboard

	// - InputText() をstd::stringなどの動的な文字列型または独自のもので使用する場合は、imgui_stdlib.hを参照してください
	// - ImGuiInputTextFlags_フラグのほとんどは、InputText() に対してのみ有用であり、InputFloatX、InputIntX、InputDoubleなどには役立ちません。

	/**
	@brief テキストボックス
	@param [in] str 受け取り先
	*/
	bool InputText(const std::string& label, std::string* str, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief テキストボックス
	@param [in] buf 受け取り先
	*/
	bool InputText(const std::string& label, char* buf, size_t buf_size, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief テキストボックス
	@param [in] str 受け取り先
	*/
	bool InputTextMultiline(const std::string& label, std::string* str, const Vector2& size = Vector2(0, 0), ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief テキストボックス
	@param [in] buf 受け取り先
	*/
	bool InputTextMultiline(const std::string& label, char* buf, size_t buf_size, const Vector2& size = Vector2(0, 0), ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief テキストボックス
	@param [in] hint ヒント
	@param [in] str 受け取り先
	*/
	bool InputTextWithHint(const std::string& label, const std::string& hint, std::string* str, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief テキストボックス
	@param [in] hint ヒント
	@param [in] buf 受け取り先
	*/
	bool InputTextWithHint(const std::string& label, const std::string& hint, char* buf, size_t buf_size, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief float 入力
	@param [in] v 受け取り先
	*/
	bool InputFloat(const std::string& label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief float 入力
	@param [in] v 受け取り先
	*/
	bool InputFloat2(const std::string& label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief float 入力
	@param [in] v 受け取り先
	*/
	bool InputFloat3(const std::string& label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief float 入力
	@param [in] v 受け取り先
	*/
	bool InputFloat4(const std::string& label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int 入力
	@param [in] v 受け取り先
	*/
	bool InputInt(const std::string& label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int 入力
	@param [in] v 受け取り先
	*/
	bool InputInt2(const std::string& label, int v[2], ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int 入力
	@param [in] v 受け取り先
	*/
	bool InputInt3(const std::string& label, int v[3], ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int 入力
	@param [in] v 受け取り先
	*/
	bool InputInt4(const std::string& label, int v[4], ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief double 入力
	@param [in] v 受け取り先
	*/
	bool InputDouble(const std::string& label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	bool InputScalar(const std::string& label, ImGuiDataType_ data_type, void* p_data, const void* p_step = nullptr, const void* p_step_fast = nullptr, const char* format = nullptr, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	bool InputScalarN(const std::string& label, ImGuiDataType_ data_type, void* p_data, int components, const void* p_step = nullptr, const void* p_step_fast = nullptr, const char* format = nullptr, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);

#pragma endregion

#pragma region Widgets: Main

	// - ほとんどのウィジェットは、値が変更されたとき、または押された/選択されたときにtrueを返します
	// - 多くのIsItemXXX関数（IsItemActive、IsItemHoveredなど）の1つを使用して、ウィジェットの状態を照会することもできます。

	/**
	@brief ボタン
	@param [in] label ボタン名
	@param [in] size_arg ボタンサイズ
	*/
	bool Button(const std::string& label, const Vector2& size_arg = Vector2(0, 0));

	/**
	@brief 小さなボタン
	@param [in] label ボタン名
	*/
	bool SmallButton(const std::string& label);

	/**
	@brief 矢印の形の正方形ボタン
	@param [in] label ボタン名
	@param [in] dir 向き
	*/
	bool ArrowButton(const char* str_id, ImGuiDir_ dir);

	/**
	@brief テクスチャの表示
	@param [in] user_texture_id テクスチャのポインタ
	*/
	void Image(void* user_texture_id, const Vector2& size, const Vector2& uv0 = Vector2(0, 0), const Vector2& uv1 = Vector2(1, 1), const Vector4& tint_col = Vector4(1, 1, 1, 1), const Vector4& border_col = Vector4(0, 0, 0, 0));

	/**
	@brief テクスチャでボタン
	@param [in] user_texture_id テクスチャのポインタ
	*/
	bool ImageButton(void* user_texture_id, const Vector2& size, const Vector2& uv0 = Vector2(0, 0), const Vector2& uv1 = Vector2(1, 1), int frame_padding = -1, const Vector4& bg_col = Vector4(0, 0, 0, 0), const Vector4& tint_col = Vector4(1, 1, 1, 1));

	/**
	@brief チェックボックス
	@param [in] label チェックボックス名
	@param [in] flag 操作するbool
	*/
	bool Checkbox(const std::string& label, bool& flag);

	/**
	@brief ラジオボタン
	@param [in] label ラジオボタン名
	*/
	bool RadioButton(const std::string& label, bool active);

	/**
	@brief ラジオボタン
	@param [in] label ラジオボタン名
	@param [in] value v_buttonの格納先
	@param [in] v_button valueに格納する値
	*/
	bool RadioButton(const std::string& label, int* value, int v_button);

	/**
	@brief プログレスバー : 0 ~ 1 までの中での fraction が何％の位置にいるのかを表示します。
	*/
	void ProgressBar(float fraction, const Vector2& size_arg = Vector2(-1, 0), const char* overlay = nullptr);

	/**
	@brief 小さな円を描き、カーソルを同じ線上に置きます。 TreeNode() が使用する距離と同じ距離で、GetTreeNodeToLabelSpacing() によってカーソルのx位置を進める
	*/
	void Bullet();

#pragma endregion

#pragma region Widgets: Combo Box

	// - BeginCombo() / EndCombo() APIを使用すると、次のように作成することで、コンテンツや選択状態を自由に管理できます。 Selectable() アイテム。
	// - 古いCombo() apiは、BeginCombo() / EndCombo() のヘルパーであり、便利な目的で利用できます。

	bool BeginCombo(const std::string& label, const char* preview_value, ImGuiComboFlags_ flags = (ImGuiComboFlags_)0);

	// only call EndCombo() if BeginCombo() returns true!
	void EndCombo(); 

	/**
	@brief ドロップダウンリスト
	@param [in] current_item アイテムのIndex
	@param [in] items アイテムリスト
	@param [in] items_size アイテムの数
	*/
	bool Combo(const std::string& label, int* current_item, const char* const items[], int items_size, int popup_max_height_in_items = -1);

	/**
	@brief ドロップダウンリスト
	文字列内でアイテムを\0で区切り、item-listを\0\0で終了します。例えば "One\0Two\0Three\0"
	@param [in] current_item アイテムのIndex
	@param [in] items_separated_by_zeros アイテムリスト
	*/
	bool Combo(const std::string& label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);

#pragma endregion

#pragma region Widgets: Drags

	// - Ctrlキーを押しながら任意のドラッグボックスをクリックして、入力ボックスに変換します。手動で入力した値は固定されず、範囲外になる可能性があります。
	// - すべての関数のすべてのFloat2 / Float3 / Float4 / Int2 / Int3 / Int4バージョンでは、「float v [X]」関数の引数は「float * v」と同じであることに注意してください。配列構文は文書化の方法にすぎませんアクセス可能であると予想される要素の数。連続したセットから最初の要素のアドレスを渡すことができます。 ＆myvector.x
	// - 書式文字列を調整して、値をプレフィックス、サフィックスで装飾するか、編集と表示の精度を調整します。 "％.3f"-> 1.234; 「％5.2f秒」-> 01.23秒。 "ビスケット：％.0f"->ビスケット：1;等
	// - 速度はマウスの動きのピクセルごとです（v_speed = 0.2f：値を1増やすには、マウスを5ピクセル動かす必要があります）。ゲームパッド/キーボードナビゲーションの場合、最小速度はMax（v_speed、minimum_step_at_given_precision）です。
	// - v_min <v_maxを使用して、指定された制限に編集をクランプします。 Ctrlキーを押しながらクリックする手動入力は、これらの制限を上書きできることに注意してください。
	// - v_max = FLT_MAX / INT_MAXなどを使用して最大値へのクランプを回避します。v_min= -FLT_MAX / INT_MINと同様に最小値へのクランプを回避します。
	// - 編集をロックするには、v_min> v_maxを使用します。

	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragFloat(const std::string& label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);     // If v_min >= v_max we have no bound
	
	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragFloat2(const std::string& label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragFloat3(const std::string& label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragFloat4(const std::string& label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief 	最小値, 最大値 スライダーを2つ作成
	@param [in/out] v_current_min 操作対象
	@param [in/out] v_current_max 操作対象
	*/
	bool DragFloatRange2(const std::string& label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = nullptr, float power = 1.0f);
	
	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragInt(const std::string& label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");                                       // If v_min >= v_max we have no bound
	
	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragInt2(const std::string& label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	
	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragInt3(const std::string& label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	
	/**
	@brief スライダー
	@param [in/out] v 操作対象
	*/
	bool DragInt4(const std::string& label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	
	bool DragIntRange2(const std::string& label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = nullptr);
	bool DragScalar(const std::string& label, ImGuiDataType_ data_type, void* p_data, float v_speed, const void* p_min = nullptr, const void* p_max = nullptr, const char* format = nullptr, float power = 1.0f);
	bool DragScalarN(const std::string& label, ImGuiDataType_ data_type, void* p_data, int components, float v_speed, const void* p_min = nullptr, const void* p_max = nullptr, const char* format = nullptr, float power = 1.0f);

#pragma endregion

#pragma region Item / Widgets Utilities

	// - ほとんどの関数は、送信した最後の/前のアイテムを参照しています。
	// - これらの機能のほとんどのインタラクティブな視覚化については、「ウィジェット->ステータスのクエリ」のデモウィンドウをご覧ください。

	/**
	@brief 最後のアイテムがホバーされていますか？ （使用可能、別名ポップアップなどによってブロックされない）。
		その他のオプションについては、ImGuiHoveredFlags_を参照してください。
	*/
	bool IsItemHovered(ImGuiHoveredFlags_ flags = (ImGuiHoveredFlags_)0);

	/**
	@brief 最後のアイテムはアクティブですか？ （例：ボタンが押されている、テキストフィールドが編集されています。
		アイテム上でマウスボタンを押している間、これは継続的にtrueを返します。相互作用しないアイテムは常にfalseを返します）
	*/
	bool IsItemActive();

	/**
	@brief 最後のアイテムはキーボード/ゲームパッドナビゲーションに焦点を合わせていますか？
	*/
	bool IsItemFocused();

	/**
	@brief 最後のアイテムはクリックされましたか？ 
		（例：ボタン/ノードをクリックしただけ）== IsMouseClicked（mouse_button）&& IsItemHovered() 
	*/
	bool IsItemClicked(ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)0);

	/**
	@brief 最後のアイテムは表示されていますか？ （
		クリッピング/スクロールのためにアイテムが見えなくなる場合があります）
	*/
	bool IsItemVisible();

	/**
	@brief 最後のアイテムは、このフレームの基礎となる値を変更しましたか？または押された？
		これは通常、多くのウィジェットの「ブール」戻り値と同じです。
	*/
	bool IsItemEdited(); 

	/**
	@brief 最後にアクティブにしたアイテムでした（アイテムは以前は非アクティブでした）。
	*/
	bool IsItemActivated();

	/**
	@brief 最後に非アクティブにしたアイテム（アイテムは以前アクティブでした）。
		継続的な編集が必要なウィジェットを使用した元に戻す/やり直しパターンに役立ちます。
	*/
	bool IsItemDeactivated();

	/**
	@brief 最後の項目がアクティブになったときに非アクティブになり、値が変更されましたか？ 
		（例：スライダー/ドラッグの移動）。
		継続的な編集が必要なウィジェットを使用した元に戻す/やり直しパターンに役立ちます。
		誤検知が発生する可能性があることに注意してください（Combo() / ListBox() / Selectable() などの一部のウィジェットは、既に選択されているアイテムをクリックしてもtrueを返します）。
	*/
	bool IsItemDeactivatedAfterEdit();

	/**
	@brief 最後のアイテムのオープン状態は切り替えられましたか？ TreeNode() によって設定されます。
	*/
	bool IsItemToggledOpen();

	/**
	@brief ホバーされたアイテムですか？
	*/
	bool IsAnyItemHovered();

	/**
	@brief アクティブなアイテムはありますか？
	*/
	bool IsAnyItemActive();

	/**
	@brief フォーカスされているアイテムはありますか？
	*/
	bool IsAnyItemFocused();

	/**
	@brief 最後のアイテム（画面スペース）の左上の境界矩形を取得します
	*/
	Vector2 GetItemRectMin();

	/**
	@brief 最後のアイテム（画面スペース）の右下の境界矩形を取得します
	*/
	Vector2 GetItemRectMax();

	/**
	@brief 最後のアイテムのサイズを取得
	*/
	Vector2 GetItemRectSize();

	/**
	@brief 最後のアイテムが後続のアイテムとオーバーラップできるようにします。
		非表示のボタン、選択可能項目などで未使用の領域をキャッチするのに役立つ場合があります。
	*/
	void SetItemAllowOverlap();

#pragma endregion

#pragma region Inputs Utilities: Keyboard

	// - 'int user_key_index'の場合、バックエンド/エンジンがio.KeysDown []に保存した方法に応じて、独自のインデックス/列挙を使用できます。
	// - これらの値の意味はわかりません。 GetKeyIndex() を使用して、ImGuiKey_値をユーザーインデックスにマップできます。
	
	/**
	@brief ImGuiKey_で指定キーのIndexを取得します
	@param [in] imgui_key ImGuiKey_ キーの指定
	@param return キーのIndex
	*/
	int GetKeyIndex(ImGuiKey_ imgui_key);
	
	/**
	@brief キー入力
	@param [in] user_key_index GetKeyIndex() のIndex
	*/
	bool IsKeyDown(int user_key_index);

	/**
	@brief キー入力 長押し
	@param [in] user_key_index GetKeyIndex() のIndex
	@param [in] repeat リピート入力
	*/
	bool IsKeyPressed(int user_key_index, bool repeat = true);

	/**
	@brief キー入力 離した時
	@param [in] user_key_index GetKeyIndex() のIndex
	*/
	bool IsKeyReleased(int user_key_index);

	// uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
	int GetKeyPressedAmount(int key_index, float repeat_delay, float rate);

	// attention: misleading name! manually override io.WantCaptureKeyboard flag next frame (said flag is entirely left for your application to handle). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting "io.WantCaptureKeyboard = want_capture_keyboard_value"; after the next NewFrame() call.
	void CaptureKeyboardFromApp(bool want_capture_keyboard_value = true);

#pragma endregion

#pragma region Inputs Utilities: Mouse

	// - マウスボタンを参照するには、コードで名前付き列挙型を使用できます。 ImGuiMouseButton_Left、ImGuiMouseButton_Right。
	// - また、通常の整数を使用することもできます。0=左、1 =右、2 =中央が永久に保証されます。
	// - ドラッグ操作は、マウスが最初のクリック位置から特定の距離だけ離れた後にのみ報告されます（「lock_threshold」および「io.MouseDraggingThreshold」を参照）
	
	/**
	@brief マウス入力
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseDown(ImGuiMouseButton_ button);
	
	/**
	@brief マウスボタンがクリックされたか
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseClicked(ImGuiMouseButton_ button, bool repeat = false);
	
	/**
	@brief マウス入力 離した時
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseReleased(ImGuiMouseButton_ button);
	
	/**
	@brief ダブルクリックしたかどうか
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseDoubleClicked(ImGuiMouseButton_ button);

	/**
	@brief ホバリング
	*/
	bool IsMouseHoveringRect(const Vector2& r_min, const Vector2& r_max, bool clip = true);

	bool IsMousePosValid(const Vector2* mouse_pos = nullptr);

	/**
	@brief マウスのボタンが押されているか
	*/
	bool IsAnyMouseDown();

	/**
	@brief マウスの座標
	*/
	Vector2 GetMousePos();

	/**
	@brief ポップアップを開くときにマウスの位置を取得
	*/
	Vector2 GetMousePosOnOpeningCurrentPopup();

	/**
	@brief ドラッグしています
	*/
	bool IsMouseDragging(ImGuiMouseButton_ button, float lock_threshold = -1.0f);

	/**
	@brief マウスボタンが押されている間、またはちょうど離されたときに、最初のクリック位置からデルタを返します
	*/
	Vector2 GetMouseDragDelta(ImGuiMouseButton_ button = (ImGuiMouseButton_)0, float lock_threshold = -1.0f);

	/**
	@brief 距離をリセット
	*/
	void ResetMouseDragDelta(ImGuiMouseButton_ button = (ImGuiMouseButton_)0);
	
	/**
	@brief どのUIに触れているかの情報を取得
	*/
	ImGuiMouseCursor_ GetMouseCursor();

	/**
	@brief 目的のカーソルタイプを設定します
	*/
	void SetMouseCursor(ImGuiMouseCursor_ cursor_type);

#pragma endregion

#pragma region Columns

	// - SameLine（pos_x）を使用して、単純化された列を模倣することもできます。
	// - 列APIは進行中の作業であり、かなり欠けています（現時点では、列は間違いなく親愛なるimguiの最悪の部分です！）
	// - 最大64列です。
	// - 2019年末までに、列を置き換える新しい「テーブル」APIが公開されます。

	/**
	@brief 表の作成
	@param [in] count 横に並べる数
	*/
	void Columns(int count = 1, const char* id = nullptr, bool border = true);

	/**
	@brief 表を次の列に
	*/
	void NextColumn();

	/**
	@brief 表のIndex
	*/
	int GetColumnIndex();

	/**
	@brief 列の幅を取得
	*/
	float GetColumnWidth(int column_index = -1);

	/**
	@brief 列の幅を設定
	*/
	void SetColumnWidth(int column_index, float width);

	/**
	@brief 列線の位置を取得
	*/
	float GetColumnOffset(int column_index = -1);

	/**
	@brief 列線の位置を設定
	*/
	void SetColumnOffset(int column_index, float offset_x);

	int GetColumnsCount();

#pragma endregion

#pragma region Tab Bars, Tabs

	// 注：タブは、ドッキングシステムによって自動的に作成されます。これを使用して、ドッキングを行わずに自分でタブバー/タブを作成します。
	
	/**
	@brief TabBarの開始
	@param [in] str_id タブID
	*/
	bool BeginTabBar(const char* str_id, ImGuiTabBarFlags_ flags = (ImGuiTabBarFlags_)0);

	/**
	@brief TabBarの終了
	*/
	void EndTabBar();

	/**
	@brief タブの開始
	*/
	bool BeginTabItem(const std::string& label, bool& p_open, ImGuiTabItemFlags_ flags = (ImGuiTabItemFlags_)0);

	/**
	@brief タブの終了
		BeginTabItem() がtrueの時のみ
	*/
	void EndTabItem();

	/**
	@brief 閉じたタブ/ウィンドウの先をTabBarまたはドッキングシステムに通知します
	*/
	void SetTabItemClosed(const char* tab_or_docked_window_label);

#pragma endregion

}

#pragma region operator reflection

//-----------------------------------------------------------------------------
// operator reflection
//-----------------------------------------------------------------------------
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiWindowFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiWindowFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiWindowFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiInputTextFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiInputTextFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiInputTextFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiTreeNodeFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiTreeNodeFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiTreeNodeFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiSelectableFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiSelectableFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiSelectableFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiComboFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiComboFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiComboFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiTabBarFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiTabBarFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiTabBarFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiTabItemFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiTabItemFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiTabItemFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiFocusedFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiFocusedFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiFocusedFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiHoveredFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiHoveredFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiHoveredFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiDockNodeFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiDockNodeFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiDockNodeFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiDragDropFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiDragDropFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiDragDropFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiDataType_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiDataType_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiDataType_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiDir_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiDir_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiDir_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiKey_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiKey_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiKey_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiNavInput_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiNavInput_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiNavInput_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiConfigFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiConfigFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiConfigFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiBackendFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiBackendFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiBackendFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiCol_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiCol_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiCol_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiStyleVar_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiStyleVar_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiStyleVar_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiColorEditFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiColorEditFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiColorEditFlags_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiMouseButton_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiMouseButton_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiMouseButton_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiMouseCursor_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiMouseCursor_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiMouseCursor_> : std::true_type {};
template<> struct mdx::common::enum_operator::calculation<mdx_imgui::ImGuiCond_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_and_or_operators<mdx_imgui::ImGuiCond_> : std::true_type {};
template<> struct mdx::common::enum_operator::has_bitwise_operators<mdx_imgui::ImGuiCond_> : std::true_type {};

#pragma endregion