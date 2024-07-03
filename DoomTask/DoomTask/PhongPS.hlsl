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

//TODO: Move to Constant buffer
// Material 
float3 diffuseMat = float3(0.4f, 0.2f, 0.09f);
float3 specularMat = float3(0.8f, 0.8f, 0.8f);
float shininess = 1;

float4 main(float3 normal : Normal, float3 worldPostion : Position) : SV_TARGET
{
	// ambient
    float3 ambientColor = lightAmbient * diffuseMat;
  	
    // diffuse 
    float3 norm = normalize(normal);
    float3 lightDir = normalize(lightPosition - worldPostion);
    float diff = max(dot(norm, lightDir), 0.0);
    float3 diffuseColor = lightDiffuse * diff * diffuseMat;
    
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

    ambientColor *= attenuation;
    diffuseColor *= attenuation;
    specularColor *= attenuation;
        
    float3 result = saturate(ambientColor + diffuseColor + specularColor);
    return float4(result, 1.0);
}