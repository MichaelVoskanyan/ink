#ifndef INK_WINDOW_H
#define INK_WINDOW_H

#include <stdint.h>

struct GLFWwindow;

struct Window {
    uint32_t i_windowWidth;
    uint32_t i_windowHeight;
    char *s_windowTitle;
    
    GLFWwindow *h_window;

    void InitWindow();
};

#endif