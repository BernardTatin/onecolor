//
// Created by bernard on 26/04/22.
//

#include <stdio.h>
#include "basic-geometry.h"
#include "image-tools.h"

// FIXME: ya1BUGGG le redimensionnement n'est pas bon AVEC OenGL
void scale_mage(const OCDimensions dimensions, OCRectangle *rectangle) {
    int left = 0;
    int top = 0;
    int width = dimensions.width;
    int height = dimensions.height;
    float ratio = main_image.ratio;
    float nw = (float)width;
    float nh = nw / ratio;

    if (nh > (float)height) {
        nh = (float)height;
        nw = (float)nh * ratio;
        if (nw > (float)width) {
            fprintf(stderr, "Resize image: nw > width (%d > %d)\n",
                    (int)roundf(nw), width);
        }
    }
    left = (int)fabsf(roundf(0.5f * (nw - (float)dimensions.width)));
    top = (int)fabsf(roundf(0.5f * (nh - (float)dimensions.height)));
    rectangle->left   = left;
    rectangle->top    = top;
    rectangle->width  = (int)nw;
    rectangle->height = (int)nh;
    fprintf(stdout, "Ratio %5.3f -> %5.3f\n", ratio, nw / nh);
}
