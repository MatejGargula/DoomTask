Texture2D texDiffuse : register(t0);
Texture2D texSpecular : register(t1);

SamplerState TexSampler;

cbuffer CCameraPos : register(b0)
{
    float3 viewPos;
}

cbuffer CLightBuf : register(b1)
{
    float3 lightPosition;
    float3 lightAmbient;
    float3 lightDiffuse;
    float3 lightSpecular;
    float3 att;
    float pad;
};

cbuffer CMaterial : register(b2)
{
    float3 ambientMat;
    bool useDiffTex;
    float3 diffuseMat;
    bool useSpecTex;
    float4 specMat;
};

float4 main(float3 normal : Normal, float3 worldPostion : Position, float2 texCoord : TexCoord) : SV_TARGET
{
    float3 specularMat = (float3) specMat;
    float shininess = specMat.a;
    
    float3 diffuseMaterialColor = diffuseMat;
    if (useDiffTex)
    {
        //return texDiffuse.Sample(TexSampler, texCoord);
        diffuseMaterialColor = texDiffuse.Sample(TexSampler, texCoord).bgr;
    }
    
	// ambient
    float3 ambientColor = lightAmbient * diffuseMaterialColor;
  	
    // diffuse 
    float3 norm = normalize(normal);
    float3 lightDir = normalize(lightPosition - worldPostion);
    float diff = max(dot(norm, lightDir), 0.0);
    float3 diffuseColor = lightDiffuse * diff * diffuseMaterialColor;
    
    // specular
    float3 viewDir = normalize(viewPos - worldPostion);
    float3 reflectDir = reflect(-lightDir, norm);
    float spec = 0.0;
    if (diff > 0.0) // Only calculate specular if the fragment is facing the light
    {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    }
    float3 specularColor = lightSpecular * spec * specularMat;
    
    // attenuation
    float dist = distance(lightPosition, worldPostion);
    float attenuation = 1.0 / (att.x + att.y * dist + att.z * (dist * dist));
    
    //ambientColor *= attenuation;
    //diffuseColor *= attenuation;
    //specularColor *= attenuation;
        
    float3 result = saturate(ambientColor + diffuseColor + specularColor);
    
    return float4(result, 1.0);
}