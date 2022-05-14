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
// Created by bernard on 25/04/22.
//

#include <stdio.h>

#if defined(WITH_GL)
#include <GL/glut.h>

#include "GL-Configuration.h"
#elif defined(WITH_NUKE)

#include "ocn-configuration.h"

#endif

#include "debug.h"
#include "filtering.h"

void apply_grey_filter(void) {
    int  n              = main_image.number_of_pixels;
    RGBA *screen_pixels = main_image.screen_pixels;
    HSV  *hsv           = main_image.hsv;
    RGBA *original      = main_image.original_pixels;

    DBG();
    for (int i = 0; i < n; i++, screen_pixels++, hsv++, original++) {
        u8 value = float_to_u8(hsv->v * 255.0f);
        screen_pixels->r = value;
        screen_pixels->g = value;
        screen_pixels->b = value;
        screen_pixels->a = original->a;
    }
}

void apply_red_filter(void) {
    int  n              = main_image.number_of_pixels;
    RGBA *screen_pixels = main_image.screen_pixels;
    HSV  *hsv           = main_image.hsv;
    RGBA *original      = main_image.original_pixels;

    DBG();
    for (int i = 0; i < n; i++, screen_pixels++, hsv++, original++) {
        u8 value = float_to_u8(hsv->v * 255.0f);
        screen_pixels->r = value;
        screen_pixels->g = original->g;
        screen_pixels->b = original->b;
        screen_pixels->a = original->a;
    }
}

void apply_green_filter(void) {
    int  n              = main_image.number_of_pixels;
    RGBA *screen_pixels = main_image.screen_pixels;
    HSV  *hsv           = main_image.hsv;
    RGBA *original      = main_image.original_pixels;

    DBG();
    for (int i = 0; i < n; i++, screen_pixels++, hsv++, original++) {
        u8 value = float_to_u8(hsv->v * 255.0f);
        screen_pixels->r = original->r;
        screen_pixels->g = value;
        screen_pixels->b = original->b;
        screen_pixels->a = original->a;
    }
}

void apply_blue_filter(void) {
    int  n              = main_image.number_of_pixels;
    RGBA *screen_pixels = main_image.screen_pixels;
    HSV  *hsv           = main_image.hsv;
    RGBA *original      = main_image.original_pixels;

    DBG();
    for (int i = 0; i < n; i++, screen_pixels++, hsv++, original++) {
        u8 value = float_to_u8(hsv->v * 255.0f);
        screen_pixels->r = original->r;
        screen_pixels->g = original->g;
        screen_pixels->b = value;
        screen_pixels->a = original->a;
    }
}

void apply_shift1_filter(void) {
    int  n              = main_image.number_of_pixels;
    RGBA *screen_pixels = main_image.screen_pixels;
    HSV  *hsv           = main_image.hsv;
    RGBA *original      = main_image.original_pixels;

    DBG();
    for (int i = 0; i < n; i++, screen_pixels++, hsv++, original++) {
        screen_pixels->r = original->b;     // green
        screen_pixels->g = original->r;     // red
        screen_pixels->b = original->g;     // blue
        screen_pixels->a = original->a;
    }
}
