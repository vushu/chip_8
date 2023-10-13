#include <iostream>

// GLFW
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include "chip_8/app.hpp"


int main()
{
    chip_8::App app { 800, 600 };
    app.run();
    return 0;
}
