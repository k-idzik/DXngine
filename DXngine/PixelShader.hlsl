///Kevin Idzik, modified code from Chris Cascioli
///Pixel shader

// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position	: SV_POSITION; //XYZW position (System Value Position)
	float2 uv : TEXCOORD; //UVs
	float3 normal : NORMAL; //Normal to the triangle
};

//Defines a directional light
struct DirectionalLight
{
	float4 AmbientColor; //Ambient lighting, should be subtle
	float4 DiffuseColor; //Diffuse lighting, should be bright
	float3 Direction; //Light direction, will be normalized in the shader
};

//Constant Buffer defines a buffer of individual variables to hold data from C++
//Non-pipeline variables that get their values from C++ must be defined in a Constant Buffer
//Constant Buffers are bound to a register
cbuffer lightingData : register(b0)
{
	DirectionalLight dirLight0;
	DirectionalLight dirLight1;
};

//Variables to be set through C++
Texture2D diffuseTexture : register(t0);
SamplerState basicSampler : register(s0);

//Calculate the directional light
float4 calculateDirectionalLight(DirectionalLight dL, float3 normies)
{
	float3 normalizedDirectionToLight = normalize(-dL.Direction); //Calculate the normalized firection to the light

	//Calculate the amount of light with N dot L
	//Clamp the result between 0 and 1
	float directionalLightAmount = saturate(dot(normies, normalizedDirectionToLight));

	//Return the calculated directional light
	return (dL.DiffuseColor * directionalLightAmount) + dL.AmbientColor;
}

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal); //Normalize the normal, it may be larger due to interpolation

	//Calculate directional lights
	float4 calcedDirLight0 = calculateDirectionalLight(dirLight0, input.normal);
	float4 calcedDirLight1 = calculateDirectionalLight(dirLight1, input.normal);

	//Sample the texture and use the resulting color in the lighting equation
	float4 surfaceColor = diffuseTexture.Sample(basicSampler, input.uv);

	return (calcedDirLight0 + calcedDirLight1) * surfaceColor;
}