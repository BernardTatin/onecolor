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
// Created by bernard on 29/04/22.
// base code from:
//      https://github.com/cxong/nuklear_cmake_demo
//

#define WITH_GL2

/* nuklear - 1.32.0 - public domain */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>


#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION

#if defined(WITH_GL3)
#define NK_SDL_GL3_IMPLEMENTATION
#else
#define NK_SDL_GL2_IMPLEMENTATION
#endif

#include "nuklear.h"

#if defined(WITH_GL3)
#include "nuklear_sdl_gl3.h"
#else

#include "nuklear_sdl_gl2.h"

#endif

#include "basic-data.h"
#include "basic-geometry.h"
#include "image-tools.h"
#include "main-dialog.h"

#define UNUSED(a) (void)a
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

static inline void ocnk_color_i2f(struct nk_color icolor, struct nk_colorf *fcolor) {
    fcolor->r = u8_to_unit(icolor.r);
    fcolor->g = u8_to_unit(icolor.g);
    fcolor->b = u8_to_unit(icolor.b);
    fcolor->a = u8_to_unit(icolor.a);
}

static inline struct nk_color ocnk_color_f2i(struct nk_colorf *fcolor) {
    struct nk_color icolor = {
            .r = unit_to_u8(fcolor->r),
            .g = unit_to_u8(fcolor->g),
            .b = unit_to_u8(fcolor->b),
            .a = unit_to_u8(fcolor->a),
    };
    return icolor;
}

/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
RGBA *pixels = NULL;

void bad_grey_filter(const int img_width, const int img_height) {
    const int n  = img_width * img_height;
    RGBA      *p = pixels;
    for (int  i  = 0; i < n; i++, p++) {
        u8 v = p->r;
        p->g = v;
        p->b = v;
    }
}

static struct nk_image load_image(const char *filename, int *w, int *h, float *ratio);

static void draw_tex(
        GLuint texid, const float x, const float y, const float w, const float h);

int
main(int argc, char *argv[]) {
    // Check args
    if (argc != 2) {
        printf("Usage: nuklear_sdl_gl2_cmake <filename>\n");
        return 0;
    }

    /* Platform */
    SDL_Window      *win;
    SDL_GLContext   glContext;
    struct nk_image tex;
    int             tex_w, tex_h;
    struct nk_color background;
    int             win_width, win_height;
    float           ratio   = 1.0f;
    int             running = 1;

    /* GUI */
    struct nk_context *ctx;

    /* SDL setup */
    //    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "1");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
#if defined(WITH_GL3)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#endif
    win = SDL_CreateWindow("OneColor Filtering",
            //SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           50, 50,
                           WINDOW_WIDTH, WINDOW_HEIGHT,
                           SDL_WINDOW_RESIZABLE | // SDL_WINDOW_ALLOW_HIGHDPI | // SDL_WINDOW_METAL |
                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    SDL_GetWindowSize(win, &win_width, &win_height);
    glContext = SDL_GL_CreateContext(win);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    tex = load_image(argv[1], &tex_w, &tex_h, &ratio);
    if (tex.handle.id == 0) {
        goto cleanup;
    }

    /* GUI */
    ctx = nk_sdl_init(win);

    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {
        struct nk_font_atlas *atlas;
        nk_sdl_font_stash_begin(&atlas);
        nk_sdl_font_stash_end();
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        /*nk_style_set_font(ctx, &roboto->handle)*/;
    }

    background = nk_rgb(28, 48, 62);
    while (running) {
        /* Input */
        SDL_Event evt;
        nk_input_begin(ctx);
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                goto cleanup;
            }
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        SDL_GetWindowSize(win, &win_width, &win_height);
        OCDimensions win_dimensions = {
                .width = win_width,
                .height = win_height
        };
        /* GUI */
        FilterType   filter         = show_main_dialog(ctx, win_dimensions);
        switch (filter) {
            case Filter_None:
                bad_grey_filter(tex_w, tex_h);
                break;
            case Filter_Grey:
                break;
            case Filter_2_Colors:
            case Filter_More:
                fprintf(stdout, "Selected filter %d\n", (int) filter);
                break;
            default:
                fprintf(stderr, "Unknown filter %d\n", filter);
                break;
        }
        OCDimensions win_size = {
                .width = win_width - 231 - 40,
                .height= win_height - 60
        };
        OCRectangle  pict_rect;
        scale_image(win_size, ratio, &pict_rect);
        if (nk_begin(ctx, "Picture", nk_rect(231, 0, win_width - 231, win_height),
                     NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                     NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {

            nk_layout_row_static(
                    ctx,
                    pict_rect.height,
                    pict_rect.width,
                    1);
            nk_image(ctx, tex);
        }
        nk_end(ctx);
        /* Draw */
        float bg[4];
        nk_color_fv(bg, background);
        glViewport(pict_rect.left, pict_rect.top, pict_rect.width, pict_rect.height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg[0], bg[1], bg[2], bg[3]);
        /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
#if defined(WITH_GL3)
        nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
#else
        nk_sdl_render(NK_ANTI_ALIASING_ON);
#endif

        // Display
        SDL_GL_SwapWindow(win);
    }

cleanup:
    nk_sdl_shutdown();
    glDeleteTextures(1, (const GLuint *) &tex.handle.id);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

static struct nk_image load_image(const char *filename, int *w, int *h, float *ratio) {
    GLuint      tex_id = 0;
    // Load image from file
    SDL_Surface *s     = IMG_Load(filename);
    if (s == NULL) {
        printf("Failed to load image from file %s\n", filename);
        goto cleanup;
    }
    *ratio = (float) s->w / (float) s->h;
    fprintf(stdout, "Image %s w, h= %d, %d ratio %5.3f\n",
            filename, s->w, s->h, *ratio);
    // Convert to RGBA
    SDL_Surface *tmp = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ABGR8888, 0);
    if (tmp == NULL) {
        printf("Failed to convert surface: %s\n", SDL_GetError());
        goto cleanup;
    }
    SDL_FreeSurface(s);
    s = tmp;
    // Convert to texture
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    int mode = GL_RGBA;
    glTexImage2D(
            GL_TEXTURE_2D, 0, mode, s->w, s->h, 0, mode, GL_UNSIGNED_BYTE,
            s->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    *w = s->w;
    *h = s->h;
    //pixels = s->pixels;

cleanup:
    SDL_FreeSurface(s);
    return nk_image_id((int) tex_id);
}

static void draw_tex(
        GLuint texid, const float x, const float y, const float w, const float h) {
    glBindTexture(GL_TEXTURE_2D, texid);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(x, y, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x + w, y, 0);
    glTexCoord2f(1, 0);
    glVertex3f(x + w, y + h, 0);
    glTexCoord2f(0, 0);
    glVertex3f(x, y + h, 0);
    glEnd();
}
