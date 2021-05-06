#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void ProcessInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float xOffset = 0.0f;

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle", nullptr, nullptr);
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
	Shader ourShader("shader.vert", "shader.frag");

	// set up vertex data and buffer(s) and configure vertex attributes
	// ----------------------------------------------------------------
	float vertices[] = {
		 // positions		 // colors
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // left 
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // right
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top 
	};

	unsigned int VAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1); 

	// uncomment for wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop (every iteration is a frame)
	// ----------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		// input
		ProcessInput(window);

		// render 
		// clear the color buffer
		glClearColor(0.165f, 0.169f, 0.176f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// activate the shader program
		ourShader.use();

		// set horizontal position
		ourShader.setFloat("xOffset", xOffset);

		// render the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: poll IO events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// optional: clear resources after outliving their purposes
	// --------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, cleraing allocated GLFW resources
	// --------------------------------------------------
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	// glfw: function is called each time the window is resized
	// --------------------------------------------------------
	// set viewport
	glViewport(0, 0, w, h);
}

void ProcessInput(GLFWwindow* window)
{
	// glfw: process all input: query if relevant keys are pressed/released
	// --------------------------------------------------------------
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}