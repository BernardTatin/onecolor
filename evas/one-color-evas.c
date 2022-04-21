// images.c
// bernard TaTiN
// 2022-04-17
//
// from the source code of evas-images.c
//

#define _GNU_SOURCE

#include <stdbool.h>
#include <IL/il.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Ecore.h>
#include <Ecore_Evas.h>

#include "evas-configuration.h"
#include "dev-IL-tools.h"
#include "evas-scene.h"
#include "widgets.h"

static char *get_base_name(const char *full_file_name) {
    char *tmp_file_name = strdup(full_file_name);
    char *base_name = strdup(basename(tmp_file_name));
    free(tmp_file_name);
    return base_name;
}

static void on_destroy(Ecore_Evas *ee EINA_UNUSED) {
    ecore_main_loop_quit();
}

/* Keep the example's window size in sync with the background image's size */
static void canvas_resize_cb(Ecore_Evas *ee) {
    int w, h;

    ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
    resize_scene(&main_scene, w, h);
//    evas_object_resize(main_data.background, w, h);
//    resize_image(w - 2 * dx, h - 2 * dy);
//    resize_text(w, h);
}

static void on_key_down(void *data EINA_UNUSED,
                        Evas *evas EINA_UNUSED,
                        Evas_Object *o EINA_UNUSED,
                        void *event) {
    Evas_Event_Key_Down *ev = event;
    const char *the_key = ev->key;
    Eina_Bool control = evas_key_modifier_is_set(ev->modifiers, "Control");
//    Eina_Bool alt = evas_key_modifier_is_set(ev->modifiers, "Alt");
//    Eina_Bool shift = evas_key_modifier_is_set(ev->modifiers, "Shift");

    if (*(the_key + 1) == 0) {
        switch (*the_key) {
            case 'q':
                if (control) {
                    on_destroy(main_data.ecore_evas);
                }
                break;
            case 's':
                if (control) {
                    evas_object_image_save(main_data.image,
                                           img_destination,
                                           NULL,
                                           "quality=100 compress=8");
                }
                break;
            default:
                fprintf(stdout, "key %d (%c)\n",
                        (int)*the_key,
                        *the_key);
                break;

        }
    } else {
        if (strcmp(the_key, "Escape") == 0) {
            on_destroy(main_data.ecore_evas);
        } else {
            fprintf(stdout, "key %d %d (%s)\n",
                    (int) *the_key, (int) *(the_key + 1), the_key);
        }
    }
}

int main(const int argc, char **argv) {
    program_name = get_base_name(argv[0]);
    if (argc != 3) {
        fprintf(stderr, "Usage: %s image_source image_destination\n",
                program_name);
        return EXIT_FAILURE;
    }

    img_source = argv[1];
    img_base_source = get_base_name(img_source);
    img_destination = argv[2];

    if (!init_DevIL()) {
        fprintf(stderr, "FATAL: cannot initialize DevIL!\n");
        return EXIT_FAILURE;
    }
    /* load the file picture with DevIL */
    if (!LoadImage(&mainImage, argv[1])) {
        fprintf(stderr, "Can't load picture file %s by DevIL\n", argv[1]);
        return -1;
    }
    fprintf(stdout, "\nImage bits/pix: %d, width: %d, height: %d, format: %d\n",
            mainImage.byte_per_pixel,
            mainImage.width,
            mainImage.height,
            mainImage.format);
    if (!ecore_evas_init()) {
        fprintf(stderr, "FATAL: cannot initialize ecore_evas\n");
        return EXIT_FAILURE;
    }

    /* this will give you a window with an Evas canvas under the first
     * engine available */
    main_data.ecore_evas = ecore_evas_new(
            NULL,
            10, 10,
            default_width, default_height,
            NULL);
    if (!main_data.ecore_evas) {
        goto error;
    }

    ecore_evas_callback_destroy_set(main_data.ecore_evas, on_destroy);
    ecore_evas_callback_resize_set(main_data.ecore_evas, canvas_resize_cb);
    ecore_evas_show(main_data.ecore_evas);

    /* the canvas pointer, de facto */
    main_data.evas = ecore_evas_get(main_data.ecore_evas);


    main_data.background = widget_background(main_data.evas)->evas_object;
    main_data.image = widget_picture(main_data.evas)->evas_object;
    main_data.txt_key_help = widget_key_text(main_data.evas)->evas_object;

    evas_object_focus_set(main_data.background, EINA_TRUE);
    evas_object_event_callback_add(
            main_data.background,
            EVAS_CALLBACK_KEY_DOWN,
            on_key_down,
            NULL);

    resize_scene(&main_scene, default_width, default_height);
    show_scene(&main_scene);

    /*
     * main loop
     */
    ecore_main_loop_begin();

    /*
     * end of the world
     */
    ecore_evas_free(main_data.ecore_evas);
    ecore_evas_shutdown();
    return EXIT_SUCCESS;
error:
    fprintf(stderr, "error: Requires at least one Evas engine built and linked"
                    " to ecore-evas for this example to run properly.\n");
    ecore_evas_shutdown();
    return EXIT_FAILURE;
}
