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
// Created by bernard on 21/03/2022.
// from:
//      https://www.tspi.at/2020/03/20/libjpegexample.html
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


#include "color-data.h"
#include "color-tools.h"
#include "filters.h"
#include "hsv-filter.h"
#include "main-configuration.h"

ImageLib_Error filter_gray_scale(ImageLib_RawImage *lpInput, ImageLib_RawImage **lpOutput) {
    unsigned long int pixelNumber = lpInput->width * lpInput->height;
    (*lpOutput) = make_lpOutput(lpInput);

    for (unsigned int i = 0; i < pixelNumber; i++) {
        /* Do a grayscale transformation */
        unsigned long i3   = i * 3;
        unsigned char luma = (unsigned char) getLuma(Rin(i3), Gin(i3), Bin(i3));
        Rout(i3) = luma;
        Gout(i3) = luma;
        Bout(i3) = luma;
    }

    return imageLibE_Ok;
}

ImageLib_Error exec_filter(ImageLib_RawImage *lpInput, ImageLib_RawImage **lpOutput) {
    switch (global_configuration.type) {
        case Filter_Grey:
            return filter_gray_scale(lpInput, lpOutput);
        case Filter_Red:
            global_configuration.hue = hsv_Red;
            return filter_hue(lpInput, lpOutput);
        case Filter_Green:
            global_configuration.hue = hsv_Green;
            return filter_hue(lpInput, lpOutput);
        case Filter_Blue:
            global_configuration.hue = hsv_Blue;
            return filter_hue(lpInput, lpOutput);
        case Filter_Yellow:
            global_configuration.hue = hsv_Yellow;
            return filter_hue(lpInput, lpOutput);
        case Filter_Hue:
            return filter_hue(lpInput, lpOutput);
        default:
            fprintf(stderr, "FATAL ERROR: unknown filter\n");
            exit(1);
    }
}
