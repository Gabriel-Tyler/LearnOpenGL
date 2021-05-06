#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void ProcessInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// shader program strings
const char* vertexShaderSource = {
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
	"}\0"
};
const char* firstFragmentShaderSource = {
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(0.176f, 0.659f, 0.847f, 1.0f);\n"
	"}\0"
};
const char* secondFragmentShaderSource = {
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(0.847f, 0.659f, 0.176f, 1.0f);\n"
	"}\0"
}; 

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",	nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	// build and compile shader program
	// ---------------------------------------
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	// check for vertex shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	// first shader program compilation
	// --------------------------------
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &firstFragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// check for vertex shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	// link shaders
	unsigned int firstShaderProgram = glCreateProgram();
	glAttachShader(firstShaderProgram, vertexShader);
	glAttachShader(firstShaderProgram, fragmentShader);
	glLinkProgram(firstShaderProgram);

	// check for linking errors
	glGetProgramiv(firstShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(firstShaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
	}

	// delete the current fragment shader
	glDeleteShader(fragmentShader);

	// second shader program compilation
	// --------------------------------
	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &secondFragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// check for vertex shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << '\n';
	}

	// link shaders
	unsigned int secondShaderProgram = glCreateProgram();
	glAttachShader(secondShaderProgram, vertexShader);
	glAttachShader(secondShaderProgram, fragmentShader);
	glLinkProgram(secondShaderProgram);

	// check for linking errors
	glGetProgramiv(secondShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(secondShaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << '\n';
	}

	// set up vertex data and buffer(s) and configure vertex attributes
	// ----------------------------------------------------------------
	float vertices1[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float vertices2[] = {
		// second triangle
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};
	// id for the buffer object and vertex array objects
	unsigned int VAOs[2], VBOs[2];
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
	
	// first triangle setup
	// --------------------
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// second triangle setup
	// ---------------------
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// uncomment for wireframe mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop (every iteration is a frame)
	// ----------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		ProcessInput(window);

		// render 
		// ---------------
		glClearColor(0.165f, 0.169f, 0.176f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(firstShaderProgram); // firstShaderProgram

		// draw first triangle
		glBindVertexArray(VAOs[0]); 
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(secondShaderProgram);
		
		// draw second triangle
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glBindVertexArray(0); // no need to unbind every time

		// glfw: poll IO events and swap buffers
		// -------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// optional: clear resources after outliving their purposes
	// --------------------------------------------------------
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(firstShaderProgram);
	glDeleteProgram(secondShaderProgram);

	// glfw: terminate, cleraing allocated GLFW resources
	// --------------------------------------------------
	glfwTerminate();
	return 0;
}

// glfw: function is called each time the window is resized
// --------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	// set viewport
	glViewport(0, 0, w, h);
}

// glfw: process all input: query if relevant keys are pressed/released
// --------------------------------------------------------------
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}