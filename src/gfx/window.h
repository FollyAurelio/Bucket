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
	int size[2] = {800, 600};
	Renderer *renderer;
	
	Window();
	void processInput();
	void loop();
	void destroy();
	void resize();
	
};
void sizeCallback(GLFWwindow* handle, int width, int height);

//global window
#endif
