#include <iostream>
#include "gfx/gfx.h"
#include "gfx/shader.h"
#include "gfx/vbo.h"
#include "gfx/vao.h"
#include "gfx/texture.h"
#include "gfx/gmath.h"
#include "gfx/renderer.h"
#include "data/loader.h"
#include "gfx/window.h"
int window_width = 800;
int window_height = 600;
void sizeCallback(GLFWwindow* handle, int width, int height)
{
	glViewport(0, 0, width, height);
	window_width = width;
	window_height = height;
}

int main()
{
	/*glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//For OS X
	GLFWwindow* window = glfwCreateWindow(800, 600, "Bucket", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, w, h);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		Renderer renderer((float)w, (float)h);

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		renderer.drawRectangle(glm::vec2(250.0f, 10.0f), glm::vec2(300.0f, 200.0f), glm::vec3(1.0f, 0.0f, 0.7f), true);

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}*/
	Window window;
	glfwSetFramebufferSizeCallback(window.handle, sizeCallback);
	window.loop();
	window.destroy();
	return 0;

}
