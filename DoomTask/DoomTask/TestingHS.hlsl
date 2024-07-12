cbuffer ConstantBuffer : register(b0)
{
    float3 CameraPosition; // Camera position in world space
    float pad1;
    float TessellationRange; // Max distance for tessellation factor adjustment
    float MinTessFactor; // Minimum tessellation factor
    float MaxTessFactor; // Maximum tessellation factor
    float pad2;
};

struct VSOut
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

struct HS_CONSTANT_DATA_OUTPUT
{
    float EdgeTessFactor[3] : SV_TessFactor;
    float InsideTessFactor : SV_InsideTessFactor;
};

#define NUM_CONTROL_POINTS 3

HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<VSOut, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT Output;
    
     // Calculate the center position of the patch
    float3 patchCenter = (ip[0].worldPos + ip[1].worldPos + ip[2].worldPos) / 3.0f;

    // Calculate the distance from the patch center to the camera
    float distanceToCamera = distance(patchCenter, CameraPosition);

    // Adjust tessellation factors based on distance
    
    
    float TessellationFactor = lerp(MaxTessFactor, MinTessFactor, saturate(distanceToCamera / TessellationRange));;

    Output.EdgeTessFactor[0] = TessellationFactor;
	Output.EdgeTessFactor[1] = TessellationFactor;
	Output.EdgeTessFactor[2] = TessellationFactor;
    Output.InsideTessFactor = TessellationFactor;

    return Output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CalcHSPatchConstants")]
HSOut main(
	InputPatch<VSOut, NUM_CONTROL_POINTS> ip,
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID)
{
    HSOut Output;

    Output.worldPos = ip[i].worldPos;
    Output.normal = ip[i].normal;
    Output.texCoord = ip[i].texCoord;
    Output.pos = ip[i].pos;

    return Output;
}
