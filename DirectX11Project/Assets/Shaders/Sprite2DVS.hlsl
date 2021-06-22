// ���_�f�[�^��`�悷�邽�߂̏������L�q����

// �萔�o�b�t�@(constant buffer). �X���b�g�ԍ�0�Ƀo�b�t�@�����蓖�Ă�.
cbuffer MatrixBuffer : register(b0)
{
	// ��D��(column_major)�Ƃ��čs����`����
    column_major matrix matproj;
    column_major matrix matview;
    column_major matrix matworld;
};

// �v���O��������󂯎�钸�_�f�[�^�̒�`
struct vsInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

// �W�I���g���V�F�[�_�[�ɓn���f�[�^�̒�`
struct gsInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

// �G���g���[�|�C���g
// �Ԃ�l��GS_INPUT
gsInput main(vsInput input)
{
    gsInput output = (gsInput) 0;
    output.pos = float4(input.pos, 1); // w���W�l��ǉ�
    output.color = input.color;
    output.tex = input.tex;
    return output;
}
