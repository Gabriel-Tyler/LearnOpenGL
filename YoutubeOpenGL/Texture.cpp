#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	// assigns the type of texture to the texture object
	type = texType;

	// stores the widht, height, and number of color channels  of the image
	int widthImg, heightImg, numColCh;
	// flips the image so it appears right-side-up
	stbi_set_flip_vertically_on_load(true);
	// reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	// generates an OpenGL texture object
	glGenTextures(1, &ID);
	// assigns the texture to a texture unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// configures the type of algorithm that is used to make the image smaller of bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// configures the way the texture repeates
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// extra lines for if GL_CLAMP_TO_BORDER is chosen
	// GLfloat flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// assigns the image to the OpenGL texture object
	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	// generates the MipMaps for the texture
	glGenerateMipmap(texType);

	// deletes the image data as it is already in the OpenGL texture object
	stbi_image_free(bytes);
	// unbind the texture object so that it can't be accidentally modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader* shader, const char* uniform, GLuint unit)
{
	// gets the location of the uniform
	GLuint texUni = glGetUniformLocation(ID, uniform);
	// the shader needs to be activated before changing the value of a uniform
	shader->activateShader();
	// sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::bindTexture()
{
	glBindTexture(type, ID);
}

void Texture::unbindTexture()
{
	glBindTexture(type, 0);

}

void Texture::deleteTexture()
{
	glDeleteTextures(1, &ID);
}
