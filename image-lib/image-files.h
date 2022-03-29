//
// Created by bernard on 24/03/2022.
//

#ifndef ONECOLOR_IMAGE_FILES_H
#define ONECOLOR_IMAGE_FILES_H

#include "filters.h"

ImageLib_RawImage *loadJpegImageFile(char *lpFilename);
int storeJpegImageFile(ImageLib_RawImage *lpImage, char *lpFilename);

#endif //ONECOLOR_IMAGE_FILES_H
