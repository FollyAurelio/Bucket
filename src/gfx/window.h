#ifndef WINDOW_H
#define WINDOW_H
#include "gfx.h"
#include "gmath.h"
#include "renderer.h"
#include "gfx.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TARGET_FPS 60

struct Button
{
	bool pressed = false;
	bool released = false;
};

struct Mouse
{
	glm::vec2 position;
	Button buttons[GLFW_MOUSE_BUTTON_LAST];
};

struct Keyboard
{
	Button buttons[GLFW_KEY_LAST];
};


class Window
{
public:
	GLFWwindow *handle;
	int size[2] = {800, 600};
	Renderer renderer = Renderer((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	float dt;
	float lastFrame;
	Mouse mouse;
	Keyboard keyboard;
	
	Window();
	void processInput();
	void processMouse();
	void loop();
	void destroy();
	void resize();
	
};

static void sizeCallback(GLFWwindow *handle, int width, int height);
static void characterCallback(GLFWwindow* handle, unsigned int keyCode, int modifierCdoe);
static void scrollCallback(GLFWwindow* handle, double xoffset, double yoffset);
static void mouseCallback(GLFWwindow* handle, int button, int action, int mods);
static void cursorCallback(GLFWwindow* handle, double xpos, double ypos);
static void mouseCallback(GLFWwindow* handle, int button, int action, int mods);
#endif
