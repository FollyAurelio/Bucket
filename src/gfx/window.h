#ifndef WINDOW_H
#define WINDOW_H
#include "gfx.h"
#include "gmath.h"
#include "renderer.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TARGET_FPS 60

class Window
{
public:
	GLFWwindow *handle;
	int size[2] = {800, 600};
	Renderer *renderer;
	float dt;
    	float lastFrame;
	
	Window();
	void processInput();
	void loop();
	void destroy();
	void resize();
	
};

static void sizeCallback(GLFWwindow *handle, int width, int height);
static void characterCallback(GLFWwindow* handle, unsigned int keyCode, int modifierCdoe);
static void scrollCallback(GLFWwindow* handle, double xoffset, double yoffset);
static void mouseCallback(GLFWwindow* handle, int button, int action, int mods);
static void cursorCallback(GLFWwindow* handle, double xpos, double ypos);
#endif
