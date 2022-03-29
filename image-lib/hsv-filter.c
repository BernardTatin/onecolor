//
// Created by bernard on 25/03/2022.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "color-tools.h"
#include "hsv-filter.h"

const float default_HSV_delta = 30.0f;

const float hsv_Red      =   0.0f;
const float hsv_Green    = 120.0f;
const float hsv_Blue     = 240.0f;
const float hsv_Yellow   =  60.0f;

HSVFilter main_HSV_filter = {
        hsv_Red,
        default_HSV_delta
};

typedef enum {
    CMaxR, CMaxG, CMaxB
} CMaxType;

static float mod_float(float x, const float m) {
    while (x < 0.0f) {
        x += m;
    }
    while (x >= m) {
        x -= m;
    }
    return x;
}

static float rgb2hue(const unsigned char R, const unsigned char G, const unsigned char B) {
    float hue = 0.0f;
    float fR = (float)R/255.0f;
    float fG = (float)G/255.0f;
    float fB = (float)B/255.0f;
    unsigned char cMax = R;
    unsigned char cMin = R;
    CMaxType mType = CMaxR;
    unsigned char delta = 0;
    float fDelta = 0.0f;
    if (G > R && G > B) {
        cMax = G;
        mType = CMaxG;
    } else if (B > R && B > G) {
        cMax = B;
        mType = CMaxB;
    }
    if (G < R && G < B) {
        cMin = G;
    } else if (B < R && B < G) {
        cMin = B;
    }
    delta = cMax - cMin;
    fDelta = (float)delta / 255.0f;
    if (delta == 0) {
       return hue;
    } else if (mType == CMaxR) {
        hue = 0.0f + (fG - fB) / fDelta;
    } else if (mType == CMaxG) {
        hue = 2.0f + (fB - fR) / fDelta;
    } else {
        hue = 4.0f + (fR - fG) / fDelta;
    }
    hue = 60.0f * hue;
//    fprintf(stdout, "RGB: %3u, %3u, %3u -> hue: %3.5f\n",
//            (unsigned)R, (unsigned)G, (unsigned)B,
//            hue);
    // hue = mod_float(60.0f * hue, 360.0f);
    return hue;
}

ImageLib_Error hsv_filter(
        const HSVFilter *filter,
        ImageLib_RawImage* lpInput,
        ImageLib_RawImage** lpOutput) {
    unsigned long int pixelNumber = lpInput->width*lpInput->height;

    fprintf(stdout, "hue = %3.5f, delta = %3.5f\n",
            filter->h, filter->delta);
    (*lpOutput) = make_lpOutput(lpInput);

    for(unsigned int i = 0; i < pixelNumber; i++) {
        unsigned long int i3 = i*3;
        bool inFilter = false;
        float hue = rgb2hue(Rin(i3), Gin(i3), Bin(i3) );
        float minHue = mod_float(filter->h - filter->delta, 360.0f);
        float maxHue = mod_float(filter->h + filter->delta, 360.0f);
        if (minHue < maxHue) {
            inFilter = (hue <= maxHue) && (hue >= minHue);
        } else {
            inFilter = (hue <= maxHue) || (hue >= minHue);
        }
        if (inFilter) {
            Rout(i3) = Rin(i3);
            Gout(i3) = Gin(i3);
            Bout(i3) = Bin(i3);
        } else {
            unsigned char luma = (unsigned char) getLuma(Rin(i3), Gin(i3), Bin(i3));
            Rout(i3) = luma;
            Gout(i3) = luma;
            Bout(i3) = luma;
        }
    }

    return imageLibE_Ok;

}
