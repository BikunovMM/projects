#version 330 core

#define MIX_COEF 0.5f

in vec2 texCoords;
out vec4 fragColor;

uniform vec3 lightColor;
uniform sampler2D tex;

void main()
{
	fragColor = mix(texture(tex, 
		vec2(texCoords.x, -texCoords.y)),
		vec4(lightColor, 1.0f), MIX_COEF);
}
