//
// Created by bernard on 25/04/22.
// code from Enlightenment efl-1.26.2
//      ./src/lib/evas/common/evas_convert_color.c
//

#include "colors.h"

void evas_color_rgb_to_hsv_k(int r, int g, int b, float *h, float *s, float *v) {
    int max, min, d = r - g;

    //set min to MIN(g,r)
    d = (d & (~(d >> 8)));
    min = r - d;
    //set max to MAX(g,r)
    max = g + d;

    //set min to MIN(b,min)
    d = min - b;
    min -= (d & (~(d >> 8)));

    //set max to MAX(max,b)
    d = b - max;
    max += (d & (~(d >> 8)));

    d = max - min;

    if (v) *v = (max / 255.0);
    if (!max || !d) {
        if (s) *s = 0;
        if (h) *h = 0;
        return;
    }

    if (s) *s = (d / (float) max);
    if (r == max) {
        if (h) {
            *h = 60 * ((g - b) / (float) d);
            if (*h < 0) *h += 360;
        }
        return;
    }
    if (g == max) {
        if (h) {
            *h = 120 + (60 * ((b - r) / (float) d));
            if (*h < 0) *h += 360;
        }
        return;
    }
    if (h) {
        *h = 240 + (60 * ((r - g) / (float) d));
        if (*h < 0) *h += 360;
    }
}

void evas_rgb_to_hsv_int_k(int r, int g, int b, int *h, int *s, int *v) {
    int min, max, d = r - g;

    d = (d & (~(d >> 8)));
    min = r - d;
    max = g + d;

    d = min - b;
    min -= (d & (~(d >> 8)));

    d = b - max;
    max += (d & (~(d >> 8)));

    d = max - min;

    *v = max;
    if (!max) {
        *s = *h = 0;
        return;
    }

    *s = ((d * 255) / max);

    if (r == max) {
        *h = (((g - b) * 255) / d);
        if (*h < 0) *h += 1530;
        return;
    }
    if (g == max) {
        *h = 510 + (((b - r) * 255) / d);
        if (*h < 0) *h += 1530;
        return;
    }
    *h = 1020 + (((r - g) * 255) / d);
    if (*h < 0) *h += 1530;
}
