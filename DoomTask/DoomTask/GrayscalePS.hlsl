Texture2D renderTex;

SamplerState texSampler;

float4 main(float2 uv : Texcoord) : SV_TARGET
{
    float3 color = renderTex.Sample(texSampler, uv).rgb;
    float gray = (color.r + color.g + color.b) / 3.0f;
    return float4(gray, gray, gray, 1.0f);
}