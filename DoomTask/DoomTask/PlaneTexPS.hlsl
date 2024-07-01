
Texture2D tex;
SamplerState TexSampler;

float4 main(float2 texCoords : TexCoord) : SV_Target
{
    return tex.Sample(TexSampler, texCoords);
}