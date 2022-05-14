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

static void scale_texture(OCDimensions *canvas_dim) {
    const int   width  = canvas_dim->width;
    const int   height = canvas_dim->height;
    const float ratio  = main_image.ratio;

    static float old_w = 0.0f;
    static float old_h = 0.0f;

    int   max_dim = width;
    int   min_dim = width;
    float w_dim, h_dim;

    if (height > max_dim) {
        max_dim = height;
    } else if (height < min_dim) {
        min_dim = height;
    } else {
    }

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

    canvas_dim->width  = new_w;
    canvas_dim->height = new_h;
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


bool show_picture_window(OCDimensions win_dimensions) {
    OCDimensions canvas_dim = {
            .width = win_dimensions.width - MAIN_DIALOG_WIDTH,
            .height= win_dimensions.height - 64
    };
    if (nk_begin(main_data.ctx, "Picture",
                 nk_rect(
                         MAIN_DIALOG_WIDTH,
                         0,
                         canvas_dim.width,
                         canvas_dim.height
                 ),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_TITLE)) {

        scale_texture(&canvas_dim);
        nk_layout_row_static(
                main_data.ctx,
                canvas_dim.height,
                canvas_dim.width,
                1);
        // Note: nk_image is the same but with the backgroud set to white
        nk_image_color(main_data.ctx, main_nk_image, main_data.pic_bg);
    }
    nk_end(main_data.ctx);

    return true;
}
