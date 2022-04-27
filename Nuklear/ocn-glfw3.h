//
// Created by bernard on 25/04/22.
//

#ifndef ONE_COLOR_OCN_GLFW3_H
#define ONE_COLOR_OCN_GLFW3_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "nuklear-config.h"
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

typedef struct MainData {
    struct nk_glfw glfw;
    GLFWwindow *win;
    int width, height;
    struct nk_context *ctx;
    struct nk_colorf bg;
    struct nk_color pic_bg;
} MainData;

extern MainData main_data;
#endif //ONE_COLOR_OCN_GLFW3_H
