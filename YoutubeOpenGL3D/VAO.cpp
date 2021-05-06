#include "VAO.h"

VAO::VAO()
{
	// generate the vertex array
	glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizei stride, void* offset)
{
	VBO.bindVBO();
	// define an array of generic vertex attribute data
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.unbindVBO();
}

void VAO::bindVAO()
{
	// tell opengl to use this VAO
	glBindVertexArray(ID);
}

void VAO::unbindVAO()
{
	glBindVertexArray(0);
}

void VAO::deleteVAO()
{
	glDeleteVertexArrays(1, &ID);
}