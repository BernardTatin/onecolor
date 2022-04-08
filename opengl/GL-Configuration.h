//
// Created by bernard on 07/04/2022.
//

#ifndef ONE_COLOR_GL_CONFIGURATION_H
#define ONE_COLOR_GL_CONFIGURATION_H

#define DEFAULT_WIDTH  640
#define DEFAULT_HEIGHT 640

typedef struct {
    int window;
    int width;
    int height;
    int menu_id;
    int submenu_id;
    int value;
} GLWindow;

typedef unsigned char u8;
typedef struct __attribute__((__packed__)) {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct {
    float r;
    float g;
    float b;
} fRGB;

typedef struct {
    float h;
    float s;
    float v;
} HSV;

typedef struct {
    ILuint image_name;

    int width;
    int height;
    int number_of_pixels;

    int byte_per_pixel;
    int format;

    float ratio;

    RGBA *original_pixels;
    RGBA *screen_pixels;
    HSV *hsv;
    fRGB *rgb;
} GLImage;

extern GLWindow mainWindow;
extern GLImage mainImage;

#endif //ONE_COLOR_GL_CONFIGURATION_H
