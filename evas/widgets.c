//
// Created by bernard on 20/04/22.
//

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <IL/il.h>
#include <Ecore.h>
#include <Ecore_Evas.h>

#include "evas-configuration.h"
#include "evas-scene.h"

#include "widgets.h"

static void redraw_background(EWidget *widget, const int width, const int height) {
    Evas_Object *obj = widget->evas_object;
    evas_object_move(obj, 0, 0); /* at canvas' origin */
    evas_object_resize(
            obj,
            width,
            height); /* covers full canvas */
}
EWidget *widget_background(Evas *evas) {
    EWidget *widget = (EWidget *) malloc(sizeof (EWidget));
    Evas_Object *obj = evas_object_rectangle_add(evas);
    static char *name = "Background";
    widget->name = name;
    widget->enabled = true;
    widget->evas_object = obj;
    widget->resize = redraw_background;

    evas_object_color_set(obj, 250, 250, 220, 255); /* white background */

    add_to_scene(&main_scene, widget);
    return widget;
}

static void resize_image(EWidget *widget, const int width, const int height) {
    // c'est l'bordel, là dedans!
    Evas_Object *obj = widget->evas_object;
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
    evas_object_move(obj,
                     left,
                     top);
    evas_object_resize(
            obj,
            (int)nw,
            (int)nh);
}
EWidget *widget_picture(Evas *evas) {
    EWidget *widget = (EWidget *) malloc(sizeof (EWidget));
    Evas_Object *obj = evas_object_image_add(evas);
    static char *name = "Image";
    widget->name = name;
    widget->enabled = true;
    widget->evas_object = obj;
    widget->resize = resize_image;

    evas_object_image_size_set(obj, mainImage.width, mainImage.height);
    evas_object_image_data_set(obj, mainImage.screen_pixels);
    evas_object_image_filled_set(obj, EINA_TRUE);

    add_to_scene(&main_scene, widget);
    return widget;
}

static void resize_text(EWidget *widget, const int width, const int height) {
    Evas_Object *obj = widget->evas_object;
    evas_object_move(obj, dx, height - dy);
    evas_object_resize(obj, width - 2*dx, dy);
}

EWidget *widget_key_text(Evas *evas) {
    EWidget *widget = (EWidget *) malloc(sizeof (EWidget));
    Evas_Object *obj = evas_object_text_add(evas);
    static char *name = "Key Text";
    widget->name = name;
    widget->enabled = true;
    widget->evas_object = obj;
    widget->resize = resize_text;

    evas_object_text_style_set(obj, EVAS_TEXT_STYLE_PLAIN);
    evas_object_color_set(obj, 0, 0, 0, 255);
    evas_object_text_font_set(obj, "Utopia", dy - 2);
    evas_object_text_text_set(obj, "sample text");

    add_to_scene(&main_scene, widget);
    return widget;
}
