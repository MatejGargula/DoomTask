Texture2D texDiffuse : register(t0);
Texture2D texSpecular : register(t1);

SamplerState TexSampler;

cbuffer CCameraPos : register(b0)
{
    float3 viewPos;
}

struct LPointLight
{
    float3 lightPosition;
    float3 lightAmbient;
    float3 lightDiffuse;
    float3 lightSpecular;
    float3 att;
    float pad;
};

cbuffer CLightBuf : register(b1)
{
    LPointLight lights[128];
    int nLights;
    float pad[3];
};
//cbuffer CLightBuf : register(b1)
//{
//    float3 lightPosition;
//    float3 lightAmbient;
//    float3 lightDiffuse;
//    float3 lightSpecular;
//    float3 att;
//    float pad;
//};

cbuffer CMaterial : register(b2)
{
    float3 ambientMat;
    bool useDiffTex;
    float3 diffuseMat;
    bool useSpecTex;
    float4 specMat;
};

// calculates the color when using a point light.
float3 CalcPointLight(LPointLight light, float3 normal, float3 pixelPos, float3 viewDir, float3 matDiffuse, float3 matSpecular, float shininess)
{
    float3 lightDir = normalize(light.lightPosition - pixelPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    float3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    // attenuation
    float distance = length(light.lightPosition - pixelPos);
    float attenuation = 1.0f / (light.att[0] + light.att[1] * distance + light.att[2] * (distance * distance));
    //attenuation *= 20.0f;
    // combine results
    float3 ambient = light.lightAmbient * matDiffuse;
    float3 diffuse = light.lightDiffuse * diff * matDiffuse;
    float3 specular = light.lightSpecular * spec * matSpecular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

float4 main(float3 normal : Normal, float3 worldPostion : Position, float2 texCoord : TexCoord) : SV_TARGET
{
    float3 viewDir = normalize(viewPos - worldPostion);
    float3 norm = normalize(normal);
    
    float3 diffuseMaterialColor = diffuseMat;
    if (useDiffTex)
    {
        diffuseMaterialColor = texDiffuse.Sample(TexSampler, texCoord).bgr;
    }
    
    float3 specularMaterialColor = specMat.rgb;
    float shininess = specMat.a;
    
    if (useSpecTex)
    {
        specularMaterialColor = texSpecular.Sample(TexSampler, texCoord).bgr;
    }
    
    float3 result = float3(0.0f,0.0f,0.0f);
    
    for (int i = 0; i < nLights; i++)
    {
        result += CalcPointLight(lights[i], norm, worldPostion, viewDir, diffuseMaterialColor, specularMaterialColor, shininess);
    }
    
    result = saturate(result);
    
    return float4(result, 1.0);
}