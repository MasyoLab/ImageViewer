//==========================================================================
// 2D�p�̃f�t�H���g�V�F�[�_�[ [2DDefaultShaderVS.hlsl]
// author: MasyoLab
//==========================================================================

//==========================================================================
// �R���X�^���g�o�b�t�@
//==========================================================================
cbuffer MatrixBuffer : register(b0)
{
    // row_major DirectX�̌����x�N�g�����g���܂�
    row_major matrix mat;
    float4 color;
}

//==========================================================================
// �\����
//==========================================================================
struct vsInput // ����
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

struct psInput // �o��
{
    float4 pos : SV_POSITION;
    float4 color : COL;
    float2 tex : TEXCOORD;
};

//==========================================================================
// ���_�V�F�[�_
//==========================================================================
psInput main(in vsInput input)
{
    psInput output = (psInput) 0;
    output.pos = mul(float4(input.pos, 1.0f), mat);
    output.color = input.color * color;
    output.tex = input.tex * float2(1, 1) + float2(0, 0);
    return output;
}