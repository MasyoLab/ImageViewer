// 頂点データを描画するための処理を記述する

// 定数バッファ(constant buffer). スロット番号0にバッファを割り当てる.
cbuffer MatrixBuffer : register(b0)
{
	// 列優先(column_major)として行列を定義する
    column_major matrix matproj;
    column_major matrix matview;
    column_major matrix matworld;
};

// プログラムから受け取る頂点データの定義
struct vsInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

// ジオメトリシェーダーに渡すデータの定義
struct gsInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

// エントリーポイント
// 返り値はGS_INPUT
gsInput main(vsInput input)
{
    gsInput output = (gsInput) 0;
    output.pos = float4(input.pos, 1); // w座標値を追加
    output.color = input.color;
    output.tex = input.tex;
    return output;
}
