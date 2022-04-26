//
// Created by bernard on 25/04/22.
//

#include <stdbool.h>
#include <stdio.h>

#include "file-data.h"
#include "ocn-glfw3.h"
#include "ocn-configuration.h"
#include "main-dialog.h"

typedef struct _nk_canvas {
    struct nk_command_buffer *painter;
    struct nk_vec2 item_spacing;
    struct nk_vec2 panel_padding;
    struct nk_style_item window_background;
} nk_canvas;

bool create_picture_window(void) {

    if (nk_begin(main_data.ctx, "Picture",
                 nk_rect(MAIN_DIALOG_WIDTH, 0, PIC_WINDOW_WIDTH, PIC_WINDOW_HEIGHT),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
    }
    nk_end(main_data.ctx);
    return true;
}
