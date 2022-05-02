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
// Created by bernard on 25/04/22.
//

#ifndef ONE_COLOR_MAIN_DIALOG_H
#define ONE_COLOR_MAIN_DIALOG_H

#include "ocn-configuration.h"
#include "basic-geometry.h"

#define MAIN_DIALOG_WIDTH   230
#define MAIN_DIALOG_HEIGHT  WINDOW_HEIGHT
#define PIC_WINDOW_WIDTH    (WINDOW_WIDTH - MAIN_DIALOG_WIDTH)
#define PIC_WINDOW_HEIGHT   WINDOW_HEIGHT

typedef enum {
    Filter_None,
    Filter_Grey,
    Filter_2_Colors,
    Filter_More
} FilterType;

FilterType show_main_dialog(struct nk_context *ctx, OCDimensions win_dimensions);

bool show_picture_window(OCDimensions win_dimensions);

#endif //ONE_COLOR_MAIN_DIALOG_H
