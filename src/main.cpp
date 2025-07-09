#include <iostream>
#include "gfx/gfx.h"
#include "gfx/shader.h"
#include "gfx/vbo.h"
#include "gfx/vao.h"
#include "gfx/texture.h"
#include "gfx/gmath.h"
#include "gfx/renderer.h"
#include "data/loader.h"

int w = 800;
int h = 600;
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	w = width;
	h = height;
}
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	//std::cout << xpos << " " << ypos << std::endl;
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
	glViewport(0, 0, w, h);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	float vertices[] = {
				1.0f, 1.0f,  
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,
				};
	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
		};
	Shader shader = Loader::loadShader("res/shaders/basic.vs",  "res/shaders/basic.fs");
	VBO ebo(GL_ELEMENT_ARRAY_BUFFER, false);
	VBO vbo(GL_ARRAY_BUFFER, false);
	VAO vao;
	vbo.buffer(vertices, sizeof(vertices));
	vao.attr(vbo, 0, 2, GL_FLOAT, 2*sizeof(float), 0);
	ebo.buffer(indices, sizeof(indices));
	//Texture texture("res/images/container.jpg", GL_RGB, GL_RGB);
	Texture texture = Loader::loadImage("res/images/container.jpg", GL_RGB, GL_RGB,GL_REPEAT, GL_NEAREST);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(250.0f, 0.0f,0.0f));
	//trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(300.0f,200.0f, 0));
	Renderer renderer;
	shader.use();
	shader.setMatrix4("model", trans);
	shader.setVector3("ourColor", glm::vec3(1.0f, 0.0f, 0.7f));

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);
		//texture.activate(0);
		shader.use();
		glm::mat4 projection = glm::ortho(0.0f, (float)w, (float)h, 0.0f, -1.0f, 1.0f);
		shader.setMatrix4("projection", projection);
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
