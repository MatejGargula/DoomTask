
struct VSOut
{
    float2 uv : Texcoord;
    float4 pos : SV_Position;
};

VSOut main( float2 pos : POSITION )
{
    VSOut ret;
    ret.pos = float4(pos, 0.0f, 1.0f);
    ret.uv = float2((pos.x + 1) / 2.0f, -(pos.y - 1) / 2.0f);
	return ret;
}