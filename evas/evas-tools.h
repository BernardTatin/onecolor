//
// Created by bernard on 21/04/22.
//

#ifndef ONE_COLOR_EVAS_TOOLS_H
#define ONE_COLOR_EVAS_TOOLS_H

#include <stdbool.h>
#include <math.h>

void canvas_resize(Ecore_Evas *ee);
void on_destroy(Ecore_Evas *ee EINA_UNUSED);
bool init_evas(void);

#endif //ONE_COLOR_EVAS_TOOLS_H
