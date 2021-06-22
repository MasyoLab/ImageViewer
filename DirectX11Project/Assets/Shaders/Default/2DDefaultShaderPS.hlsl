//==========================================================================
// 2D�p�̃f�t�H���g�V�F�[�_�[ [2DDefaultShaderPS.hlsl]
// author: MasyoLab
//==========================================================================
SamplerState samLinear : register(s0); // �T���v���[
Texture2D texDiffuse : register(t0); // �e�N�X�`��

//==========================================================================
// �\����
//==========================================================================
struct psInput // ����
{
    float4 pos : SV_POSITION;
    float4 color : COL;
    float2 tex : TEXCOORD;
};

//==========================================================================
// �s�N�Z���V�F�[�_
//==========================================================================
float4 main(in psInput input) : SV_TARGET
{
    float4 result = 0;
    result = texDiffuse.Sample(samLinear, input.tex) * input.color;
    return result;
}