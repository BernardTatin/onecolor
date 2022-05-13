//
// Created by bernard on 25/04/22.
//

#include <stdio.h>
#if defined(WITH_EVAS)
#include <Ecore_Evas.h>

#include "evas-configuration.h"
#include "evas-tools.h"
#elif defined(WITH_GL)
#include <GL/glut.h>

#include "GL-Configuration.h"
#elif defined(WITH_NUKE)
#include "ocn-configuration.h"
#endif

#include "debug.h"
#include "filtering.h"

void apply_grey_filter(void) {
    int n = main_image.number_of_pixels;
#if defined(WITH_EVAS)
    Evas_Object *image = main_data.image;
    static BGRA *p_bgra = NULL;
    BGRA *screen_pixels = NULL;
    if (p_bgra == NULL) {
        DBG();
        p_bgra = (BGRA *) malloc(sizeof(BGRA) * n);
        DBG();
    }
    screen_pixels = p_bgra;
#else
    RGBA *screen_pixels = main_image.screen_pixels;
#endif
    HSV *hsv = main_image.hsv;
    RGBA *original = main_image.original_pixels;

    DBG();
    for (int i=0; i<n; i++, screen_pixels++, hsv++, original++) {
        u8 value = float_to_u8(hsv->v * 255.0f);
        screen_pixels->r = value;     // green
        screen_pixels->g = value;     // red
        screen_pixels->b = value;     // blue
        screen_pixels->a = original->a;
    }
#if defined(WITH_EVAS)
//    evas_object_image_size_set(image, main_image.width, main_image.height);
    DBG();
    evas_object_image_data_copy_set(image, p_bgra);
    DBG();
#endif
}
