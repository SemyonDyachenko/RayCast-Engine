#version 450

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	
};

uniform Material material;

in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;

uniform vec3 cameraPos;
uniform vec3 lightPos0;
uniform bool textured;

out vec4 fs_color;

void main()
{
	vec3 ambientLight = material.ambient;

	vec3 posToLightDirVec = normalize(vs_position - lightPos0);
	float diffuse = clamp(dot(posToLightDirVec, normalize(vs_normal)), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	vec3 lightToPosDirVec = normalize(lightPos0 - vs_position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVec,normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - cameraPos);
	float specular = pow(max(dot(posToViewDirVec,reflectDirVec),0),1);
	vec3 specularResult = material.specular * specular;
    
	if(textured) {
	fs_color = texture(material.diffuseTexture,vs_texcoord)  * (vec4(ambientLight,1.f) + vec4(diffuseFinal,1.f) + vec4(specularResult,1.f));
	}
	else { fs_color = vec4(0.7f, 0.2f, 0.4f,1.f); } 
}