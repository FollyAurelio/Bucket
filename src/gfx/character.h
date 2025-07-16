#ifndef CHARACTER_H
#define CHARACTER_H
#include "texture.h"
#include "gmath.h"

struct Character {
	Texture texture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

#endif


