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

/* nuklear - 1.32.0 - public domain */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include "file-data.h"
#include "ocn-glfw3.h"
#include "ocn-configuration.h"
#include "basic-geometry.h"
#include "main-dialog.h"
#include "dev-IL-tools.h"
#include "file-tools.h"

/* ===============================================================
 *
 *                          EXAMPLE
 *
 * ===============================================================*/
/* This are some code examples to provide a small overview of what can be
 * done with this library. To try out an example uncomment the defines */

#include "style.c"

/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
static void error_callback(int e, const char *d) { printf("Error %d: %s\n", e, d); }

struct nk_image image_create(void);

int main(int argc, char **argv) {
    /* Platform */

    if (!init_file_data(argc, argv)) {
        return EXIT_FAILURE;
    }

    /* Initialization of DevIL */
    if (!init_DevIL()) {
        fprintf(stderr, "wrong DevIL version\n");
        return EXIT_FAILURE;
    }

    /* load the file picture with DevIL */
    if (!LoadImage(&main_image, argv[1])) {
        fprintf(stderr, "Can't load picture file %s by DevIL\n", argv[1]);
        return EXIT_FAILURE;
    }
    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    main_data.win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OneColor", NULL, NULL);
    glfwMakeContextCurrent(main_data.win);
    glfwGetWindowSize(main_data.win, &main_data.width, &main_data.height);

    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to setup GLEW\n");
        exit(1);
    }

    main_data.ctx = nk_glfw3_init(&main_data.glfw, main_data.win, NK_GLFW3_INSTALL_CALLBACKS);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {
        struct nk_font_atlas *atlas;
        nk_glfw3_font_stash_begin(&main_data.glfw, &atlas);
        /*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
        /*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
        /*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
        /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
        /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
        /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
        nk_glfw3_font_stash_end(&main_data.glfw);
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        /*nk_style_set_font(ctx, &droid->handle);*/}

    //    set_style(main_data.ctx, THEME_WHITE);
    //set_style(main_data.ctx, THEME_RED);
    //    set_style(main_data.ctx, THEME_BLUE);
    //    set_style(main_data.ctx, THEME_DARK);

    main_data.bg.r     = 0.10f;
    main_data.bg.g     = 0.18f;
    main_data.bg.b     = 0.24f;
    main_data.bg.a     = 1.00f;
    main_data.pic_bg.r = float_to_u8(255.0f * 0.10f);
    main_data.pic_bg.g = float_to_u8(255.0f * 0.18f);
    main_data.pic_bg.b = float_to_u8(255.0f * 0.24f);
    main_data.pic_bg.a = float_to_u8(255.0f * 1.00f);
    image_create();
    while (!glfwWindowShouldClose(main_data.win)) {
        OCDimensions win_dimensions;
        /* Input */
        nk_glfw3_new_frame(&main_data.glfw);
        glfwGetWindowSize(main_data.win, &win_dimensions.width, &win_dimensions.height);

        /* GUI */
        show_main_dialog(main_data.ctx, win_dimensions);
        show_picture_window(win_dimensions);
        /* -------------- EXAMPLES ---------------- */
        /* ----------------------------------------- */

        /* Draw */
        glViewport(0, 0, win_dimensions.width, win_dimensions.height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(main_data.bg.r,
                     main_data.bg.g,
                     main_data.bg.b,
                     main_data.bg.a);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_glfw3_render(&main_data.glfw,
                        NK_ANTI_ALIASING_ON,
                        MAX_VERTEX_BUFFER,
                        MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(main_data.win);
        glfwPollEvents();
    }
    nk_glfw3_shutdown(&main_data.glfw);
    glfwTerminate();
    return 0;
}
