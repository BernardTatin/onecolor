//
// Created by bernard on 25/03/2022.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "color-tools.h"
#include "hsv-filter.h"

HSVFilter hsvRed = {0.0f, 5.0f};
HSVFilter hsvGreen = {120.0f, 5.0f};
HSVFilter hsvBlue = {240.0f, 5.0f};
HSVFilter hsvYellow = {60.0f, 5.0f};

static float modF(float x, float m) {
    while (x < 0.0f) {
        x += m;
    }
    while (x >= m) {
        x -= m;
    }
    return x;
}
static float rgb2hue(unsigned char R, unsigned char G, unsigned char B) {
    float hue = 0.0f;
    float fR = (float)R/255.0f;
    float fG = (float)G/255.0f;
    float fB = (float)B/255.0f;
    unsigned char cMax = R;
    unsigned char cMin = R;
    unsigned char delta = 0;
    float fDelta = 0.0f;
    if (G > R && G > B) {
        cMax = G;
    } else if (B > R && B > G) {
        cMax = B;
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
    } else if (cMax == R) {
        hue = (fG - fB) / fDelta;
    } else if (cMax == G) {
        hue = 2.0f + (fB - fR) / fDelta;
    } else {
        hue = 4.0f + (fR - fG) / fDelta;
    }
    hue = modF(60.0f * hue, 360.0f);
    return hue;
}

imageLibraryError hsvFilter(
        HSVFilter *filter,
        imgRawImage* lpInput,
        imgRawImage** lpOutput) {
    unsigned long int i;

    if(lpOutput == NULL) {
        (*lpOutput) = lpInput; /* We will replace our input structure ... */
    } else {
        (*lpOutput) = make_lpOutput(lpInput);
    }

    for(i = 0; i < lpInput->width*lpInput->height; i=i+1) {
        /* Do a grayscale transformation */
        unsigned long int i3 = i*3;
        bool inFilter = false;
        float hue = rgb2hue(Rin(i3), Gin(i3), Bin(i3) );
        float minHue = modF(filter->h - filter->delta, 360.0f);
        float maxHue = modF(filter->h + filter->delta, 360.0f);
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
