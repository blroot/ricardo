cbuffer transforms : register(b0) {
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
};

struct ps_input {
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

ps_input vs_main(float4 pos : POSITION, float4 Color : COLOR, float4 normal : NORMAL, float2 texcoord : TEXCOORD) {
	ps_input p;

	pos = mul(pos, World);
	pos = mul(pos, View);
	pos = mul(pos, Projection);
	p.pos = pos;
	p.color = Color;
	return p;
}