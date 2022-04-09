//
// Created by bernard on 08/04/2022.
//

#include <stdbool.h>
#include <math.h>
#include <IL/il.h>
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-filters.h"

void filter_bw_normal1(void) {
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float KlR = 0.299f;
    const float KlG = 0.587f;
    const float KlB = 0.114f;


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

void filter_bw_normal2(void) {
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float KlR = 0.2126f;
    const float KlG = 0.7152f;
    const float KlB = 0.0722f;

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

void filter_bw_normal3(void) {
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float KlR = 0.2627f;
    const float KlG = 0.6780f;
    const float KlB = 0.0593f;

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

static void filter_bw_medianne(const u8 r, const u8 g, const u8 b) {
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float KlR = 0.2627f;
    const float KlG = 0.6780f;
    const float KlB = 0.0593f;
    float minLuma = 300.0f;
    float maxLuma = 0.0f;
    float *greys = (float *) malloc(n * sizeof(float));
    float *pGreys = greys;

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
    float mid = 0.5f * (maxLuma + minLuma);
    pGreys = greys;
    for (int i=0; i<n; i++, pGreys++, rgba++) {
        if (*pGreys > mid) {
            rgba->r = (u8)255;
            rgba->g = (u8)255;
            rgba->b = (u8)255;
        } else {
            rgba->r = (u8)r;
            rgba->g = (u8)g;
            rgba->b = (u8)b;
        }
    }
    free(greys);
    fprintf(stdout, "End of filter 'hard 1'\n");
}

void filter_bw_hard_black1(void) {
    filter_bw_medianne(0, 0, 0);
}

void filter_bw_hard_black2(void) {
    int n = mainImage.number_of_pixels;
    fRGB *rgb = mainImage.rgb;
    RGBA *rgba = mainImage.screen_pixels;
    const float KlR = 0.2627f;
    const float KlG = 0.6780f;
    const float KlB = 0.0593f;
    float average = 0.0f;
    float *greys = (float *) malloc(n * sizeof(float));
    float *pGreys = greys;

    for (int i=0; i<n; i++, rgb++, pGreys++) {
        float luma = roundf(255.0f * (KlR * rgb->r + KlG * rgb->g + KlB * rgb->b));
        if (luma > 255.0f) {
            luma = 255.0f;
        }
        *pGreys = luma;
        average += luma;
    }
    float mid = average / (float)n;
    pGreys = greys;
    for (int i=0; i<n; i++, pGreys++, rgba++) {
        if (*pGreys > mid) {
            rgba->r = (u8)255;
            rgba->g = (u8)255;
            rgba->b = (u8)255;
        } else {
            rgba->r = (u8)0;
            rgba->g = (u8)0;
            rgba->b = (u8)0;
        }
    }
    free(greys);
    fprintf(stdout, "End of filter 'hard 1'\n");
}

void filter_bw_hard_blue(void) {
    filter_bw_medianne(0, 0, 120);
}

void filter_bw_hard_red(void) {
    filter_bw_medianne(120, 0, 0);
}

void filter_bw_hard_green(void) {
    filter_bw_medianne(0, 120, 0);
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
