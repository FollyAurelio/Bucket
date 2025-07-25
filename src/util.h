#ifndef UTIL_H
#define UTIL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>
#include <fstream>
#include <sstream>


struct Character {
	unsigned int texture;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

struct Font{
	float lineoffset;
	std::map<char, Character> characters;
};
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#endif

