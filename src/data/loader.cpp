#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "loader.h"



std::string Loader::loadFile(const char *filePath)
{
	std::string content;
	std::ifstream file;
	// ensure ifstream objects can throw exceptions:
	file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		file.open(filePath);
		std::stringstream fileStream;
		// read file’s buffer contents into streams
		fileStream << file.rdbuf();
		// close file handlers
		file.close();
		// convert stream into string
		content = fileStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;

	}
	return content;
}

Shader Loader::loadShader(const char *vertexPath, const char *fragmentPath)
{
	Shader shader(loadFile(vertexPath), loadFile(fragmentPath));
	return shader;
}

Texture Loader::loadImage(const char *texturePath, GLint outputFormat, GLint sourceFormat, GLint wrap, GLint filter)
{
	int width, height, nrChannels;
	unsigned char *data= stbi_load(texturePath, &width, &height, &nrChannels, 0);
	//stbi_set_flip_vertically_on_load(true);
	if(!data)
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	Texture texture(data, outputFormat, width, height, sourceFormat, wrap, filter);
	texture.init();
	stbi_image_free(data);
	return texture;
}
