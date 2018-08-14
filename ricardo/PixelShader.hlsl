struct ps_input {
	float4 pos : SV_POSITION;
	float4 color : COLOR;
	float4 normal : NORMAL;
	float2 texcoord : TEXCOORD;
};

float4 ps_main(ps_input input) : SV_Target{
	return input.color;
}