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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file-data.h"
#include "ocn-glfw3.h"
#include "ocn-configuration.h"
#include "basic-geometry.h"
#include "main-dialog.h"
#include "dev-IL-tools.h"
#include "filtering.h"

#include "style.c"

static void error_callback(int e, const char *d) {
    fprintf(stderr, "Error %d: %s\n", e, d);
}

static void init_fonts(struct nk_glfw *glfw, struct nk_context *ctx) {
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(glfw, &atlas);
    /*
     * TODO: font path must be computed
     */
    struct nk_font *gillius = nk_font_atlas_add_from_file(atlas,
                                                          "/home/bernard/git/onecolor/fonts2/GilliusADF/GilliusADFNo2-Regular.otf",
                                                          20, 0);
    nk_glfw3_font_stash_end(glfw);
    if (gillius != NULL) {
        nk_style_set_font(ctx, &gillius->handle);
    } else {
        fprintf(stderr, "Cannot load Gillius font...\n");
    }
}

static bool init_glfw(void) {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        return false;
    }
#if 1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    main_data.win = glfwCreateWindow(WINDOW_WIDTH,
                                     WINDOW_HEIGHT,
                                     "OneColor",
                                     NULL,
                                     NULL);
    glfwMakeContextCurrent(main_data.win);
    glfwGetWindowSize(main_data.win, &main_data.width, &main_data.height);

    /* OpenGL */
    glViewport(0, 0, main_data.width, main_data.height);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to setup GLEW\n");
        return false;
    }

    main_data.ctx = nk_glfw3_init(&main_data.glfw, main_data.win, NK_GLFW3_INSTALL_CALLBACKS);
    return true;
}

static OCDimensions begin_glfw_loop() {
    OCDimensions win_dimensions;

    nk_glfw3_new_frame(&main_data.glfw);
    glfwGetWindowSize(main_data.win,
                      &win_dimensions.width,
                      &win_dimensions.height);
    return win_dimensions;
}

static void end_glfw_loop(OCDimensions *win_dimensions) {
    glViewport(0, 0, win_dimensions->width, win_dimensions->height);
    glClearColor(main_data.bg.r,
                 main_data.bg.g,
                 main_data.bg.b,
                 main_data.bg.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
     * with blending, scissor, face culling, depth test and viewport and
     * defaults everything back into a default state.
     * Make sure to either a.) save and restore or b.) reset your own state after
     * rendering the UI.
     */
    nk_glfw3_render(&main_data.glfw,
                    NK_ANTI_ALIASING_ON,
                    MAX_VERTEX_BUFFER,
                    MAX_ELEMENT_BUFFER);
    glfwSwapBuffers(main_data.win);
    glfwPollEvents();
}

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

    // TODO: image can be loaded from user interface, not only from command line
    /* load the file picture with DevIL */
    if (!LoadImage(&main_image, argv[1])) {
        fprintf(stderr, "Can't load picture file %s by DevIL\n", argv[1]);
        return EXIT_FAILURE;
    }
    /* GLFW */
    if (!init_glfw()) {
        return EXIT_FAILURE;
    }

    init_fonts(&main_data.glfw, main_data.ctx);

    set_style(main_data.ctx, THEME_RED);

    image_create();
    while (!glfwWindowShouldClose(main_data.win)) {
        OCDimensions win_dimensions;
        /* Input */
        win_dimensions = begin_glfw_loop();

        /* GUI */
        FilterType filter = show_main_dialog(main_data.ctx, win_dimensions);
        switch (filter) {
            case Filter_None:
                break;
            case Filter_Grey:
                apply_grey_filter();
                refresh_image();
                break;
            case Filter_Red:
                apply_red_filter();
                refresh_image();
                break;
            case Filter_Green:
                apply_grey_filter();
                refresh_image();
                break;
            case Filter_Blue:
                apply_blue_filter();
                refresh_image();
                break;
            case Filter_Shift1:
                apply_shift1_filter();
                refresh_image();
                break;
            default:
                fprintf(stderr, "Unknown filter %d\n", filter);
                break;
        }
        show_picture_window(win_dimensions);

        /* Draw */
        end_glfw_loop(&win_dimensions);

    }
    nk_glfw3_shutdown(&main_data.glfw);
    glfwTerminate();
    return 0;
}
