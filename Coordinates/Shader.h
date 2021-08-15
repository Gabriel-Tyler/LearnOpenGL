#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, GLboolean value) const;
    void setInt(const std::string& name, GLint value) const;
    void setFloat(const std::string& name, GLfloat value) const;

    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, GLfloat x, GLfloat y) const;

    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;

    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;

    void setMat2(const std::string& name, GLint count, GLboolean transform, const glm::mat2& mat) const;
    void setMat3(const std::string& name, GLint count, GLboolean transform, const glm::mat3& mat) const;
    void setMat4(const std::string& name, GLint count, GLboolean transform, const glm::mat4& mat) const;

private:
	// check for any compile or linking errors in the shader program
	void compileErrors(GLuint Shader, const char* type);
};

#endif