//==========================================================================
// 2D用のデフォルトシェーダー [2DDefaultShaderPS.hlsl]
// author: MasyoLab
//==========================================================================
SamplerState samLinear : register(s0); // サンプラー
Texture2D texDiffuse : register(t0); // テクスチャ

//==========================================================================
// 構造体
//==========================================================================
struct psInput // 入力
{
    float4 pos : SV_POSITION;
    float4 color : COL;
    float2 tex : TEXCOORD;
};

//==========================================================================
// ピクセルシェーダ
//==========================================================================
float4 main(in psInput input) : SV_TARGET
{
    float4 result = 0;
    result = texDiffuse.Sample(samLinear, input.tex) * input.color;
    return result;
}