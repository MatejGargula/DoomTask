cbuffer CBuf
{
    matrix transform;
};

float4 main(float3 pos : Position) : SV_Position
{
    return mul(float4(pos, 1.0f), transform);
}

//struct VSOut
//{
//    float3 color : Color;
//    float4 pos : SV_Position;
//};

//VSOut main(float2 pos : Position, float3 color : Color) 
//{
//    VSOut vso;
//    vso.color = color;
//    vso.pos = float4(pos.x, pos.y, 0.0f, 1.0f);
    
//    return vso;

//}
