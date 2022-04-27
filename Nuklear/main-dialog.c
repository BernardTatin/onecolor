//
// Created by bernard on 25/04/22.
//

#include <stdbool.h>
#include <stdio.h>

#include "ocn-glfw3.h"
#include "main-dialog.h"

static const char *filter_names[] = {
        "Soft Grey",
        "Two colors",
        "More"
};

bool show_main_dialog(OCDimensions win_dimensions) {

    static int selected_filter = 0;
    if (nk_begin(main_data.ctx, "Filtering", nk_rect(0, 0, MAIN_DIALOG_WIDTH, win_dimensions.height),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

        nk_layout_row_dynamic(main_data.ctx, 20, 1);
        nk_label(main_data.ctx, "Picture background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(main_data.ctx, 25, 1);
        if (nk_combo_begin_color(main_data.ctx, main_data.pic_bg,
                                 nk_vec2(nk_widget_width(main_data.ctx), 400))) {
            nk_layout_row_dynamic(main_data.ctx, 120, 1);
            struct nk_colorf fbg = {
                    .r = u8_to_unit(main_data.pic_bg.r),
                    .g = u8_to_unit(main_data.pic_bg.g),
                    .b = u8_to_unit(main_data.pic_bg.b),
                    .a = u8_to_unit(main_data.pic_bg.a),
            };
            nk_color_pick(main_data.ctx, &fbg, NK_RGBA);
            main_data.pic_bg.r = unit_to_u8(fbg.r);
            main_data.pic_bg.g = unit_to_u8(fbg.g);
            main_data.pic_bg.b = unit_to_u8(fbg.b);
            main_data.pic_bg.a = unit_to_u8(fbg.a);
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
