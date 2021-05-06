#ifndef CFG_H
#define CFG_H

#include <glad/glad.h>

namespace cfg // config
{
	// window constants
	constexpr int width = 600;
	constexpr int height = 600;
	const char* name = {"YoutubeOpenGL"};

	// shader files
	const char* vertexShader = "default.vert";
	const char* fragmentShader = "default.frag";

	// color constants
	constexpr GLfloat clear[4] = {0.07f, 0.13f, 0.17f, 1.0f};
	//constexpr GLfloat fgcolors[4] = {0.8f, 0.3f, 0.02f, 1.0f};

	GLfloat vertices[] = {
		// coordinates		    // colors
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // lower-left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // upper-left
		 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // upper-right
		 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f, 	1.0f, 0.0f  // lower-right
	};

	// indices of each vertex
	GLuint indices[] = {
		0, 2, 1, // upper triangle 
		0, 3, 2  // lower trianlge
	};
}

#endif
