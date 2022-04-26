//
// Created by bernard on 26/04/22.
//

#ifndef ONE_COLOR_BASIC_GEOMETRY_H
#define ONE_COLOR_BASIC_GEOMETRY_H

typedef struct {
    int x;
    int y;
} OCPoint;

typedef struct {
    int width;
    int height;
} OCDimensions;

typedef struct {
    int left;
    int top;
    int width;
    int height;
} OCRectangle;

#endif //ONE_COLOR_BASIC_GEOMETRY_H
