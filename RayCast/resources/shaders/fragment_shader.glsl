#version 450

struct Material {
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	float shininess;
	vec3 color;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	vec3 lightColor;

	float constant;
	float linear;
	float quadratic;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;	

	vec3 color;

};

uniform Material material;
uniform Light light;
uniform DirectionalLight dirLight;

in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;

uniform vec3 cameraPos;
uniform bool textured;
uniform bool hasDirecionalLight;
uniform bool hasPointLight;

uniform vec3 u_Color;

out vec4 fs_color;

vec3 CalcDirLight(DirectionalLight light,vec3 normal,vec3 viewDir) {

vec3 lightDir = normalize(-light.direction);

float diff = max(dot(normal,lightDir),0.0);

vec3 reflectDir = reflect(-lightDir,normal);

float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture,vs_texcoord));
vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture,vs_texcoord));
vec3 specular = light.specular * spec * vec3(texture(material.specularTexture,vs_texcoord));


return (ambient+diffuse+specular);
}


vec3 CalcPointLight(Light light,vec3 normal,vec3 vsPos,vec3 viewDir) {
vec3 lightDir = normalize(light.position - vsPos);

float diff = max(dot(normal,lightDir),0.0);

vec3 reflectDir = reflect(-lightDir,normal);
float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);

float distance = length(light.position - vsPos);
float attenuaion = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance*distance));


vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture,vs_texcoord));
vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseTexture,vs_texcoord));
vec3 specular = light.specular * spec * vec3(texture(material.specularTexture,vs_texcoord));


ambient *= attenuaion;
diffuse *= attenuaion;
specular *= attenuaion;


return (ambient+diffuse+specular);
}

void main()
{
	//ambient
	//vec3 ambientLight = light.ambient * texture(material.diffuseTexture,vs_texcoord).rgb;

		
	//diffuse
	vec3 norm = normalize(vs_normal);
	vec3 viewDir = normalize(cameraPos - vs_position);
	//vec3 lightDirection = normalize(light.position - vs_position);
//	float diff = max(dot(norm, lightDirection), 0.0);	
	//vec3 diffuse = light.diffuse * diff * texture(material.diffuseTexture,vs_texcoord).rgb;		

	//specular
	//vec3 ViewDirection = normalize(cameraPos - vs_position);
//	vec3 reflectDir = reflect(-lightDirection,norm);
//	float spec = pow(max(dot(ViewDirection,reflectDir),0.0),material.shininess);
//vec3 specular = light.specular * spec * texture(material.specularTexture,vs_texcoord).rgb;

	//float distance = length(light.position - vs_position);
	//float attenuation = 1.0 / (light.constant  + light.linear * distance + light.quadratic * (distance*distance));

	//ambientLight *= attenuation;
	//diffuse *= attenuation;
	//specular *= attenuation;


	//vec3 result = ambientLight + diffuse + specular;

	vec3 result = CalcDirLight(dirLight,norm,viewDir);
	
	
	if(hasPointLight) {
		 result = CalcPointLight(light,norm,vs_position,viewDir);
	}

		
	if(textured) {
		fs_color = vec4(result,1.0) * vec4(u_Color,1.0);
	}
	else { fs_color = vec4(u_Color,1.0); } 
}