//
// Created by bernard on 24/03/2022.
//

#ifndef ONECOLOR_COLOR_TOOLS_H
#define ONECOLOR_COLOR_TOOLS_H

#include <stdbool.h>
#include <math.h>

#include "color-data.h"

#define Rin(i3) lpInput->lpData[i3 + 0]
#define Gin(i3) lpInput->lpData[i3 + 1]
#define Bin(i3) lpInput->lpData[i3 + 2]

#define Rout(i3) (*lpOutput)->lpData[i3 + 0]
#define Gout(i3) (*lpOutput)->lpData[i3 + 1]
#define Bout(i3) (*lpOutput)->lpData[i3 + 2]


static inline imgRawImage* make_lpOutput(imgRawImage* lpInput) {
    imgRawImage* lpOutput;

    lpOutput = malloc(sizeof(imgRawImage));
    lpOutput->width = lpInput->width;
    lpOutput->height = lpInput->height;
    lpOutput->numComponents = lpInput->numComponents;
    lpOutput->lpData = malloc(sizeof(unsigned char) * lpInput->width*lpInput->height*3);
    return lpOutput;
}
static inline bool isRed(unsigned char R, unsigned char G, unsigned char B) {
    return (KlR*(float)R > KlG*(float)G) && (KlR*(float)R > KlG*(float)B);
}

static inline bool isYellow(unsigned char R, unsigned char G, unsigned char B) {
    float yDiff = fabsf(KlR*(float)R - KlG*(float)G);
    float yellow = KlR*(float)R + KlG*(float)G;
    if (yDiff >= 255.0f) {
        fprintf(stderr, "Yellow diff: %3.5f, R: %3u, G: %3u\n",
                yDiff, R, G);
    }
    return (yDiff < 31.0f) && (yellow > (float)B);
}
static inline float getLuma(unsigned char R, unsigned char G, unsigned char B) {
    return roundf(KlR * (float)R + KlG * (float)G + KlB * (float)B);
}

#endif //ONECOLOR_COLOR_TOOLS_H
