#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H
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
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data= stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if(!data)
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	Texture texture(data, outputFormat, width, height, sourceFormat, wrap, filter, false);
	//texture.init();
	//stbi_image_free(data);
	return texture;
}

std::map<char, Character> Loader::loadFont(const char *fontPath)
{
	std::map<char, Character> Characters;
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}
	FT_Face face;
	if (FT_New_Face(ft, fontPath, 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	//FT_Set_Char_Size(face,0, 48, 1920, 1080);
	FT_Set_Pixel_Sizes(face, 0, 47);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	for (unsigned char c = 1; c < 128; c++)
	{
		// load character glyph
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
	// generate texture
		//std::cout << (char)c << " " << FT_Get_Char_Index(face, c)<< " " << face->glyph->glyph_index << std::endl;

		Texture texture(face->glyph->bitmap.buffer, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED, GL_CLAMP_TO_EDGE, GL_LINEAR, true);
	// now store character for later use
		Character character = {
		texture,
		glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
		glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
		(unsigned int)face->glyph->advance.x
		};
		Characters.insert(std::pair<char, Character>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	return Characters;
}


