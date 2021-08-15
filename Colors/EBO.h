#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO
{
public:
	// reference ID of the Element Buffer Object
	GLuint ID;

	// generates an EBO and links it to indices
	EBO(GLuint* indices, GLsizeiptr size);
	
	// binds the EBO
	void bindEBO();
	// unbinds the EBO
	void unbindEBO();
	// deletes the EBO
	void deleteEBO();
};

#endif

