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
// Created by bernard on 21/03/2022.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "color-data.h"
#include "image-files.h"
#include "../filtering/filters.h"
#include "../filtering/hsv-filter.h"
#include "main-configuration.h"

static void do_help(const int exit_code) {
    fprintf(stderr, "one-color [-0|-R|-V|-B|-Y|-h hue] jpegin jpegout\n");
    exit(exit_code);
}

static inline float get_float_arg(char *arg) {
    char  *end_ptr;
    float f = strtof(arg, &end_ptr);
    if (end_ptr == arg) {
        fprintf(stderr, "Float argument expected, get %s instead\n", arg);
        do_help(1);
    }
    return f;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        do_help(1);
    } else {
        int idx = 1;
        while (*argv[idx] == '-') {
            switch (argv[idx][1]) {
                case 'V' :
                    global_configuration.verbose = true;
                    break;
                case '0':
                    global_configuration.type = Filter_Grey;
                    break;
                case 'R':
                    global_configuration.type = Filter_Red;
                    break;
                case 'G':
                    global_configuration.type = Filter_Green;
                    break;
                case 'B':
                    global_configuration.type = Filter_Blue;
                    break;
                case 'Y':
                    global_configuration.type = Filter_Yellow;
                    break;
                case 'h':
                    global_configuration.type = Filter_Hue;
                    idx++;
                    if (idx >= argc) {
                        do_help(1);
                    }
                    global_configuration.hue = get_float_arg(argv[idx]);
                    break;
                default:
                    fprintf(stderr, "Bad filter name (%s)\n", argv[1]);
                    break;
            }
            idx++;
        }
        ImageLib_RawImage *image = loadJpegImageFile(argv[idx]);
        ImageLib_RawImage *grey_image;
        if (image == NULL) {
            fprintf(stderr, "Cannot read %s\n", argv[idx]);
            exit(1);
        }
        idx++;
        exec_filter(image, &grey_image);
        storeJpegImageFile(grey_image, argv[idx]);
    }
    return 0;
}
