a#version 330


uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;

in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    fs_color = vec4(result, 1.0);
	//fs_color = texture(texture1,vs_texcoord);
	//fs_color = vec4(0.9, 0.9, 0.9,1.0);
}