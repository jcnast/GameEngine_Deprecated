#version 450 core
// we are using version 4.3 and the core functionalities of the GLSL language

layout(location = 0) in vec3 vPosition;
// set the first input on location (index) 0; in_position is our attribute
layout(location = 1) in vec3 vNormal;
// set the second input on location (index) 1; in_color is our attribute
layout(location = 2) in vec2 vUV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP; // rotation, scaling, and transformation matrix (model view projection matrix)
uniform vec4 modColor; // color change passed in by CPU

out vec2 UV;
out vec4 Color;

void main()
{
	UV = vUV; // get texture coordinate
	Color = modColor; // get color modification from CPU

	gl_Position = MVP * vec4(vPosition, 1.0); // w is 1.0, also notice cast to vec4
}

// passing variables between stages is done using in/out variables. to send them correctly, the NAME and TYPE of the variable must be the same in BOTH shaders
// currently we have <out vec4 color> for the vertex shader that gets passed as <in vec4 color> for the fragment shader