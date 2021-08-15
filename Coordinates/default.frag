#version 330 core


// texture coordinate input from the vertex shader
in vec2 texCoord;


// outputs the colors in RGBA
out vec4 FragColor;


// gets the texture unit from the main function
uniform sampler2D tex0;


void main()
{
	// assigns the texture and colors to "FragColor"
	FragColor = texture(tex0, texCoord);
}