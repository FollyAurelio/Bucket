#include "texture.h"
#include <stb/stb_image.h>
#include <ft2build.h>
#include FT_FREETYPE_H

Texture::Texture(){}

Texture::Texture(unsigned char *data, GLint outputFormat, int width, int height, GLint sourceFormat, GLint wrap, GLint filter, bool isText)
{
	this->data = data;
	this->outputFormat = outputFormat;
	this->width = width;
	this->height = height;
	this->sourceFormat = sourceFormat;
	this->wrap = wrap;
	this->filter = filter;
	this->isText = isText;
}

void Texture::init()
{
	glGenTextures(1 , &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	// load and generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, outputFormat, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	if(!isText)
	{stbi_image_free(data);}


}
void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, handle);
}
void Texture::activate(GLint unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
}

void Texture::destory()
{
	glDeleteTextures(1 , &handle);
}

