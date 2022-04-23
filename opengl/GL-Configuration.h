//
// Created by bernard on 07/04/2022.
//

#ifndef ONE_COLOR_GL_CONFIGURATION_H
#define ONE_COLOR_GL_CONFIGURATION_H


#if defined(GL_VERSION_4_6)
#define gl_version "4.6"
#elif defined(GL_VERSION_4_5)
#define gl_version "4.5"
#elif defined(GL_VERSION_4_4)
#define gl_version "4.4"
#elif defined(GL_VERSION_4_3)
#define gl_version "4.3"
#elif defined(GL_VERSION_4_2)
#define gl_version "4.2"
#elif defined(GL_VERSION_4_1)
#define gl_version "4.1"
#elif defined(GL_VERSION_4_0)
#define gl_version "4.0"
#elif defined(GL_VERSION_3GL_VERSION_3_3)
#define gl_version "3.3"
#elif defined(GL_VERSION_3GL_VERSION_3_2)
#define gl_version "3.2"
#else
#error "We need Open GL version 3.2 or more recent"
#endif


#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 640

#include "basic-data.h"

typedef struct {
    int window;
    int width;
    int height;
    int menu_id;
    int submenu_id;
    int value;
} GLWindow;


extern GLWindow mainWindow;
extern TheImage main_image;

#endif //ONE_COLOR_GL_CONFIGURATION_H
