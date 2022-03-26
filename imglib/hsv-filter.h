//
// Created by bernard on 25/03/2022.
//

#ifndef ONECOLOR_HSV_FILTER_H
#define ONECOLOR_HSV_FILTER_H

typedef struct {
    float h;
    float s;
    float v;
} HSV;

typedef struct {
    float h;
    float delta;
} HSVFilter;

extern const float defaultHSVDelta;
extern HSVFilter mainHSVFilter;

extern const float hsvRed;
extern const float hsvGreen;
extern const float hsvBlue;
extern const float hsvYellow;

imageLibraryError hsvFilter(
        HSVFilter *filter,
        imgRawImage* lpInput,
        imgRawImage** lpOutput);

#endif //ONECOLOR_HSV_FILTER_H
