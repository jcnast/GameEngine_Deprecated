#version 450 core

layout(location = 0) out vec4 fColor;

in vec2 UV;
in vec4 Color;

// Values that stay constant for the whole mesh.
uniform sampler2D texture0; // rotation, scaling, and transformation matrix (model view projection matrix)

void main()
{
	fColor = texture(texture0, UV) * Color; // color times texture color
}