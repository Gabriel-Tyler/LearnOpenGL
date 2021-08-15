#version 330 core

// positions/coordinates
layout (location = 0) in vec3 aPos;

// texture coordinate
layout (location = 1) in vec2 aTex;


// outputs the texture coordinate to the fragment shaders
out vec2 texCoord;


// transformation matrix uniforms
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	// outputs the positions/coordinates of all vertices
	gl_Position = projection * view * model * vec4(aPos, 1.0f);

	// assigns the texture coordinate from the vertex data to "texCoord"
	texCoord = aTex;
}