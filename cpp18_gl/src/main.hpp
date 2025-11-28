#ifndef __CPP_18_HPP__
#define __CPP_18_HPP__

#include <SDL3/SDL_main.h>
#include <cstdio>
#include "Game.hpp"

#endif /* !__CPP_18_HPP__ */

//  Spotlight (sharp-edges)
/* 
vec3 lightDir = normalize(light.position - fragPos);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outCutOff;
	float intensity = clamp((theta - light.outCutOff) / epsilon, 0.0f, 1.0f);

	if(theta > light.cutOff) 
	{
		vec3 ambient = 
			light.ambient * texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;
				
		//vec3 lightDir = normalize(-light.direction);
		//float diff = max(dot(normals, light.position), 0.0f);
		float diff = max(dot(normals, lightDir), 0.0f);
		vec3 diffuse = 
			diff * light.diffuse * texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;

		vec3 viewDir = normalize(viewPos - fragPos);
		vec3 reflectDir = reflect(-lightDir, normals);
		float spec =
			pow(max(dot(viewDir, reflectDir), 0.0f), mat.shininess);
		vec3 specular = spec * light.specular 
			* texture(mat.specular, vec2(texCoords.x, -texCoords.y)).rgb;

		vec3 emission = texture(mat.emission, vec2(texCoords.x, -texCoords.y)).rgb;

		float distance = length(light.position - fragPos);
		float attenuation = 1 / 
			(light.constant + light.linear * distance
			+ light.quadratic * (distance * distance));

		ambient  *= attenuation;
		diffuse  *= intensity * attenuation;
		specular *= intensity * attenuation;

		fragColor = vec4(ambient + diffuse + specular , 1.0f);
		//fragColor = vec4(light.ambient * texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb, 1.0f);
	}
	else {
		fragColor = vec4(light.ambient * 
			texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb, 1.0f);
	}	
*/

/*

	vec3 ambient = 
		light.ambient * texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;

	float distance = length(light.position - fragPos);
	float attenuation = 1 / 
		(light.constant + light.linear * distance
		+ light.quadratic * (distance * distance));
	
	vec3 lightDir = normalize(light.position - fragPos);
	//vec3 lightDir = normalize(-light.direction);
	//float diff = max(dot(normals, light.position), 0.0f);
	float diff = max(dot(normals, lightDir), 0.0f);
	vec3 diffuse = 
		diff * light.diffuse * texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)).rgb;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, normals);
	float spec =
		pow(max(dot(viewDir, reflectDir), 0.0f), mat.shininess);
	vec3 specular = spec * light.specular 
		* texture(mat.specular, vec2(texCoords.x, -texCoords.y)).rgb;

	vec3 emission = texture(mat.emission, vec2(texCoords.x, -texCoords.y)).rgb;


	float theta = dot(lightDir, normalize(-light.direction));

	if (theta > light.cutOff) {

	}
	else {
		color = vec4(ambient 
			* vec3(texture(mat.diffuse, vec2(texCoords.x, -texCoords.y)), 1.0f));
	}


	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;

	fragColor = vec4(ambient + diffuse + specular + emission, 1.0f);

*/