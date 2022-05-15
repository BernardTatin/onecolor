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
// Created by bernard on 08/04/2022.
//

#ifndef ONE_COLOR_GL_MENUS_H
#define ONE_COLOR_GL_MENUS_H

typedef enum {
    Menu_Quit,
    Menu_Clear,
    Menu_BW_Normal1,
    Menu_BW_Normal2,
    Menu_BW_Normal3,
    Menu_BW_Hard1,
    Menu_BW_Hard2,
    Menu_BW_Hard_Red,
    Menu_BW_Hard_Green,
    Menu_BW_Hard_Blue,
    Menu_BW_Average,
    Menu_BW_No_Saturation
} Menu_Values;

void createMenu(void);

void on_key(unsigned char key, int x, int y);

void on_special_keys(int key, int x, int y);

#endif //ONE_COLOR_GL_MENUS_H
