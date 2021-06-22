//==========================================================================
// �����_���[�}�l�[�W���[ [RendererManager.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "Component.h"
#include "GameObject.h"
#include "../System.h"

#pragma region forward declaration
// �O���錾
_MDX_OBJECT_BEGIN
class Scene;
_MDX_OBJECT_END
#pragma endregion

_MDX_COMPONENT_BEGIN

// �`��@�\���X�g
enum class ERendererList : int
{
	Empty = -1,
	GridRenderer,
	MeshRenderer,
	CanvasRenderer,
	PointRenderer,
	Max
};

//==========================================================================
//
// class : RendererManager 
// Content : �����_���[�}�l�[�W���[
// details : �p���p/�V�[�����Ŏg�p
//
//==========================================================================
class RendererManager :
	public Component
{
	friend object::Scene;
private:
	// �����_���[�̊Ǘ�
	// [�����Ă���V�[��][�����_���[�̎��][�����_���[]
	static std::unordered_map<object::Scene*, std::unordered_map<ERendererList, std::list< RendererManager*>>> m_Renderers;
public:
	RendererManager();
	~RendererManager();
protected:
	/**
	@brief �F��o�^���܂��B
	@param [in] color : �F
	@details 0.0f�`1.0f�̊Ԃł��肢���܂��B
	*/
	virtual void SetColor(const math::Vector4& color);

	/**
	@brief �F��o�^���܂��B
	@param [in] r : R�l
	@param [in] g : G�l
	@param [in] b : B�l
	@param [in] a : A�l
	@details 0.0f�`1.0f�̊Ԃł��肢���܂��B
	*/
	virtual void SetColor(float r, float g, float b, float a);

	/**
	@brief �F���擾���܂��B
	@return �F
	*/
	virtual const math::Vector4& GetColor() const;

	/**
	@brief ���_�V�F�[�_�[��o�^���܂��B
	@param [in] shader : �V�F�[�_�[
	@details �f�t�H���g�V�F�[�_�[�͕ێ�����Ă��܂��B
	*/
	virtual void SetVertexShader(const structure::VertexShader& shader);

	/**
	@brief �s�N�Z���V�F�[�_�[��o�^���܂��B
	@param [in] shader : �V�F�[�_�[
	@details �f�t�H���g�V�F�[�_�[�͕ێ�����Ă��܂��B
	*/
	virtual void SetPixelShader(const structure::PixelShader& shader);

	/**
	@brief ���_���C�A�E�g��o�^���܂��B
	@param [in] layout : ���C�A�E�g
	@details �f�t�H���g���C�A�E�g�͕ێ�����Ă��܂��B
	*/
	virtual void SetInputLayout(const structure::InputLayout& layout);

	/**
	@brief �f�t�H���g�V�F�[�_�[�𕜌����܂��B
	@details �w�肵���V�F�[�_�[�̓o�^�͉�������܂��B
	*/
	virtual void RestoreDefaultShader();

	/**
	@brief �`��
	@param [in] view : �r���[�s��
	@param [in] projection : �v���W�F�N�V�����s��
	*/
	virtual void Draw(const math::Matrix& view, const math::Matrix& projection);

	/**
	@brief �`��
	*/
	virtual void Draw();

	/**
	@brief �����_���[�̓o�^
	@param [in] RendererPtr : �����_���[�̃|�C���^�B
	@param [in] ObjectPtr : �I�u�W�F�N�g�̃|�C���^�B
	*/
	void SetRenderer(ERendererList RendererType, RendererManager* RendererPtr, object::GameObject* ObjectPtr);

	/**
	@brief �����_���[�̉��
	@param [in] RendererPtr : �����_���[�̃|�C���^�B
	@param [in] ObjectPtr : �I�u�W�F�N�g�̃|�C���^�B
	*/
	void ReleaseRenderer(ERendererList RendererType, RendererManager* RendererPtr, object::GameObject* ObjectPtr);
private:
	/**
	@brief �V�[���p�̃����_���[�Ǘ��g�̐����B
	@param [in] scene : �V�[���̃|�C���^�B
	*/
	static void CreateSceneRenderer(object::Scene* scene);

	/**
	@brief �V�[���ɑ����Ă��郌���_���[�̔j���B
	@param [in] scene : �V�[���̃|�C���^
	*/
	static void ReleaseSceneRenderer(object::Scene* scene);

	/**
	@brief �V�[���ɑ����Ă��郌���_���[�S�Ă̕`��
	@param [in] scene : �V�[���̃|�C���^�B
	*/
	static void DrawSceneRenderer(object::Scene* scene, const math::Matrix& view, const math::Matrix& projection);
};

_MDX_COMPONENT_END