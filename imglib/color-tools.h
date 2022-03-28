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
static inline float getLuma(const unsigned char R, const unsigned char G, const unsigned char B) {
    return roundf(KlR * (float)R + KlG * (float)G + KlB * (float)B);
}

#endif //ONECOLOR_COLOR_TOOLS_H
