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


#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <IL/il.h>
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "GL-menus.h"
#include "GL-filters.h"

static void exec_option(const Menu_Values option) {
    bool redraw = true;
    switch (option) {
        case Menu_BW_Normal1:
            filter_bw_normal1();
            break;
        case Menu_BW_Normal2:
            filter_bw_normal2();
            break;
        case Menu_BW_Normal3:
            filter_bw_normal3();
            break;
        case Menu_BW_Hard1:
            filter_bw_hard_black1();
            break;
        case Menu_BW_Hard2:
            filter_bw_hard_black2();
            break;
        case Menu_BW_Hard_Red:
            filter_bw_hard_red();
            break;
        case Menu_BW_Hard_Green:
            filter_bw_hard_green();
            break;
        case Menu_BW_Hard_Blue:
            filter_bw_hard_blue();
            break;
        case Menu_BW_Average:
            filter_average();
            break;
        case Menu_Quit:
            glutDestroyWindow(main_window.window);
            exit(0);
            break;
        case Menu_Clear:
            memcpy(main_image.screen_pixels,
                   main_image.original_pixels,
                   main_image.number_of_pixels * sizeof(RGBA));
            glutPostRedisplay();
            break;
        default:
            fprintf(stderr, "Unknown option %d\n", (int) option);
            redraw = false;
            break;
    }
    if (redraw) {
        glutPostRedisplay();
    }
}

static void menuBlackAndWhite(int num) {
    exec_option((Menu_Values) num);
}

static void menuMain(int num) {
    exec_option((Menu_Values) num);
}

void on_special_keys(int key, int x __attribute__((unused)), int y __attribute__((unused))) {
    switch (key) {
        case GLUT_KEY_F1:
            fprintf(stdout, "F1 pressed\n");
            break;
        default:
            fprintf(stdout, "Special key %d pressed\n", key);
            break;
    }
}

void on_key(unsigned char key, int x __attribute__((unused)), int y __attribute__((unused))) {
    switch (key) {
        case 'c':
            exec_option(Menu_Clear);
            break;
        case 'q':
            exec_option(Menu_Quit);
            break;
        case 'R':
            exec_option(Menu_BW_Hard_Red);
            break;
        case 'G':
            exec_option(Menu_BW_Hard_Green);
            break;
        case 'B':
            exec_option(Menu_BW_Hard_Blue);
            break;
    }
}

void createMenu(void) {
    main_window.submenu_id = glutCreateMenu(menuBlackAndWhite);
    glutAddMenuEntry("Normal 1", Menu_BW_Normal1);
    glutAddMenuEntry("Normal 2", Menu_BW_Normal2);
    glutAddMenuEntry("Normal 3", Menu_BW_Normal3);
    glutAddMenuEntry("Average", Menu_BW_Average);
    glutAddMenuEntry("Hard 1", Menu_BW_Hard1);
    glutAddMenuEntry("Hard 2", Menu_BW_Hard2);
    glutAddMenuEntry("Hard Red :r", Menu_BW_Hard_Red);
    glutAddMenuEntry("Hard Green :g", Menu_BW_Hard_Green);
    glutAddMenuEntry("Hard Blue :b", Menu_BW_Hard_Blue);
    glutAddMenuEntry("Suppress saturation", Menu_BW_No_Saturation);

    main_window.menu_id = glutCreateMenu(menuMain);
    glutAddMenuEntry("Clear :c", Menu_Clear);
    glutAddSubMenu("Black and White", main_window.submenu_id);
    glutAddMenuEntry("Quit :q", Menu_Quit);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
