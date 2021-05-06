#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>

#include "VBO.h"

class VAO
{
public:
	// reference ID of a Vertex Array Object
	GLuint ID;

	// generates a VBO ID
	VAO();

	// links a VBO attribute such as position or color to the VAO
	void linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset);
	// binds the VAO
	void bindVAO();
	// unbinds the VAO
	void unbindVAO();
	// deletes the VAO
	void deleteVAO();
};

#endif