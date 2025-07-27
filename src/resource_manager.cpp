#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "resource_manager.h"

std::string loadFile(const char *filePath)
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
	catch(std::ifstream::failure *e)
	{
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		exit(1);
	}
	return content;
}

void writeFile(const char *filePath, const char *text)
{
	std::ofstream file;
	file.exceptions (std::ofstream::failbit | std::ofstream::badbit);
	try
	{
	
		file.open(filePath);
  		file << text;
		file.close();
	}
	catch(std::ofstream::failure *e)
	{
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_WRITTEN" << std::endl;
	}
}




Shader loadShader(const char *vertexPath, const char *fragmentPath)
{
	Shader shader(loadFile(vertexPath), loadFile(fragmentPath));
	return shader;
}


unsigned int loadImage(const char *texturePath, GLint outputFormat, GLint sourceFormat, GLint wrap, GLint filter)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data= stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if(!data)
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	unsigned int texture;
	glGenTextures(1 , &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	glTexImage2D(GL_TEXTURE_2D, 0, outputFormat, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	return texture;
}

Font loadFont(const char *fontPath)
{
	Font font;
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		exit(1);
	}
	FT_Face face;
	if (FT_New_Face(ft, fontPath, 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		exit(1);
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	font.lineoffset = face->size->metrics.height >> 6;
	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		unsigned int texture;
		glGenTextures(1 , &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RED,face->glyph->bitmap.width,face->glyph->bitmap.rows,0,GL_RED,GL_UNSIGNED_BYTE,face->glyph->bitmap.buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		Character character = {
		texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		(unsigned int)face->glyph->advance.x
		};
		font.characters.insert(std::pair<char, Character>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	return font;
}


