#version 450

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec2 vertex_texcoord;
layout (location = 2) in vec3 vertex_normal;
layout (location = 3) in ivec4 boneIds;
layout (location = 4) in vec4 weights;

const int MAX_BONES = 100;
const int MAX_WEIGHTS = 4;

out vec3 vs_position;
out vec2 vs_texcoord;
out vec3 vs_normal;

uniform int animated;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform mat4 bonesTransforms[MAX_BONES];


void main()
{
	if(animated == 1) {
	mat4 BoneTransform = bonesTransforms[boneIds[0]] * weights[0];
	BoneTransform += bonesTransforms[boneIds[1]] * weights[1];
    BoneTransform += bonesTransforms[boneIds[2]] * weights[2];
    BoneTransform += bonesTransforms[boneIds[3]] * weights[3];

	vec4 tPos = BoneTransform * vec4(vertex_position, 1.0);

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * tPos;

	} 

	else {
		vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
		vs_normal = mat3(ModelMatrix) * vertex_normal;
		gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vs_position, 1.f);
	} 

	

	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);
}