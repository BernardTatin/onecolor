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
// Created by bernard on 29/03/2022.
//

#ifndef ONE_COLOR_MAIN_CONFIGURATION_H
#define ONE_COLOR_MAIN_CONFIGURATION_H

#include "hsv-filter.h"

extern const float hsv_Red;
extern const float hsv_Green;
extern const float hsv_Blue;
extern const float hsv_Yellow;

typedef enum {
    Filter_Grey,
    Filter_Red,
    Filter_Green,
    Filter_Blue,
    Filter_Yellow,
    Filter_Hue
}                  FilterType;

typedef struct {
    bool       verbose;
    FilterType type;
    float      delta;
    float      hue;
}                  Global_Configuration;

extern Global_Configuration global_configuration;

#endif //ONE_COLOR_MAIN_CONFIGURATION_H
