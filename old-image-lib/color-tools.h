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


static inline ImageLib_RawImage *make_lpOutput(ImageLib_RawImage *lpInput) {
    ImageLib_RawImage *lpOutput;

    lpOutput = malloc(sizeof(ImageLib_RawImage));
    lpOutput->width         = lpInput->width;
    lpOutput->height        = lpInput->height;
    lpOutput->numComponents = lpInput->numComponents;
    lpOutput->lpData        = malloc(sizeof(unsigned char) * lpInput->width * lpInput->height * 3);
    return lpOutput;
}

static inline float getLuma(const unsigned char R, const unsigned char G, const unsigned char B) {
    return roundf(KlR * (float) R + KlG * (float) G + KlB * (float) B);
}

#endif //ONECOLOR_COLOR_TOOLS_H
