//==========================================================================
// �R���X�^���g�o�b�t�@
//==========================================================================
cbuffer MatrixBuffer : register(b0)
{
    // row_major DirectX�̌����x�N�g�����g���܂�
    row_major matrix mat;
}

//==========================================================================
// �\����
//==========================================================================
struct vsInput // ����
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct psInput // �o��
{
    float4 pos : SV_POSITION;
    float4 color : COL;
};

psInput main(in vsInput input)
{
    psInput output = (psInput) 0;
    output.pos = mul(float4(input.pos, 1.0f), mat);
    output.color = input.color;
    return output;
}