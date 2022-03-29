//
// Created by bernard on 24/03/2022.
//

#ifndef ONECOLOR_COLOR_DATA_H
#define ONECOLOR_COLOR_DATA_H

#define KlR 0.299f
#define KlG 0.587f
#define KlB 0.114f

typedef struct {
    unsigned int numComponents;
    unsigned long int width, height;

    unsigned char* lpData;
} ImageLib_RawImage;

typedef enum {
    imageLibE_Ok,
    imageLibE_Bad
} ImageLib_Error;

#endif //ONECOLOR_COLOR_DATA_H
