//
// Created by bernard on 07/04/2022.
//

#ifndef ONE_COLOR_GL_CONFIGURATION_H
#define ONE_COLOR_GL_CONFIGURATION_H

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 640

typedef struct {
    int window;
    int menu_id;
    int submenu_id;
    int value;
} GLWindow;

typedef struct {
    ILuint image_name;
    int width;
    int height;
    int byte_per_pixel;
    int format;
} GLImage;

#endif //ONE_COLOR_GL_CONFIGURATION_H
