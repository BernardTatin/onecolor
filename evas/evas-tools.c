//
// Created by bernard on 21/04/22.
//

#include <stdbool.h>
#include <IL/il.h>
#include <stdio.h>
#include <stdlib.h>
#include <Ecore.h>
#include <Ecore_Evas.h>

#include "evas-configuration.h"
#include "evas-scene.h"
#include "evas-tools.h"

void on_destroy(Ecore_Evas *ee EINA_UNUSED) {
    ecore_main_loop_quit();
}

/* Keep the example's window size in sync with the background image's size */
void canvas_resize(Ecore_Evas *ee) {
    int w, h;

    ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
    resize_scene(&main_scene, w, h);
}

bool init_evas(void) {

    if (!ecore_evas_init()) {
        fprintf(stderr, "FATAL: cannot initialize ecore_evas\n");
        exit(EXIT_FAILURE);
    }

    /* this will give you a window with an Evas canvas under the first
     * engine available */
    main_data.ecore_evas = ecore_evas_new(
            NULL,
            10, 10,
            default_width, default_height,
            NULL);
    if (!main_data.ecore_evas) {
        return false;
    }
    ecore_evas_callback_destroy_set(main_data.ecore_evas, on_destroy);
    ecore_evas_callback_resize_set(main_data.ecore_evas, canvas_resize);
    /* the canvas pointer, de facto */
    main_data.evas = ecore_evas_get(main_data.ecore_evas);

    return true;
}
