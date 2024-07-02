
const static float3 LightPos = { 0.0f, 0.0f, 0.0f };
const static float3 LightColor = { 1.0f, 1.0f, 1.0f };

const static float3 ObjectColor = { 1.0f, 0.0f, 0.4f };

float4 main(float3 normal : Normal, float3 worldPostion: Position) : SV_TARGET
{
	// ambient
    float ambientStrength = 0.1;
    float3 ambient = ambientStrength * LightColor;
    
     // diffuse 
    float3 norm = normalize(normal);
    float3 lightDir = normalize(LightPos - worldPostion);
    float diff = max(dot(norm, lightDir), 0.0);
    float3 diffuse = diff * LightColor;
    
    // specular
    float specularStrength = 0.5;
    float3 viewDir = normalize(-worldPostion); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    float3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float3 specular = specularStrength * spec * LightColor;
    
    float3 result = (ambient + diffuse + specular) * ObjectColor;
    return float4(result, 1.0);
}