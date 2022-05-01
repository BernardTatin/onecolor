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
// Created by bernard on 26/04/22.
//

#include <stdio.h>
#include "basic-geometry.h"
#include "image-tools.h"

#define _dbg_

// FIXME: ya1BUGGG le redimensionnement n'est pas bon AVEC OenGL
void scale_image(const OCDimensions canvas_dimensions, const float ratio, OCRectangle *pict_rectangle) {
#if defined(_dbg_)
    static int       kk = 0;
    static const int m  = 128;
#endif
    int   left   = 0;
    int   top    = 0;
    int   width  = canvas_dimensions.width;
    int   height = canvas_dimensions.height;
    float nw     = (float) width;
    float nh     = nw / ratio;

    if (nh > (float) height) {
        nh = (float) height;
        nw = (float) nh * ratio;
        if (nw > (float) width) {
            fprintf(stderr, "Resize image: nw > width (%d > %d)\n",
                    (int) roundf(nw), width);
        }
    }
    left         = (int) fabsf(roundf(0.5f * (nw - (float) canvas_dimensions.width)));
    top          = (int) fabsf(roundf(0.5f * (nh - (float) canvas_dimensions.height)));
    pict_rectangle->left   = left;
    pict_rectangle->top    = top;
    pict_rectangle->width  = (int) nw;
    pict_rectangle->height = (int) nh;
#if defined(_dbg_)
    if (kk == 0) {
        fprintf(stdout, "Ratio %5.3f -> %5.3f\n", ratio, nw / nh);
    }
    kk++;
    kk &= m - 1;
#endif
}
