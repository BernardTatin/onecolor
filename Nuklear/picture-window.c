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


static inline void map_tex_point(const float s, const float t,
                                 const int x, const int y) {
    glTexCoord2f(s, t);
    glVertex2i(x, y);
}

static inline void map_tex_square(const float delta_x, const float delta_y,
                                  const int x1, const int y1,
                                  const int x2, const int y2) {
    map_tex_point(0.0f - delta_x, 0.0f - delta_y,
                  x1, y1);
    map_tex_point(1.0f + delta_x, 0.0f - delta_y,
                  x2, y1);
    map_tex_point(1.0f + delta_x, 1.0f + delta_y,
                  x2, y2);
    map_tex_point(0.0f - delta_x, 1.0f + delta_y,
                  x1, y2);
}

static inline float compute_delta(const int dim) {
    const float f_dim = (float) dim;
    if (dim > 128) {
        return 24.0f / f_dim;
    } else {
        return 0.0f;
    }
}

void map_texture(OCDimensions *canvas_dim) {
    const int   width  = canvas_dim->width;
    const int   height = canvas_dim->height;
    const float ratio  = main_image.ratio;

    static float old_w = 0.0f;
    static float old_h = 0.0f;

    int   max_dim = width;
    int   min_dim = width;
    float delta_x, delta_y;
    float w_dim, h_dim;

    if (height > max_dim) {
        max_dim = height;
    } else if (height < min_dim) {
        min_dim = height;
    } else {
    }

    delta_x = compute_delta(width);
    delta_y = compute_delta(height);

    w_dim = (float) width;
    h_dim = roundf((float) width / ratio);
    if (h_dim > (float) height) {
        h_dim = (float) height;
        w_dim = roundf(h_dim * ratio);
    }
    if (old_h != h_dim || old_w != w_dim) {
        fprintf(stdout, "%-10s: x2 %4d y2 %4d r %5.3f -> %5.3f\n",
                "landscape", (int) w_dim, (int) h_dim, ratio, w_dim / h_dim);
        old_w = w_dim;
        old_h = h_dim;
    }
    const int new_w = (int) roundf(w_dim);
    const int new_h = (int) roundf(h_dim);

    glViewport(0, 0, new_w, new_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (double) new_w, (double) new_h, 0.0, 0.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Operate on model-view matrix
    glMatrixMode(GL_MODELVIEW);

    /* Draw a fullscreen mapped quad */
    glBegin(GL_QUADS);
    {
        map_tex_square(delta_x, delta_y,
                       0, 0,
                       new_w, new_h);
    }
    glEnd();
    canvas_dim->width  = new_w;
    canvas_dim->height = new_h;
}

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
    if (!nk_begin(ctx, "Picture",
                  nk_rect(x, y, width, height),
                  flags)) {
        //NK_WINDOW_NO_SCROLLBAR | flags)) {
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
                 main_image.format,
                 GL_UNSIGNED_BYTE,
                 main_image.screen_pixels);

    main_nk_image = nk_image_id((int) tex);
    return main_nk_image;
}


static void canvas(struct nk_context *ctx, OCDimensions canvas_dim) {
    nk_canvas      canvas;
    struct nk_rect img_rect = {
            MAIN_DIALOG_WIDTH,
            0,
            canvas_dim.width,
            canvas_dim.height
    };
    //    nk_rect(MAIN_DIALOG_WIDTH, 0, canvas_dim.width-MAIN_DIALOG_WIDTH, canvas_dim.height),
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
        map_texture(&canvas_dim);
        img_rect.w = canvas_dim.width;
        img_rect.h = canvas_dim.height;
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
    OCDimensions canvas_dim = {
            .width = win_dimensions.width - MAIN_DIALOG_WIDTH,
            .height= win_dimensions.height - 48
    };
#if 1
    canvas(main_data.ctx, canvas_dim);
#else
    if (nk_begin(main_data.ctx, "Picture",
                 nk_rect(
                         MAIN_DIALOG_WIDTH,
                         0,
                         canvas_dim.width,
                         canvas_dim.height
                 ),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                 NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

        // sadly, it does nothing at all
        map_texture(&canvas_dim);
        nk_layout_row_static(
                main_data.ctx,
                canvas_dim.height,
                canvas_dim.width,
                1);
        // Note: nk_image is the same but with the backgroud set to white
        nk_image_color(main_data.ctx, main_nk_image, main_data.pic_bg);
    }
    nk_end(main_data.ctx);
#endif
    return true;
}
