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
#include "Camera.h"

#include <iostream>
#include <cmath>

#include "cfg.h"

void framebuffer_size_callback(GLFWwindow* window, int w, int h);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
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

	// call this function every time the mouse moves
	glfwSetCursorPosCallback(window, mouse_callback);

	// call this function every time the mouse wheel scrolls
	glfwSetScrollCallback(window, scroll_callback);

	// hide the cursor and center it to the application window
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// load GLAD to configure OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// configure global opengl state
	glEnable(GL_DEPTH_TEST);

	// specify the viewport of OpenGL in the window
	glViewport(0, 0, cfg::width, cfg::height);

	// generate shader object using the vertex and fragment shaders
	Shader ourShader(cfg::vertexShader, cfg::fragmentShader);

	// generate the VBO and EBO and binds them
	VBO ourVBO(cfg::vertices, sizeof(cfg::vertices));

	// generate the vertex array object and bind it
	VAO cubeVAO;
	// tell opengl to use this VAO
	cubeVAO.bindVAO();
	// link the VBO to the VAO
	cubeVAO.linkAttrib(&ourVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	// unbind the objects to prevent accidental modification to them
	cubeVAO.unbindVAO();

	// create a light VAO
	VAO lightVAO;
	lightVAO.bindVAO();
	lightVAO.linkAttrib(&ourVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
	lightVAO.unbindVAO();

	// main while loop
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		float currentFrame = (float)glfwGetTime();
		cfg::deltaTime = currentFrame - cfg::lastFrame;
		cfg::lastFrame = currentFrame;

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

		// set the color of the light and object
		ourShader.setVec3("objectColor", glm::vec3(1.00f, 0.50f, 0.31f));
		ourShader.setVec3("lightColor",  glm::vec3(1.00f, 1.00f, 1.00f));

		// pass projection matrix to shader
		glm::mat4 projection = glm::perspective(glm::radians(cfg::camera.Zoom), (float)cfg::width/(float)cfg::height, 0.1f, 100.0f);
		ourShader.setMat4("projection", 1, GL_FALSE, projection);

		// pass view transformation to the shaders
		glm::mat4 view = cfg::camera.GetViewMatrix();
		ourShader.setMat4("view", 1, GL_FALSE, view);

		// bind VAO so openGL knows to use it
		cubeVAO.bindVAO();

		// render boxes
		for (int i = 0; i < 10; ++i)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cfg::cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", 1, GL_FALSE, model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// swap the buffers
		glfwSwapBuffers(window);
		// take care of all GLFW events
		glfwPollEvents();
	}

	// delete the objects that were created
	cubeVAO.deleteVAO();
	ourVBO.deleteVBO();
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (cfg::firstMouse)
	{
		cfg::lastX = static_cast<float>(xpos);
		cfg::lastY = static_cast<float>(ypos);
		cfg::firstMouse = false;
	}

	float xoffset = static_cast<float>(xpos) - cfg::lastX;
	float yoffset = cfg::lastY - static_cast<float>(ypos); // reversed

	cfg::lastX = static_cast<float>(xpos);
	cfg::lastY = static_cast<float>(ypos);

	cfg::camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cfg::camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInputs(GLFWwindow* window)
{
	// process inputs
	// close window when escape is pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// camera movement keys
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cfg::camera.ProcessKeyboard(Camera_Movement::FORWARD, cfg::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cfg::camera.ProcessKeyboard(Camera_Movement::BACKWARD, cfg::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cfg::camera.ProcessKeyboard(Camera_Movement::LEFT, cfg::deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cfg::camera.ProcessKeyboard(Camera_Movement::RIGHT, cfg::deltaTime);
}