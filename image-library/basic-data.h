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

#include <math.h>

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

extern TheImage main_image;

static inline u8 float_to_u8(const float x) {
    int ix = (int) roundf(x);
    if (ix > 255) {
        return (u8)255;
    } else if (ix < 0) {
        return (u8)0;
    } else {
        return (u8)ix;
    }
}

static inline float squeeze_float(const float x, const float min, const float max) {
    if (x < min) {
        return min;
    } else if (x > max) {
        return max;
    } else {
        return x;
    }
}

static inline float squeeze_round_float(const float x, const float min, const float max) {
    return squeeze_float(roundf(x), min, max);
}

#endif //ONE_COLOR_BASIC_DATA_H
