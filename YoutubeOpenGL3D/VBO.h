#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
public:
	// reference ID of the Vertex Buffer Object
	GLuint ID;

	// generates a VBO and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size);

	// binds the VBO
	void bindVBO();
	// unbinds the VBO
	void unbindVBO();
	// deletes the VBO
	void deleteVBO();
};

#endif



