//==========================================================================
// コンスタントバッファ
//==========================================================================
cbuffer MatrixBuffer : register(b0)
{
    // row_major DirectXの向きベクトルを使います
    row_major matrix mat;
}

//==========================================================================
// 構造体
//==========================================================================
struct vsInput // 入力
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct psInput // 出力
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