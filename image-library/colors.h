//
// Created by bernard on 25/04/22.
//

#ifndef ONE_COLOR_COLORS_H
#define ONE_COLOR_COLORS_H

#include "basic-data.h"

void evas_color_rgb_to_hsv_k(int r, int g, int b, float *h, float *s, float *v);
void evas_rgb_to_hsv_int_k(int r, int g, int b, int *h, int *s, int *v);

static inline void evas_color_RGBA_to_hsv(RGBA *rgba, HSV *hsv) {
    evas_color_rgb_to_hsv_k(rgba->r,
                            rgba->g,
                            rgba->b,
                            &hsv->h,
                            &hsv->s,
                            &hsv->v);
}

static inline void evas_color_BGRA_to_hsv(BGRA *bgra, HSV *hsv) {
    evas_color_rgb_to_hsv_k(bgra->r,
                            bgra->g,
                            bgra->b,
                            &hsv->h,
                            &hsv->s,
                            &hsv->v);
}
#endif //ONE_COLOR_COLORS_H
