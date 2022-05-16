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
// Created by bernard on 07/04/2022.
//

#ifndef ONE_COLOR_GL_CONFIGURATION_H
#define ONE_COLOR_GL_CONFIGURATION_H


#if defined(GL_VERSION_4_6)
#define gl_version "4.6"
#elif defined(GL_VERSION_4_5)
#define gl_version "4.5"
#elif defined(GL_VERSION_4_4)
#define gl_version "4.4"
#elif defined(GL_VERSION_4_3)
#define gl_version "4.3"
#elif defined(GL_VERSION_4_2)
#define gl_version "4.2"
#elif defined(GL_VERSION_4_1)
#define gl_version "4.1"
#elif defined(GL_VERSION_4_0)
#define gl_version "4.0"
#elif defined(GL_VERSION_3GL_VERSION_3_3)
#define gl_version "3.3"
#else
#warning "We need Open GL version 3.3 or more recent"
#endif


#define DEFAULT_WIDTH  960
#define DEFAULT_HEIGHT 640

#include "basic-data.h"

typedef struct {
    int window;
    int width;
    int height;
    int menu_id;
    int submenu_id;
    int value;
} GLWindow;


extern GLWindow main_window;

#endif //ONE_COLOR_GL_CONFIGURATION_H
