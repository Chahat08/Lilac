#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WIDTH 1500
#define HEIGHT 800

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Lilac", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW initiation failed." << std::endl;
	
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -WIDTH / 2, WIDTH / 2, 0.0, 1.0);
	
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSwapInterval(1);
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}