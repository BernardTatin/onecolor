/******************************************************************************
 * MIT License                                                                *
 *                                                                            *
 * Copyright (c) 2022.  Bernard Tatin                                         *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell  *
 * copies of the Software, and to permit persons to whom the Software is      *
 * furnished to do so, subject to the following conditions:                   *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.                            *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.                                                                  *
 ******************************************************************************/

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
