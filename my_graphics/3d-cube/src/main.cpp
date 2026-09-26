#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit())
		return -1;

	// No OpenGL context: we only want a plain window
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(800, 600, "3D cube", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	while (!glfwWindowShouldClose(window)){
		//glfwWaitEvents();  // sleeps until an event arrives, so no CPU spinning
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
