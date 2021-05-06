#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// read a text file and output a string with everything in the text file
std::string get_file_contents(const char* filename);

class Shader
{
public:
	// reference ID of the shader program
	GLuint ID;
	// build the shader program from two shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	
	// activate the shader program
	void activateShader();
	// delete the shader program
	void deleteShader();
	
	// set a bool uniform in the shader
	void setBool(const std::string& name, GLboolean value);
	// set the int uniform in the shader
	void setInt(const std::string& name, GLint value);
	// set a float uniform in the shader
	void setFloat(const std::string& name, GLfloat value);

private:
	// check for any compile or linking errors in the shader program
	void compileErrors(GLuint Shader, const char* type);
};

#endif