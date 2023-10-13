#ifndef APP_HPP
#define APP_HPP
// GLAD
#include <glad/glad.h>
#include <iostream>

// GLFW
#include <GLFW/glfw3.h>
namespace chip_8 {

inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    std::cout << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

class App {
public:
    App() = default;
    ~App()
    {
        glfwDestroyWindow(window_);
    }
    App(int width, int height)
        : width_(width)
        , height_(height)
    {
    }

    void run();

private:
    void render_frame();
    void init();
    int width_, height_;
    GLFWwindow* window_;
};
}
#endif
