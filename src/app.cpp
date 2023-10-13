#include "chip_8/app.hpp"
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

namespace chip_8 {
void App::init()
{
    std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    window_ = glfwCreateWindow(width_, height_, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window_);
    if (window_ == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // Set the required callback functions
    glfwSetKeyCallback(window_, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
    }

    // Define the viewport dimensions
    glViewport(0, 0, width_, height_);
}

void App::render_frame()
{
    // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
    glfwPollEvents();

    // Render
    // Clear the colorbuffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap the screen buffers
    glfwSwapBuffers(window_);
}

void render_loop_callback(void* arg)
{
    static_cast<App*>(arg)->render_frame();
}

void App::run()
{
    init();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(&render_loop_callback, this, -1, 1);
#else
    while (!glfwWindowShouldClose(window_)) {
        render_frame();
    }
#endif
    glfwTerminate();
}
}
