
Texture2D tex : register(t0);
SamplerState TexSampler : register(s0);

float4 main(float2 texCoords : TexCoord) : SV_Target
{
    return tex.Sample(TexSampler, texCoords);
}