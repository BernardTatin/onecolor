//
// Created by bernard on 21/03/2022.
// from:
//      https://www.tspi.at/2020/03/20/libjpegexample.html
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


#include "color-tools.h"
#include "filters.h"
#include "hsv-filter.h"

imageLibraryError hsvFilterRed(
        imgRawImage* lpInput,
        imgRawImage** lpOutput) {
    mainHSVFilter.h = hsvRed;
    return hsvFilter(&mainHSVFilter, lpInput, lpOutput);
}

imageLibraryError hsvFilterGreen(
        imgRawImage* lpInput,
        imgRawImage** lpOutput) {
    mainHSVFilter.h = hsvGreen;
    return hsvFilter(&mainHSVFilter, lpInput, lpOutput);
}

imageLibraryError hsvFilterBlue(
        imgRawImage* lpInput,
        imgRawImage** lpOutput) {
    mainHSVFilter.h = hsvBlue;
    return hsvFilter(&mainHSVFilter, lpInput, lpOutput);
}

imageLibraryError hsvFilterYellow(
        imgRawImage* lpInput,
        imgRawImage** lpOutput) {
    mainHSVFilter.h = hsvYellow;
    return hsvFilter(&mainHSVFilter, lpInput, lpOutput);
}

imageLibraryError hsvFilterNormal(
        imgRawImage* lpInput,
        imgRawImage** lpOutput) {
    return hsvFilter(&mainHSVFilter, lpInput, lpOutput);
}

imageLibraryError filterGrayscale(imgRawImage* lpInput, imgRawImage** lpOutput) {
    unsigned long int pixelNumber = lpInput->width*lpInput->height;
    (*lpOutput) = make_lpOutput(lpInput);

    for(unsigned int i = 0; i < pixelNumber; i++) {
        /* Do a grayscale transformation */
        unsigned long  i3 = i*3;
        unsigned char luma = (unsigned char)getLuma(Rin(i3), Gin(i3), Bin(i3) );
        Rout(i3) = luma;
        Gout(i3) = luma;
        Bout(i3) = luma;
    }

    return imageLibE_Ok;
}
