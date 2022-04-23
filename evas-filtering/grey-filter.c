//
// Created by bernard on 21/04/22.
//

#include <IL/il.h>
#include <stdio.h>
#include <stdlib.h>
#include <Ecore_Evas.h>

#include "debug.h"
#include "evas-configuration.h"
#include "evas-tools.h"
#include "grey-filter.h"

void apply_grey_filter(void) {
    int n = main_image.number_of_pixels;
#if defined(WITH_EVAS)
    Evas_Object *image = main_data.image;
    static BGRA *p_bgra = NULL;
    BGRA *bgra = NULL;
    if (p_bgra == NULL) {
        DBG();
        p_bgra = (BGRA *) malloc(sizeof(BGRA) * n);
        DBG();
    }
    bgra = p_bgra;
#else
    RGBA *p_bgra = main_image.screen_pixels;
#endif
    HSV *hsv = main_image.hsv;
    RGBA *original = main_image.original_pixels;

    DBG();
    for (int i=0; i<n; i++, bgra++, hsv++, original++) {
        u8 value = float_to_u8(hsv->v * 255.0f);
        bgra->r = value;     // green
        bgra->g = value;     // red
        bgra->b = value;     // blue
        bgra->a = original->a;
    }
#if defined(WITH_EVAS)
//    evas_object_image_size_set(image, main_image.width, main_image.height);
    DBG();
    evas_object_image_data_copy_set(image, p_bgra);
    DBG();
#endif
}
