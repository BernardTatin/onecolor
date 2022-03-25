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

extern HSVFilter hsvRed;
extern HSVFilter hsvGreen;
extern HSVFilter hsvBlue;
extern HSVFilter hsvYellow;

imageLibraryError hsvFilter(
        HSVFilter *filter,
        imgRawImage* lpInput,
        imgRawImage** lpOutput);

#endif //ONECOLOR_HSV_FILTER_H
