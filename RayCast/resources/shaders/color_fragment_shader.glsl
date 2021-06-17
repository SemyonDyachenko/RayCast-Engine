#version 450


in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;

uniform vec3 u_Color;

out vec4 fs_color;

void main()
{
	
	fs_color = vec4(u_Color,1.f);
}