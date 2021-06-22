//==========================================================================
// �O���b�h�����_���[ [GridRenderer.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "RendererManager.h"

// �O���b�h�̒��_
_MDX_STRUCTURE_BEGIN
struct GridVertex :
	public Vertex
{
	math::Vector4 color; // �F
};
_MDX_STRUCTURE_END

_MDX_COMPONENT_BEGIN
//==========================================================================
//
// class : GridRenderer 
// Content : �O���b�h�����_���[
// details : �p���֎~/�f�t�H���g�̃V�F�[�_�[���ݒ肳��Ă��܂�
//
//==========================================================================
class GridRenderer final :
	public RendererManager
{
private:
	std::vector<structure::GridVertex> m_Vertex; // ���_�f�[�^
	int m_Size; // �T�C�Y�̋L�^
	structure::VertexShader m_VertexShader; // ���_�V�F�[�_�[
	structure::PixelShader m_PixelShader; // �s�N�Z���V�F�[�_�[
	structure::InputLayout m_InputLayout; // ���C�A�E�g
	structure::VertexBuffer m_VertexBuffer; // ���ʂ̃o�[�e�b�N�X�o�b�t�@
	static structure::VertexShader m_ShareVertexShader; // �f�t�H���g�̒��_�V�F�[�_�[
	static structure::PixelShader m_SharePixelShader; // �f�t�H���g�̃s�N�Z���V�F�[�_�[
	static structure::InputLayout m_ShareInputLayout; // ���ʂ̃��C�A�E�g
	static structure::ConstantBuffer m_ShareConstantBuffer; // �o�b�t�@
	static structure::MatrixBuffer m_ShareMatrixBuffer; // ���ʂ̃}�g���N�X�o�b�t�@
public:
	GridRenderer() = delete;
	GridRenderer(int size);
	virtual ~GridRenderer();

	/**
	@brief ���_�V�F�[�_�[��o�^���܂��B
	@param [in] shader : �V�F�[�_�[
	@details �f�t�H���g�V�F�[�_�[�͕ێ�����Ă��܂��B
	*/
	void SetVertexShader(const structure::VertexShader& shader) override;

	/**
	@brief �s�N�Z���V�F�[�_�[��o�^���܂��B
	@param [in] shader : �V�F�[�_�[
	@details �f�t�H���g�V�F�[�_�[�͕ێ�����Ă��܂��B
	*/
	void SetPixelShader(const structure::PixelShader& shader) override;

	/**
	@brief ���_���C�A�E�g��o�^���܂��B
	@param [in] layout : ���C�A�E�g
	@details �f�t�H���g���C�A�E�g�͕ێ�����Ă��܂��B
	*/
	void SetInputLayout(const structure::InputLayout& layout) override;

	/**
	@brief �f�t�H���g�V�F�[�_�[�𕜌����܂��B
	@details �w�肵���V�F�[�_�[�̓o�^�͉�������܂��B
	*/
	void RestoreDefaultShader() override;
private:
	/**
	@brief ������
	*/
	void Init() override;

	/**
	@brief �`��
	@param [in] view : �r���[�s��
	@param [in] projection : �v���W�F�N�V�����s��
	*/
	void Draw(const math::Matrix& view, const math::Matrix& projection) override;
};

_MDX_COMPONENT_END