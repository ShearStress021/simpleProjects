#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include 

int main() {
    if (!glfwInit()) return -1;

    // Explicitly tell GLFW we are using Vulkan
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
// Keep it simple for now

    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);
    

   
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
