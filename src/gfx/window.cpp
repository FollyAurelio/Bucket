#include "window.h"



Window::Window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//For OS X
	handle = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Bucket", NULL, NULL);
	if (handle == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(handle);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(1);
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	*renderer = Renderer((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	glfwSetWindowUserPointer(handle, this);
	glfwSetFramebufferSizeCallback(handle, sizeCallback);
	glfwSetCharModsCallback(handle, characterCallback);
	glfwSetScrollCallback(handle, scrollCallback);
	glfwSetCursorPosCallback(handle, cursorCallback);
	glfwSetMouseButtonCallback(handle, mouseCallback);
	
}


void Window::processInput()
{
	if(glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(handle, true);
	if(glfwGetKey(handle, GLFW_KEY_UP) == GLFW_PRESS)
		renderer->camera = glm::translate(renderer->camera, glm::vec3(0.0f, 3.0f, 0.0f));
	if(glfwGetKey(handle, GLFW_KEY_DOWN) == GLFW_REPEAT)
		renderer->camera = glm::translate(renderer->camera, glm::vec3(0.0f, -3.0f, 0.0f));
	if (glfwGetKey(handle, GLFW_KEY_KP_ADD) == GLFW_REPEAT)
		renderer->camera = glm::scale(renderer->camera, glm::vec3(1.1f, 1.1f, 0.0f));
	if (glfwGetKey(handle, GLFW_KEY_KP_SUBTRACT) == GLFW_REPEAT)
		renderer->camera = glm::scale(renderer->camera, glm::vec3(0.9f, 0.9f, 0.0f));


	double xpos, ypos;
	glfwGetCursorPos(handle, &xpos, &ypos);
	//std::cout << xpos << " " << ypos << std::endl;
	//std::cout << width << " " << height << std::endl;
}

void Window::processMouse()
{
	if(mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].pressed)
	{
		std::cout << "pressed" << std::endl;
	}
	else if(mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].released)
	{
		std::cout << "released" << std::endl;
		mouse.buttons[GLFW_MOUSE_BUTTON_LEFT].released = false;
	}
}

void Window::loop()
{
	while(!glfwWindowShouldClose(handle))
	{	
		//float currentFrame = glfwGetTime();
		//std::cout << glfwGetTime() << std::endl;
        	//dt = (currentFrame - lastFrame) * TARGET_FPS;
        	//lastFrame = currentFrame;
		glfwPollEvents();
		processMouse();
		renderer->drawRectangle(glm::vec2(60.0f, 40.0f), glm::vec2(50.0f, 30.0f), glm::vec3(0.7f, 0.2f, 0.5f), false);
		renderer->drawRectangle(glm::vec2(0.0f, 40.0f), glm::vec2(800.0f, 30.0f), glm::vec3(0.7f, 0.2f, 0.5f), false);
		glfwSwapBuffers(handle);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
	
void Window::destroy()
{
	glfwTerminate();
}

static void sizeCallback(GLFWwindow *handle, int width, int height)
{

	Window *pWindow = (Window*)glfwGetWindowUserPointer(handle);
	glViewport(0, 0, width, height);
	pWindow->renderer->projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	pWindow->size[0] = width;
	pWindow->size[1] = height;
	
}

void characterCallback(GLFWwindow* handle, unsigned int keyCode, int modifierCode)
{
	//std::cout << (char)keyCode <<std::endl;
	//std::cout << modifierCode <<std::endl;
}

static void scrollCallback(GLFWwindow* handle, double xoffset, double yoffset)
{
	Window *pWindow = (Window*)glfwGetWindowUserPointer(handle);
	pWindow->renderer->camera = glm::translate(pWindow->renderer->camera, glm::vec3(0.0f, 100.0f * yoffset, 0.0f));
}

static void cursorCallback(GLFWwindow* handle, double xpos, double ypos)
{
	Window *pWindow = (Window*)glfwGetWindowUserPointer(handle);
	glm::mat4 inverseCamera = glm::inverse(pWindow->renderer->camera);
	glm::vec4 b = inverseCamera * glm::vec4(xpos, ypos, 0.0f,1.0f) ;
}

static void mouseCallback(GLFWwindow* handle, int button, int action, int mods)
{
	Window *pWindow = (Window*)glfwGetWindowUserPointer(handle);
	if (button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(!pWindow->mouse.buttons[button].pressed && action == GLFW_PRESS)
		{
			pWindow->mouse.buttons[button].pressed = true;
		}
		else if(pWindow->mouse.buttons[button].pressed && action == GLFW_RELEASE)
		{
			pWindow->mouse.buttons[button].pressed = false;
			pWindow->mouse.buttons[button].released = true;
		}
	}

}
