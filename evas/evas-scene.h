//
// Created by bernard on 20/04/22.
//

#ifndef ONE_COLOR_EVAS_SCENE_H
#define ONE_COLOR_EVAS_SCENE_H

typedef struct _EWidget {
    bool enabled;
    char *name;
    Evas_Object *evas_object;
    void (*resize)(struct _EWidget *widget, const int width, const int height);
} EWidget;

typedef struct _SceneElement {
    EWidget *widget;
    struct _SceneElement *next;
} SceneElement;

typedef struct _EScene {
   SceneElement *first;
   SceneElement *last;
} EScene;

extern EScene main_scene;

static inline SceneElement *new_scene_element(EWidget *widget) {
    SceneElement *elt = (SceneElement *) malloc(sizeof (SceneElement));
    elt->widget = widget;
    elt->next = NULL;
    return elt;
}

void add_to_scene(EScene *scene, EWidget *widget);
void show_scene(EScene *scene);
void resize_scene(EScene *scene, const int width, const int height);

#endif //ONE_COLOR_EVAS_SCENE_H
