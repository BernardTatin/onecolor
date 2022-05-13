//
// Created by bernard on 27/04/22.
//

#ifndef ONE_COLOR_NK_TOOLS_H
#define ONE_COLOR_NK_TOOLS_H

#include "basic-data.h"

static inline void ocnk_color_i2f(struct nk_color icolor, struct nk_colorf *fcolor) {
    fcolor->r = u8_to_unit(icolor.r);
    fcolor->g = u8_to_unit(icolor.g);
    fcolor->b = u8_to_unit(icolor.b);
    fcolor->a = u8_to_unit(icolor.a);
}

static inline struct nk_color ocnk_color_f2i(struct nk_colorf *fcolor) {
    struct nk_color icolor = {
            .r = unit_to_u8(fcolor->r),
            .g = unit_to_u8(fcolor->g),
            .b = unit_to_u8(fcolor->b),
            .a = unit_to_u8(fcolor->a),
    };
    return icolor;
}

#endif //ONE_COLOR_NK_TOOLS_H
