//
// Created by bernard on 19/04/22.
//

#include <stdbool.h>
#include <IL/il.h>
#include <stdio.h>
#include <stdlib.h>
#include <Ecore_Evas.h>

#include "evas-configuration.h"
#include "dev-IL-tools.h"

static void fill_pixels_buffers(EV_image *image) {
    image->width = ilGetInteger(IL_IMAGE_WIDTH);
    image->height = ilGetInteger(IL_IMAGE_HEIGHT);
    int n = image->width * image->height;
    image->number_of_pixels = n;
    image->byte_per_pixel = ilGetInteger(IL_IMAGE_BPP);
    image->format = ilGetInteger(IL_IMAGE_FORMAT);
    image->ratio = (float)image->width / (float)image->height;
    image->original_pixels = (RGBA *)ilGetData();
    image->screen_pixels = (RGBA *)malloc(n * sizeof(RGBA));
    ilCopyPixels(0, 0, 0,
                 image->width, image->height,
                 1,
                 IL_RGBA, IL_UNSIGNED_BYTE,
                 image->screen_pixels);
    image->hsv = (HSV *) malloc(n * sizeof(HSV));
    image->rgb = (fRGB *) malloc(n * sizeof(fRGB));

    RGBA *pixels = image->original_pixels;
    HSV *hsv = image->hsv;
    fRGB *rgb = image->rgb;
    for (int i=0; i<n; i++, pixels++, rgb++, hsv++) {
        rgb->r = (float)pixels->r / 255.0f;
        rgb->g = (float)pixels->g / 255.0f;
        rgb->b = (float)pixels->b / 255.0f;
    }
}

/* Initialization of DevIL */
bool init_DevIL(void) {
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
        fprintf(stderr, "wrong DevIL version\n");
        return false;
    }
    ilInit();
    return true;
}

bool LoadImage(EV_image *image, char *filename) {
    ILboolean success;

    ilGenImages(1, &(image->image_name));    /* Generation of one image name */
    ilBindImage(image->image_name);        /* Binding of image name */


    /* Loading of the image filename by DevIL */
    success = ilLoadImage(filename);
    if (success) {
        /* Convert every colour component into unsigned byte */
        /* You can replace IL_RGB with IL_RGBA if your image contains alpha channel */

        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        if (!success) {
            return false;
        }
    } else
        return false;

    fill_pixels_buffers(image);
    return true;
}