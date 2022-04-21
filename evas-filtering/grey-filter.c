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
    int n = main_image.number_of_pixels;
    RGBA *rgb = main_image.screen_pixels;
    HSV *hsv = main_image.hsv;

    for (int i=0; i<n; i++, rgb++, hsv++) {
        u8 value = (int)roundf(hsv->v * 255.0f);
        rgb->r = value;
        rgb->g = value;
        rgb->b = value;
    }
    evas_object_image_size_set(main_data.image, main_image.width, main_image.height);
    evas_object_image_data_set(main_data.image, main_image.screen_pixels);
    evas_object_image_filled_set(main_data.image, EINA_TRUE);
}
