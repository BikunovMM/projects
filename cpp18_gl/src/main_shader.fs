#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;

	float shininess;
};
struct Light {
	vec3  position;
	vec3  direction;
	float cutOff;
	float outCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 emission;

	float constant;
	float linear;
	float quadratic;

	sampler2D tex;
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
	vec3 lightDir = normalize(light.position - fragPos);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outCutOff;
	float intensity = clamp((theta - light.outCutOff) / epsilon, 0.0f, 1.0f);

	vec3 ambient = 
		light.ambient * 
		texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;
			
	float diff = max(dot(normals, lightDir), 0.0f);
	vec3 diffuse = 
		diff * light.diffuse * 
		texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normals);
	float spec =
		pow(max(dot(viewDir, reflectDir), 0.0f), mat.shininess);
	vec3 specular = spec * light.specular * 
		texture(mat.specular, vec2(texCoords.x, -texCoords.y)).rgb;

	vec3 emission = light.emission
		* texture(mat.emission, vec2(texCoords.x, -texCoords.y)).rgb;

	float distance = length(light.position - fragPos);
	float attenuation = 1 / 
		(light.constant + light.linear * distance
		+ light.quadratic * (distance * distance));

	ambient  *= attenuation;
	diffuse  *= intensity * attenuation
		* texture(light.tex, vec2(texCoords.x, -texCoords.y)).rgb; 	
	specular *= intensity * attenuation;

	fragColor = vec4(ambient + diffuse + specular + emission, 1.0f);
}