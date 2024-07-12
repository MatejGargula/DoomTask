Texture2D texDiffuse : register(t0); // Diffuse color texture
Texture2D texPosition : register(t1); // world position texture
Texture2D texNormal : register(t2); // normal vectors texture
Texture2D texSpecular : register(t3); // specular component texture

SamplerState texSampler;

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
    LPointLight lights[256];
    int nLights;
    float pad[3];
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
 
    // combine results
    float3 ambient = light.lightAmbient * matDiffuse;
    float3 diffuse = light.lightDiffuse * diff * matDiffuse;
    float3 specular = light.lightSpecular * spec * matSpecular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}

float4 main(float2 uv : Texcoord) : SV_TARGET
{
    float3 diffuseMaterialColor = texDiffuse.Sample(texSampler, uv).rgb;
    float3 pixelPosition = texPosition.Sample(texSampler, uv).rgb;
    float3 normal = texNormal.Sample(texSampler, uv);
    
    float4 specularMat = texSpecular.Sample(texSampler, uv);    
    float shininess = specularMat.a;
   
    float3 viewDir = normalize(viewPos - pixelPosition);
    float3 norm = normalize(normal);
       
    float3 result = float3(0.0f, 0.0f, 0.0f);
    
    for (int i = 0; i < nLights; i++)
    {
        result += CalcPointLight(lights[i], norm, pixelPosition, viewDir, diffuseMaterialColor, specularMat.rgb, shininess);
    }
    
    result = saturate(result);
    
    return float4(result, 1.0);

}
