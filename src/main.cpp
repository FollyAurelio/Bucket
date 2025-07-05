#include <iostream>
#include "gfx/gfx.h"
#include "gfx/shader.h"
#include "gfx/vbo.h"
#include "gfx/vao.h"
#include "gfx/texture.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
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
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	float vertices[] = {
				0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
				0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
				-0.5f, -0.5f, 0.0f,0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
				-0.5f, 0.5f, 0.0f,1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				};
	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
		};
	Shader shader("res/shaders/basic.vs",  "res/shaders/basic.fs");
	VBO ebo(GL_ELEMENT_ARRAY_BUFFER, false);
	VBO vbo(GL_ARRAY_BUFFER, false);
	VAO vao;
	vbo.buffer(vertices, sizeof(vertices));
	vao.attr(vbo, 0, 3, GL_FLOAT, 8*sizeof(float), 0);
	vao.attr(vbo, 1, 3, GL_FLOAT, 8*sizeof(float), 3 * sizeof(float));
	vao.attr(vbo, 2, 2, GL_FLOAT, 8*sizeof(float), 6 * sizeof(float));
	ebo.buffer(indices, sizeof(indices));
	Texture texture("res/images/container.jpg", GL_RGB, GL_RGB);
	shader.use();
	shader.setInt("tex", 0);

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		texture.activate(0);
		shader.use();
		vao.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	glfwTerminate();
	return 0;

}
