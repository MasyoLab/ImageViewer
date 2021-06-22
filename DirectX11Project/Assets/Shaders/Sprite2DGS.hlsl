cbuffer MatrixBuffer : register(b0)
{
    column_major matrix matproj;
    column_major matrix matview;
    column_major matrix matworld;
}

struct gsInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

struct psInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL; // 面法線
};

[maxvertexcount(3)]
void main(triangle gsInput input[3], inout TriangleStream<psInput> tristream)
{
    psInput output = (psInput) 0;
	// 面法線の取得
    float3 edge1 = input[1].pos.xyz - input[0].pos.xyz;
    float3 edge2 = input[2].pos.xyz - input[0].pos.xyz;
    output.normal = normalize(cross(edge1, edge2));
    for (int i = 0; i < 3; ++i)
    {
        output.pos = mul(input[i].pos, matworld); // ローカル座標からワールド座標へ変換
        output.pos = mul(output.pos, matview); // ワールド座標からビュー座標(カメラ座標)へ変換
        output.pos = mul(output.pos, matproj); // ビュー座標からプロジェクション座標へ変換
        output.color = input[i].color; // 色情報は入力値をそのまま渡す
        output.tex = input[i].tex; // 色情報は入力値をそのまま渡す
        tristream.Append(output); // 三角形ポリゴン単位でデータを格納する
    }
    tristream.RestartStrip();
}
