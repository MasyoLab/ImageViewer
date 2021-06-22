//==========================================================================
// 2D用のデフォルトシェーダー [2DDefaultShaderVS.hlsl]
// author: MasyoLab
//==========================================================================

//==========================================================================
// コンスタントバッファ
//==========================================================================
cbuffer MatrixBuffer : register(b0)
{
    // row_major DirectXの向きベクトルを使います
    row_major matrix mat;
    float4 color;
}

//==========================================================================
// 構造体
//==========================================================================
struct vsInput // 入力
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

struct psInput // 出力
{
    float4 pos : SV_POSITION;
    float4 color : COL;
    float2 tex : TEXCOORD;
};

//==========================================================================
// 頂点シェーダ
//==========================================================================
psInput main(in vsInput input)
{
    psInput output = (psInput) 0;
    output.pos = mul(float4(input.pos, 1.0f), mat);
    output.color = input.color * color;
    output.tex = input.tex * float2(1, 1) + float2(0, 0);
    return output;
}