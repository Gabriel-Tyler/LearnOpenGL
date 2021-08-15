#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

#include <iostream>
#include <cmath>

#include "cfg.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void processInputs(GLFWwindow* window);

int main()
{
	// initialize GLFW
	glfwInit();
	
	// tell GLFW what version of openGL we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// tell GLFW we are using the CORE profile (so we only have modern functions)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a GLFWwindow object
	GLFWwindow* window = glfwCreateWindow(
		cfg::width,
		cfg::height,
		cfg::name, 
		nullptr,
		nullptr
	);
	// check if the window failed to create
	if (!window)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	// introduce the window into the current context
	glfwMakeContextCurrent(window);
	// call this function every time the window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// load GLAD to configure OpenGL
	gladLoadGL();

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	// specify the viewport of OpenGL in the window
	glViewport(0, 0, cfg::width, cfg::height);

	// generate shader object using the vertex and fragment shaders
	Shader ourShader(cfg::vertexShader, cfg::fragmentShader);

	// generate the vertex array object and bind it
	VAO VAO1;
	// tell opengl to use this VAO
	VAO1.bindVAO();

	// generate the VBO and EBO and binds them
	VBO VBO1(cfg::vertices, sizeof(cfg::vertices));

	// link the VBO to the VAO
	VAO1.linkAttrib(&VBO1, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAO1.linkAttrib(&VBO1, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));

	// unbind the objects to prevent accidental modification to them
	VAO1.unbindVAO();
	VBO1.unbindVBO();

	// generate a texture object for the cutecat.png
	Texture cutecat("cutecat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	// assign the cutecat texture to the 0 texture unit
	cutecat.texUnit(&ourShader, "tex0", 0);

	// main while loop
	while (!glfwWindowShouldClose(window))
	{
		// process any inputs
		processInputs(window);
		// specify the color of the background
		glClearColor(
			cfg::clear[0],
			cfg::clear[1],
			cfg::clear[2],
			cfg::clear[3]
		);
		// clear the back buffer and assign a new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// tell OpenGL which shader program to use
		ourShader.activateShader();
		// bind the cutecat texture so that it appears in rendering
		cutecat.bindTexture();

		// create transformations
		glm::mat4 view  = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3((float)std::sin(glfwGetTime()), (float)std::cos(glfwGetTime()), -5.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)cfg::width/(float)cfg::height, 0.1f, 100.0f);

		// pass transformations to the shaders
		ourShader.setMat4("view", 1, GL_FALSE, view);
		ourShader.setMat4("projection", 1, GL_FALSE, projection);

		// bind VAO so openGL knows to use it
		VAO1.bindVAO();
		for (int i = 0; i < 10; ++i)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cfg::cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians((float)glfwGetTime()*45.0f + angle), glm::vec3(0.5f, 1.0f, 0.0f));
			ourShader.setMat4("model", 1, GL_FALSE, model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// swap the buffers
		glfwSwapBuffers(window);
		// take care of all GLFW events
		glfwPollEvents();
	}

	// delete the objects that were created
	VAO1.deleteVAO();
	VBO1.deleteVBO();
	cutecat.deleteTexture();
	ourShader.deleteShader();
	// delete window
	glfwDestroyWindow(window);
	// terminate GLFW
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	// specify the viewport of OpenGL in the window
	glViewport(0, 0, w, h);
}
void processInputs(GLFWwindow* window)
{
	// process inputs
	// close window when escape is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}