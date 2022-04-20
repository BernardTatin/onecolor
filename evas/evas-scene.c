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

EScene main_scene = {
        .first = NULL,
        .last = NULL
};

void add_to_scene(EScene *scene, EWidget *widget) {
    SceneElement *elt = new_scene_element(widget);
    fprintf(stdout, "Add to scene %s\n", widget->name);
    if (scene->first == NULL) {
        scene->first = elt;
        scene->last = elt;
    } else {
        scene->last->next = elt;
        scene->last = elt;
    }
}

void show_scene(EScene *scene) {
    SceneElement *elt = scene->first;
    while (elt != NULL) {
        EWidget *widget = elt->widget;
        if (widget->enabled) {
            evas_object_show(widget->evas_object);
            fprintf(stdout, "Show widget %s\n", widget->name);
        } else {
            fprintf(stdout, "NO Show widget %s\n", widget->name);
        }
        elt = elt->next;
    }
}

void resize_scene(EScene *scene, const int width, const int height) {
    SceneElement *elt = scene->first;
    while (elt != NULL) {
        EWidget *widget = elt->widget;
        if (widget->enabled) {
            widget->resize(widget, width, height);
            fprintf(stdout, "Resize widget %s\n", widget->name);
        } else {
            fprintf(stdout, "NO Resize widget %s\n", widget->name);
        }
        elt = elt->next;
    }
}
