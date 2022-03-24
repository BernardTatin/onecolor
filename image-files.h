//
// Created by bernard on 24/03/2022.
//

#ifndef ONECOLOR_IMAGE_FILES_H
#define ONECOLOR_IMAGE_FILES_H

#include "filters.h"

imgRawImage *loadJpegImageFile(char *lpFilename);
int storeJpegImageFile(imgRawImage *lpImage, char *lpFilename);

#endif //ONECOLOR_IMAGE_FILES_H
