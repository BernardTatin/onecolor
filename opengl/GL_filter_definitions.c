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
// Created by bernard on 12/04/2022.
//

#include <stdbool.h>
#include <math.h>
#include <IL/il.h>
#include <GL/glut.h>

#include "GL-Configuration.h"
#include "../filtering/GL-filters.h"

/*
 * Normal black and white
 */

GLPFilterBWNormal p_bw_normal1 = {
        .KlR = 0.299f,
        .KlG = 0.587f,
        .KlB = 0.114f
};
GLPFilterBWNormal p_bw_normal2 = {
        .KlR = 0.2126f,
        .KlG = 0.7152f,
        .KlB = 0.0722f
};
GLPFilterBWNormal p_bw_normal3 = {
        .KlR = 0.2627f,
        .KlG = 0.6780f,
        .KlB = 0.0593f
};

GLFilter bw_normal1 = {
        FT_BW_Simple,
        bw_normal_function,
        &p_bw_normal1
};
GLFilter bw_normal2 = {
        FT_BW_Simple,
        bw_normal_function,
        &p_bw_normal1
};
GLFilter bw_normal3 = {
        FT_BW_Simple,
        bw_normal_function,
        &p_bw_normal1
};

/*
 * hard black and white
 */

GLPFilterBWHard p_bw_hard_average = {
        .type = BWH_average,
        .darkR = 0.0f,
        .darkG = 0.0f,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};

const float     dark               = 120.0f;
GLPFilterBWHard p_bw_hard_averageR = {
        .type = BWH_average,
        .darkR = dark,
        .darkG = 0.0f,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};
GLPFilterBWHard p_bw_hard_averageG = {
        .type = BWH_average,
        .darkR = 0.0f,
        .darkG = dark,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};
GLPFilterBWHard p_bw_hard_averageB = {
        .type = BWH_average,
        .darkR = 0.0f,
        .darkG = 0.0f,
        .darkB = dark,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};
GLPFilterBWHard p_bw_hard_median   = {
        .type = BWH_median,
        .darkR = 0.0f,
        .darkG = 0.0f,
        .darkB = 0.0f,
        .lightR = 1.0f,
        .lightG = 1.0f,
        .lightB = 1.0f,
};

GLFilter bw_hard_average  = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_average
};
GLFilter bw_hard_averageR = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_averageR
};
GLFilter bw_hard_averageG = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_averageG
};
GLFilter bw_hard_averageB = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_averageB
};
GLFilter bw_hard_median   = {
        .type = FT_BW_HARD,
        .filter_function = bw_hard_function,
        .parameters = &p_bw_hard_median
};
