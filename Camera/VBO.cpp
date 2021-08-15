#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	// generate the VBO
	glGenBuffers(1, &ID);
	// bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	// create and intitialize the buffer object's data store
	glBufferData(
		GL_ARRAY_BUFFER, 
		size, 
		vertices, 
		GL_STATIC_DRAW
	);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::bindVBO()
{
	// bind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbindVBO()
{
	// unbind the vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO()
{
	// delete the vertex buffer object
	glDeleteBuffers(1, &ID);
}