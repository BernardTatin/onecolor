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

#include "file-data.h"
#include "ocn-glfw3.h"
#include <GL/glut.h>
#include "ocn-configuration.h"
#include "main-dialog.h"

typedef struct _nk_canvas {
    struct nk_command_buffer *painter;
    struct nk_vec2           item_spacing;
    struct nk_vec2           panel_padding;
    struct nk_style_item     window_background;
} nk_canvas;

static nk_bool canvas_begin(struct nk_context *ctx,
                            nk_canvas *canvas,
                            nk_flags flags,
                            int x, int y, int width, int height,
                            struct nk_color background_color) {
    /* save style properties which will be overwritten */
    canvas->panel_padding     = ctx->style.window.padding;
    canvas->item_spacing      = ctx->style.window.spacing;
    canvas->window_background = ctx->style.window.fixed_background;

    /* use the complete window space and set background */
    ctx->style.window.spacing          = nk_vec2(0, 0);
    ctx->style.window.padding          = nk_vec2(0, 0);
    ctx->style.window.fixed_background = nk_style_item_color(background_color);

    /* create/update window and set position + size */
    if (!nk_begin(ctx, "Picture", nk_rect(x, y, width, height), NK_WINDOW_NO_SCROLLBAR | flags)) {
        return nk_false;
    }

    /* allocate the complete window space for drawing */
    {
        struct nk_rect total_space;
        total_space = nk_window_get_content_region(ctx);
        nk_layout_row_dynamic(ctx, total_space.h, 1);
        nk_widget(&total_space, ctx);
        canvas->painter = nk_window_get_canvas(ctx);
    }

    return nk_true;
}

static void canvas_end(struct nk_context *ctx, nk_canvas *canvas) {
    nk_end(ctx);
    ctx->style.window.spacing          = canvas->panel_padding;
    ctx->style.window.padding          = canvas->item_spacing;
    ctx->style.window.fixed_background = canvas->window_background;
}

static struct nk_image main_nk_image;

struct nk_image image_create(void) {
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR); /* We will use linear interpolation for magnification filter */
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR); /* We will use linear interpolation for minifying filter */
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,
                    GL_CLAMP_TO_BORDER);


    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 main_image.width,
                 main_image.height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 main_image.screen_pixels);

    main_nk_image = nk_image_id((int) tex);
    return main_nk_image;
}


static void canvas(struct nk_context *ctx, OCDimensions win_dimensions) {
    nk_canvas      canvas;
    struct nk_rect img_rect = {
            MAIN_DIALOG_WIDTH,
            0,
            win_dimensions.width - MAIN_DIALOG_WIDTH,
            win_dimensions.height
    };
    //    nk_rect(MAIN_DIALOG_WIDTH, 0, win_dimensions.width-MAIN_DIALOG_WIDTH, win_dimensions.height),
    if (canvas_begin(ctx, &canvas, NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                                   NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE,
                     img_rect.x,
                     img_rect.y,
                     img_rect.w,
                     img_rect.h,
                     main_data.pic_bg)) {
        float x = canvas.painter->clip.x, y = canvas.painter->clip.y;

        nk_fill_rect(canvas.painter, img_rect, 5, main_data.pic_bg);
        // nk_draw_image
        //        NK_API void nk_draw_image(struct nk_command_buffer*,
        //        struct nk_rect,
        //        const struct nk_image*,
        //        struct nk_color);
#if 1
        nk_draw_image(canvas.painter,
                      img_rect,
                      &main_nk_image,
                      main_data.pic_bg);
#else
        nk_image(ctx, main_nk_image);
#endif
    }
    canvas_end(ctx, &canvas);
}

bool show_picture_window(OCDimensions win_dimensions) {
#if 0
    canvas(main_data.ctx, win_dimensions);
#else
    if (nk_begin(main_data.ctx, "Picture",
                 nk_rect(
                         MAIN_DIALOG_WIDTH,
                         0,
                         win_dimensions.width - MAIN_DIALOG_WIDTH,
                         win_dimensions.height
                 ),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

        nk_layout_row_static(
                main_data.ctx,
                win_dimensions.height,
                win_dimensions.width - MAIN_DIALOG_WIDTH,
                1);
        nk_image_color(main_data.ctx, main_nk_image, main_data.pic_bg);
        nk_image(main_data.ctx, main_nk_image);
        //        nk_draw_image();
    }
    nk_end(main_data.ctx);
#endif
    return true;
}
