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

static char *get_base_name(const char *full_file_name) {
    char *tmp_file_name = strdup(full_file_name);
    char *base_name = strdup(basename(tmp_file_name));
    free(tmp_file_name);
    return base_name;
}

static void _on_destroy(Ecore_Evas *ee EINA_UNUSED) {
    ecore_main_loop_quit();
}

/* Keep the example's window size in sync with the background image's size */
static void _canvas_resize_cb(Ecore_Evas *ee) {
    int w, h;

    ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
    evas_object_resize(main_data.background, w, h);
    evas_object_resize(main_data.image, w - 2 * dx, h - 2 * dy);
}

static void _on_keydown(void *data EINA_UNUSED,
                        Evas *evas EINA_UNUSED,
                        Evas_Object *o EINA_UNUSED,
                        void *einfo) {
    Evas_Event_Key_Down *ev = einfo;
    const char *the_key = ev->key;
    if (*(the_key + 1) == 0) {
        switch (*the_key) {
            case 27:
            case 'q':
                _on_destroy(main_data.ecore_evas);
                break;
            case 's':
                // does not work :'
                evas_object_image_save(main_data.image,
                                       img_destination,
                                       NULL,
                                       "quality=100 compress=8");
                break;
            default:
                break;

        }
    }
}

/* Initialization of DevIL */
static bool init_DevIL(void) {
    if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
        fprintf(stderr, "wrong DevIL version\n");
        return false;
    }
    ilInit();
    return true;
}

int main(const int argc, char **argv) {
    int err;

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

    ecore_evas_callback_destroy_set(main_data.ecore_evas, _on_destroy);
    ecore_evas_callback_resize_set(main_data.ecore_evas, _canvas_resize_cb);
    ecore_evas_show(main_data.ecore_evas);

    /* the canvas pointer, de facto */
    main_data.evas = ecore_evas_get(main_data.ecore_evas);

    /* the white background */
    main_data.background = evas_object_rectangle_add(main_data.evas);
    evas_object_color_set(main_data.background, 50, 50, 0, 55); /* white background */
    evas_object_move(main_data.background, 0, 0); /* at canvas' origin */
    evas_object_resize(
            main_data.background,
            default_width,
            default_height); /* covers full canvas */
    evas_object_show(main_data.background);

    /*
     * the image
     */
    main_data.image = evas_object_image_filled_add(main_data.evas);
    evas_object_image_file_set(main_data.image, img_source, NULL);
    err = evas_object_image_load_error_get(main_data.image);
    if (err != EVAS_LOAD_ERROR_NONE) {
        fprintf(stderr, "could not load image '%s'. error string is \"%s\"\n",
                img_source, evas_load_error_str(err));
        return EXIT_FAILURE;
    }
    fprintf(stdout, "loaded image '%s' with success! error string is \"%s\"\n",
           img_source, evas_load_error_str(err));

    evas_object_image_scale_hint_set(main_data.image, EMILE_IMAGE_SCALE_HINT_NONE);
    evas_object_image_smooth_scale_set(main_data.image, EINA_TRUE);
//        evas_object_image_filled_set(main_data.image, EINA_TRUE);
    evas_object_move(main_data.image, dx, dy);
    evas_object_image_fill_set(
            main_data.image,
            dx, dy,
            default_width - 2 * dx,
            default_height - 2 * dy);
    evas_object_resize(
            main_data.image,
            default_width - 2 * dx,
            default_height - 2 * dy);
    evas_object_show(main_data.image);

    evas_object_focus_set(main_data.background, EINA_TRUE);
    evas_object_event_callback_add(
            main_data.background,
            EVAS_CALLBACK_KEY_DOWN,
            _on_keydown,
            NULL);

    ecore_main_loop_begin();

    ecore_evas_free(main_data.ecore_evas);
    ecore_evas_shutdown();
    return EXIT_SUCCESS;
    error:
    fprintf(stderr, "error: Requires at least one Evas engine built and linked"
                    " to ecore-evas for this example to run properly.\n");
    ecore_evas_shutdown();
    return EXIT_FAILURE;
}
