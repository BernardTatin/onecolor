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

static inline u8 float_to_u8(const float x) {
    int ix = (int) roundf(x);
    if (ix > 255) {
        ix = 255;
    } else if (ix < 0) {
        ix = 0;
    }
    return (u8)ix;
}
#endif //ONE_COLOR_EVAS_TOOLS_H
