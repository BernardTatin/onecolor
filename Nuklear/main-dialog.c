
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

#include <stdbool.h>
#include <stdio.h>

#include "ocn-glfw3.h"
#include "nk_tools.h"
#include "main-dialog.h"

static const char *filter_names[] = {
        "-- None --",
        "Soft Grey",
        "Bad Red Filter",
        "Bad Green Filter",
        "Bad Blue Filter",
        "Shift 1",
        "Shift 2",
};

FilterType show_main_dialog(struct nk_context *ctx, OCDimensions win_dimensions) {

    static int              selected_filter = 0;
    static struct nk_colorf fbg;
    FilterType              filter          = Filter_None;

    if (nk_begin(ctx, "Filtering",
                 nk_rect(0, 0, MAIN_DIALOG_WIDTH, win_dimensions.height),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "Picture background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, main_data.pic_bg,
                                 nk_vec2(nk_widget_width(ctx), 400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            ocnk_color_i2f(main_data.pic_bg, &fbg);
            nk_color_pick(ctx, &fbg, NK_RGBA);
            main_data.pic_bg = ocnk_color_f2i(&fbg);
            nk_combo_end(ctx);
        }
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "filter type:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        int selected = nk_combo(ctx, filter_names, 7, selected_filter, 25, nk_vec2(nk_widget_width(ctx),
                                                                                   400));
        if (selected != selected_filter) {
            fprintf(stdout, "filter: %d:%s\n", selected, filter_names[selected]);
            selected_filter = selected;
            filter          = (FilterType) selected;
        }
    }
    nk_end(ctx);
    return filter;
}
