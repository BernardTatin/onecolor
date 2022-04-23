//
// Created by bernard on 22/04/22.
//

#ifndef ONE_COLOR_BASIC_DATA_H
#define ONE_COLOR_BASIC_DATA_H

#include <IL/il.h>
#if defined(WITH_EVAS)
#include <Ecore.h>
#include <Ecore_Evas.h>
#elif defined(WITH_GL)
#include <GL/glut.h>
#endif


typedef unsigned char u8;
typedef struct __attribute__((__packed__)) {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct __attribute__((__packed__)) {
    u8 b;
    u8 g;
    u8 r;
    u8 a;
} BGRA;

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
#if !defined(WITH_EVAS)
    RGBA *screen_pixels;
#else
    BGRA *screen_pixels;
#endif
    HSV *hsv;
    fRGB *rgb;
}  TheImage;


#endif //ONE_COLOR_BASIC_DATA_H
