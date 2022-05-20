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

#ifndef ONE_COLOR_COLORS_H
#define ONE_COLOR_COLORS_H

#include "basic-data.h"

void evas_color_rgb_to_hsv_fk(int r, int g, int b, float *h, float *s, float *v);

void evas_color_rgb_to_hsv_ik(int r, int g, int b, int *h, int *s, int *v);

static inline void evas_color_RGBA_to_hsv(RGBA *rgba, HSV *hsv) {
    evas_color_rgb_to_hsv_fk(rgba->r,
                             rgba->g,
                             rgba->b,
                             &hsv->h,
                             &hsv->s,
                             &hsv->v);
}

static inline float get_hue_360f(const unsigned char R, const unsigned char G, const unsigned char B) {
    HSV   hsv;
    float hue;

    evas_color_rgb_to_hsv_fk((int) R,
                             (int) G,
                             (int) B,
                             &hsv.h,
                             &hsv.s,
                             &hsv.v);
    hue = hsv.h;
    if (hue < 0.0f) {
        hue += 360.0f;
    } else if (hue > 360.0f) {
        hue -= 360.0f;
    }
    return hue;
}

#endif //ONE_COLOR_COLORS_H
