//
// Created by bernard on 25/04/22.
//

#include <stdbool.h>
#include <stdio.h>

#include "ocn-glfw3.h"
#include "nk_tools.h"
#include "main-dialog.h"

static const char *filter_names[] = {
        "Soft Grey",
        "Two colors",
        "More"
};

bool show_main_dialog(OCDimensions win_dimensions) {

    static int selected_filter = 0;
    static struct nk_colorf fbg;

    if (nk_begin(main_data.ctx, "Filtering", nk_rect(0, 0, MAIN_DIALOG_WIDTH, win_dimensions.height),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(main_data.ctx, 20, 1);
        nk_label(main_data.ctx, "Picture background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(main_data.ctx, 25, 1);
        if (nk_combo_begin_color(main_data.ctx, main_data.pic_bg,
                                 nk_vec2(nk_widget_width(main_data.ctx), 400))) {
            nk_layout_row_dynamic(main_data.ctx, 120, 1);
            ocnk_color_i2f(main_data.pic_bg, &fbg);
            nk_color_pick(main_data.ctx, &fbg, NK_RGBA);
            main_data.pic_bg = ocnk_color_f2i(&fbg);
            nk_combo_end(main_data.ctx);
        }
        nk_layout_row_dynamic(main_data.ctx, 20, 1);
        nk_label(main_data.ctx, "filter type:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(main_data.ctx, 25, 1);
        int selected = nk_combo(main_data.ctx, filter_names, 3, selected_filter, 25, nk_vec2(nk_widget_width(main_data.ctx),
                                                                                   400));
        if (selected != selected_filter) {
            fprintf(stdout, "filter: %d:%s\n", selected, filter_names[selected]);
            selected_filter = selected;
        }
    }
    nk_end(main_data.ctx);
    return true;
}
