#include <iostream>
#include "util.h"
#include "gfx/renderer.h"
#include "gfx/renderer.h"
#include "ui/UIComponent.h"
#include "ui/box.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TARGET_FPS 60
//#include "gfx/window.h"

struct Button
{
	bool pressed, released;
};

struct Mouse
{
	glm::vec2 position, offposition;
	Button buttons[GLFW_MOUSE_BUTTON_LAST];
};

struct Keyboard
{
	Button buttons[GLFW_KEY_LAST];
};


static void sizeCallback(GLFWwindow *window, int width, int height);
static void characterCallback(GLFWwindow* window, unsigned int keyCode, int modifierCdoe);
static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
static void cursorCallback(GLFWwindow* window, double xpos, double ypos);
static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void processInput()
void processMouse();

Renderer renderer((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
float dt, lastFrame;
Mouse mouse;
Keyboard keyboard;
Box box = Box(glm::vec2(140, 3), glm::vec2(200, 100), glm::vec3(0.1f, 0.7f, 0.0f), false);
std::string text;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//For OS X
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bucket", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	renderer.init();
	glfwSetFramebufferSizeCallback(window, sizeCallback);
	glfwSetCharModsCallback(window, characterCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetKeyCallback(window, keyboardCallback);
	
	while(!glfwWindowShouldClose(window))
	{	
		float currentFrame = glfwGetTime();
        	dt = (currentFrame - lastFrame) * TARGET_FPS;
        	lastFrame = currentFrame;
		glfwPollEvents();
		renderer.setCamera();
		//processInput();
		processMouse();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderer.drawRectangle(glm::vec2(60.0f, 40.0f), glm::vec2(50.0f, 30.0f), glm::vec3(0.7f, 0.2f, 0.5f), false);
		renderer.drawRectangle(glm::vec2(0.0f, 150.0f), glm::vec2(800.0f, 30.0f), glm::vec3(0.7f, 0.2f, 0.5f), true);
		renderer.drawText(text, 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

		box.update();
		//bo.update();
		box.render(renderer);
		//bo.render(renderer);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	exit(0);
	


}


/*void processInput()
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
//	if(glfwGetKey(handle, GLFW_KEY_UP) == GLFW_PRESS)
		renderer.cameraPosition.y += glm::translate(renderer.camera, glm::vec3(0.0f, 3.0f, 0.0f));
	//if(glfwGetKey(handle, GLFW_KEY_DOWN) == GLFW_REPEAT)
		//renderer.camera = glm::translate(renderer.camera, glm::vec3(0.0f, -3.0f, 0.0f));
	if (glfwGetKey(handle, GLFW_KEY_P) == GLFW_PRESS)
		renderer.cameraZoom += 0.1f; 
	if (glfwGetKey(handle, GLFW_KEY_L) == GLFW_PRESS)
		renderer.cameraZoom -= 0.1f; 


	double xpos, ypos;
	glfwGetCursorPos(handle, &xpos, &ypos);
	//std::cout << xpos << " " << ypos << std::endl;
	//std::cout << width << " " << height << std::endl;
}*/

void processMouse()
{
	if(box.collideMouse(mouse.offposition))
	{
		if(mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].pressed)
		{box.state = STATE_CLICK;
		}
	
		else if(mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].released)
		{
			box.state = STATE_RELEASE;
		}
		else
		{box.state = STATE_HOVER;}
	}
	else
	{
		box.state = STATE_DEFAULT;
	}
	mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].released = false;

}

static void sizeCallback(GLFWwindow *window, int width, int height)
{

	glViewport(0, 0, width, height);
	renderer.projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	//pWindow->size[0] = width;
	//pWindow->size[1] = height;
	
}

void characterCallback(GLFWwindow* window, unsigned int keyCode, int modifierCode)
{
	text += (char)keyCode;
	std::cout << (char)keyCode <<std::endl;
	std::cout << keyCode <<std::endl;
	std::cout << modifierCode <<std::endl;
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	renderer.cameraPosition.y += yoffset;
}

static void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	mouse.position = glm::vec2(xpos, ypos);
	glm::vec4 offsetMouse = renderer.inverseCamera * glm::vec4(mouse.position, 0.0f,1.0f);
	mouse.offposition = glm::vec2(offsetMouse.x, offsetMouse.y);
}

static void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if(!mouse.buttons[button].pressed && action == GLFW_PRESS)
	{
		mouse.buttons[button].pressed = true;
	}
	else if(mouse.buttons[button].pressed && action == GLFW_RELEASE)
	{
		mouse.buttons[button].pressed = false;
		mouse.buttons[button].released = true;
	}

}

static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	/*if(key == GLFW_KEY_UP && action == GLFW_PRESS)
		renderer.cameraPosition.y += glm::translate(renderer.camera, glm::vec3(0.0f, 3.0f, 0.0f));
	if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		renderer.camera = glm::translate(renderer.camera, glm::vec3(0.0f, -3.0f, 0.0f));*/
	if (key == GLFW_KEY_P && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
		renderer.cameraZoom += 0.1f; 
	if (key == GLFW_KEY_L && action == GLFW_REPEAT)
		renderer.cameraZoom -= 0.1f; 
}
