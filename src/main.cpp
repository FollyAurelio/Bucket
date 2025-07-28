#include <iostream>
#include "util.h"
#include "resource_manager.h"
#include "renderer.h"
#include "editor.h"
#include "ui.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TARGET_FPS 60

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
Editor editor;
float dt, lastFrame, previous = 0;
int frames;
Mouse mouse;
Keyboard keyboard;
Box box = Box(glm::vec2(140, 3), glm::vec2(200, 100), glm::vec4(0.1f, 0.7f, 0.0f, 1.0f), false);
int main(int argc, char *argv[])
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
	glfwSwapInterval(0);
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
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCharModsCallback(window, characterCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetMouseButtonCallback(window, mouseCallback);
	if(argc != 2){
		std::cout << "ERROR::MUST PROVIDE EXACTLY ONE ARGUMENT" << std::endl;
		return 1;
	}
	editor.file_path = argv[1];
	editor.init(loadFile(argv[1]));
	
	while(!glfwWindowShouldClose(window))
	{	
		float currentFrame = glfwGetTime();
        	//dt = (currentFrame - lastFrame) * TARGET_FPS;
        	lastFrame = currentFrame;
		frames++;
		if(currentFrame - previous >= 1){
			std::cout << frames << std::endl;
			frames = 0;
			previous = currentFrame;
		}
		glfwPollEvents();
		renderer.setCamera();
		//processInput();
		processMouse();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//renderer.drawRectangle(glm::vec2(60.0f, 40.0f), glm::vec2(30.0f, 30.0f), glm::vec3(0.7f, 0.2f, 0.5f), true);
		//renderer.drawRectangle(renderer.rect_shader, glm::vec2(0.0f, 150.0f), glm::vec2(800.0f, 30.0f), glm::vec3(0.7f, 0.2f, 0.5f), true);
		//renderer.drawText(renderer.text_shader,"abc\n123/[}\niwfjoewij" , glm::vec2(25.0f, 25.0f), 1.0f, glm::vec3(0.5, 0.8f, 0.2f), false);
		
		editor.render(renderer);

		//box.update();
		//bo.update();
		//box.render(renderer);
		//bo.render(renderer);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
	


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
	
}

void characterCallback(GLFWwindow* window, unsigned int keyCode, int modifierCode)
{
	if(editor.mode == MODE_INSERT){
		editor.insert(keyCode, 1);
	}
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
	switch(action)
	{
		case GLFW_PRESS:
		case GLFW_REPEAT:
			if(editor.mode == MODE_NORMAL){
				switch(key)
				{
					case GLFW_KEY_LEFT_CONTROL:
					editor.mode = MODE_INSERT;
					break;

					case GLFW_KEY_RIGHT_CONTROL:
					editor.move_char_right();
					editor.mode = MODE_INSERT;
					break;

					case GLFW_KEY_J:
					editor.move_line_down();
					break;
					
					case GLFW_KEY_L:
					editor.move_char_right();
					break;

					case GLFW_KEY_K:
					editor.move_line_up();
					break;

					case GLFW_KEY_H:
					editor.move_char_left();
					break;

					case GLFW_KEY_X:
					editor.remove();
					break;

					case GLFW_KEY_EQUAL:
					renderer.cameraZoom += 0.1f; 
					break;

					case GLFW_KEY_MINUS:
					renderer.cameraZoom -= 0.1f; 
					break;

					case GLFW_KEY_UP:
					renderer.cameraPosition.y += 3.0f;
					break;

					case GLFW_KEY_DOWN:
					renderer.cameraPosition.y -= 3.0f;
					break;

					case GLFW_KEY_S:
					editor.save();
					break;

					case GLFW_KEY_U:
					editor.undo();
					break;

					case GLFW_KEY_R:
					editor.redo();
					break;
				}

			}
			if(editor.mode == MODE_INSERT){
				switch(key)
				{
					case GLFW_KEY_ESCAPE:
					editor.mode = MODE_NORMAL;
					break;

					case GLFW_KEY_BACKSPACE:
					editor.backspace();
					break;

					case GLFW_KEY_ENTER:
					editor.enter();
					break;
				}
			}

	}

}
