//==========================================================================
// Dear ImGui �̃��b�p�[ [mdx_imgui.h]
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
		ImGuiWindowFlags_NoTitleBar = 1 << 0,  // �^�C�g���o�[�𖳌��ɂ���
		ImGuiWindowFlags_NoResize = 1 << 1,  // �E���̃O���b�v�Ń��[�U�[�̃T�C�Y�ύX�𖳌��ɂ��܂�
		ImGuiWindowFlags_NoMove = 1 << 2,  // ���[�U�[���E�B���h�E���ړ��ł��Ȃ��悤�ɂ���
		ImGuiWindowFlags_NoScrollbar = 1 << 3,  // �X�N���[���o�[�𖳌��ɂ��܂�(�E�B���h�E�̓}�E�X�܂��̓v���O�����ŃX�N���[���ł��܂�)
		ImGuiWindowFlags_NoScrollWithMouse = 1 << 4,  // ���[�U�[���}�E�X�z�C�[���Ő����ɃX�N���[���ł��Ȃ��悤�ɂ��܂��B�q�E�B���h�E�ł́ANoScrollbar���ݒ肳��Ă��Ȃ�����A�}�E�X�z�C�[���͐e�ɓ]������܂��B
		ImGuiWindowFlags_NoCollapse = 1 << 5,  // ���[�U�[�܂肽���݃E�B���h�E���_�u���N���b�N���Ė����ɂ��܂��B�h�b�L���O�m�[�h���́u�E�B���h�E���j���[�{�^���v�Ƃ��Ă΂�܂��B
		ImGuiWindowFlags_AlwaysAutoResize = 1 << 6,  // ���ׂẴE�B���h�E�̃T�C�Y�����ׂẴt���[���̃R���e���c�ɕύX���܂�
		ImGuiWindowFlags_NoBackground = 1 << 7,  // �`��w�i�F(WindowBg�Ȃ�)����ъO�g�𖳌��ɂ��܂��B SetNextWindowBgAlpha(0.0f) ���g�p����ꍇ�Ɠ��l�ł��B
		ImGuiWindowFlags_NoSavedSettings = 1 << 8,  // .ini�t�@�C���̐ݒ�����[�h/�ۑ����Ȃ�
		ImGuiWindowFlags_NoMouseInputs = 1 << 9,  // �p�X�X���[�Ńe�X�g���z�o�����O�A�}�E�X�̃L���b�`�𖳌��ɂ��܂��B
		ImGuiWindowFlags_MenuBar = 1 << 10, // ���j���[�o�[������܂�
		ImGuiWindowFlags_HorizontalScrollbar = 1 << 11, // �����X�N���[���o�[�̕\���������܂�(�f�t�H���g�ł̓I�t)�B SetNextWindowContentSize(ImVec2(width�A0.0f)); ���g�p�ł��܂��B Begin() ���Ăяo���ĕ����w�肷��O�ɁB �u�����X�N���[���v�Z�N�V������imgui_demo�̃R�[�h��ǂ�ł��������B
		ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12, // ��\������\����ԂɈڍs����Ƃ��Ƀt�H�[�J�X���擾�ł��Ȃ��悤�ɂ��܂�
		ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13, // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
		ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14, // �t�H�[�J�X���擾����Ƃ��ɃE�B���h�E��O�ʂɈړ����邱�Ƃ𖳌��ɂ��܂�(���Ƃ��΁A�N���b�N���邩�A�v���O�����Ńt�H�[�J�X��ݒ肵�܂�)
		ImGuiWindowFlags_AlwaysHorizontalScrollbar = 1 << 15, // ��ɐ����X�N���[���o�[��\�����܂�(ContentSize.x <Size.x�ł����Ă�)
		ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16, // ���E���̂Ȃ��q�E�B���h�E��style.WindowPadding���g�p����悤�ɂ��܂�(���E���̂Ȃ��q�E�B���h�E�ł̓f�t�H���g�Ŗ�������邽�߁A���֗��ł�)
		ImGuiWindowFlags_NoNavInputs = 1 << 18, // �E�B���h�E���ɃQ�[���p�b�h/�L�[�{�[�h�i�r�Q�[�V�����͂���܂���
		ImGuiWindowFlags_NoNavFocus = 1 << 19, // �Q�[���p�b�h/�L�[�{�[�h�i�r�Q�[�V�����ł��̃E�B���h�E�ɏœ_�����킹�Ȃ�(���Ƃ��΁ACTRL + TAB�ŃX�L�b�v)
		ImGuiWindowFlags_UnsavedDocument = 1 << 20, // ###���Z�q�̎g�p������邽�߂ɁAID�ɉe����^�����Ƀ^�C�g���Ɂu*�v��ǉ����܂��B�^�u/�h�b�L���O�R���e�L�X�g�Ŏg�p����ƁA�N���[�W���[�Ń^�u���I������A�N���[�W���[��1�t���[����������āA�R�[�h��������̂Ȃ�(�m�F�|�b�v�A�b�v�Ȃǂ�)�N���[�W���[���L�����Z���ł���悤�ɂȂ�܂��B
		ImGuiWindowFlags_NoDocking = 1 << 21, // ���̃E�B���h�E�̃h�b�L���O�𖳌��ɂ��܂�

		ImGuiWindowFlags_NoNav = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
		ImGuiWindowFlags_NoDecoration = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse,
		ImGuiWindowFlags_NoInputs = ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoNavFocus,
	};

	// Flags for InputText()
	enum class ImGuiInputTextFlags_
	{
		ImGuiInputTextFlags_None = 0,
		ImGuiInputTextFlags_CharsDecimal = 1 << 0,  // 0123456789.+-* ������/
		ImGuiInputTextFlags_CharsHexadecimal = 1 << 1,  // 0123456789ABCDEFabcdef ������
		ImGuiInputTextFlags_CharsUppercase = 1 << 2,  // a..z��A..Z�ɕς���
		ImGuiInputTextFlags_CharsNoBlank = 1 << 3,  // �X�y�[�X�A�^�u�����O����
		ImGuiInputTextFlags_AutoSelectAll = 1 << 4,  // �ŏ��Ƀ}�E�X�t�H�[�J�X�����Ƃ��Ƀe�L�X�g�S�̂�I������
		ImGuiInputTextFlags_EnterReturnsTrue = 1 << 5,  // (�l���ύX����邽�тɂł͂Ȃ�)Enter�������ꂽ�Ƃ��Ɂutrue�v��Ԃ��܂��B IsItemDeactivatedAfterEdit() �֐��𒲂ׂ邱�Ƃ��������Ă��������B
		ImGuiInputTextFlags_CallbackCompletion = 1 << 6,  // Tab�L�[���������Ƃ��̃R�[���o�b�N(���������̂���)
		ImGuiInputTextFlags_CallbackHistory = 1 << 7,  // ��/�����������ƃR�[���o�b�N(���������p)
		ImGuiInputTextFlags_CallbackAlways = 1 << 8,  // �e�����ł̃R�[���o�b�N�B���[�U�[�R�[�h�̓J�[�\���ʒu���Ɖ�A�e�L�X�g�o�b�t�@��ύX�ł��܂��B
		ImGuiInputTextFlags_CallbackCharFilter = 1 << 9,  // �u���܂��͔j�����镶�����͂̃R�[���o�b�N�B 'EventChar'��ύX���Ēu���܂��͔j�����邩�A�R�[���o�b�N��1��Ԃ��Ĕj�����܂��B
		ImGuiInputTextFlags_AllowTabInput = 1 << 10, // Tab�L�[�������ƁA�e�L�X�g�t�B�[���h�Ɂu\ t�v���������͂���܂�
		ImGuiInputTextFlags_CtrlEnterForNewLine = 1 << 11, // �����s���[�h�ł́AEnter�Ńt�H�[�J�X���������ACtrl + Enter�ŐV�����s��ǉ����܂�(�f�t�H���g�͔��΂ł� : Ctrl + Enter�Ńt�H�[�J�X���������AEnter�ōs��ǉ����܂�)�B
		ImGuiInputTextFlags_NoHorizontalScroll = 1 << 12, // �J�[�\���̐��������̃t�H���[�𖳌��ɂ���
		ImGuiInputTextFlags_AlwaysInsertMode = 1 << 13, // �}�����[�h
		ImGuiInputTextFlags_ReadOnly = 1 << 14, // �ǂݎ���p���[�h
		ImGuiInputTextFlags_Password = 1 << 15, // �p�X���[�h���[�h�A���ׂĂ̕������u*�v�Ƃ��ĕ\��
		ImGuiInputTextFlags_NoUndoRedo = 1 << 16, // ���ɖ߂�/��蒼���𖳌��ɂ��܂��B�A�N�e�B�u�ȊԂ͓��̓e�L�X�g���e�L�X�g�f�[�^�����L���Ă��邱�Ƃɒ��ӂ��Ă��������B�Ǝ��̌��ɖ߂�/��蒼���X�^�b�N��񋟂���ꍇ�́A���Ƃ���ClearActiveID() ���Ăяo���܂��B
		ImGuiInputTextFlags_CharsScientific = 1 << 17, // 0123456789�B+-*/eE(�Ȋw�\�L�@�̓���)������
		ImGuiInputTextFlags_CallbackResize = 1 << 18, // �o�b�t�@�e�ʂ̃R�[���o�b�N�̓��N�G�X�g��ύX��(�ubuf_size�v�p�����[�^�l�𒴂���)�A�������傫�����邱�Ƃ��ł��܂��B������̃T�C�Y��ύX����K�v������ꍇ�ɒʒm���܂�(�T�C�Y�̃L���b�V����ێ����镶����^�C�v�̏ꍇ)�B�R�[���o�b�N�ŐV����BufSize���񋟂���A����𑸏d����K�v������܂��B (����̎g�p��ɂ��ẮAmisc/cpp/imgui_stdlib.h���Q�Ƃ��Ă�������)
	};

	// Flags for TreeNodeEx(), CollapsingHeader*()
	enum class ImGuiTreeNodeFlags_
	{
		ImGuiTreeNodeFlags_None = 0,
		ImGuiTreeNodeFlags_Selected = 1 << 0,  // �I�����ꂽ�Ƃ���ɕ`��
		ImGuiTreeNodeFlags_Framed = 1 << 1,  // �t���J���[�t���[��(CollapsingHeader�Ȃ�)
		ImGuiTreeNodeFlags_AllowItemOverlap = 1 << 2,  // �e�X�g���q�b�g���āA�㑱�̃E�B�W�F�b�g�����̃E�B�W�F�b�g�ƃI�[�o�[���b�v�ł���悤�ɂ��܂�
		ImGuiTreeNodeFlags_NoTreePushOnOpen = 1 << 3,  // �J���Ă���Ƃ���TreePush() �����s���Ȃ�(�� : CollapsingHeader�̏ꍇ)=�ǉ��̃C���f���g��ID�X�^�b�N�̃v�b�V�����s��Ȃ�
		ImGuiTreeNodeFlags_NoAutoOpenOnLog = 1 << 4,  // ���M���O���A�N�e�B�u�ȂƂ��Ƀm�[�h�������I�Ɉꎞ�I�ɊJ���Ȃ��ł�������(�f�t�H���g�ł́A���M���O�͎����I�Ƀc���[�m�[�h���J���܂�)
		ImGuiTreeNodeFlags_DefaultOpen = 1 << 5,  // �J���f�t�H���g�̃m�[�h
		ImGuiTreeNodeFlags_OpenOnDoubleClick = 1 << 6,  // �m�[�h���J���ɂ̓_�u���N���b�N���K�v�ł�
		ImGuiTreeNodeFlags_OpenOnArrow = 1 << 7,  // ��󕔕����N���b�N�����Ƃ��ɂ̂݊J���܂��B ImGuiTreeNodeFlags_OpenOnDoubleClick���ݒ肳��Ă���ꍇ�A�����V���O���N���b�N���邩�A���ׂẴ{�b�N�X���_�u���N���b�N���ĊJ���܂��B
		ImGuiTreeNodeFlags_Leaf = 1 << 8,  // �܂肽���݂���������܂���(���[�t�m�[�h�̗��֐��Ƃ��Ďg�p)�B
		ImGuiTreeNodeFlags_Bullet = 1 << 9,  // ���̑���ɒe�ۂ�\������
		ImGuiTreeNodeFlags_FramePadding = 1 << 10, // FramePadding���g�p����(�t���[��������Ă��Ȃ��e�L�X�g�m�[�h�̏ꍇ�ł�)�A�e�L�X�g�̃x�[�X���C����ʏ�̃E�B�W�F�b�g�̍����ɐ����ɑ����܂��B AlignTextToFramePadding() �̌Ăяo���Ɠ����ł��B
		ImGuiTreeNodeFlags_SpanAvailWidth = 1 << 11, // �q�b�g�{�b�N�X���E�[�܂Ŋg�����܂�(�t���[��������Ă��Ȃ��ꍇ�ł�)�B����́A�����s�ɑ��̃A�C�e����ǉ��ł���悤�ɂ��邽�߂̃f�t�H���g�ł͂���܂���B�����I�ɂ́A�q�b�g�V�X�e����O�ʂ���w�ʂɃ��t�@�N�^�����O���āA���R�ȃI�[�o�[���b�v���\�ɂ��A���ꂪ�f�t�H���g�ɂȂ�\��������܂��B
		ImGuiTreeNodeFlags_SpanFullWidth = 1 << 12, // �q�b�g�{�b�N�X�����[�ƉE�[�Ɋg�����܂�(�C���f���g���ꂽ�̈���o�C�p�X���܂�)�B
		ImGuiTreeNodeFlags_NavLeftJumpsBackHere = 1 << 13, // (WIP)Nav : �������́A���̎q(TreeNode��TreePop�̊Ԃő��M���ꂽ�A�C�e��)���炱��TreeNode() �Ɉړ��ł��܂�
		//ImGuiTreeNodeFlags_NoScrollOnOpen     = 1 << 14, // FIXME : TODO : �m�[�h���J�����΂���œ��e���\������Ȃ��ꍇ�ATreePop() �̎����X�N���[���𖳌��ɂ��܂�
		ImGuiTreeNodeFlags_CollapsingHeader = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_NoAutoOpenOnLog
	};

	// Flags for Selectable()
	enum class ImGuiSelectableFlags_
	{
		ImGuiSelectableFlags_None = 0,
		ImGuiSelectableFlags_DontClosePopups = 1 << 0,  // ������N���b�N���Ă��A�e�|�b�v�A�b�v�E�B���h�E�͕��܂���B
		ImGuiSelectableFlags_SpanAllColumns = 1 << 1,  // �I���\�ȃt���[���͂��ׂĂ̗�ɂ܂����邱�Ƃ��ł��܂�(�e�L�X�g�͌��݂̗�Ɏ��܂�܂�)
		ImGuiSelectableFlags_AllowDoubleClick = 1 << 2,  // �_�u���N���b�N�ł��v���X�C�x���g�𐶐�
		ImGuiSelectableFlags_Disabled = 1 << 3,  // �I���ł��܂���A�O���[�\�����ꂽ�e�L�X�g��\�����܂�
		ImGuiSelectableFlags_AllowItemOverlap = 1 << 4   // (WIP)�q�b�g�e�X�g�ɂ��A�㑱�̃E�B�W�F�b�g�����̃E�B�W�F�b�g�ƃI�[�o�[���b�v�ł���悤�ɂ��܂�
	};

	// Flags for BeginCombo()
	enum class ImGuiComboFlags_
	{
		ImGuiComboFlags_None = 0,
		ImGuiComboFlags_PopupAlignLeft = 1 << 0,  // �f�t�H���g�Ń|�b�v�A�b�v�����ɑ�����
		ImGuiComboFlags_HeightSmall = 1 << 1,  // �ő�4�̃A�C�e�����\������܂��B�q���g : �R���{�|�b�v�A�b�v�����̃T�C�Y�ɂ���ɂ́ABeginCombo() ���Ăяo���O��SetNextWindowSizeConstraints() ���g�p�ł��܂��B
		ImGuiComboFlags_HeightRegular = 1 << 2,  // �ő�8�̃A�C�e�����\������܂�(�f�t�H���g)
		ImGuiComboFlags_HeightLarge = 1 << 3,  // �ő�20�̃A�C�e�����\������܂�
		ImGuiComboFlags_HeightLargest = 1 << 4,  // �ł��邾�������̃t�B�b�e�B���O�A�C�e��
		ImGuiComboFlags_NoArrowButton = 1 << 5,  // �l�p�����{�^���Ȃ��Ńv���r���[�{�b�N�X�ɕ\������
		ImGuiComboFlags_NoPreview = 1 << 6,  // �l�p�����{�^���݂̂�\������
		ImGuiComboFlags_HeightMask_ = ImGuiComboFlags_HeightSmall | ImGuiComboFlags_HeightRegular | ImGuiComboFlags_HeightLarge | ImGuiComboFlags_HeightLargest
	};

	// Flags for BeginTabBar()
	enum class ImGuiTabBarFlags_
	{
		ImGuiTabBarFlags_None = 0,
		ImGuiTabBarFlags_Reorderable = 1 << 0,  // �^�u���蓮�Ńh���b�O���ĕ��בւ��邱�Ƃ��ł��܂�+���X�g�̍Ō�ɐV�����^�u���ǉ�����܂�
		ImGuiTabBarFlags_AutoSelectNewTabs = 1 << 1,  // �V�����^�u���\�����ꂽ�玩���I�ɑI������
		ImGuiTabBarFlags_TabListPopupButton = 1 << 2,  // �{�^���𖳌��ɂ��ă^�u���X�g�|�b�v�A�b�v���J���܂�
		ImGuiTabBarFlags_NoCloseWithMiddleMouseButton = 1 << 3,  // �}�E�X�̒��{�^���Ń^�u�����(p_open�I= nullptr�ő��M�����)����𖳌��ɂ��܂��Bif(IsItemHovered() && IsMouseClicked(2))* p_open = false���g�p����ƁA���[�U�[���ł��̓�����Č��ł��܂��B
		ImGuiTabBarFlags_NoTabListScrollingButtons = 1 << 4,  // �X�N���[���{�^���𖳌��ɂ���(�t�B�b�e�B���O�|���V�[��ImGuiTabBarFlags_FittingPolicyScroll�̏ꍇ�ɓK�p)
		ImGuiTabBarFlags_NoTooltip = 1 << 5,  // �^�u���z�o�[����Ƃ��Ƀc�[���`�b�v�𖳌��ɂ���
		ImGuiTabBarFlags_FittingPolicyResizeDown = 1 << 6,  // ���܂�Ȃ��^�u�̃T�C�Y��ύX����
		ImGuiTabBarFlags_FittingPolicyScroll = 1 << 7,  // �^�u�����܂�Ȃ��ꍇ�ɃX�N���[���{�^����ǉ�����
		ImGuiTabBarFlags_FittingPolicyMask_ = ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_FittingPolicyScroll,
		ImGuiTabBarFlags_FittingPolicyDefault_ = ImGuiTabBarFlags_FittingPolicyResizeDown
	};

	// Flags for BeginTabItem()
	enum class ImGuiTabItemFlags_
	{
		ImGuiTabItemFlags_None = 0,
		ImGuiTabItemFlags_UnsavedDocument = 1 << 0,  // ###���Z�q�̎g�p������邽�߂ɁAID�ɉe����^�����Ƀ^�C�g���Ɂu*�v��ǉ����܂��B�܂��A�N���[�W���[�Ń^�u���I������A�N���[�W���[��1�t���[����������A�t���b�J�[�Ȃ��ŃR�[�h�����ɖ߂����Ƃ��ł��܂��B
		ImGuiTabItemFlags_SetSelected = 1 << 1,  // BeginTabItem() �̌Ăяo�����Ƀv���O�����Ń^�u��I�����邽�߂̃g���K�[�t���O
		ImGuiTabItemFlags_NoCloseWithMiddleMouseButton = 1 << 2,  // �}�E�X�̒��{�^���Ń^�u�����(p_open�I= nullptr�ő��M�����)����𖳌��ɂ��܂��Bif(IsItemHovered() && IsMouseClicked(2))* p_open = false���g�p����ƁA���[�U�[���ł��̓�����Č��ł��܂��B
		ImGuiTabItemFlags_NoPushId = 1 << 3   // BeginTabItem()/EndTabItem() ��PushID(tab-> ID)/ PopID() ���Ăяo���Ȃ��ł�������
	};

	// Flags for IsWindowFocused()
	enum class ImGuiFocusedFlags_
	{
		ImGuiFocusedFlags_None = 0,
		ImGuiFocusedFlags_ChildWindows = 1 << 0,  // IsWindowFocused() : �E�B���h�E�̂����ꂩ�̎q���t�H�[�J�X����Ă���ꍇ��true��Ԃ��܂�
		ImGuiFocusedFlags_RootWindow = 1 << 1,  // IsWindowFocused() : ���[�g�E�B���h�E����e�X�g(���݂̊K�w�̍ŏ�ʂ̐e)
		ImGuiFocusedFlags_AnyWindow = 1 << 2,  // IsWindowFocused() : �E�B���h�E���t�H�[�J�X����Ă���ꍇ��true��Ԃ��܂��B�d�v : �჌�x���̓��͂��f�B�X�p�b�`������@��`���悤�Ƃ��Ă���ꍇ�́A������g�p���Ȃ��ł��������B�����GetIO() �BWantCaptureMouse���g�p���Ă��������B
		ImGuiFocusedFlags_RootAndChildWindows = ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_ChildWindows
	};

	// IsItemHovered() �AIsWindowHovered() �̃t���O
	// �� : �}�E�X��imgui�܂��̓A�v���Ƀf�B�X�p�b�`����K�v�����邩�ǂ������m�F���悤�Ƃ��Ă���ꍇ�́A 'io.WantCaptureMouse'�u�[���l���g�p����K�v������܂��B FAQ��ǂ�ł��������I
	// �� : ImGuiWindowFlags_NoInputs�t���O�����E�B���h�E�́AIsWindowHovered() �Ăяo���ɂ���Ė�������܂��B
	enum class ImGuiHoveredFlags_
	{
		ImGuiHoveredFlags_None = 0,       // �A�C�e��/�E�B���h�E�̂�����ŁA�ʂ̃E�B���h�E�ŎՂ��Ă��Ȃ��ꍇ�A�܂��̓A�N�e�B�u�ȃ|�b�v�A�b�v�⃂�[�_���u���b�N���͂ŎՂ��Ă��Ȃ��ꍇ�Atrue��Ԃ��܂��B
		ImGuiHoveredFlags_ChildWindows = 1 << 0,  // IsWindowHovered() only : �E�B���h�E�̂����ꂩ�̎q���z�o�[����Ă���ꍇ��true��Ԃ��܂�
		ImGuiHoveredFlags_RootWindow = 1 << 1,  // IsWindowHovered() only : ���[�g�E�B���h�E(���݂̊K�w�̍ŏ�ʂ̐e)����e�X�g����
		ImGuiHoveredFlags_AnyWindow = 1 << 2,  // IsWindowHovered() only : �E�B���h�E���z�o�[����Ă���ꍇ��true��Ԃ��܂�
		ImGuiHoveredFlags_AllowWhenBlockedByPopup = 1 << 3,  // �|�b�v�A�b�v�E�B���h�E�����̃A�C�e��/�E�B���h�E�ւ̃A�N�Z�X��ʏ�u���b�N���Ă���ꍇ�ł�true��Ԃ��܂�
		//ImGuiHoveredFlags_AllowWhenBlockedByModal     = 1 << 4,  // ���[�_���|�b�v�A�b�v�E�B���h�E�����̃A�C�e��/�E�B���h�E�ւ̃A�N�Z�X��ʏ�u���b�N���Ă���ꍇ�ł�true��Ԃ��܂��B FIXME-TODO : �܂����p�ł��܂���B
		ImGuiHoveredFlags_AllowWhenBlockedByActiveItem = 1 << 5,  // �A�N�e�B�u�ȃA�C�e�������̃A�C�e��/�E�B���h�E�ւ̃A�N�Z�X���u���b�N���Ă���ꍇ�ł�true��Ԃ��܂��B�h���b�O�A���h�h���b�v�p�^�[���ɖ𗧂��܂��B
		ImGuiHoveredFlags_AllowWhenOverlapped = 1 << 6,  // �ʒu�����̃E�B���h�E�ɂ���ĎՂ�ꂽ��A�d�Ȃ��Ă���ꍇ�ł�true��Ԃ��܂�
		ImGuiHoveredFlags_AllowWhenDisabled = 1 << 7,  // �A�C�e���������ɂȂ��Ă��Ă�true��Ԃ��܂�
		ImGuiHoveredFlags_RectOnly = ImGuiHoveredFlags_AllowWhenBlockedByPopup | ImGuiHoveredFlags_AllowWhenBlockedByActiveItem | ImGuiHoveredFlags_AllowWhenOverlapped,
		ImGuiHoveredFlags_RootAndChildWindows = ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_ChildWindows
	};

	// �q�m�[�h�ɂ���ċ��L/�p�������DockSpace() �̃t���O�B
	// (�ꕔ�̃t���O�͌X�̃m�[�h�ɒ��ړK�p�ł��܂�)
	// FIXME-DOCK : �܂��AWIP����ѓ���DockBuilder API�̎g�p�𔺂��\��������ImGuiDockNodeFlagsPrivate_���Q�Ƃ��Ă��������B
	enum class ImGuiDockNodeFlags_
	{
		ImGuiDockNodeFlags_None = 0,
		ImGuiDockNodeFlags_KeepAliveOnly = 1 << 0,  // ���L      // �h�b�N�X�y�[�X�m�[�h��\�����Ȃ��ŁA���̂܂܂ɂ��Ă��������B���̃h�b�N�X�y�[�X�m�[�h�Ƀh�b�L���O���ꂽWindows�́A�h�b�L���O��������܂���B
		//ImGuiDockNodeFlags_NoCentralNode          = 1 << 1,  // ���L      // �Z���g�����m�[�h(��̂܂܂ɂł���m�[�h)�𖳌��ɂ���
		ImGuiDockNodeFlags_NoDockingInCentralNode = 1 << 2,  // ���L      // ��ɋ�̂܂܂ɂȂ�Z���g�����m�[�h���̃h�b�L���O�𖳌��ɂ��܂��B
		ImGuiDockNodeFlags_PassthruCentralNode = 1 << 3,  // ���L      // �p�X�X���[�h�b�N�X�y�[�X��L���ɂ��܂��B1)DockSpace() �́A��̂Ƃ��ɃZ���g�����m�[�h���������ׂĂ��J�o�[����ImGuiCol_WindowBg�o�b�N�O���E���h�������_�����O���܂��B������g�p����ꍇ�A�z�X�g�E�B���h�E�̈Ӗ��́A�����炭Begin() �̑O��SetNextWindowBgAlpha(0.0f)���g�p����K�v������܂��B 2)�Z���g�����m�[�h����̏ꍇ : ���̓p�X�X���[+ DockingEmptyBg�o�b�N�O���E���h��\�����܂���B�ڍׂɂ��ẮA�f�����������������B
		ImGuiDockNodeFlags_NoSplit = 1 << 4,  // ���L/���[�J�� // �m�[�h�������ȃm�[�h�ɕ������邱�Ƃ𖳌��ɂ��܂��B�֗��ȗჁ�C���̃��[�g1�Ƀh�b�N�X�y�[�X�𖄂ߍ��ޏꍇ(���[�g1�ł͍���������邽�߂ɕ����������ɂȂ��Ă���ꍇ������܂�)�B�� : �I�t�ɂ���ƁA�����̕������ێ�����܂��B
		ImGuiDockNodeFlags_NoResize = 1 << 5,  // ���L/���[�J�� // �X�v���b�^�[/�Z�p���[�^�[���g�p���ăm�[�h�̃T�C�Y�ύX�𖳌��ɂ��܂��B�v���O�����ŃZ�b�g�A�b�v���ꂽ�h�b�N�X�y�[�X�Ŗ𗧂��܂��B
		ImGuiDockNodeFlags_AutoHideTabBar = 1 << 6   // ���L/���[�J�� // �h�b�N�m�[�h�ɒP��̃E�B���h�E������ꍇ�A�^�u�o�[�͎����I�ɔ�\���ɂȂ�܂��B
	};

	// BeginDragDropSource(), AcceptDragDropPayload() �̃t���O
	enum class ImGuiDragDropFlags_
	{
		ImGuiDragDropFlags_None = 0,
		// BeginDragDropSource() flags
		ImGuiDragDropFlags_SourceNoPreviewTooltip = 1 << 0,  // �f�t�H���g�ł́ABeginDragDropSource�𐳏�ɌĂяo���ƃc�[���`�b�v���J���A�\�[�X�R���e���c�̃v���r���[�܂��͐�����\���ł��܂��B���̃t���O�͂��̓���𖳌��ɂ��܂��B
		ImGuiDragDropFlags_SourceNoDisableHover = 1 << 1,  // �f�t�H���g�ł́A�h���b�O����Ƃ��Ƀf�[�^���N���A���āAIsItemHovered() ��false��Ԃ��悤�ɂ��āA�㑱�̃��[�U�[�R�[�h���c�[���`�b�v�𑗐M���Ȃ��悤�ɂ��܂��B���̃t���O�͂��̓���𖳌��ɂ��邽�߁A�\�[�X�A�C�e����IsItemHovered() ���Ăяo�����Ƃ��ł��܂��B
		ImGuiDragDropFlags_SourceNoHoldToOpenOthers = 1 << 2,  // �\�[�X�m�[�h���h���b�O���Ă���Ƃ��Ƀc���[�m�[�h��ێ����ăw�b�_�[��܂肽���ނ��Ƃ��ł��铮��𖳌��ɂ��܂��B
		ImGuiDragDropFlags_SourceAllowNullID = 1 << 3,  // �E�B���h�E�ɑ��ΓI�Ȉʒu�Ɋ�Â��Ĉꎞ�I�Ȏ��ʎq���쐬���邱�Ƃɂ��A��ӂ̎��ʎq�������Ȃ�Text() �AImage() �Ȃǂ̃A�C�e�����h���b�O�\�[�X�Ƃ��Ďg�p�ł���悤�ɂ��܂��B����́A�e���Ȃ�imgui�G�R�V�X�e�����ł͔��ɒ��������ƂȂ̂ŁA���m�ɂ��܂����B
		ImGuiDragDropFlags_SourceExtern = 1 << 4,  // �O���\�[�X(�e���Ȃ�imgui�̊O������)�A���݂̃A�C�e��/�E�B���h�E����ǂݎ�낤�Ƃ��܂���B���true��Ԃ��܂��B�����ɃA�N�e�B�u�ɂł���O���\�[�X��1�����ł��B
		ImGuiDragDropFlags_SourceAutoExpirePayload = 1 << 5,  // �\�[�X�̑��M����~�����ꍇ�A�y�C���[�h�������I�Ɋ����؂�ɂ��܂�(����ȊO�̏ꍇ�A�y�C���[�h�̓h���b�O���ɕێ�����܂�)
		// AcceptDragDropPayload() flags
		ImGuiDragDropFlags_AcceptBeforeDelivery = 1 << 10, // AcceptDragDropPayload() �́A�}�E�X�{�^�����������O�ł�true��Ԃ��܂��B���̌�AIsDelivery() ���Ăяo���āA�y�C���[�h��z�M����K�v�����邩�ǂ������e�X�g�ł��܂��B
		ImGuiDragDropFlags_AcceptNoDrawDefaultRect = 1 << 11, // �^�[�Q�b�g�ɃJ�[�\�������킹���Ƃ��Ƀf�t�H���g�̃n�C���C�g�����`��`�悵�Ȃ��ł��������B
		ImGuiDragDropFlags_AcceptNoPreviewTooltip = 1 << 12, // BeginDragDropSource�T�C�g����BeginDragDropSource�c�[���`�b�v���\���ɂ��邱�Ƃ�v�����܂��B
		ImGuiDragDropFlags_AcceptPeekOnly = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect // �z���O�ɐ��`���ăy�C���[�h���������܂��B
	};

	// �v���C�}���f�[�^�^�C�v
	enum class ImGuiDataType_
	{
		ImGuiDataType_S8,      // signed char/char(�����ȃR���p�C�����g�p)
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

	// ��{�I�ȕ���
	enum class ImGuiDir_
	{
		ImGuiDir_None = -1,
		ImGuiDir_Left = 0,
		ImGuiDir_Right = 1,
		ImGuiDir_Up = 2,
		ImGuiDir_Down = 3,
		ImGuiDir_COUNT
	};

	// ���[�U�[��ImGuiIO.KeyMap[] �z���ImGuiIO.KeysDown[512] �z��ւ̃C���f�b�N�X����͂��܂�
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

	// �Q�[���p�b�h/�L�[�{�[�h�̕����i�r�Q�[�V����
	// �L�[�{�[�h : io.ConfigFlags!=ImGuiConfigFlags_NavEnableKeyboard��L���ɐݒ肵�܂��B NewFrame() �́Aio.KeysDown[] + io.KeyMap[]�z��Ɋ�Â���io.NavInputs[] �������I�ɖ��߂܂��B
	// �Q�[���p�b�h : io.ConfigFlags!=ImGuiConfigFlags_NavEnableGamepad��L���ɐݒ肵�܂��B�o�b�N�G���h : ImGuiBackendFlags_HasGamepad��ݒ肵�ANewFrame() ���Ăяo���O��io.NavInputs[]�t�B�[���h�𖄂߂܂��B io.NavInputs[] ��EndFrame() �ɂ���ăN���A����邱�Ƃɒ��ӂ��Ă��������B
	// �ڍׂɂ��ẮAimgui.cpp�̎菇���Q�Ƃ��Ă��������B http://goo.gl/9LgVZW��PNG/PSD���_�E�����[�h���܂��B
	enum class ImGuiNavInput_
	{
		// �Q�[���p�b�h�}�b�s���O
		ImGuiNavInput_Activate,     // �l��L����/�J��/�؂�ւ���/����������      // �Ⴆ�΃N���X(PS4)�AA(Xbox)�AA(�X�C�b�`)�A�X�y�[�X(�L�[�{�[�h)
		ImGuiNavInput_Cancel,       // �L�����Z��/����/�I��                       // �Ⴆ�΃T�[�N��(PS4)�AB(Xbox)�AB(�X�C�b�`)�A�G�X�P�[�v(�L�[�{�[�h)
		ImGuiNavInput_Input,        // �e�L�X�g����/�X�N���[���L�[�{�[�h             // �Ⴆ�ΎO�p�`(PS4)�AY(Xbox)�AX(�X�C�b�`)�A���^�[��(�L�[�{�[�h)
		ImGuiNavInput_Menu,         // �^�b�v : ���j���[�̐؂�ւ�/�z�[���h : �t�H�[�J�X�A�ړ��A�T�C�Y�ύX // �Ⴆ�ΐ����`(PS4)�AX(Xbox)�AY(�X�C�b�`)�AAlt(�L�[�{�[�h)
		ImGuiNavInput_DpadLeft,     // �E�B���h�E�̈ړ�/����/�T�C�Y�ύX(w/PadMenu)   // �Ⴆ��D-pad��/�E/��/��(�Q�[���p�b�h)�A���L�[�i�L�[�{�[�h)
		ImGuiNavInput_DpadRight,    //
		ImGuiNavInput_DpadUp,       //
		ImGuiNavInput_DpadDown,     //
		ImGuiNavInput_LStickLeft,   // �E�B���h�E�̃X�N���[��/�ړ�(PadMenu�t��)           // �Ⴆ�΍��A�i���O�X�e�B�b�N��/�E/��/��
		ImGuiNavInput_LStickRight,  //
		ImGuiNavInput_LStickUp,     //
		ImGuiNavInput_LStickDown,   //
		ImGuiNavInput_FocusPrev,    // ���̃E�B���h�E(PadMenu�t��)              // �Ⴆ��L1�܂���L2(PS4)�ALB�܂���LT(Xbox)�AL�܂���ZL(�X�C�b�`)s
		ImGuiNavInput_FocusNext,    // �O�̃E�B���h�E(w/PadMenu)              // �Ⴆ��R1�܂���R2(PS4)�ARB�܂���RT(Xbox)�AR�܂���ZL(�X�C�b�`)
		ImGuiNavInput_TweakSlow,    // ���x������                               // �Ⴆ��L1�܂���L2(PS4)�ALB�܂���LT(Xbox)�AL�܂���ZL(�X�C�b�`)
		ImGuiNavInput_TweakFast,    // ��葬������                               // �Ⴆ��R1�܂���R2(PS4)�ARB�܂���RT(Xbox)�AR�܂���ZL(�X�C�b�`)
	};

	// io.ConfigFlags�ɕۑ�����Ă���\���t���O�B���[�U�[/�A�v���P�[�V�����ɂ���Đݒ肳��܂��B
	enum class ImGuiConfigFlags_
	{
		ImGuiConfigFlags_None = 0,
		ImGuiConfigFlags_NavEnableKeyboard = 1 << 0,  // �}�X�^�[�L�[�{�[�h�i�r�Q�[�V�����L�����t���O�B NewFrame() �́Aio.KeysDown[] �Ɋ�Â���io.NavInputs[] �������I�ɖ��߂܂��B
		ImGuiConfigFlags_NavEnableGamepad = 1 << 1,  // �}�X�^�[�Q�[���p�b�h�i�r�Q�[�V�����L�����t���O�B����͎�ɁAimgui�o�b�N�G���h��io.NavInputs[] �𖄂߂�悤�Ɏw�����邽�߂̂��̂ł��B�o�b�N�G���h��ImGuiBackendFlags_HasGamepad��ݒ肷��K�v������܂��B
		ImGuiConfigFlags_NavEnableSetMousePos = 1 << 2,  // �i�r�Q�[�V�����Ƀ}�E�X�J�[�\�����ړ�����悤�w�����܂��B���z�}�E�X�̈ړ������ȃe���r/�R���\�[���V�X�e���Ŗ𗧂ꍇ������܂��B io.MousePos���X�V���Aio.WantSetMousePos = true��ݒ肵�܂��B�L���ɂ����ꍇ�A�o�C���f�B���O��io.WantSetMousePos���N�G�X�g�𑸏d����K�v������܂��B�������Ȃ��ƁAImGui�̓}�E�X���O��ɃW�����v���Ă���悤�ɔ������܂��B
		ImGuiConfigFlags_NavNoCaptureKeyboard = 1 << 3,  // io.NavActive���ݒ肳��Ă���ꍇ�Aio.WantCaptureKeyboard�t���O��ݒ肵�Ȃ��悤�Ƀi�r�Q�[�V�����Ɏw�����܂��B
		ImGuiConfigFlags_NoMouse = 1 << 4,  // NewFrame() �Ń}�E�X�̈ʒu/�{�^�����N���A����悤��imgui�Ɏw�����܂��B����ɂ��A�o�b�N�G���h�ɂ���Đݒ肳�ꂽ�}�E�X���𖳎��ł��܂��B
		ImGuiConfigFlags_NoMouseCursorChange = 1 << 5,  // �}�E�X�J�[�\���̌`��Ɖ�����ύX���Ȃ��悤�Ƀo�b�N�G���h�Ɏw�����܂��B�o�b�N�G���h�J�[�\���̕ύX�����Ȃ��̎ז��ɂȂ�A�}�E�X�J�[�\���̕ύX��SetMouseCursor() ���g�p�������Ȃ��ꍇ�Ɏg�p���܂��B����ɁA������GetMouseCursor() ��ǂނ��Ƃɂ��Aimgui����̃��N�G�X�g�𑸏d���邱�Ƃ��ł��܂��B

		// [BETA] Docking
		ImGuiConfigFlags_DockingEnable = 1 << 6,  // �h�b�L���O�C�l�[�u���t���O�B

		// [BETA] �r���[�|�[�g
		// �r���[�|�[�g���g�p����ꍇ�AImGuiCol_WindowBg�̃f�t�H���g�l��s����(Alpha = 1.0)�ɂ��āA�r���[�|�[�g�ւ̈ڍs���ڗ����Ȃ��悤�ɂ��邱�Ƃ������߂��܂��B
		ImGuiConfigFlags_ViewportsEnable = 1 << 10, // �r���[�|�[�g�L�����t���O(ImGuiConfigFlags_PlatformHasViewports +���ꂼ��̃o�b�N�G���h�ɂ���Đݒ肳���ImGuiConfigFlags_RendererHasViewports�̗������K�v�ł�)

		// ���[�U�[�X�g���[�W(�o�b�N�G���h/�G���W���������̃v���W�F�N�g�Ԃŋ��L�����R�[�h�ƒʐM�ł���悤�ɂ��܂��B�����̃t���O�̓R�ADear ImGui�ł͎g�p����܂���)
		ImGuiConfigFlags_IsSRGB = 1 << 20, // �A�v���P�[�V������SRGB�Ή��ł��B
		ImGuiConfigFlags_IsTouchScreen = 1 << 21  // �A�v���P�[�V�����́A�}�E�X�̑���Ƀ^�b�`�X�N���[�����g�p���Ă��܂��B
	};

	// io.BackendFlags�ɕۑ�����Ă���o�b�N�G���h�@�\�t���O�B imgui_impl_xxx�܂��̓J�X�^���o�b�N�G���h�ɂ���Đݒ肳��܂��B
	enum class ImGuiBackendFlags_
	{
		ImGuiBackendFlags_None = 0,
		ImGuiBackendFlags_HasGamepad = 1 << 0,  // �o�b�N�G���h�v���b�g�t�H�[���̓Q�[���p�b�h���T�|�[�g���A���ݐڑ�����Ă��܂��B
		ImGuiBackendFlags_HasMouseCursors = 1 << 1,  // �o�b�N�G���h�v���b�g�t�H�[���́AOS�J�[�\���̌`���ύX���邽�߂�GetMouseCursor() �l�𑸏d���邱�Ƃ��T�|�[�g���Ă��܂��B
		ImGuiBackendFlags_HasSetMousePos = 1 << 2,  // �o�b�N�G���h�v���b�g�t�H�[����io.WantSetMousePos�v�����T�|�[�g���āAOS�}�E�X�̈ʒu��ύX���܂�(ImGuiConfigFlags_NavEnableSetMousePos���ݒ肳��Ă���ꍇ�ɂ̂ݎg�p����܂�)�B
		ImGuiBackendFlags_RendererHasVtxOffset = 1 << 3,  // �o�b�N�G���h�����_���[��ImDrawCmd::VtxOffset���T�|�[�g���܂��B����ɂ��A16�r�b�g�C���f�b�N�X���g�p���Ȃ���A�傫�ȃ��b�V��(64K +���_)�̏o�͂��\�ɂȂ�܂��B

		// [BETA] �r���[�|�[�g
		ImGuiBackendFlags_PlatformHasViewports = 1 << 10, // �o�b�N�G���h�v���b�g�t�H�[���͕����̃r���[�|�[�g���T�|�[�g���Ă��܂��B
		ImGuiBackendFlags_HasMouseHoveredViewport = 1 << 11, // �o�b�N�G���h�v���b�g�t�H�[���́AImGuiViewportFlags_NoInputs�t���O�ƁA�ʂ̃r���[�|�[�g���t�H�[�J�X����Ă��邩�A�}�E�X���L���v�`�����Ă���\�������邩������_REGARDLESS_���g�p���āA�}�E�X_IGNORING_�r���[�|�[�g�̒����̃r���[�|�[�g��io�B���̏��́A�قƂ�ǂ̍����x���̃G���W���Ő������񋟂��邽�߂�_�ȒP�ł͂���܂���I��/�o�b�N�G���h��������ǂ̂悤�Ɉ����������������ɂ����ݒ肵�Ȃ��ł��������I
		ImGuiBackendFlags_RendererHasViewports = 1 << 12  // �o�b�N�G���h�����_���[�͕����̃r���[�|�[�g���T�|�[�g���Ă��܂��B
	};

	// PushStyleColor()/PopStyleColor() �̗񋓑�
	enum class ImGuiCol_
	{
		ImGuiCol_Text,
		ImGuiCol_TextDisabled,
		ImGuiCol_WindowBg,             // �ʏ�̃E�B���h�E�̔w�i
		ImGuiCol_ChildBg,              // �q�E�B���h�E�̔w�i
		ImGuiCol_PopupBg,              // �|�b�v�A�b�v�A���j���[�A�c�[���`�b�v�E�B���h�E�̔w�i
		ImGuiCol_Border,
		ImGuiCol_BorderShadow,
		ImGuiCol_FrameBg,              // �`�F�b�N�{�b�N�X�A���W�I�{�^���A�v���b�g�A�X���C�_�[�A�e�L�X�g���͂̔w�i
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
		ImGuiCol_Header,               // �w�b�_�[*�̐F�́ACollapsingHeader�ATreeNode�ASelectable�AMenuItem�Ɏg�p����܂�
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
		ImGuiCol_DockingEmptyBg,       // ��̃m�[�h�̔w�i�F(�E�B���h�E���h�b�L���O����Ă��Ȃ�CentralNode�Ȃ�)
		ImGuiCol_PlotLines,
		ImGuiCol_PlotLinesHovered,
		ImGuiCol_PlotHistogram,
		ImGuiCol_PlotHistogramHovered,
		ImGuiCol_TextSelectedBg,
		ImGuiCol_DragDropTarget,
		ImGuiCol_NavHighlight,         // �Q�[���p�b�h/�L�[�{�[�h : ���݃n�C���C�g����Ă���A�C�e��
		ImGuiCol_NavWindowingHighlight, // Ctrl + Tab�L�[���g�p����Ƃ��ɃE�B���h�E�������\������
		ImGuiCol_NavWindowingDimBg,    // �A�N�e�B�u�ȏꍇ�ACTRL + TAB�E�B���h�E���X�g�̔w��ɂ����ʑS�̂��Â�����/�F�t������
		ImGuiCol_ModalWindowDimBg,     // �A�N�e�B�u�ȏꍇ�A���[�_���E�B���h�E�̔w��̉�ʑS�̂��Â�/�F�t������
		ImGuiCol_COUNT
	};

	// ImGuiStyle�\�����ꎞ�I�ɕύX���邽�߂�PushStyleVar()/PopStyleVar() �̗񋓑́B
	// NB : �񋓌^�́AUI�R�[�h���Ńv�b�V��/�|�b�v����Ӗ�������ImGuiStyle�̃t�B�[���h�݂̂��Q�Ƃ��܂��B���������ɁAImGuiStyle�ɒ��ړ˂�����ł��������B
	// NB : ���̗񋓌^��ύX����ꍇ�A�֘A��������e�[�u��GStyleVarInfo[]��K�X�X�V����K�v������܂��B����́A�񋓒l�������o�[�̃I�t�Z�b�g/�^�C�v�Ƀ����N����ꏊ�ł��B
	enum class ImGuiStyleVar_
	{
		// Enum name --------------------- // ImGuiStyle�\���̂̃����o�[�i�����ɂ��Ă�ImGuiStyle���Q��)
		ImGuiStyleVar_Alpha,              // float     Alpha
		ImGuiStyleVar_WindowPadding,      // ImVec2    Window Padding
		ImGuiStyleVar_WindowRounding,     // float     Window Rounding
		ImGuiStyleVar_WindowBorderSize,   // float     WindowBorderSize
		ImGuiStyleVar_WindowMinSize,      // ImVec2    WindowMinSize
		ImGuiStyleVar_WindowTitleAlign,   // ImVec2    WindowTitleAlign
		ImGuiStyleVar_ChildRounding,      // float     Child �O�g���p�ۂ�
		ImGuiStyleVar_ChildBorderSize,    // float     Child �O�g�̑���
		ImGuiStyleVar_PopupRounding,      // float     Popup �O�g���p�ۂ�
		ImGuiStyleVar_PopupBorderSize,    // float     Popup �O�g�̑���
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

	// ColorEdit3()/ColorEdit4()/ColorPicker3()/ColorPicker4()/ColorButton() �̃t���O
	enum class ImGuiColorEditFlags_
	{
		ImGuiColorEditFlags_None = 0,
		ImGuiColorEditFlags_NoAlpha = 1 << 1,  //             // ColorEdit, ColorPicker, ColorButton : Alpha�R���|�[�l���g�𖳎����܂�(���̓|�C���^�[����3�̃R���|�[�l���g�݂̂�ǂݎ��܂�)�B
		ImGuiColorEditFlags_NoPicker = 1 << 2,  //             // ColorEdit : �F�t���̎l�p�`���N���b�N�����Ƃ��Ƀs�b�J�[�𖳌��ɂ��܂��B
		ImGuiColorEditFlags_NoOptions = 1 << 3,  //             // ColorEdit : ����/�����ȃv���r���[���E�N���b�N�����Ƃ��̃I�v�V�������j���[�̐؂�ւ��𖳌��ɂ��܂��B
		ImGuiColorEditFlags_NoSmallPreview = 1 << 4,  //             // ColorEdit, ColorPicker : ���͂̉��ɂ���F�t���̐����`�v���r���[�𖳌��ɂ��܂��B (�� : ���݂͂̂�\������)
		ImGuiColorEditFlags_NoInputs = 1 << 5,  //             // ColorEdit, ColorPicker : ���̓X���C�_�[/�e�L�X�g�E�B�W�F�b�g�𖳌��ɂ��܂�(���Ƃ��΁A�����ȃv���r���[�̐F�t���̎l�p�`�݂̂�\�����܂�)�B
		ImGuiColorEditFlags_NoTooltip = 1 << 6,  //             // ColorEdit, ColorPicker, ColorButton : �v���r���[���z�o�[����Ƃ��Ƀc�[���`�b�v�𖳌��ɂ��܂��B
		ImGuiColorEditFlags_NoLabel = 1 << 7,  //             // ColorEdit, ColorPicker : �C�����C���e�L�X�g���x���̕\���𖳌��ɂ��܂�(���x���͈��������c�[���`�b�v�ƃs�b�J�[�ɓ]������܂�)�B
		ImGuiColorEditFlags_NoSidePreview = 1 << 8,  //             // ColorPicker : �s�b�J�[�̉E���ő傫�ȐF�̃v���r���[�𖳌��ɂ��A����ɏ����ȐF�̐����`�̃v���r���[���g�p���܂��B
		ImGuiColorEditFlags_NoDragDrop = 1 << 9,  //             // ColorEdit : �h���b�O�A���h�h���b�v�^�[�Q�b�g�𖳌��ɂ��܂��B ColorButton : �h���b�O�A���h�h���b�v�\�[�X�𖳌��ɂ��܂��B

		// ���[�U�[�I�v�V����(�E�B�W�F�b�g���E�N���b�N���āA�����̈ꕔ��ύX���܂�)�B
		ImGuiColorEditFlags_AlphaBar = 1 << 16, //             // ColorEdit, ColorPicker : �s�b�J�[�ɐ����A���t�@�o�[/�O���f�[�V������\�����܂��B
		ImGuiColorEditFlags_AlphaPreview = 1 << 17, //             // ColorEdit, ColorPicker, ColorButton : �v���r���[��s�����ł͂Ȃ��A�`�F�b�J�[�{�[�h��̓����F�Ƃ��ĕ\�����܂��B
		ImGuiColorEditFlags_AlphaPreviewHalf = 1 << 18, //             // ColorEdit,ColorPicker,ColorButton : �s�����ł͂Ȃ��A���s����/���s���͗l��\�����܂��B
		ImGuiColorEditFlags_HDR = 1 << 19, //             // (WIP) ColorEdit : ���݁ARGBA�G�f�B�V�����ł�0.0f..1.0f�̐����݂̂𖳌��ɂ��܂�(�� : �����炭ImGuiColorEditFlags_Float�t���O���g�p�������ł��傤)�B
		ImGuiColorEditFlags_DisplayRGB = 1 << 20, // [Display]   // ColorEdit : RGB/HSV/Hex�Ԃ�_display_�^�C�v���I�[�o�[���C�h���܂��B ColorPicker : 1�ȏ��RGB/HSV/Hex���g�p���ĔC�ӂ̑g�ݍ��킹��I�����܂��B
		ImGuiColorEditFlags_DisplayHSV = 1 << 21, // [Display]   // "
		ImGuiColorEditFlags_DisplayHex = 1 << 22, // [Display]   // "
		ImGuiColorEditFlags_Uint8 = 1 << 23, // [DataType]  // ColorEdit,ColorPicker,ColorButton : 0..255�Ƃ��ăt�H�[�}�b�g���ꂽ_display_�l�B
		ImGuiColorEditFlags_Float = 1 << 24, // [DataType]  // ColorEdit,ColorPicker,ColorButton : _display_�l�́A0..255�����ł͂Ȃ�0.0f..1.0f���������_�Ƃ��ăt�H�[�}�b�g����܂��B�����ɂ��l�̉����͂���܂���B
		ImGuiColorEditFlags_PickerHueBar = 1 << 25, // [Picker]    // ColorPicker : Hue�̃o�[�ASat/Value�̒����`�B
		ImGuiColorEditFlags_PickerHueWheel = 1 << 26, // [Picker]    // ColorPicker : Hue�̃z�C�[���ASat/Value�̎O�p�`�B
		ImGuiColorEditFlags_InputRGB = 1 << 27, // [Input]     // ColorEdit,ColorPicker : RGB�`���̓��o�̓f�[�^�B
		ImGuiColorEditFlags_InputHSV = 1 << 28, // [Input]     // ColorEdit,ColorPicker : HSV�`���̓��o�̓f�[�^�B

		// �f�t�H���g�I�v�V�����B SetColorEditOptions() ���g�p���āA�A�v���P�[�V�����̃f�t�H���g��ݒ�ł��܂��B�Ӑ}�͂����炭���Ȃ����������Ȃ����Ƃł�
		// �قƂ�ǂ̌Ăяo���ł������I�[�o�[���C�h���܂��B���[�U�[���I�v�V�������j���[����I���ł���悤�ɂ��邩�A�N������SetColorEditOptions() ��1��Ăяo���܂��B
		ImGuiColorEditFlags__OptionsDefault = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_PickerHueBar,
	};

	// �}�E�X�{�^�������ʂ��܂��B 
	// �����̒l�͈��肵�Ă��邱�Ƃ��ۏ؂���Ă���A�p�ɂ�0/1�𒼐ڎg�p���܂��B�֋X��A���O�t���񋓌^���񋟂���܂��B
	enum class ImGuiMouseButton_
	{
		ImGuiMouseButton_Left = 0,
		ImGuiMouseButton_Right = 1,
		ImGuiMouseButton_Middle = 2,
		ImGuiMouseButton_COUNT = 5
	};

	// GetMouseCursor() �̗�
	// ���[�U�[�R�[�h�́ASetMouseCursor() ���Ăяo�����Ƃɂ��A�w�肳�ꂽ�J�[�\����\�����邽�߂̃o�C���f�B���O��v������ꍇ������܂��B���ꂪ�A�����Ŗ��g�p�ƃ}�[�N���ꂽ�J�[�\�������闝�R�ł��B
	enum class ImGuiMouseCursor_
	{
		ImGuiMouseCursor_None = -1,
		ImGuiMouseCursor_Arrow = 0,
		ImGuiMouseCursor_TextInput,       // InputText�ȂǂɃJ�[�\�������킹���
		ImGuiMouseCursor_ResizeAll,       // (Dear ImGui�֐��ł͎g�p����܂���)
		ImGuiMouseCursor_ResizeNS,        // �����̋��E����Ƀ}�E�X���ړ�����Ƃ�
		ImGuiMouseCursor_ResizeEW,        // �����̋��E���܂��͗�̏�Ƀz�o�[����Ƃ�
		ImGuiMouseCursor_ResizeNESW,      // �E�B���h�E�̍������ɃJ�[�\�������킹���
		ImGuiMouseCursor_ResizeNWSE,      // �E�B���h�E�̉E�����ɃJ�[�\�������킹���
		ImGuiMouseCursor_Hand,            // (�e���Ȃ�ImGui�֐��ł͎g�p����܂���B�g�p��n�C�p�[�����N)
		ImGuiMouseCursor_NotAllowed,      // ������Ă��Ȃ�����ŉ������z�o�[����Ƃ��B�ʏ�A���������~�B
		ImGuiMouseCursor_COUNT
	};

	// SetWindow***(),SetNextWindow***(),SetNextItem***() functions �̗�
	// ������\���܂��B
	// �d�v : �ʏ�̗񋓌^�Ƃ��Ĉ����܂��I�񍀉��Z�q���g�p���ĕ����̒l���������Ȃ��ł��������I��L�̂��ׂĂ̊֐��́A0��ImGuiCond_Always�ւ̃V���[�g�J�b�g�Ƃ��Ĉ����܂��B
	enum class ImGuiCond_
	{
		ImGuiCond_Always = 1 << 0, // �ϐ���ݒ肷��
		ImGuiCond_Once = 1 << 1, // �����^�C���Z�b�V�������Ƃɕϐ���1��ݒ肵�܂�(���������ŏ��̌Ăяo���̂�)
		ImGuiCond_FirstUseEver = 1 << 2, // �I�u�W�F�N�g/�E�B���h�E�ɉi���I�ɕۑ����ꂽ�f�[�^���Ȃ��ꍇ(.ini�t�@�C���ɃG���g�����Ȃ��ꍇ)�A�ϐ���ݒ肵�܂�
		ImGuiCond_Appearing = 1 << 3  // �I�u�W�F�N�g/�E�B���h�E����\��/��A�N�e�B�u�ɂȂ��Ă���(�܂��͍ŏ���)�\�������ꍇ�́A�ϐ���ݒ肵�܂�
	};

#pragma endregion

	/**
	@brief string�̐���
	@param [in] format ���͕�����
	@param [in] args �\�����������l
	@return string �e�L�X�g
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
	@brief ������
	*/
	void Init(HWND hWnd, ComPtr<ID3D11Device> Device, ComPtr<ID3D11DeviceContext> DeviceContext);

	/**
	@brief �ݒ�
	*/
	void Setting();

	/**
	@brief �t�H���g�̐ݒ�
	*/
	void SetFont(const char* font_str);

	/**
	@brief �A�C�R���̒ǉ�
	*/
	void SetIcon(const char* icon_str, float size_icon, unsigned short icon_ranges_min, unsigned short icon_ranges_max);

	/**
	@brief �I������
	*/
	void Uninit();

	/**
	@brief �`��
	*/
	void Draw();

	/**
	@brief �f�B�X�v���C�̃T�C�Y
	*/
	Vector2 GetDisplaySize();

	/**
	@brief �o�ߎ��Ԃ�\������
	*/
	void DisplayElapsedTime();

	/**
	@brief �t���[�����[�g��\������
	*/
	void DisplayFramerate();

	/**
	@brief �E�B���h�E�T�C�Y��\������
	*/
	void DisplayWindowsSize();

	/**
	@brief �\���t���[���J�n
	*/
	void NewFrame();

	/**
	@brief �\���t���[���J�n�I���
	*/
	void EndFrame();

	/**
	@brief NewFrame ���Ă΂ꂽ
	*/
	bool IsCheckCallNewFrame();

#pragma region Windows

	/*
    // - Begin() =�E�B���h�E���X�^�b�N�Ƀv�b�V�����A�ǉ����J�n���܂��B End() =�X�^�b�N����E�B���h�E���|�b�v���܂��B
    // - �����t���[�����ɓ����E�B���h�E�ɕ�����ǉ��ł��܂��B
    // - 'bool * p_open�I= nullptr'��n���ƁA�E�B���h�E�̉E����ɃE�B���h�E�����E�B�W�F�b�g���\������A
    //   �N���b�N����ƃu�[���l��false�ɐݒ肳��܂��B
    // - Begin() ��false��Ԃ��A�E�B���h�E���܂肽���܂�Ă��邩���S�ɃN���b�v����Ă��邱�Ƃ������܂��B
    //   �E�B���h�E�ɉ��ł��B�߂�l�Ɋ֌W�Ȃ��ABegin() �Ăяo�����Ƃɏ�Ɉ�v����End() ���Ăяo���܂��I
    //   [�d�v�F�]���̗��R�ɂ��A�����BeginMenu / EndMenu�Ȃǂ̑��̂قƂ�ǂ̋@�\�Ɩ������Ă��܂��B
    //    BeginPopup / EndPopup�ȂǁBEndXXX�Ăяo���́A�Ή�����BeginXXX�֐���
    //    true��Ԃ��܂����B Begin��BeginChild���B��̊�Ȃ��̂ł��B�����̃A�b�v�f�[�g�ŏC�������\��ł��B]
    // - �E�B���h�E�X�^�b�N�̉����ɂ́A��Ɂu�f�o�b�O�v�ƌĂ΂��E�B���h�E���܂܂�Ă��邱�Ƃɒ��ӂ��Ă��������B
	*/

	/**
	@brief �V�����E�B���h�E�J�n
	@param [in] p_open false�ŊJ���Ȃ�/true�ŊJ����
	*/
	bool Begin(const std::string& label, bool* p_open = nullptr, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);

	/**
	@brief �E�B���h�E�I��
	*/
	void End();

#pragma endregion

#pragma region Child Windows

	// - �q�E�B���h�E���g�p���āA�z�X�g�E�B���h�E���̓Ɨ������Ɨ������X�N���[��/�N���b�s���O�̈���J�n���܂��B�q�E�B���h�E�͎����̎q�𖄂ߍ��ނ��Ƃ��ł��܂��B
	// - �u�T�C�Y�v�̊e�Ɨ����ɂ��āF== 0.0f�F�c��̃z�X�g�E�B���h�E�T�C�Y���g�p/> 0.0f�F�Œ�T�C�Y/ <0.0f�F�c��̃E�B���h�E�T�C�Y����abs�isize�j�����������̂��g�p/�e���͈قȂ郂�[�h���g�p�ł��܂��B ImVec2�i0,400�j�B
	// - BeginChild() ��false��Ԃ��A�E�B���h�E���܂肽���܂�Ă��邩���S�ɃN���b�v����Ă��邱�Ƃ������܂��B���̂��߁A�E�B���h�E�ɉ����𑗐M���邱�Ƃ𑁂߂ɏȗ��ł��܂��B
	//   �߂�l�Ɋ֌W�Ȃ��ABeginChild() �Ăяo�����Ƃɏ�Ɉ�v����EndChild() ���Ăяo���܂��iBegin�Ɠ��l�F����́A�]���̗��R�ɂ����̂ŁABeginChild() �̂悤�ɓ��삷��ʏ��Begin() �ȊO�̂قƂ�ǂ�BeginXXX�֐��Ɩ������܂��j ]
	
	/**
	@brief �V�����q�E�B���h�E�J�n
	@param [in] border false�ŊJ���Ȃ�/true�ŊJ����
	*/
	bool BeginChild(const char* str_id, const Vector2& size = Vector2(0, 0), bool border = true, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);
	
	/**
	@brief �V�����q�E�B���h�E�J�n
	@param [in] border false�ŊJ���Ȃ�/true�ŊJ����
	*/
	bool BeginChild(unsigned int id, const Vector2& size = Vector2(0, 0), bool border = true, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);
	
	/**
	@brief �q�E�B���h�E�I��
	*/
	void EndChild();

#pragma endregion

#pragma region Windows Utilities

	// - �u���݂̃E�B���h�E�v= Begin() / End() �u���b�N���ɂ���Ԃɒǉ�����E�B���h�E�B 'next window' = Begin() ���鎟�̃E�B���h�E�B

	/**
	@brief ��ʃX�y�[�X�̌��݂̃E�B���h�E�ʒu���擾���܂��iDrawList API����ēƎ��̕`����s�������ꍇ�ɕ֗��ł��j
	*/
	Vector2 GetWindowPos();

	/**
	@brief ���݂̃E�B���h�E�T�C�Y���擾
	*/
	Vector2 GetWindowSize();

	/**
	@brief ���݂̃E�B���h�E�̕����擾���܂��iGetWindowSize() �Bx�̃V���[�g�J�b�g�j
	*/
	float GetWindowWidth();

	/**
	@brief ���݂̃E�B���h�E�̍������擾����iGetWindowSize() �By�̃V���[�g�J�b�g�j
	*/
	float GetWindowHeight();

	/**
	@brief ���݂̃E�B���h�E�̃^�C�g���o�[�̍������擾
	*/
	float GetTitleBarHeight();
#pragma endregion

#pragma region Prefer using SetNextXXX functions(before Begin) rather that SetXXX functions(after Begin).

	/**
	@brief ���̃E�B���h�E�̈ʒu��ݒ肷��BBegin() �̑O�ɌĂяo���܂��B
	@param [in] pos �E�B���h�E�̈ʒu
	@param [in] cond
	@param [in] pivot �^����ꂽ�_�Ȃǂ𒆐S��
	*/
	void SetNextWindowPos(const Vector2& pos, ImGuiCond_ cond = (ImGuiCond_)0, const Vector2& pivot = Vector2(0, 0));

	/**
	@brief ���̃E�B���h�E�̃T�C�Y��ݒ肷��BBegin() �̑O�ɌĂяo���܂��B
	@param [in] size �E�B���h�E�̃T�C�Y
	@param [in] cond
	*/
	void SetNextWindowSize(const Vector2& size, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief ���̃E�B���h�E�̃T�C�Y������ݒ�
	*/
	void SetNextWindowSizeConstraints(const Vector2& size_min, const Vector2& size_max, void* custom_callback = nullptr, void* custom_callback_data = nullptr);
	
	/**
	@brief ���̃E�B���h�E�̃R���e���c�T�C�Y��ݒ�
	*/
	void SetNextWindowContentSize(const Vector2& size);
	
	/**
	@brief ���̃E�B���h�E�̐܂肽���ݏ�Ԃ�ݒ�
	*/
	void SetNextWindowCollapsed(bool collapsed, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief ���̃E�B���h�E���t�H�[�J�X / ��ԏ�ɐݒ�
	*/
	void SetNextWindowFocus();

	/**
	@brief ���̃E�B���h�E�̔w�i�F�̃A���t�@�l��ݒ�
	*/
	void SetNextWindowBgAlpha(float alpha);
	
	/**
	@brief ���̃E�B���h�E�̃r���[�|�[�g��ݒ�
	*/
	void SetNextWindowViewport(unsigned int viewport_id);

	/**
	@brief �t�H���g�X�P�[����ݒ�
	*/
	void SetWindowFontScale(float scale);
	
	/**
	@brief �E�B���h�E�����w�肵�Ĉʒu���w��
	*/
	void SetWindowPos(const char* name, const Vector2& pos, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief �E�B���h�E�����w�肵�ăT�C�Y���w��
	*/
	void SetWindowSize(const char* name, const Vector2& size, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief �E�B���h�E�����w�肵�Đ܂肽���ݏ�Ԃ��w��
	*/
	void SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond_ cond = (ImGuiCond_)0);

	/**
	@brief ���O�t���E�B���h�E���t�H�[�J�X/��ԏ�ɐݒ� NULL���g�p���ăt�H�[�J�X���폜
	*/
	void SetWindowFocus(const char* name);

#pragma endregion

#pragma region Content region

	// - �����̊֐��͂����ɍĐ݌v����邱�ƂɂȂ��Ă��܂��i�����������܂����A���[�J���E�B���h�E���W�̒l���������A�s���S�ŁA�߂�l�ł��j
	
	/**
	@brief �E�B���h�E���W�̌��݂̃R���e���c���E
	*/
	Vector2 GetContentRegionMax();
	
	/**
	@brief GetContentRegionMax() - GetCursorPos()
	*/
	Vector2 GetContentRegionAvail();

	/**
	@brief �R���e���c�̋��E�̍ŏ��l
	*/
	Vector2 GetWindowContentRegionMin();

	/**
	@brief �E�B���h�E�̍��W�ŁASetNextWindowContentSize�i�j�ŃT�C�Y���I�[�o�[���C�h�ł���R���e���c���E�̍ő�l�i�����悻�i0,0�j+ Size-Scroll�j
	*/
	Vector2 GetWindowContentRegionMax();
	
	float GetWindowContentRegionWidth();

#pragma endregion

#pragma region Windows Scrolling

	/**
	@brief �X�N���[���ʂ��擾
	*/
	float GetScrollX();

	/**
	@brief �X�N���[���ʂ��擾
	*/
	float GetScrollY();
	
	/**
	@brief �ő�X�N���[���ʂ��擾
	*/
	float GetScrollMaxX();

	/**
	@brief �ő�X�N���[���ʂ��擾
	*/
	float GetScrollMaxY();

	/**
	@brief �X�N���[���ʂ�ݒ肷��
	*/
	void SetScrollX(float scroll_x);

	/**
	@brief �X�N���[���ʂ�ݒ肷��
	*/
	void SetScrollY(float scroll_y);

	/**
	@brief ���݂̃J�[�\���ʒu��������悤�ɃX�N���[���ʂ𒲐����܂��B
	*/
	void SetScrollHereX(float center_x_ratio = 0.5f);

	/**
	@brief ���݂̃J�[�\���ʒu��������悤�ɃX�N���[���ʂ𒲐����܂��B
	*/
	void SetScrollHereY(float center_y_ratio = 0.5f);

	/**
	@brief ����̈ʒu��������悤�ɃX�N���[���ʂ𒲐����܂��B
	*/
	void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
	
	/**
	@brief ����̈ʒu��������悤�ɃX�N���[���ʂ𒲐����܂��B
	*/
	void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);

#pragma endregion

#pragma region Parameters stacks (shared)

	/**
	@brief ����UI�̐F��ݒ�
	@param [in] idx UI�̎�ނ̎w��
	@param [in] col �F
	*/
	void PushStyleColor(ImGuiCol_ idx, unsigned int col);

	/**
	@brief UI�̐F��ݒ�
	@param [in] idx UI�̎�ނ̎w��
	@param [in] col �F
	*/
	void PushStyleColor(ImGuiCol_ idx, const Vector4& col);

	/**
	@brief UI�̐F�ύX���I��
	*/
	void PopStyleColor(int count = 1);

	/**
	@brief UI�̃X�^�C����ύX
	*/
	void PushStyleVar(ImGuiStyleVar_ idx, float val);

	/**
	@brief UI�̃X�^�C����ύX
	*/
	void PushStyleVar(ImGuiStyleVar_ idx, const Vector2& val);

	/**
	@brief UI�̃X�^�C���̕ύX���I��
	*/
	void PopStyleVar(int count = 1);

	/**
	@brief UI�̐F���擾
	*/
	Vector4 GetStyleColorVec4(ImGuiCol_ idx);

	/**
	@brief �t�H���g�T�C�Y���擾
	*/
	float GetFontSize();

	/**
	@brief �s�N�Z����UV���W���擾
		ImDrawListAPI����ăJ�X�^���V�F�C�v��`�悷��̂ɖ𗧂��܂�
	*/
	Vector2 GetFontTexUvWhitePixel();

	/**
	@brief UI�̐F���擾
	*/
	unsigned int GetColorU32(ImGuiCol_ idx, float alpha_mul = 1.0f);

	/**
	@brief UI�̐F���擾
	*/
	unsigned int GetColorU32(const Vector4& col);

	/**
	@brief UI�̐F���擾
	*/
	unsigned int GetColorU32(unsigned int col);

#pragma endregion

#pragma region Parameters stacks (current window)

	/**
	@brief ���ꂩ����UI�p�[�c�̕����w��
	*/
	void PushItemWidth(float item_width);

	/**
	@brief UI�p�[�c�̕��̎w��̏I���
	*/
	void PopItemWidth();

	/**
	@brief �܂�Ԃ������镝���w�肵�܂�
	*/
	void PushTextWrapPos(float wrap_local_pos_x = 0.0f);

	/**
	@brief �܂�Ԃ��I���
	*/
	void PopTextWrapPos();

	/**
	@brief ����UI�p�[�c�̕���ݒ�
	*/
	void SetNextItemWidth(float item_width);

	/**
	@brief �{�^���̒��������\�ɂ���
	*/
	void PushButtonRepeat(bool repeat);

	/**
	@brief �{�^���̒��������I���ɂ���
	*/
	void PopButtonRepeat();

#pragma endregion

#pragma region Cursor / Layout

	// - �u�J�[�\���v�Ƃ́A���݂̏o�͈ʒu���Ӗ����܂��B
	// - �E�B�W�F�b�g�̈�ʓI�ȓ���́A���݂̃J�[�\���ʒu�Ŏ������g���o�͂��A�J�[�\����1�s���Ɉړ����邱�Ƃł��B
	// - �E�B�W�F�b�g�Ԃ�SameLine() ���Ăяo���āA���O�̕��A�ƌ��̃E�B�W�F�b�g�̉E���̏o�͂����������Ƃ��ł��܂��B

	/**
	@brief ��������
	*/
	void Separator();

	/**
	@brief �E�B�W�F�b�g�܂��̓O���[�v�ԂŌĂяo���āA�����𐅕��Ƀ��C�A�E�g���܂��B
	@param [in] offset_from_start_x �E�B���h�E���W�ŗ^������X�ʒu
	*/
	void SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);

	/**
	@brief �󔒍s��ǉ�
	*/
	void NewLine();

	/**
	@brief ���������̊Ԋu��ǉ�
	*/
	void Spacing();

	/**
	@brief �w�肳�ꂽ�T�C�Y�̃_�~�[�A�C�e����ǉ����܂��B
	*/
	void Dummy(const Vector2& size);

	/**
	@brief �R���e���c�̈ʒu���E�Ɉړ����܂�
	*/
	void Indent(float indent_w = 0.0f);

	/**
	@brief �R���e���c�̈ʒu�����ɖ߂�
	*/
	void Unindent(float indent_w = 0.0f);

	/**
	@brief �����J�n�ʒu�����b�N
	*/
	void BeginGroup();

	/**
	@brief ���������̊J�n�ʒu�̃��b�N����+�O���[�v�̋��E�{�b�N�X�S�̂�1�́u�A�C�e���v�ɃL���v�`�����܂�
		�i���������āAIsItemHovered�i�j�܂��̓O���[�v�S�̂�SameLine() �Ȃǂ̃��C�A�E�g�v���~�e�B�u���g�p�ł��܂��j�B
	*/
	void EndGroup();

	/**
	@brief �E�B���h�E���W�ł̃J�[�\���ʒu�i�E�B���h�E�ʒu�ɑ��ΓI�j
	*/
	Vector2 GetCursorPos();

	/**
	@brief �E�B���h�E���W�ł̃J�[�\���ʒu X
	*/
	float GetCursorPosX();

	/**
	@brief �E�B���h�E���W�ł̃J�[�\���ʒu Y
	*/
	float GetCursorPosY();

	/**
	@brief �E�B���h�E���W�ł̃J�[�\���ʒu ���C���̐�΍��W�n���g�p���Ă��܂��B
	*/
	void SetCursorPos(const Vector2& local_pos);

	/**
	@brief �E�B���h�E���W�ł̃J�[�\���ʒu ���C���̐�΍��W�n���g�p���Ă��܂��B
		GetWindowPos() + GetCursorPos() == GetCursorScreenPos() etc.)
	*/
	void SetCursorPosX(float local_x);

	/**
	@brief �E�B���h�E���W�ł̃J�[�\���ʒu ���C���̐�΍��W�n���g�p���Ă��܂��B
		GetWindowPos() + GetCursorPos() == GetCursorScreenPos() etc.)
	*/
	void SetCursorPosY(float local_y);

	/**
	@brief �E�B���h�E���W�ł̏����J�[�\���ʒu
	*/
	Vector2 GetCursorStartPos();

	/**
	@brief �����̃r���[�|�[�g���g�p����ꍇ�̐�Ή�ʍ��W
		�i0..io.DisplaySize�j�܂��͎��ROS���W�ł̃J�[�\���ʒu�B ImDrawList API���g�p����ƕ֗��ł��B
	*/
	Vector2 GetCursorScreenPos();

	/**
	@brief �����̃r���[�|�[�g���g�p����ꍇ�̐�Ή�ʍ��W
		�i0..io.DisplaySize�j�܂��͎��ROS���W�ł̃J�[�\���ʒu�B
	*/
	void SetCursorScreenPos(const Vector2& pos);

	/**
	@brief ����̃e�L�X�g�x�[�X���C����FramePadding.y�ɐ����ɑ����āA����I�Ƀt���[�������ꂽ�A�C�e���ɓK�؂ɑ����܂�
		�i�t���[�������ꂽ�A�C�e���̑O�̍s�Ƀe�L�X�g������ꍇ�ɌĂяo���܂��j
	*/
	void AlignTextToFramePadding();

	/**
	@brief FontSize
	*/
	float GetTextLineHeight();

	/**
	@brief FontSize + style.ItemSpacing.y�i2�̘A�������e�L�X�g�s�̊Ԃ̃s�N�Z���P�ʂ̋����j
	*/
	float GetTextLineHeightWithSpacing();

	/**
	@brief FontSize + style.FramePadding.y * 2
	*/
	float GetFrameHeight();

	/**
	@brief FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y
		�i�t���[�������ꂽ�E�B�W�F�b�g��2�̘A�������s�̊Ԃ̃s�N�Z���P�ʂ̋����j
	*/
	float GetFrameHeightWithSpacing();

#pragma endregion

#pragma region Widgets: Trees

	/**
	@brief �c���[�m�[�h
	@param [in] is_open false �f�t�H���g�ŕ��Ă��܂�/true �f�t�H���g�ŊJ���Ă��܂�
	*/
	bool NewTreeNode(const std::string& label, bool& is_open);

	/**
	@brief �c���[�m�[�h�I���
	*/
	void EndTreeNode();

	/**
	@brief �c���[�m�[�h
	*/
	bool TreeNode(const std::string& label);

	/**
	@brief �c���[�m�[�h�I���
	*/
	void TreePop();

	/**
	@brief �J�\�ȃt�B�[���h
	*/
	bool CollapsingHeader(const std::string& label, ImGuiTreeNodeFlags_ flags = (ImGuiTreeNodeFlags_)0);

	/**
	@brief �J�\�ȃt�B�[���h
	*/
	bool CollapsingHeader(const std::string& label, bool& is_open, ImGuiTreeNodeFlags_ flags = (ImGuiTreeNodeFlags_)0);

	/**
	@brief ���̃c���[�m�[�h���J������Ԃɂ��܂�
	*/
	void SetNextItemOpen(bool is_open, ImGuiCond_ cond = (ImGuiCond_)0);

#pragma endregion

#pragma region Widgets: Selectables

	// - �z�o�[����ƑI���\�ȃn�C���C�g���\������A�I������ƕʂ̐F��\���ł��܂��B
	// - �I���\�ȗאl�́A�ނ�̊ԂɌ��Ԃ��c���Ȃ����߂ɁA�n�C���C�g�̋��E���g�����܂��B����́A�I�����ꂽ��A��Selectable���A�����ĕ\������邽�߂ł��B
	
	//�����I������

	/**
	@brief �����I������
	*/
	bool Selectable(const std::string& label, bool selected = false, ImGuiSelectableFlags_ flags = (ImGuiSelectableFlags_)0, const Vector2& size = Vector2(0, 0));  // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
	
	/**
	@brief �����I������
	*/
	bool Selectable(const std::string& label, bool* p_selected, ImGuiSelectableFlags_ flags = (ImGuiSelectableFlags_)0, const Vector2& size = Vector2(0, 0));       // "bool* p_selected" point to the selection state (read-write), as a convenient helper.

#pragma endregion

#pragma region Widgets: List Boxes

	// - FIXME�F���ׂĂ̐V����API�Ƃ̈�ѐ���ۂ��߁AListBoxHeader / ListBoxFooter�͎��ۂɂ�BeginListBox / EndListBox�ƌĂ΂��ׂ��ł��B�����̖��O��ύX���܂��B
	
	/**
	@brief ���X�g�{�b�N�X
	@param [out] current_item �I�񂾃A�C�e��Index
	@param [in] items �A�C�e�����X�g
	@param [in] items_count �A�C�e���̐�
	*/
	bool ListBox(const std::string& label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
	
	bool ListBoxHeader(const std::string& label, const Vector2& size = Vector2(0, 0)); // use if you want to reimplement ListBox() will custom data or interactions. if the function return true, you can output elements then call ListBoxFooter() afterwards.
	bool ListBoxHeader(const std::string& label, int items_count, int height_in_items = -1); // "
	void ListBoxFooter(); // terminate the scrolling region. only call ListBoxFooter() if ListBoxHeader() returned true!

#pragma endregion

#pragma region Widgets: Data Plotting

	/**
	@brief �܂���O���t (�v���b�g���C��)
	@param [in] values �f�[�^
	@param [in] values_count �f�[�^�̐�
	@param [in] overlay_text �^�C�g��
	@param [in] scale_min �ŏ��l
	@param [in] scale_max �ő�l
	@param [in] graph_size �O���t�T�C�Y Vector2(0, 0)�̏ꍇ�͕������͎����ł�
	*/
	void PlotLines(const std::string& label, const float* values, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0), int stride = sizeof(float));
	
	/**
	@brief �܂���O���t (�v���b�g���C��)
	@param [in] values_getter �֐��|�C���^
	@param [in] data �f�[�^
	@param [in] values_count �f�[�^�̐�
	@param [in] overlay_text �^�C�g��
	@param [in] scale_min �ŏ��l
	@param [in] scale_max �ő�l
	@param [in] graph_size �O���t�T�C�Y Vector2(0, 0)�̏ꍇ�͕������͎����ł�
	*/
	void PlotLines(const std::string& label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0));
	
	/**
	@brief �q�X�g�O����
	@param [in] values �f�[�^
	@param [in] values_count �f�[�^�̐�
	@param [in] overlay_text �^�C�g��
	@param [in] scale_min �ŏ��l
	@param [in] scale_max �ő�l
	@param [in] graph_size �O���t�T�C�Y Vector2(0, 0)�̏ꍇ�͕������͎����ł�
	*/
	void PlotHistogram(const std::string& label, const float* values, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0), int stride = sizeof(float));
	
	/**
	@brief �q�X�g�O����
	@param [in] values_getter �֐��|�C���^
	@param [in] data �f�[�^
	@param [in] values_count �f�[�^�̐�
	@param [in] overlay_text �^�C�g��
	@param [in] scale_min �ŏ��l
	@param [in] scale_max �ő�l
	@param [in] graph_size �O���t�T�C�Y Vector2(0, 0)�̏ꍇ�͕������͎����ł�
	*/
	void PlotHistogram(const std::string& label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const std::string overlay_text = std::string(), float scale_min = FLT_MAX, float scale_max = FLT_MAX, Vector2 graph_size = Vector2(0, 0));

#pragma endregion

#pragma region Widgets: Menus

	// - �E�B���h�EImGuiWindowFlags_MenuBar��BeginMenuBar�i�j���g�p���āA���j���[�o�[�ɒǉ����܂��B
	// - BeginMainMenuBar�i�j���g�p���āA��ʏ㕔�Ƀ��j���[�o�[���쐬���܂��B

	/**
	@brief ���j���[�o�[�̊J�n
	*/
	bool BeginMenuBar();

	/**
	@brief ���j���[�o�[�̏I��� 
		BeginMenuBar() ��true�̂Ƃ��̂�
	*/
	void EndMenuBar();

	/**
	@brief �S��ʃ��j���[�o�[�̊J�n
	*/
	bool BeginMainMenuBar();

	/**
	@brief �S��ʃ��j���[�o�[�̏I��� 
		BeginMainMenuBar() ��true�̂Ƃ��̂�
	*/
	void EndMainMenuBar();

	/**
	@brief ���j���[�̊J�n
	*/
	bool BeginMenu(const std::string& label, bool enabled = true);

	/**
	@brief ���j���[�̏I���
		BeginMenu() ��true�̂Ƃ��̂�
	*/
	void EndMenu();

	/**
	@brief ���j���[�̃A�C�e��
	*/
	bool MenuItem(const std::string& label, const char* shortcut = nullptr, bool selected = false, bool enabled = true);

	/**
	@brief ���j���[�̃A�C�e��
	*/
	bool MenuItem(const std::string& label, const char* shortcut, bool* p_selected, bool enabled = true);

#pragma endregion

#pragma region Widgets: Trees Tooltips

	// - �c�[���`�b�v�̓}�E�X�ɑ����E�B���h�E�ŁA�t�H�[�J�X��D���܂���B

	/**
	@brief �c�[���`�b�v�E�B���h�E���J�n/�ǉ����܂��B
		�i�������ނ̃A�C�e�����܂ށj�t���@�\�̃c�[���`�b�v���쐬���܂��B
	*/
	void BeginTooltip();

	/**
	@brief �c�[���`�b�v�E�B���h�E���I��
	*/
	void EndTooltip();

	/**
	@brief �e�L�X�g�݂̂̃c�[���`�b�v��ݒ肵�܂��B
	�ʏ��ImGui::IsItemHovered() �Ŏg�p���܂��B SetTooltip() �ւ̈ȑO�̌Ăяo�����I�[�o�[���C�h���܂��B
	*/
	void SetTooltip(const std::string& label);

#pragma endregion

#pragma region Popups, Modals

	// �|�b�v�A�b�v�E�B���h�E�̃v���p�e�B�͎��̂Ƃ���ł��B
	// - �����́A�ʏ�̃}�E�X�z�o�����O���o���u���b�N���܂��B
	// - ���[�_���łȂ�����A�����̊O���̂ǂ������N���b�N���邩�AESCAPE���������Ƃŕ��邱�Ƃ��ł��܂��B
	// - �����̉�����ԁibool�j�́A�ʏ��Begin�i�j�Ăяo���Ŋ���Ă���v���O���}�[�ɂ���ĕێ������̂ł͂Ȃ��Aimgui�ɂ���ē����I�ɕێ�����܂��B
	//   ���[�U�[�́AOpenPopup�i�j���Ăяo�����Ƃɂ��A������Ԃ𑀍�ł��܂��B
	// - Popup Context�֐��ɂ́A�f�t�H���g�ŉE�}�E�X�iImGuiMouseButton_Right = 1�j���g�p���܂��B
	// IsItemHovered�iImGuiHoveredFlags_AllowWhenBlockedByPopup�j���g�p���āA������o�C�p�X���A�|�b�v�A�b�v�ɂ���Ēʏ�u���b�N����Ă���ꍇ�ł��z�o�����O�����o�ł��܂��B
	// ������3�̃v���p�e�B�͐ڑ�����Ă��܂��B���C�u�����͂��ł��|�b�v�A�b�v����邱�Ƃ��ł��邽�߁A������Ԃ�ێ�����K�v������܂��B
	
	/**
	@brief ID���w�肵�ă|�b�v�A�b�v�����܂� 
	@param [in] str_id �|�b�v�A�b�vID
		BeginPopup(),EndPopup() �Ƃ̕��p
	*/
	void OpenPopup(const char* str_id);

	/**
	@brief �|�b�v�A�b�v�̊J�n
	@param [in] str_id �|�b�v�A�b�vID
		�|�b�v�A�b�v���J���Ă���ꍇ��true��Ԃ��A�o�͂��J�n�ł��܂��B BeginPopup�i�j��true��Ԃ��ꍇ�ɂ̂�EndPopup�i�j���Ăяo���Ă��������I
	*/
	bool BeginPopup(const char* str_id, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0); 
	
	/**
	@brief �A�C�e�����N���b�N���Ƀ|�b�v�A�b�v�̊J�n
	@param [in] str_id �|�b�v�A�b�vID
	@param [in] mouse_button �}�E�X�̃{�^�� �f�t�H���g�͉E�N���b�N
	*/
	bool BeginPopupContextItem(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1);

	/**
	@brief ImGui�E�B���h�E���N���b�N���Ƀ|�b�v�A�b�v�̊J�n
	@param [in] str_id �|�b�v�A�b�vID
	@param [in] mouse_button �}�E�X�̃{�^�� �f�t�H���g�͉E�N���b�N
	*/
	bool BeginPopupContextWindow(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1, bool also_over_items = true);

	/**
	@brief imgui�E�B���h�E���Ȃ��ꍇ�ł̃N���b�N���Ƀ|�b�v�A�b�v�̊J�n 
	@param [in] str_id �|�b�v�A�b�vID
	@param [in] mouse_button �}�E�X�̃{�^�� �f�t�H���g�͉E�N���b�N
	*/
	bool BeginPopupContextVoid(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1);
	
	/**
	@brief ���[�_���_�C�A���O���N���b�N���Ƀ|�b�v�A�b�v�̊J�n
	*/
	bool BeginPopupModal(const char* name, bool* p_open = nullptr, ImGuiWindowFlags_ flags = (ImGuiWindowFlags_)0);

	/**
	@brief �|�b�v�A�b�v�̏I��
		BeginPopupXXX() ��true��Ԃ��ꍇ�ɂ̂�EndPopup() ���Ăяo���Ă��������I
	*/
	void EndPopup();

	/**
	@brief ���ڂ��N���b�N�����Ƃ��Ƀ|�b�v�A�b�v�̊J�n 
	@param [in] str_id �|�b�v�A�b�vID
	@param [in] mouse_button �}�E�X�̃{�^�� �f�t�H���g�͉E�N���b�N
	*/
	bool OpenPopupOnItemClick(const char* str_id = nullptr, ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)1);
	
	/**
	@brief �w��|�b�v�A�b�vID�����݂̓|�b�v�A�b�v���Ă��܂�
	*/
	bool IsPopupOpen(const char* str_id);

	/**
	@brief �|�b�v�A�b�v����܂�
		MenuItem�܂���Selectable���N���b�N����ƁA�|�b�v�A�b�v�͎����I�ɕ��܂��B
	*/
	void CloseCurrentPopup();

#pragma endregion

#pragma region ID stack / scopes

	// - DearImGui�ł�ID�̏������@�̏ڍׂɂ��ẮAFAQ���Q�Ƃ��Ă��������B���[�v���ŃE�B�W�F�b�g���쐬���Ă���ꍇ�́A
	//   ��ӂ̎��ʎq�i�I�u�W�F�N�g�|�C���^�[�A���[�v�C���f�b�N�X�Ȃǁj���v�b�V�����āA��ӂɋ�ʂ������ꍇ������܂��B
	// - ���ʂ�ID�́A�X�^�b�N�S�̂̃n�b�V���ł��B
	// - �܂��A�E�B�W�F�b�g���x�����ŁuLabel ## foobar�v�\�����g�p���āA�������݂��ɋ�ʂ��邱�Ƃ��ł��܂��B
	// - ���̃w�b�_�[�t�@�C���ł́A�u���x���v/�u���O�v�Ƃ����p����g�p���āAID�Ƃ��ĕ\������юg�p����镶����������܂��B
	//   �ustr_id�v�́AID�Ƃ��Ă̂ݎg�p����A�ʏ�͕\������Ȃ�������������܂��B

	/**
	@brief ID�X�^�b�N�ɕ�������v�b�V�����܂��i��������n�b�V�����܂��j
	*/
	void PushID(const char* str_id);

	/**
	@brief ID�X�^�b�N�ɕ�������v�b�V�����܂��i��������n�b�V�����܂��j
	*/
	void PushID(const char* str_id_begin, const char* str_id_end); 

	/**
	@brief ID�X�^�b�N�Ƀ|�C���^�[���v�b�V�����܂��i�|�C���^�[���n�b�V�����܂��j
	*/
	void PushID(const void* ptr_id);

	/**
	@brief ID�X�^�b�N�ɐ������v�b�V�����܂��i�������n�b�V�����܂��j�B
	*/
	void PushID(int int_id);

	/**
	@brief ID�X�^�b�N����|�b�v���܂��B
	*/
	void PopID();

#pragma endregion

#pragma region Widgets: Text

	/**
	@brief �����ȕ����\��
	@param [in] text �\�����e
		�����Ȃ��̐��e�L�X�g�A�������R�s�[�╶���R�[�h�ϊ����Ȃ��̂ō����ł�
	*/
	void TextUnformatted(const char* text, const char* text_end = nullptr);

	/**
	@brief �����\��
	@param [in] fmt �\�����e
	*/
	void Text(const std::string& fmt);

	/**
	@brief �F�t�������\��
	@param [in] fmt �\�����e
	@param [in] collar �F
	*/
	void Text(const std::string& fmt, const Vector4& collar);

	/**
	@brief Bullet�t�������\��
	@param [in] fmt �\�����e
	*/
	void BulletText(const std::string& fmt);

	/**
	@brief �����ȕ��� �O���[�ŕ\��
	@param [in] fmt �\�����e
	*/
	void TextDisabled(const std::string& fmt);

	/**
	@brief �����I�ɐ܂�Ԃ��Ď��̍s�ɕ\��
	@param [in] fmt �\�����e
	*/
	void TextWrapped(const std::string& fmt);

	/**
	@brief value + label�E�B�W�F�b�g�Ɠ������@�Ő��񂳂ꂽtext + label��\�����܂�
	@param [in] label ���x��
	@param [in] fmt �l
	*/
	void LabelText(const std::string& label, const std::string& fmt);

#pragma endregion

#pragma region Widgets: Color Editor/Picker

	// �E�B�W�F�b�g�F�J���[�G�f�B�^�[/�s�b�J�[�i�q���g�FColorEdit *�֐��ɂ́A�����ȐF�̃v���r���[�l�p�`������A���N���b�N���ăs�b�J�[���J���A�E�N���b�N���ăI�v�V�������j���[���J�����Ƃ��ł��܂��B�j
	// - C ++�ł́A�ufloat v [X]�v�֐��̈����́ufloat * v�v�Ɠ����ł��邱�Ƃɒ��ӂ��Ă��������B�z��\���́A�A�N�Z�X�\�ȗv�f�̐��𕶏���������@�ɂ����܂���B
	// - �A������\���̂���ŏ��̃t���[�g�v�f�̃A�h���X��n�����Ƃ��ł��܂��B ��myvector.x

	/**
	@brief RGB�l
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

	// - Ctrl�L�[�������Ȃ���X���C�_�[���N���b�N���āA���̓{�b�N�X�ɕϊ����܂��B�蓮�œ��͂����l�͌Œ肳�ꂸ�A�͈͊O�ɂȂ�\��������܂��B
	// - ����������𒲐����āA�l���v���t�B�b�N�X�A�T�t�B�b�N�X�ő������邩�A�ҏW�ƕ\���̐��x�𒲐����܂��B "��.3f"-> 1.234; �u��5.2f�b�v-> 01.23�b�B "�r�X�P�b�g�F��.0f"->�r�X�P�b�g�F1;��
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderFloat(const std::string& label, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);     // �X���C�_�[�����x���܂��̓��j�b�g�\���̃v���t�B�b�N�X�܂��̓T�t�B�b�N�X�Œl���C������悤�Ƀt�H�[�}�b�g�𒲐����܂��B power�I= 1.0���p���[�J�[�u�X���C�_�[�Ɏg�p���܂�
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderFloat2(const std::string& label, float v[2], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderFloat3(const std::string& label, float v[3], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderFloat4(const std::string& label, float v[4], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief �X�N���[���o�[ �p�x
	@param [in/out] v ����Ώ�
	*/
	bool SliderAngle(const std::string& label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg");
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderInt(const std::string& label, int* v, int v_min, int v_max, const char* format = "%d");
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderInt2(const std::string& label, int v[2], int v_min, int v_max, const char* format = "%d");
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderInt3(const std::string& label, int v[3], int v_min, int v_max, const char* format = "%d");
	
	/**
	@brief �X�N���[���o�[
	@param [in/out] v ����Ώ�
	*/
	bool SliderInt4(const std::string& label, int v[4], int v_min, int v_max, const char* format = "%d");
	
	bool SliderScalar(const std::string& label, ImGuiDataType_ data_type, void* p_data, const void* p_min, const void* p_max, const char* format = nullptr, float power = 1.0f);
	bool SliderScalarN(const std::string& label, ImGuiDataType_ data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = nullptr, float power = 1.0f);
	bool VSliderFloat(const std::string& label, const Vector2& size, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
	bool VSliderInt(const std::string& label, const Vector2& size, int* v, int v_min, int v_max, const char* format = "%d");
	bool VSliderScalar(const std::string& label, const Vector2& size, ImGuiDataType_ data_type, void* p_data, const void* p_min, const void* p_max, const char* format = nullptr, float power = 1.0f);

#pragma endregion

#pragma region Widgets: Input with Keyboard

	// - InputText() ��std::string�Ȃǂ̓��I�ȕ�����^�܂��͓Ǝ��̂��̂Ŏg�p����ꍇ�́Aimgui_stdlib.h���Q�Ƃ��Ă�������
	// - ImGuiInputTextFlags_�t���O�̂قƂ�ǂ́AInputText() �ɑ΂��Ă̂ݗL�p�ł���AInputFloatX�AInputIntX�AInputDouble�Ȃǂɂ͖𗧂��܂���B

	/**
	@brief �e�L�X�g�{�b�N�X
	@param [in] str �󂯎���
	*/
	bool InputText(const std::string& label, std::string* str, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief �e�L�X�g�{�b�N�X
	@param [in] buf �󂯎���
	*/
	bool InputText(const std::string& label, char* buf, size_t buf_size, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief �e�L�X�g�{�b�N�X
	@param [in] str �󂯎���
	*/
	bool InputTextMultiline(const std::string& label, std::string* str, const Vector2& size = Vector2(0, 0), ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief �e�L�X�g�{�b�N�X
	@param [in] buf �󂯎���
	*/
	bool InputTextMultiline(const std::string& label, char* buf, size_t buf_size, const Vector2& size = Vector2(0, 0), ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief �e�L�X�g�{�b�N�X
	@param [in] hint �q���g
	@param [in] str �󂯎���
	*/
	bool InputTextWithHint(const std::string& label, const std::string& hint, std::string* str, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief �e�L�X�g�{�b�N�X
	@param [in] hint �q���g
	@param [in] buf �󂯎���
	*/
	bool InputTextWithHint(const std::string& label, const std::string& hint, char* buf, size_t buf_size, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0, int* callback = nullptr, void* user_data = nullptr);
	
	/**
	@brief float ����
	@param [in] v �󂯎���
	*/
	bool InputFloat(const std::string& label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief float ����
	@param [in] v �󂯎���
	*/
	bool InputFloat2(const std::string& label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief float ����
	@param [in] v �󂯎���
	*/
	bool InputFloat3(const std::string& label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief float ����
	@param [in] v �󂯎���
	*/
	bool InputFloat4(const std::string& label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int ����
	@param [in] v �󂯎���
	*/
	bool InputInt(const std::string& label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int ����
	@param [in] v �󂯎���
	*/
	bool InputInt2(const std::string& label, int v[2], ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int ����
	@param [in] v �󂯎���
	*/
	bool InputInt3(const std::string& label, int v[3], ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief int ����
	@param [in] v �󂯎���
	*/
	bool InputInt4(const std::string& label, int v[4], ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	/**
	@brief double ����
	@param [in] v �󂯎���
	*/
	bool InputDouble(const std::string& label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	
	bool InputScalar(const std::string& label, ImGuiDataType_ data_type, void* p_data, const void* p_step = nullptr, const void* p_step_fast = nullptr, const char* format = nullptr, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);
	bool InputScalarN(const std::string& label, ImGuiDataType_ data_type, void* p_data, int components, const void* p_step = nullptr, const void* p_step_fast = nullptr, const char* format = nullptr, ImGuiInputTextFlags_ flags = (ImGuiInputTextFlags_)0);

#pragma endregion

#pragma region Widgets: Main

	// - �قƂ�ǂ̃E�B�W�F�b�g�́A�l���ύX���ꂽ�Ƃ��A�܂��͉����ꂽ/�I�����ꂽ�Ƃ���true��Ԃ��܂�
	// - ������IsItemXXX�֐��iIsItemActive�AIsItemHovered�Ȃǁj��1���g�p���āA�E�B�W�F�b�g�̏�Ԃ��Ɖ�邱�Ƃ��ł��܂��B

	/**
	@brief �{�^��
	@param [in] label �{�^����
	@param [in] size_arg �{�^���T�C�Y
	*/
	bool Button(const std::string& label, const Vector2& size_arg = Vector2(0, 0));

	/**
	@brief �����ȃ{�^��
	@param [in] label �{�^����
	*/
	bool SmallButton(const std::string& label);

	/**
	@brief ���̌`�̐����`�{�^��
	@param [in] label �{�^����
	@param [in] dir ����
	*/
	bool ArrowButton(const char* str_id, ImGuiDir_ dir);

	/**
	@brief �e�N�X�`���̕\��
	@param [in] user_texture_id �e�N�X�`���̃|�C���^
	*/
	void Image(void* user_texture_id, const Vector2& size, const Vector2& uv0 = Vector2(0, 0), const Vector2& uv1 = Vector2(1, 1), const Vector4& tint_col = Vector4(1, 1, 1, 1), const Vector4& border_col = Vector4(0, 0, 0, 0));

	/**
	@brief �e�N�X�`���Ń{�^��
	@param [in] user_texture_id �e�N�X�`���̃|�C���^
	*/
	bool ImageButton(void* user_texture_id, const Vector2& size, const Vector2& uv0 = Vector2(0, 0), const Vector2& uv1 = Vector2(1, 1), int frame_padding = -1, const Vector4& bg_col = Vector4(0, 0, 0, 0), const Vector4& tint_col = Vector4(1, 1, 1, 1));

	/**
	@brief �`�F�b�N�{�b�N�X
	@param [in] label �`�F�b�N�{�b�N�X��
	@param [in] flag ���삷��bool
	*/
	bool Checkbox(const std::string& label, bool& flag);

	/**
	@brief ���W�I�{�^��
	@param [in] label ���W�I�{�^����
	*/
	bool RadioButton(const std::string& label, bool active);

	/**
	@brief ���W�I�{�^��
	@param [in] label ���W�I�{�^����
	@param [in] value v_button�̊i�[��
	@param [in] v_button value�Ɋi�[����l
	*/
	bool RadioButton(const std::string& label, int* value, int v_button);

	/**
	@brief �v���O���X�o�[ : 0 ~ 1 �܂ł̒��ł� fraction �������̈ʒu�ɂ���̂���\�����܂��B
	*/
	void ProgressBar(float fraction, const Vector2& size_arg = Vector2(-1, 0), const char* overlay = nullptr);

	/**
	@brief �����ȉ~��`���A�J�[�\���𓯂�����ɒu���܂��B TreeNode() ���g�p���鋗���Ɠ��������ŁAGetTreeNodeToLabelSpacing() �ɂ���ăJ�[�\����x�ʒu��i�߂�
	*/
	void Bullet();

#pragma endregion

#pragma region Widgets: Combo Box

	// - BeginCombo() / EndCombo() API���g�p����ƁA���̂悤�ɍ쐬���邱�ƂŁA�R���e���c��I����Ԃ����R�ɊǗ��ł��܂��B Selectable() �A�C�e���B
	// - �Â�Combo() api�́ABeginCombo() / EndCombo() �̃w���p�[�ł���A�֗��ȖړI�ŗ��p�ł��܂��B

	bool BeginCombo(const std::string& label, const char* preview_value, ImGuiComboFlags_ flags = (ImGuiComboFlags_)0);

	// only call EndCombo() if BeginCombo() returns true!
	void EndCombo(); 

	/**
	@brief �h���b�v�_�E�����X�g
	@param [in] current_item �A�C�e����Index
	@param [in] items �A�C�e�����X�g
	@param [in] items_size �A�C�e���̐�
	*/
	bool Combo(const std::string& label, int* current_item, const char* const items[], int items_size, int popup_max_height_in_items = -1);

	/**
	@brief �h���b�v�_�E�����X�g
	��������ŃA�C�e����\0�ŋ�؂�Aitem-list��\0\0�ŏI�����܂��B�Ⴆ�� "One\0Two\0Three\0"
	@param [in] current_item �A�C�e����Index
	@param [in] items_separated_by_zeros �A�C�e�����X�g
	*/
	bool Combo(const std::string& label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);

#pragma endregion

#pragma region Widgets: Drags

	// - Ctrl�L�[�������Ȃ���C�ӂ̃h���b�O�{�b�N�X���N���b�N���āA���̓{�b�N�X�ɕϊ����܂��B�蓮�œ��͂����l�͌Œ肳�ꂸ�A�͈͊O�ɂȂ�\��������܂��B
	// - ���ׂĂ̊֐��̂��ׂĂ�Float2 / Float3 / Float4 / Int2 / Int3 / Int4�o�[�W�����ł́A�ufloat v [X]�v�֐��̈����́ufloat * v�v�Ɠ����ł��邱�Ƃɒ��ӂ��Ă��������B�z��\���͕������̕��@�ɂ����܂���A�N�Z�X�\�ł���Ɨ\�z�����v�f�̐��B�A�������Z�b�g����ŏ��̗v�f�̃A�h���X��n�����Ƃ��ł��܂��B ��myvector.x
	// - ����������𒲐����āA�l���v���t�B�b�N�X�A�T�t�B�b�N�X�ő������邩�A�ҏW�ƕ\���̐��x�𒲐����܂��B "��.3f"-> 1.234; �u��5.2f�b�v-> 01.23�b�B "�r�X�P�b�g�F��.0f"->�r�X�P�b�g�F1;��
	// - ���x�̓}�E�X�̓����̃s�N�Z�����Ƃł��iv_speed = 0.2f�F�l��1���₷�ɂ́A�}�E�X��5�s�N�Z���������K�v������܂��j�B�Q�[���p�b�h/�L�[�{�[�h�i�r�Q�[�V�����̏ꍇ�A�ŏ����x��Max�iv_speed�Aminimum_step_at_given_precision�j�ł��B
	// - v_min <v_max���g�p���āA�w�肳�ꂽ�����ɕҏW���N�����v���܂��B Ctrl�L�[�������Ȃ���N���b�N����蓮���͂́A�����̐������㏑���ł��邱�Ƃɒ��ӂ��Ă��������B
	// - v_max = FLT_MAX / INT_MAX�Ȃǂ��g�p���čő�l�ւ̃N�����v��������܂��Bv_min= -FLT_MAX / INT_MIN�Ɠ��l�ɍŏ��l�ւ̃N�����v��������܂��B
	// - �ҏW�����b�N����ɂ́Av_min> v_max���g�p���܂��B

	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragFloat(const std::string& label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);     // If v_min >= v_max we have no bound
	
	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragFloat2(const std::string& label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragFloat3(const std::string& label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragFloat4(const std::string& label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
	
	/**
	@brief 	�ŏ��l, �ő�l �X���C�_�[��2�쐬
	@param [in/out] v_current_min ����Ώ�
	@param [in/out] v_current_max ����Ώ�
	*/
	bool DragFloatRange2(const std::string& label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = nullptr, float power = 1.0f);
	
	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragInt(const std::string& label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");                                       // If v_min >= v_max we have no bound
	
	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragInt2(const std::string& label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	
	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragInt3(const std::string& label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	
	/**
	@brief �X���C�_�[
	@param [in/out] v ����Ώ�
	*/
	bool DragInt4(const std::string& label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
	
	bool DragIntRange2(const std::string& label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = nullptr);
	bool DragScalar(const std::string& label, ImGuiDataType_ data_type, void* p_data, float v_speed, const void* p_min = nullptr, const void* p_max = nullptr, const char* format = nullptr, float power = 1.0f);
	bool DragScalarN(const std::string& label, ImGuiDataType_ data_type, void* p_data, int components, float v_speed, const void* p_min = nullptr, const void* p_max = nullptr, const char* format = nullptr, float power = 1.0f);

#pragma endregion

#pragma region Item / Widgets Utilities

	// - �قƂ�ǂ̊֐��́A���M�����Ō��/�O�̃A�C�e�����Q�Ƃ��Ă��܂��B
	// - �����̋@�\�̂قƂ�ǂ̃C���^���N�e�B�u�Ȏ��o���ɂ��ẮA�u�E�B�W�F�b�g->�X�e�[�^�X�̃N�G���v�̃f���E�B���h�E���������������B

	/**
	@brief �Ō�̃A�C�e�����z�o�[����Ă��܂����H �i�g�p�\�A�ʖ��|�b�v�A�b�v�Ȃǂɂ���ău���b�N����Ȃ��j�B
		���̑��̃I�v�V�����ɂ��ẮAImGuiHoveredFlags_���Q�Ƃ��Ă��������B
	*/
	bool IsItemHovered(ImGuiHoveredFlags_ flags = (ImGuiHoveredFlags_)0);

	/**
	@brief �Ō�̃A�C�e���̓A�N�e�B�u�ł����H �i��F�{�^����������Ă���A�e�L�X�g�t�B�[���h���ҏW����Ă��܂��B
		�A�C�e����Ń}�E�X�{�^���������Ă���ԁA����͌p���I��true��Ԃ��܂��B���ݍ�p���Ȃ��A�C�e���͏��false��Ԃ��܂��j
	*/
	bool IsItemActive();

	/**
	@brief �Ō�̃A�C�e���̓L�[�{�[�h/�Q�[���p�b�h�i�r�Q�[�V�����ɏœ_�����킹�Ă��܂����H
	*/
	bool IsItemFocused();

	/**
	@brief �Ō�̃A�C�e���̓N���b�N����܂������H 
		�i��F�{�^��/�m�[�h���N���b�N���������j== IsMouseClicked�imouse_button�j&& IsItemHovered() 
	*/
	bool IsItemClicked(ImGuiMouseButton_ mouse_button = (ImGuiMouseButton_)0);

	/**
	@brief �Ō�̃A�C�e���͕\������Ă��܂����H �i
		�N���b�s���O/�X�N���[���̂��߂ɃA�C�e���������Ȃ��Ȃ�ꍇ������܂��j
	*/
	bool IsItemVisible();

	/**
	@brief �Ō�̃A�C�e���́A���̃t���[���̊�b�ƂȂ�l��ύX���܂������H�܂��͉����ꂽ�H
		����͒ʏ�A�����̃E�B�W�F�b�g�́u�u�[���v�߂�l�Ɠ����ł��B
	*/
	bool IsItemEdited(); 

	/**
	@brief �Ō�ɃA�N�e�B�u�ɂ����A�C�e���ł����i�A�C�e���͈ȑO�͔�A�N�e�B�u�ł����j�B
	*/
	bool IsItemActivated();

	/**
	@brief �Ō�ɔ�A�N�e�B�u�ɂ����A�C�e���i�A�C�e���͈ȑO�A�N�e�B�u�ł����j�B
		�p���I�ȕҏW���K�v�ȃE�B�W�F�b�g���g�p�������ɖ߂�/��蒼���p�^�[���ɖ𗧂��܂��B
	*/
	bool IsItemDeactivated();

	/**
	@brief �Ō�̍��ڂ��A�N�e�B�u�ɂȂ����Ƃ��ɔ�A�N�e�B�u�ɂȂ�A�l���ύX����܂������H 
		�i��F�X���C�_�[/�h���b�O�̈ړ��j�B
		�p���I�ȕҏW���K�v�ȃE�B�W�F�b�g���g�p�������ɖ߂�/��蒼���p�^�[���ɖ𗧂��܂��B
		�댟�m����������\�������邱�Ƃɒ��ӂ��Ă��������iCombo() / ListBox() / Selectable() �Ȃǂ̈ꕔ�̃E�B�W�F�b�g�́A���ɑI������Ă���A�C�e�����N���b�N���Ă�true��Ԃ��܂��j�B
	*/
	bool IsItemDeactivatedAfterEdit();

	/**
	@brief �Ō�̃A�C�e���̃I�[�v����Ԃ͐؂�ւ����܂������H TreeNode() �ɂ���Đݒ肳��܂��B
	*/
	bool IsItemToggledOpen();

	/**
	@brief �z�o�[���ꂽ�A�C�e���ł����H
	*/
	bool IsAnyItemHovered();

	/**
	@brief �A�N�e�B�u�ȃA�C�e���͂���܂����H
	*/
	bool IsAnyItemActive();

	/**
	@brief �t�H�[�J�X����Ă���A�C�e���͂���܂����H
	*/
	bool IsAnyItemFocused();

	/**
	@brief �Ō�̃A�C�e���i��ʃX�y�[�X�j�̍���̋��E��`���擾���܂�
	*/
	Vector2 GetItemRectMin();

	/**
	@brief �Ō�̃A�C�e���i��ʃX�y�[�X�j�̉E���̋��E��`���擾���܂�
	*/
	Vector2 GetItemRectMax();

	/**
	@brief �Ō�̃A�C�e���̃T�C�Y���擾
	*/
	Vector2 GetItemRectSize();

	/**
	@brief �Ō�̃A�C�e�����㑱�̃A�C�e���ƃI�[�o�[���b�v�ł���悤�ɂ��܂��B
		��\���̃{�^���A�I���\���ڂȂǂŖ��g�p�̗̈���L���b�`����̂ɖ𗧂ꍇ������܂��B
	*/
	void SetItemAllowOverlap();

#pragma endregion

#pragma region Inputs Utilities: Keyboard

	// - 'int user_key_index'�̏ꍇ�A�o�b�N�G���h/�G���W����io.KeysDown []�ɕۑ��������@�ɉ����āA�Ǝ��̃C���f�b�N�X/�񋓂��g�p�ł��܂��B
	// - �����̒l�̈Ӗ��͂킩��܂���B GetKeyIndex() ���g�p���āAImGuiKey_�l�����[�U�[�C���f�b�N�X�Ƀ}�b�v�ł��܂��B
	
	/**
	@brief ImGuiKey_�Ŏw��L�[��Index���擾���܂�
	@param [in] imgui_key ImGuiKey_ �L�[�̎w��
	@param return �L�[��Index
	*/
	int GetKeyIndex(ImGuiKey_ imgui_key);
	
	/**
	@brief �L�[����
	@param [in] user_key_index GetKeyIndex() ��Index
	*/
	bool IsKeyDown(int user_key_index);

	/**
	@brief �L�[���� ������
	@param [in] user_key_index GetKeyIndex() ��Index
	@param [in] repeat ���s�[�g����
	*/
	bool IsKeyPressed(int user_key_index, bool repeat = true);

	/**
	@brief �L�[���� ��������
	@param [in] user_key_index GetKeyIndex() ��Index
	*/
	bool IsKeyReleased(int user_key_index);

	// uses provided repeat rate/delay. return a count, most often 0 or 1 but might be >1 if RepeatRate is small enough that DeltaTime > RepeatRate
	int GetKeyPressedAmount(int key_index, float repeat_delay, float rate);

	// attention: misleading name! manually override io.WantCaptureKeyboard flag next frame (said flag is entirely left for your application to handle). e.g. force capture keyboard when your widget is being hovered. This is equivalent to setting "io.WantCaptureKeyboard = want_capture_keyboard_value"; after the next NewFrame() call.
	void CaptureKeyboardFromApp(bool want_capture_keyboard_value = true);

#pragma endregion

#pragma region Inputs Utilities: Mouse

	// - �}�E�X�{�^�����Q�Ƃ���ɂ́A�R�[�h�Ŗ��O�t���񋓌^���g�p�ł��܂��B ImGuiMouseButton_Left�AImGuiMouseButton_Right�B
	// - �܂��A�ʏ�̐������g�p���邱�Ƃ��ł��܂��B0=���A1 =�E�A2 =�������i�v�ɕۏ؂���܂��B
	// - �h���b�O����́A�}�E�X���ŏ��̃N���b�N�ʒu�������̋����������ꂽ��ɂ̂ݕ񍐂���܂��i�ulock_threshold�v����сuio.MouseDraggingThreshold�v���Q�Ɓj
	
	/**
	@brief �}�E�X����
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseDown(ImGuiMouseButton_ button);
	
	/**
	@brief �}�E�X�{�^�����N���b�N���ꂽ��
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseClicked(ImGuiMouseButton_ button, bool repeat = false);
	
	/**
	@brief �}�E�X���� ��������
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseReleased(ImGuiMouseButton_ button);
	
	/**
	@brief �_�u���N���b�N�������ǂ���
	@param [in] button ImGuiMouseButton_
	*/
	bool IsMouseDoubleClicked(ImGuiMouseButton_ button);

	/**
	@brief �z�o�����O
	*/
	bool IsMouseHoveringRect(const Vector2& r_min, const Vector2& r_max, bool clip = true);

	bool IsMousePosValid(const Vector2* mouse_pos = nullptr);

	/**
	@brief �}�E�X�̃{�^����������Ă��邩
	*/
	bool IsAnyMouseDown();

	/**
	@brief �}�E�X�̍��W
	*/
	Vector2 GetMousePos();

	/**
	@brief �|�b�v�A�b�v���J���Ƃ��Ƀ}�E�X�̈ʒu���擾
	*/
	Vector2 GetMousePosOnOpeningCurrentPopup();

	/**
	@brief �h���b�O���Ă��܂�
	*/
	bool IsMouseDragging(ImGuiMouseButton_ button, float lock_threshold = -1.0f);

	/**
	@brief �}�E�X�{�^����������Ă���ԁA�܂��͂��傤�Ǘ����ꂽ�Ƃ��ɁA�ŏ��̃N���b�N�ʒu����f���^��Ԃ��܂�
	*/
	Vector2 GetMouseDragDelta(ImGuiMouseButton_ button = (ImGuiMouseButton_)0, float lock_threshold = -1.0f);

	/**
	@brief ���������Z�b�g
	*/
	void ResetMouseDragDelta(ImGuiMouseButton_ button = (ImGuiMouseButton_)0);
	
	/**
	@brief �ǂ�UI�ɐG��Ă��邩�̏����擾
	*/
	ImGuiMouseCursor_ GetMouseCursor();

	/**
	@brief �ړI�̃J�[�\���^�C�v��ݒ肵�܂�
	*/
	void SetMouseCursor(ImGuiMouseCursor_ cursor_type);

#pragma endregion

#pragma region Columns

	// - SameLine�ipos_x�j���g�p���āA�P�������ꂽ���͕킷�邱�Ƃ��ł��܂��B
	// - ��API�͐i�s���̍�Ƃł���A���Ȃ茇���Ă��܂��i�����_�ł́A��͊ԈႢ�Ȃ��e���Ȃ�imgui�̍ň��̕����ł��I�j
	// - �ő�64��ł��B
	// - 2019�N���܂łɁA���u��������V�����u�e�[�u���vAPI�����J����܂��B

	/**
	@brief �\�̍쐬
	@param [in] count ���ɕ��ׂ鐔
	*/
	void Columns(int count = 1, const char* id = nullptr, bool border = true);

	/**
	@brief �\�����̗��
	*/
	void NextColumn();

	/**
	@brief �\��Index
	*/
	int GetColumnIndex();

	/**
	@brief ��̕����擾
	*/
	float GetColumnWidth(int column_index = -1);

	/**
	@brief ��̕���ݒ�
	*/
	void SetColumnWidth(int column_index, float width);

	/**
	@brief ����̈ʒu���擾
	*/
	float GetColumnOffset(int column_index = -1);

	/**
	@brief ����̈ʒu��ݒ�
	*/
	void SetColumnOffset(int column_index, float offset_x);

	int GetColumnsCount();

#pragma endregion

#pragma region Tab Bars, Tabs

	// ���F�^�u�́A�h�b�L���O�V�X�e���ɂ���Ď����I�ɍ쐬����܂��B������g�p���āA�h�b�L���O���s�킸�Ɏ����Ń^�u�o�[/�^�u���쐬���܂��B
	
	/**
	@brief TabBar�̊J�n
	@param [in] str_id �^�uID
	*/
	bool BeginTabBar(const char* str_id, ImGuiTabBarFlags_ flags = (ImGuiTabBarFlags_)0);

	/**
	@brief TabBar�̏I��
	*/
	void EndTabBar();

	/**
	@brief �^�u�̊J�n
	*/
	bool BeginTabItem(const std::string& label, bool& p_open, ImGuiTabItemFlags_ flags = (ImGuiTabItemFlags_)0);

	/**
	@brief �^�u�̏I��
		BeginTabItem() ��true�̎��̂�
	*/
	void EndTabItem();

	/**
	@brief �����^�u/�E�B���h�E�̐��TabBar�܂��̓h�b�L���O�V�X�e���ɒʒm���܂�
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