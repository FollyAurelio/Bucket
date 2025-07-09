#include "window.h"



Window::Window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//For OS X
	handle = glfwCreateWindow(800, 600, "Bucket", NULL, NULL);
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
	glViewport(0, 0, 800, 600);
	*renderer = Renderer(800.0f, 600.0f);
	//glfwSetFramebufferSizeCallback(handle, sizeCallback);
}


void Window::processInput()
{
	if(glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(handle, true);
	double xpos, ypos;
	glfwGetCursorPos(handle, &xpos, &ypos);
	//std::cout << xpos << " " << ypos << std::endl;
	//std::cout << width << " " << height << std::endl;
}

void Window::loop()
{
	while(!glfwWindowShouldClose(handle))
	{
		processInput();
		resize();
		renderer->drawRectangle(glm::vec2(250.0f, 10.0f), glm::vec2(300.0f, 200.0f), glm::vec3(1.0f, 0.0f, 0.7f), true);
		glfwSwapBuffers(handle);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}
	
void Window::destroy()
{
	glfwTerminate();
}

void Window::resize()
{
	glfwGetFramebufferSize(handle,&size[0], &size[1]);
	glViewport(0, 0, size[0], size[1]);
	renderer->projection = glm::ortho(0.0f, (float)size[0], (float)size[1], 0.0f, -1.0f, 1.0f);


	
}
