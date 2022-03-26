//
// Created by bernard on 21/03/2022.
//

#ifndef ONECOLOR_FILTERS_H
#define ONECOLOR_FILTERS_H

imageLibraryError filterGrayscale(
        imgRawImage* lpInput,
        imgRawImage** lpOutput);

imageLibraryError hsvFilterRed(
        imgRawImage* lpInput,
        imgRawImage** lpOutput);
imageLibraryError hsvFilterGreen(
        imgRawImage* lpInput,
        imgRawImage** lpOutput);
imageLibraryError hsvFilterBlue(
        imgRawImage* lpInput,
        imgRawImage** lpOutput);
imageLibraryError hsvFilterYellow(
        imgRawImage* lpInput,
        imgRawImage** lpOutput);
imageLibraryError hsvFilterNormal(
        imgRawImage* lpInput,
        imgRawImage** lpOutput);

#endif //ONECOLOR_FILTERS_H
