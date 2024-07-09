cbuffer CBuf : register(b0)
{
    matrix model;
    matrix modelView;
    matrix modelViewProjection;
};

struct VS_INPUT
{
    float3 position : Position;
    float3 normal : Normal;
    float2 texCoord : TexCoord;
};

struct VSOut
{
    float3 normal : Normal;
    float3 worldPos : Position;
    float2 texCoord : TexCoord;
    float4 pos : SV_Position;
};

VSOut main(VS_INPUT input)
{
    VSOut vso;
    vso.worldPos = (float3) mul(float4(input.position, 1.0f), model);
    vso.normal = normalize(mul(input.normal, (float3x3) model)); // No translation for normal vectors 
    vso.pos = mul(float4(input.position, 1.0f), modelViewProjection);
    vso.texCoord = input.texCoord;
    return vso;
}