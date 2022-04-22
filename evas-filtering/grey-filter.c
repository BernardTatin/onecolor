//
// Created by bernard on 21/04/22.
//

#include <stdbool.h>
#include <IL/il.h>
#include <stdio.h>
#include <stdlib.h>
#include <Ecore.h>
#include <math.h>
#include <Ecore_Evas.h>

#include "evas-configuration.h"
#include "evas-scene.h"
#include "evas-tools.h"
#include "grey-filter.h"

void apply_grey_filter(void) {
    Evas_Object *image = main_data.image;
    int n = main_image.number_of_pixels;
#if defined(WITH_EVAS)
    BGRA *bgra = evas_object_image_data_get(image, EINA_TRUE);
#else
    RGBA *bgra = main_image.screen_pixels;
#endif
    HSV *hsv = main_image.hsv;
    RGBA *original = main_image.original_pixels;

    for (int i=0; i<n; i++, bgra++, hsv++, original++) {
        u8 value = float_to_u8(hsv->v * 255.0f);
        bgra->r = value;     // green
        bgra->g = value;     // red
        bgra->b = value;     // blue
        bgra->a = original->a;
    }
//    evas_object_image_size_set(image, main_image.width, main_image.height);
//    evas_object_image_data_set(image, main_image.screen_pixels);
//    evas_object_image_filled_set(image, EINA_TRUE);
}
