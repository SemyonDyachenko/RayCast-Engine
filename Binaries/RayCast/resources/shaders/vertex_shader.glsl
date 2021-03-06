#version 450

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec2 vertex_texcoord;
layout (location = 3) in vec3 vertex_normal;

const int MAX_BONES = 100;
const int MAX_WEIGHTS = 4;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;
out vec3 vs_normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform mat4 bonesTransforms[MAX_BONES];
uniform bool animated;

void main()
{
	vs_position = vec4(ModelMatrix * vec4(normalize(vertex_position), 1.f)).xyz;
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);
	vs_normal = vec3(mat3(ModelMatrix) * normalize(vertex_normal));

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.f);
}