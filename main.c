#include <stdio.h>
#include <stdlib.h>

#include "color-data.h"
#include "image-files.h"
#include "filters.h"

int main(int argc, char **argv) {
    imageLibraryError (*filter)(
            imgRawImage* lpInput,
            imgRawImage** lpOutput) = NULL;
    if (argc < 3) {
        fprintf(stderr, "%s [-0|-R|-V|-B|-Y] jpegin jpegout\n", argv[0]);
        exit (1);
    } else {
        int idx = 1;
        if (*argv[1] == '-') {
            switch (argv[1][1]) {
                case '0': filter = filterGrayscale;
                    break;
                case 'R': filter = hsvFilterRed;
                    break;
                case 'G': filter = hsvFilterGreen;
                    break;
                case 'B': filter = hsvFilterBlue;
                    break;
                case 'Y': filter = hsvFilterYellow;
                    break;
                default:
                    fprintf(stderr, "Bad filter name (%s)\n", argv[1]);
            }
            idx++;
        }
        imgRawImage *image = loadJpegImageFile(argv[idx]);
        imgRawImage *grey_image;
        if (image == NULL) {
            fprintf(stderr, "Cannot read %s\n", argv[idx]);
            exit (1);
        }
        idx++;
        filter(image, &grey_image);
        storeJpegImageFile(grey_image, argv[idx]);
    }
    return 0;
}
