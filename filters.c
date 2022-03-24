//
// Created by bernard on 21/03/2022.
// from:
//      https://www.tspi.at/2020/03/20/libjpegexample.html
//

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "color-tools.h"
#include "filters.h"


imageLibraryError filterGrayscale(imgRawImage* lpInput, imgRawImage** lpOutput) {
    unsigned long int i;

    if(lpOutput == NULL) {
        (*lpOutput) = lpInput; /* We will replace our input structure ... */
    } else {
        (*lpOutput) = make_lpOutput(lpInput);
    }

    for(i = 0; i < lpInput->width*lpInput->height; i=i+1) {
        /* Do a grayscale transformation */
        int i3 = i*3;
        unsigned char luma = (unsigned char)getLuma(Rin(i3), Gin(i3), Bin(i3) );
        Rout(i3) = luma;
        Gout(i3) = luma;
        Bout(i3) = luma;
    }

    return imageLibE_Ok;
}

imageLibraryError filterRed(
        imgRawImage* lpInput,
        imgRawImage** lpOutput
) {
    unsigned long int i;

    if(lpOutput == NULL) {
        (*lpOutput) = lpInput; /* We will replace our input structure ... */
    } else {
        (*lpOutput) = make_lpOutput(lpInput);
    }

    for(i = 0; i < lpInput->width*lpInput->height; i=i+1) {
        int i3 = i*3;
        if (isRed(Rin(i3), Gin(i3), Bin(i3))) {
            Rout(i3) = Rin(i3);
            Gout(i3) = Gin(i3);
            Bout(i3) = Bin(i3);
        } else {
            unsigned char luma = (unsigned char)getLuma(Rin(i3), Gin(i3), Bin(i3) );
            Rout(i3) = luma;
            Gout(i3) = luma;
            Bout(i3) = luma;
        }
    }

    return imageLibE_Ok;
}

imageLibraryError filterGreen(
        imgRawImage* lpInput,
        imgRawImage** lpOutput
) {
    unsigned long int i;

    if(lpOutput == NULL) {
        (*lpOutput) = lpInput; /* We will replace our input structure ... */
    } else {
        (*lpOutput) = make_lpOutput(lpInput);
    }

    for(i = 0; i < lpInput->width*lpInput->height; i=i+1) {
        /* Do a grayscale transformation */
        int i3 = i*3;
        unsigned char luma = (unsigned char)getLuma(Rin(i3), Gin(i3), Bin(i3) );

        if (luma < lpInput->lpData[i3 + 1]) {
            Rout(i3) = Rin(i3);
            Gout(i3) = Gin(i3);
            Bout(i3) = Bin(i3);
        } else {
            Rout(i3) = luma;
            Gout(i3) = luma;
            Bout(i3) = luma;
        }
    }

    return imageLibE_Ok;
}

imageLibraryError filterBlue(
        imgRawImage* lpInput,
        imgRawImage** lpOutput
) {
    unsigned long int i;

    if(lpOutput == NULL) {
        (*lpOutput) = lpInput; /* We will replace our input structure ... */
    } else {
        (*lpOutput) = make_lpOutput(lpInput);
    }

    for(i = 0; i < lpInput->width*lpInput->height; i=i+1) {
        /* Do a grayscale transformation */
        int i3 = i*3;
        unsigned char luma = (unsigned char)getLuma(Rin(i3), Gin(i3), Bin(i3) );
        if (luma < lpInput->lpData[i3 + 2]) {
            Rout(i3) = Rin(i3);
            Gout(i3) = Gin(i3);
            Bout(i3) = Bin(i3);
        } else {
            Rout(i3) = luma;
            Gout(i3) = luma;
            Bout(i3) = luma;
        }
    }

    return imageLibE_Ok;
}

imageLibraryError filterYellow(
        imgRawImage* lpInput,
        imgRawImage** lpOutput
) {
    unsigned long int i;

    if(lpOutput == NULL) {
        (*lpOutput) = lpInput; /* We will replace our input structure ... */
    } else {
        (*lpOutput) = make_lpOutput(lpInput);
    }

    for(i = 0; i < lpInput->width*lpInput->height; i=i+1) {
        /* Do a grayscale transformation */
        int i3 = i*3;
        if (isYellow(Rin(i3), Gin(i3), Bin(i3))) {
            Rout(i3) = Rin(i3);
            Gout(i3) = Gin(i3);
            Bout(i3) = Bin(i3);
        } else {
            float luma = getLuma(Rin(i3), Gin(i3), Bin(i3) );
            Rout(i3) = (unsigned char)luma;
            Gout(i3) = (unsigned char)luma;
            Bout(i3) = (unsigned char)luma;
        }
    }

    return imageLibE_Ok;
}
