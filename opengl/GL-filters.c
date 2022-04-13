//
// Created by bernard on 08/04/2022.
//

#include <stdbool.h>
#include <math.h>
#include <IL/il.h>
#if defined(WITH_GLFW)
#include <GLFW/glfw3.h>
#else
#endif
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-filters.h"

void bw_normal_function(struct _GLFilter *_parameters) {
    GLPFilterBWNormal *parameters = (GLPFilterBWNormal *)_parameters->parameters;
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float KlR = parameters->KlR;
    const float KlG = parameters->KlG;
    const float KlB = parameters->KlB;


    for (int i=0; i<n; i++, rgb++, rgba++) {
        float luma = roundf(255.0f * (KlR * rgb->r + KlG * rgb->g + KlB * rgb->b));
        if (luma > 255.0f) {
            luma = 255.0f;
        }
        u8 cLuma = (u8)luma;
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
    bw_normal_function(&bw_normal2);
}

void filter_bw_normal3(void) {
    bw_normal_function(&bw_normal3);
}

void bw_hard_function(struct _GLFilter *_parameters) {
    GLPFilterBWHard *parameters = (GLPFilterBWHard *)_parameters->parameters;
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float KlR = 0.2627f;
    const float KlG = 0.6780f;
    const float KlB = 0.0593f;
    float minLuma = 300.0f;
    float maxLuma = 0.0f;
    float average = 0.0f;
    float *greys = (float *) malloc(n * sizeof(float));
    float *pGreys = greys;
    float mid;
    float lr = roundf(255.0f * parameters->lightR),
            lg = roundf(255.0f * parameters->lightG),
            lb = roundf(255.0f * parameters->lightB),
            dr = roundf(255.0f * parameters->darkR),
            dg = roundf(255.0f * parameters->darkG),
            db = roundf(255.0f * parameters->darkB);


    if (parameters->type == BWH_median) {
        for (int i=0; i<n; i++, rgb++, pGreys++) {
            float luma = roundf(255.0f * (KlR * rgb->r + KlG * rgb->g + KlB * rgb->b));
            if (luma > 255.0f) {
                luma = 255.0f;
            }
            *pGreys = luma;
            if (luma > maxLuma) {
                maxLuma = luma;
            } else if (luma < minLuma) {
                minLuma = luma;
            }
        }
        mid = 0.5f * (maxLuma + minLuma);
    } else {
        for (int i=0; i<n; i++, rgb++, pGreys++) {
            float luma = roundf(255.0f * (KlR * rgb->r + KlG * rgb->g + KlB * rgb->b));
            if (luma > 255.0f) {
                luma = 255.0f;
            }
            *pGreys = luma;
            average += luma;
        }
        mid = average / (float)n;
    }
    pGreys = greys;
    for (int i=0; i<n; i++, pGreys++, rgba++) {
        if (*pGreys > mid) {
            rgba->r = (u8)lr;
            rgba->g = (u8)lg;
            rgba->b = (u8)lb;
        } else {
            rgba->r = (u8)dr;
            rgba->g = (u8)dg;
            rgba->b = (u8)db;
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
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float k = 255.0f / 3.0f;

    for (int i=0; i<n; i++, rgb++, rgba++) {
        float luma = roundf(k * (rgb->r + rgb->g + rgb->b));
        if (luma > 255.0f) {
            luma = 255.0f;
        }
        u8 cLuma = (u8)luma;
        rgba->r = cLuma;
        rgba->g = cLuma;
        rgba->b = cLuma;
    }
    fprintf(stdout, "End of filter 'average'\n");
}
