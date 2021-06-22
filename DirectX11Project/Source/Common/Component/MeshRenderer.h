//==========================================================================
// ���b�V�������_���[ [MeshRenderer.h]
// author : MasyoLab
//==========================================================================
#pragma once
#include "RendererManager.h"

_MDX_COMPONENT_BEGIN

//==========================================================================
//
// class : MeshRenderer 
// Content : ���b�V�������_���[
// details : �p���֎~/�f�t�H���g�̃V�F�[�_�[���ݒ肳��Ă��܂�
//
//==========================================================================
class MeshRenderer final :
	public RendererManager
{
private:
	structure::VertexShader m_VertexShader; // ���_�V�F�[�_�[
	structure::PixelShader m_PixelShader; // �s�N�Z���V�F�[�_�[
	structure::InputLayout m_InputLayout; // ���C�A�E�g
	structure::SpriteMatrixBuffer m_MatrixBuffer; // �}�g���N�X�o�b�t�@
	static structure::VertexShader m_ShareVertexShader; // �f�t�H���g�̒��_�V�F�[�_�[
	static structure::PixelShader m_SharePixelShader; // �f�t�H���g�̃s�N�Z���V�F�[�_�[
	static structure::InputLayout m_ShareInputLayout; // ���ʂ̃��C�A�E�g
	static structure::VertexBuffer m_ShareVertexBuffer; // ���ʂ̃o�[�e�b�N�X�o�b�t�@
	static structure::ConstantBuffer m_ShareConstantBuffer; // �o�b�t�@
	static std::vector<structure::Vertex> m_ShareVertex; // ���ʂ̃f�[�^
	static D3D11_INPUT_ELEMENT_DESC m_ShareInputElementDesc[1]; // ���ʂ̃C���v�b�g���C�A�E�g
public:
	MeshRenderer();
	virtual ~MeshRenderer();

	/**
	@brief �F��o�^���܂��B
	@param [in] color : �F
	@details 0.0f�`1.0f�̊Ԃł��肢���܂��B
	*/
	void SetColor(const math::Vector4& color) override;

	/**
	@brief �F��o�^���܂��B
	@param [in] r : R�l
	@param [in] g : G�l
	@param [in] b : B�l
	@param [in] a : A�l
	@details 0.0f�`1.0f�̊Ԃł��肢���܂��B
	*/
	void SetColor(float r, float g, float b, float a) override;

	/**
	@brief �F���擾���܂��B
	@return �F
	*/
	const math::Vector4& GetColor() const override;

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