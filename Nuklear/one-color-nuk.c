
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
    main_data.win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo", NULL, NULL);
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

    set_style(main_data.ctx, THEME_WHITE);
    set_style(main_data.ctx, THEME_RED);
    set_style(main_data.ctx, THEME_BLUE);
    set_style(main_data.ctx, THEME_DARK);

    main_data.bg.r = 0.10f;
    main_data.bg.g = 0.18f;
    main_data.bg.b = 0.24f;
    main_data.bg.a = 1.00f;
    while (!glfwWindowShouldClose(main_data.win)) {
        /* Input */
        glfwPollEvents();
        nk_glfw3_new_frame(&main_data.glfw);

        /* GUI */
        if (nk_begin(main_data.ctx, "Filtering", nk_rect(0, 0, 230, 250),
                     NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                     NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
            enum {
                EASY, HARD
            };
            static int op = EASY;
            static int property = 20;
            nk_layout_row_static(main_data.ctx, 30, 80, 1);
            if (nk_button_label(main_data.ctx, "button"))
                fprintf(stdout, "button pressed\n");

            nk_layout_row_dynamic(main_data.ctx, 30, 2);
            if (nk_option_label(main_data.ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(main_data.ctx, "hard", op == HARD)) op = HARD;

            nk_layout_row_dynamic(main_data.ctx, 25, 1);
            nk_property_int(main_data.ctx, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(main_data.ctx, 20, 1);
            nk_label(main_data.ctx, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(main_data.ctx, 25, 1);
            if (nk_combo_begin_color(main_data.ctx, nk_rgb_cf(main_data.bg), nk_vec2(nk_widget_width(main_data.ctx), 400))) {
                nk_layout_row_dynamic(main_data.ctx, 120, 1);
                main_data.bg = nk_color_picker(main_data.ctx, main_data.bg, NK_RGBA);
                nk_layout_row_dynamic(main_data.ctx, 25, 1);
                main_data.bg.r = nk_propertyf(main_data.ctx, "#R:", 0, main_data.bg.r, 1.0f, 0.01f, 0.005f);
                main_data.bg.g = nk_propertyf(main_data.ctx, "#G:", 0, main_data.bg.g, 1.0f, 0.01f, 0.005f);
                main_data.bg.b = nk_propertyf(main_data.ctx, "#B:", 0, main_data.bg.b, 1.0f, 0.01f, 0.005f);
                main_data.bg.a = nk_propertyf(main_data.ctx, "#A:", 0, main_data.bg.a, 1.0f, 0.01f, 0.005f);
                nk_combo_end(main_data.ctx);
            }
        }
        nk_end(main_data.ctx);

        /* -------------- EXAMPLES ---------------- */
#ifdef INCLUDE_CALCULATOR
        calculator(main_data.ctx);
#endif
#ifdef INCLUDE_CANVAS
        canvas(main_data.ctx);
#endif
#ifdef INCLUDE_OVERVIEW
        overview(main_data.ctx);
#endif
#ifdef INCLUDE_NODE_EDITOR
        node_editor(main_data.ctx);
#endif
        /* ----------------------------------------- */

        /* Draw */
        glfwGetWindowSize(main_data.win, &main_data.width, &main_data.height);
        glViewport(0, 0, main_data.width, main_data.height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(main_data.bg.r, main_data.bg.g, main_data.bg.b, main_data.bg.a);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_glfw3_render(&main_data.glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(main_data.win);
    }
    nk_glfw3_shutdown(&main_data.glfw);
    glfwTerminate();
    return 0;
}
