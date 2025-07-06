#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "texture.h"

Texture::Texture(const char* path, GLint outputFormat, GLint sourceFormat)
{
	glGenTextures(1 , &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	//stbi_set_flip_vertically_on_load(true);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, outputFormat, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, handle);
}
void Texture::activate(GLint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	bind();
}

void Texture::destory()
{
	glDeleteTextures(1 , &handle);
}

