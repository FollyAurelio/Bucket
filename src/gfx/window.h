#ifndef WINDOW_H
#define WINDOW_H
#include "gfx.h"
#include "gmath.h"
#include "renderer.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

class Window
{
public:
	GLFWwindow *handle;
	glm::vec2 size = {800, 600};
	Renderer *renderer;
	
	Window();
	void processInput();
	void loop();
	void destroy();
	
};

//global window
//extern Window window;
#endif
