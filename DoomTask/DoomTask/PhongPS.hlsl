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
    float3 specularMat = specMat.rgb;
    float shininess = specMat.a;
    
    float3 viewDir = normalize(viewPos - worldPostion);
    float3 norm = normalize(normal);
    
    float3 diffuseMaterialColor = diffuseMat;
    if (useDiffTex)
    {
        //return texDiffuse.Sample(TexSampler, texCoord);
        diffuseMaterialColor = texDiffuse.Sample(TexSampler, texCoord).bgr;
    }
    
    //float3 ambientColor = lights[0].lightAmbient * diffuseMaterialColor;
    //float3 finalColor = ambientColor;
    
    float3 result = float3(0.0f,0.0f,0.0f);
    
    for (int i = 0; i < nLights; i++)
    {
        result += CalcPointLight(lights[i], norm, worldPostion, viewDir, diffuseMaterialColor, specularMat, shininess);
    }
        // ambient
        
    
    //// diffuse 
    //    float3 lightDir = normalize(lights[i].lightPosition - worldPostion);
    //    float diff = max(dot(norm, lightDir), 0.0);
    //    float3 diffuseColor = lights[i].lightDiffuse * diff * diffuseMaterialColor;
    //
    //// specular
    //    float3 reflectDir = reflect(-lightDir, norm);
    //    float spec = 0.0;
    //    if (diff > 0.0) // Only calculate specular if the fragment is facing the light
    //    {
    //        spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    //    }
    //    float3 specularColor = lights[i].lightSpecular * spec * specularMat;
    //
    //// attenuation
    //    float dist = distance(lights[i].lightPosition, worldPostion);
    //    float attenuation = 1.0 / (lights[i].att.x + lights[i].att.y * dist + lights[i].att.z * (dist * dist));
    //
    //    //ambientColor *= attenuation;
    //    //diffuseColor *= attenuation;
    //    //specularColor *= attenuation;
    //    
    //    finalColor = saturate( diffuseColor + specularColor);
    //}
    result = saturate(result);
    
    return float4(result, 1.0);
}