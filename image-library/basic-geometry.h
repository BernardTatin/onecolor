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
// Created by bernard on 26/04/22.
//

#ifndef ONE_COLOR_BASIC_GEOMETRY_H
#define ONE_COLOR_BASIC_GEOMETRY_H

#include "basic-types.h"

typedef int oc_int;

typedef struct {
    oc_int x;
    oc_int y;
}           OCPoint;

typedef struct {
    oc_int width;
    oc_int height;
}           OCDimensions;

typedef struct {
    oc_int left;
    oc_int top;
    oc_int width;
    oc_int height;
}           OCRectangle;

/*
 *  from Microsoft:
#define TYPE_NAME(X) _Generic((X), \
      int: "int", \
      char: "char", \
      double: "double", \
      default: "unknown")

  * from https://en.cppreference.com/w/c/language/generic
 // Possible implementation of the tgmath.h macro cbrt
#define cbrt(X) _Generic((X), \
              long double: cbrtl, \
                  default: cbrt,  \
                    float: cbrtf  \
              )(X)

 * https://gist.github.com/shintakezou/82c4601284dc05fd26f8
// this works (thanks to Michael Stoffregen who suggested the right way)
#define sumx(X, Y) _Generic((X),                    \
                            int: sum2l,             \
                            long: sum2l,            \
                            double: sum2d,          \
                            float: sum2d,           \
                            vec2d: sum2v)((X), (Y))
 */
static inline int mini(const int j, const int k) {
    if (j < k) {
        return j;
    } else {
        return k;
    }
}

static inline int maxi(const int j, const int k) {
    if (j > k) {
        return j;
    } else {
        return k;
    }
}

#endif //ONE_COLOR_BASIC_GEOMETRY_H
