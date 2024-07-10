Texture2D texDiffuse : register(t0);
Texture2D texSpecular : register(t1);

SamplerState TexSampler;

struct PSOut
{
    float4 diffuse : SV_Target0;
    float4 position : SV_Target1;
    float4 normal : SV_Target2;
    float4 specular : SV_Target3;
};

cbuffer CMaterial : register(b2)
{
    float3 ambientMat;
    bool useDiffTex;
    float3 diffuseMat;
    bool useSpecTex;
    float4 specMat;
};

PSOut main(float3 normal : Normal, float3 worldPostion : Position, float2 texCoord : TexCoord)
{
    float4 diffuseMaterialColor = float4(diffuseMat, 1.0f);
    if (useDiffTex)
    {
        diffuseMaterialColor = texDiffuse.Sample(TexSampler, texCoord).bgra;
    }
    
    float4 specularMaterialColor = specMat;
    if (useSpecTex)
    {
        specularMaterialColor = float4(texSpecular.Sample(TexSampler, texCoord).bgr, specMat.a);
    }
    
    PSOut ret;
    
    // TODO: Later add also specular output
    ret.diffuse = diffuseMaterialColor;
    ret.normal = float4(normal,1.0f);
    ret.position = float4(worldPostion, 1.0f);
    ret.specular = specularMaterialColor;
    
	return ret;
}