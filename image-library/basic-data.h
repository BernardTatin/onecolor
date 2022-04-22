//
// Created by bernard on 22/04/22.
//

#ifndef ONE_COLOR_BASIC_DATA_H
#define ONE_COLOR_BASIC_DATA_H

typedef unsigned char u8;
typedef struct __attribute__((__packed__)) {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RGBA;

typedef struct __attribute__((__packed__)) {
    u8 a;
    u8 r;
    u8 g;
    u8 b;
} ARGB;

typedef struct {
    float r;
    float g;
    float b;
} fRGB;

typedef struct {
    float h;
    float s;
    float v;
} HSV;
#endif //ONE_COLOR_BASIC_DATA_H
