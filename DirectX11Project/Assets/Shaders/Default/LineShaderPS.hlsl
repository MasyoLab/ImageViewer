//==========================================================================
// ç\ë¢ëÃ
//==========================================================================
struct psInput // ì¸óÕ
{
    float4 pos : SV_POSITION;
    float4 color : COL;
};

float4 main(in psInput input) : SV_TARGET
{
    return input.color;
}