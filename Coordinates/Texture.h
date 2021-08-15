#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Shader.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;

	// generates an OpenGL texture object
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// assigns a texture unit to a texture
	void texUnit(Shader* shader, const char* uniform, GLuint unit);
	// binds a texture
	void bindTexture();
	// unibinds a texture
	void unbindTexture();
	// deletes a texture
	void deleteTexture();
};

#endif


