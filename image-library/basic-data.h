/******************************************************************************
 * MIT License                                                                *
 *                                                                            *
 * Copyright (c) 2022.  Bernard Tatin                                         *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.                            *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.                                                                  *
 ******************************************************************************/

//
// Created by bernard on 22/04/22.
//

#ifndef ONE_COLOR_BASIC_DATA_H
#define ONE_COLOR_BASIC_DATA_H

#include <IL/il.h>

#if defined(WITH_GL)
#include <GL/glut.h>
#endif

#include <math.h>

#include "basic-types.h"

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
    HSV  *hsv;
    fRGB *rgb;
} TheImage;

extern TheImage main_image;

static inline u8 float_to_u8(const float x) {
    int ix = (int) roundf(x);
    if (ix > 255) {
        return (u8) 255;
    } else if (ix < 0) {
        return (u8) 0;
    } else {
        return (u8) ix;
    }
}

static inline float u8_to_unit(u8 v) {
    static const float u_factor = 1.0f / 255.0f;
    return (float) v * u_factor;
}

static inline float unit_to_u8(float v) {
    return float_to_u8(v * 255.0f);
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
