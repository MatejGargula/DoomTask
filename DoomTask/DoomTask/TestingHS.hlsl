float TessellationFactor = 4.0f;

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

    Output.EdgeTessFactor[0] =
		Output.EdgeTessFactor[1] =
		Output.EdgeTessFactor[2] =
		Output.InsideTessFactor = 15;

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
