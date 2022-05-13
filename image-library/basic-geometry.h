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
} OCPoint;

typedef struct {
    oc_int width;
    oc_int height;
} OCDimensions;

typedef struct {
    oc_int left;
    oc_int top;
    oc_int width;
    oc_int height;
} OCRectangle;

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
