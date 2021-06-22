SamplerState samLinear : register(s0);

Texture2D Diffuse : register(t0);

struct psInput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
    float3 normal : NORMAL; // ñ ñ@ê¸
};

float4 main(psInput input) : SV_TARGET
{
    float4 result = 0;
    result = Diffuse.Sample(samLinear, input.tex) * float4(input.color.xyz, input.color.w);
    return result;
}
