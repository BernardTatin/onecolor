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

static void on_destroy(Ecore_Evas *ee EINA_UNUSED) {
    ecore_main_loop_quit();
}

static void resize_text(const int width, const int height) {
    evas_object_move(main_data.txt_key_help, dx, height - dy);
    evas_object_resize(main_data.txt_key_help, width - 2*dx, dy);
}

static void resize_image(const int width, const int height) {
    // c'est l'bordel, là dedans!
    int left = dx;
    int top = dy;
    float nh = (float)height;
    float nw = mainImage.ratio * (float)height;
    float fw = (float)width;
    float fh = (float)height;
    if (nw > fw) {
        float fTop;
        float r = fw / nw;
        nh = roundf(nh * r);
        nw = fw;
        fTop = roundf(0.5f * (fh - nh));
        top = (int)fTop;
    } else {
        float fLeft;
        nw = roundf(nw);
        fLeft = roundf(0.5f * (fw - nw));
        left = (int)fLeft;
    }
    evas_object_move(main_data.image,
                     left,
                     top);
    evas_object_resize(
            main_data.image,
            (int)nw,
            (int)nh);
}

/* Keep the example's window size in sync with the background image's size */
static void canvas_resize_cb(Ecore_Evas *ee) {
    int w, h;

    ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
    evas_object_resize(main_data.background, w, h);
    resize_image(w - 2 * dx, h - 2 * dy);
    resize_text(w, h);
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

    /*
     * the white background
     */
    main_data.background = evas_object_rectangle_add(main_data.evas);
    evas_object_color_set(main_data.background, 250, 250, 220, 255); /* white background */
    evas_object_move(main_data.background, 0, 0); /* at canvas' origin */
    evas_object_resize(
            main_data.background,
            default_width,
            default_height); /* covers full canvas */

    /*
     * the image
     */
    main_data.image = evas_object_image_add(main_data.evas);
    evas_object_image_size_set(main_data.image, mainImage.width, mainImage.height);
    evas_object_image_data_set(main_data.image, mainImage.screen_pixels);
    evas_object_image_filled_set(main_data.image, EINA_TRUE);

    evas_object_move(main_data.image, dx, dy);
    resize_image(
            default_width - 2 * dx,
            default_height - 2 * dy);
    evas_object_show(main_data.background);
    evas_object_show(main_data.image);

    evas_object_focus_set(main_data.background, EINA_TRUE);
    evas_object_event_callback_add(
            main_data.background,
            EVAS_CALLBACK_KEY_DOWN,
            on_key_down,
            NULL);

    /*
     * text: key help at the bottom of the screen
     */
    main_data.txt_key_help = evas_object_text_add(main_data.evas);
    evas_object_text_style_set(main_data.txt_key_help, EVAS_TEXT_STYLE_PLAIN);
    evas_object_color_set(main_data.txt_key_help, 0, 0, 0, 255);
    evas_object_text_font_set(main_data.txt_key_help, "Utopia", dy - 2);
    evas_object_text_text_set(main_data.txt_key_help, "sample text");
    resize_text(
            default_width,
            default_height);

    /*
     * we show all
     */
    evas_object_show(main_data.background);
    evas_object_show(main_data.txt_key_help);
    evas_object_show(main_data.image);


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
