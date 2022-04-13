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

typedef struct {
#if defined(WITH_GLFW)
    GLFWwindow* window;
#else
    int window;
#endif
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
