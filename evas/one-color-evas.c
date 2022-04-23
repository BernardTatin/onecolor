// images.c
// bernard TaTiN
// 2022-04-17
//
// from the source code of evas-images.c
//

#if !defined(WITH_EVAS)
#error "WITH_EVAS must be defined"
#endif


#include <stdbool.h>
#include <IL/il.h>
#include <stdio.h>
#include <stdlib.h>
#include <Ecore.h>
#include <Ecore_Evas.h>

#include "file-tools.h"
#include "evas-configuration.h"
#include "dev-IL-tools.h"
#include "evas-scene.h"
#include "widgets.h"
#include "evas-tools.h"
#include "grey-filter.h"

// on_show_image
static void on_show_image(void *data EINA_UNUSED,
                          Evas *evas EINA_UNUSED,
                          Evas_Object *o EINA_UNUSED,
                          void *event) {
    fprintf(stdout, "Image show\n");
}

static void on_key_down(void *data EINA_UNUSED,
                        Evas *evas EINA_UNUSED,
                        Evas_Object *o EINA_UNUSED,
                        void *event) {
    Evas_Event_Key_Down *ev = event;
    const char *the_key = ev->key;
    Eina_Bool control = evas_key_modifier_is_set(ev->modifiers, "Control");
    Eina_Bool alt = evas_key_modifier_is_set(ev->modifiers, "Alt");
    Eina_Bool shift = evas_key_modifier_is_set(ev->modifiers, "Shift");
    bool ctrl_only = control && !alt && !shift;
    bool no_modifiers = !control && !alt && !shift;

    if (*(the_key + 1) == 0) {
        if (ctrl_only) {
            switch (*the_key) {
                case 'q':
                    on_destroy(main_data.ecore_evas);
                    break;
                case 's':
                    evas_object_image_save(main_data.image,
                                           img_destination,
                                           NULL,
                                           "quality=100 compress=8");
                    break;
                default:
                    break;
            }
        } else if (no_modifiers) {
            switch(*the_key) {
                case 'g':
                    apply_grey_filter();
//                    redraw_scene(&main_scene);
//                    show_scene(&main_scene);
//                    evas_object_show(main_data.image);
                    return;
                default:
                    break;
            }
        } else {
            fprintf(stdout, "key %d (%c)\n",
                    (int)*the_key,
                    *the_key);
        }
    } else {
        if (strcmp(the_key, "Escape") == 0) {

        } else {
            fprintf(stdout, "key <%s>\n",
                    the_key);
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
    if (!LoadImage(&main_image, argv[1])) {
        fprintf(stderr, "Can't load picture file %s by DevIL\n", argv[1]);
        return -1;
    }

    if (!init_evas()) {
        goto error;
    }

    main_data.background = widget_background(main_data.evas)->evas_object;
    main_data.image = widget_picture(main_data.evas)->evas_object;
    main_data.txt_key_help = widget_key_text(main_data.evas)->evas_object;

    evas_object_focus_set(main_data.background, EINA_TRUE);
    evas_object_event_callback_add(
            main_data.background,
            EVAS_CALLBACK_KEY_DOWN,
            on_key_down,
            NULL);
    evas_object_event_callback_add(
            main_data.image,
            EVAS_CALLBACK_SHOW,
            on_show_image,
            NULL);

    resize_scene(&main_scene, default_width, default_height);
    ecore_evas_show(main_data.ecore_evas);
    show_scene(&main_scene);

    /*
     * main loop
     */
    ecore_main_loop_begin();

    /*
     * end of the world
     */
    ilDeleteImages(1, &main_image.image_name);
    ecore_evas_free(main_data.ecore_evas);
    ecore_evas_shutdown();
    return EXIT_SUCCESS;
error:
    fprintf(stderr, "error: Requires at least one Evas engine built and linked"
                    " to ecore-evas for this example to run properly.\n");
    ecore_evas_shutdown();
    return EXIT_FAILURE;
}
