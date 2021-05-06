#include "Shader.h"

// read a text file and output a string with everything in the text file
std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw errno;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	// create and compile the vertex shader and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// attach the vertex shader source to the fragment shader object
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	// compile the vertex shader into machine code
	glCompileShader(vertexShader);
	// check for vertex shader compile errors
	compileErrors(vertexShader, "VERTEX");

	// create and compile the fragment shader and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// attach the fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	// compile the fragment shader into machine code
	glCompileShader(fragmentShader);
	// check for fragment shader compile errors
	compileErrors(fragmentShader, "FRAGMENT");

	// create the shader program
	ID = glCreateProgram();

	// link the shaders into the shader program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	// link all the shaders together into shader program
	glLinkProgram(ID);
	// check for shader program linking errors
	compileErrors(ID, "PROGRAM");

	// delete both shaders as they are not needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::activateShader()
{
	// use the shader program
	glUseProgram(ID);
}

void Shader::deleteShader()
{
	glDeleteProgram(ID);
}

void Shader::setBool(const std::string& name, GLboolean value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), GLint(value));
}

void Shader::setInt(const std::string& name, GLint value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, GLfloat value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::compileErrors(GLuint shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR::" << type << '\n';
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << '\n';
		}
	}
}