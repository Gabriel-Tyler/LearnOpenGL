#version 330 core

// outputs the colors in RGBA
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	// assigns colors to "FragColor"
	FragColor = vec4(objectColor * lightColor, 1.0f);
}