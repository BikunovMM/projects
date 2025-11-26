#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 texCoords;
in vec3 normals;
in vec3 fragPos;

out vec4 fragColor;

uniform vec3 viewPos;

uniform Material mat;
uniform Light light;

void main()
{
	vec3 ambient = light.ambient * texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;
	
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(normals, light.position), 0.0f);
	vec3 diffuse = diff * light.diffuse * texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normals);
	float spec =
		pow(max(dot(viewDir, reflectDir), 0.0f), mat.shininess);
	vec3 specular = spec * light.specular 
		* texture(mat.specular, vec2(texCoords.x, -texCoords.y)).rgb;

	vec3 emission = texture(mat.emission, vec2(texCoords.x, -texCoords.y)).rgb;

	fragColor = vec4(ambient + diffuse + specular + emission, 1.0f);
}