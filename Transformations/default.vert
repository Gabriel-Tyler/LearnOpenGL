#version 330 core

// positions/coordinates
layout (location = 0) in vec3 aPos;

// colors
layout (location = 1) in vec3 aColor;

// texture coordinate
layout (location = 2) in vec2 aTex;

// outputs the color for the fragment shader
out vec3 color;

// outputs the texture coordinate to the fragment shaders
out vec2 texCoord;


// controls the scale of the vertices
uniform float scale;

// transformation matrix
uniform mat4 transform;


void main()
{
	// outputs the positions/coordinates of all vertices
	gl_Position = transform * vec4(aPos.xyz, 1.0f);

	// assigns the colors from the vertex data to "color"
	color = aColor;

	// assigns the texture coordinate from the vertex data to "texCoord"
	texCoord = aTex;
}