struct DSOut
{
    float3 normal : Normal;
    float3 worldPos : Position;
    float2 texCoord : TexCoord;
    float4 pos : SV_Position;
};

struct HSOut
{
    float3 normal : Normal;
    float3 worldPos : Position;
    float2 texCoord : TexCoord;
    float4 pos : SV_Position;
};

struct HSConstantDataOutput
{
    float TessFactor[3] : SV_TessFactor;
    float InsideTessFactor : SV_InsideTessFactor;
};

[domain("tri")]
DSOut main(HSConstantDataOutput input, float3 barycentricCoords : SV_DomainLocation, const OutputPatch<HSOut, 3> patch)
{
    DSOut output;
    
    output.pos = barycentricCoords.x * patch[0].pos +
                 barycentricCoords.y * patch[1].pos +
                 barycentricCoords.z * patch[2].pos;

    float3 normal = normalize(barycentricCoords.x * patch[0].normal +
                              barycentricCoords.y * patch[1].normal +
                              barycentricCoords.z * patch[2].normal);

    float3 worldPos = barycentricCoords.x * patch[0].worldPos +
                      barycentricCoords.y * patch[1].worldPos +
                      barycentricCoords.z * patch[2].worldPos;

    output.texCoord = barycentricCoords.x * patch[0].texCoord +
                      barycentricCoords.y * patch[1].texCoord +
                      barycentricCoords.z * patch[2].texCoord;

    // Example: Adjust vertex position based on LOD level (pseudo-code)
    output.normal = normal;
    output.worldPos = worldPos;
    
    return output;
}