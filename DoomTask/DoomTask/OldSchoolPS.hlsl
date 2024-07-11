Texture2D renderTex;

SamplerState texSampler;

float quantize(float value, float levels)
{
    return floor(value * levels) / levels;
}

float4 main(float2 uv : Texcoord) : SV_TARGET
{
    return renderTex.Sample(texSampler, uv);
    //float pixelSize = 128.0f;
    //float2 pixelatedTexCoord = floor(uv * pixelSize) / pixelSize;
    //float3 color = renderTex.Sample(texSampler, pixelatedTexCoord).rgb;
    //
    //float3 ret;
    //ret.r = quantize(color.r, 32.0f);
    //ret.g = quantize(color.g, 32.0f);
    //ret.b = quantize(color.b, 32.0f);
    //
    //return float4(ret, 1.0f);
    
}