cbuffer CBuf
{
    matrix transform;
};

struct VSOut
{
    float3 normal : Normal;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : Position, float3 normal : Normal)
{
    VSOut vso;
    vso.pos = mul(float4(pos, 1.0f), transform);
    vso.normal = normal;
    return vso;
}