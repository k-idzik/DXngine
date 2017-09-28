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
	DirectionalLight dirLight;
};

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

	float3 normalizedDirectionToLight = normalize(-dirLight.Direction); //Calculate the normalized firection to the light

	//Calculate the amount of light with N dot L
	//Clamp the result between 0 and 1
	float directionalLightAmount = saturate(dot(input.normal, normalizedDirectionToLight));

	return (dirLight.DiffuseColor * directionalLightAmount) + dirLight.AmbientColor;
}