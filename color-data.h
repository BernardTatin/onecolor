//
// Created by bernard on 24/03/2022.
//

#ifndef ONECOLOR_COLOR_DATA_H
#define ONECOLOR_COLOR_DATA_H

#define KlR 0.299f
#define KlG 0.587f
#define KlB 0.114f

typedef struct _imgRawImage {
    unsigned int numComponents;
    unsigned long int width, height;

    unsigned char* lpData;
} imgRawImage;

typedef enum {
    imageLibE_Ok,
    imageLibE_Bad
} imageLibraryError;

#endif //ONECOLOR_COLOR_DATA_H
