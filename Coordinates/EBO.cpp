#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	// generate the EBO
	glGenBuffers(1, &ID);
	// bind the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	// create and intitialize the buffer object's data store
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER, 
		size,
		indices, 
		GL_STATIC_DRAW
	);
}

void EBO::bindEBO()
{
	// bind the element buffer object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbindEBO()
{
	// unbind EBO after unbinding EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::deleteEBO()
{
	// delete the EBO
	glDeleteBuffers(1, &ID);
}