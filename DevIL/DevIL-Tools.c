//
// Created by bernard on 13/04/2022.
//

#include <stdbool.h>
#include <math.h>
#include <IL/il.h>
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-menus.h"
#include "DevIL-Tools.h"

bool DevIL_init(void) {
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
        fprintf(stderr, "wrong DevIL version\n");
        return false;
    }
    fprintf(stdout, "DevIL version num %d, DevIL version %d\n",
            ilGetInteger(IL_VERSION_NUM), IL_VERSION);
    ilInit();
    return true;
}

static void fill_pixels_buffers(GLImage *image) {
    int n = image->number_of_pixels;
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

/* Load an image using DevIL and return the devIL handle (-1 if failure) */
bool LoadImage(GLImage *image, char *filename) {
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
    fill_pixels_buffers(image);
    return true;
}
