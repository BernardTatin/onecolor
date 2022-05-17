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
// Created by bernard on 08/04/2022.
//

#include <stdbool.h>
#include <math.h>
#include <IL/il.h>
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-filters.h"

void bw_normal_function(struct _GLFilter *_parameters) {
    GLPFilterBWNormal *parameters = (GLPFilterBWNormal *) _parameters->parameters;
    int               n           = main_image.number_of_pixels;
    fRGB              *rgb        = main_image.rgb;
    RGBA              *rgba       = main_image.screen_pixels;
    const float       KlR         = parameters->KlR;
    const float       KlG         = parameters->KlG;
    const float       KlB         = parameters->KlB;

    for (int i = 0; i < n; i++, rgb++, rgba++) {
        u8 cLuma = float_to_u8(255.0f * (KlR * rgb->r + KlG * rgb->g + KlB * rgb->b));
        rgba->r = cLuma;
        rgba->g = cLuma;
        rgba->b = cLuma;
    }
    fprintf(stdout, "End of filter 'normal'\n");
}

void filter_bw_normal1(void) {
    bw_normal_function(&bw_normal1);
}

void filter_bw_normal2(void) {
    bw_normal_function(&bw_normal1);
}

void filter_bw_normal3(void) {
    bw_normal_function(&bw_normal3);
}

void bw_hard_function(struct _GLFilter *_parameters) {
    GLPFilterBWHard *parameters = (GLPFilterBWHard *) _parameters->parameters;
    int             n           = main_image.number_of_pixels;
    fRGB            *rgb        = main_image.rgb;
    RGBA            *rgba       = main_image.screen_pixels;
    const float     KlR         = 0.2627f;
    const float     KlG         = 0.6780f;
    const float     KlB         = 0.0593f;
    float           minLuma     = 300.0f;
    float           maxLuma     = 0.0f;
    float           average     = 0.0f;
    float           *greys      = (float *) malloc(n * sizeof(float));
    float           *pGreys     = greys;
    float           mid;
    u8              lr          = float_to_u8(255.0f * parameters->lightR),
                    lg          = float_to_u8(255.0f * parameters->lightG),
                    lb          = float_to_u8(255.0f * parameters->lightB),
                    dr          = float_to_u8(255.0f * parameters->darkR),
                    dg          = float_to_u8(255.0f * parameters->darkG),
                    db          = float_to_u8(255.0f * parameters->darkB);


    if (parameters->type == BWH_median) {
        for (int i = 0; i < n; i++, rgb++, pGreys++) {
            float luma = squeeze_round_float(
                    KlR * rgb->r + KlG * rgb->g + KlB * rgb->b,
                    0.0f, 1.0f);
            *pGreys = luma;
            if (luma > maxLuma) {
                maxLuma = luma;
            } else if (luma < minLuma) {
                minLuma = luma;
            }
        }
        mid        = 0.5f * (maxLuma + minLuma);
    } else {
        for (int i = 0; i < n; i++, rgb++, pGreys++) {
            float luma = squeeze_round_float(
                    KlR * rgb->r + KlG * rgb->g + KlB * rgb->b,
                    0.0f, 1.0f);
            *pGreys = luma;
            average += luma;
            if (luma > maxLuma) {
                maxLuma = luma;
            } else if (luma < minLuma) {
                minLuma = luma;
            }
        }
        mid        = average / (float) n;
    }
    fprintf(stdout, "luma: %5.3f, %5.3f, %5.3f\n",
            minLuma, mid, maxLuma);
    pGreys = greys;
    for (int i = 0; i < n; i++, pGreys++, rgba++) {
        if (*pGreys > mid) {
            rgba->r = lr;
            rgba->g = lg;
            rgba->b = lb;
        } else {
            rgba->r = dr;
            rgba->g = dg;
            rgba->b = db;
        }
    }
    free(greys);
}


void filter_bw_hard_black1(void) {
    bw_hard_function(&bw_hard_average);
}

void filter_bw_hard_black2(void) {
    bw_hard_function(&bw_hard_median);
}

void filter_bw_hard_blue(void) {
    bw_hard_function(&bw_hard_averageB);
}

void filter_bw_hard_red(void) {
    bw_hard_function(&bw_hard_averageR);
}

void filter_bw_hard_green(void) {
    bw_hard_function(&bw_hard_averageG);
}

void filter_average(void) {
    int         n     = main_image.number_of_pixels;
    fRGB        *rgb  = main_image.rgb;
    RGBA        *rgba = main_image.screen_pixels;
    const float k     = 255.0f / 3.0f;

    for (int i = 0; i < n; i++, rgb++, rgba++) {
        float luma = roundf(k * (rgb->r + rgb->g + rgb->b));
        if (luma > 255.0f) {
            luma = 255.0f;
        }
        u8 cLuma = (u8) luma;
        rgba->r = cLuma;
        rgba->g = cLuma;
        rgba->b = cLuma;
    }
    fprintf(stdout, "End of filter 'average'\n");
}
