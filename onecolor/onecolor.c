#include <stdio.h>
#include <stdlib.h>

#include "../imglib/color-data.h"
#include "../imglib/image-files.h"
#include "../imglib/filters.h"
#include "../imglib/hsv-filter.h"

static void dohelp(const int exit_code) {
    fprintf(stderr, "onecolor [-0|-R|-V|-B|-Y|-h hue] jpegin jpegout\n");
    exit(exit_code);
}
static inline float getFloatArg(char *arg) {
    char *endptr;
    float f = strtof(arg, &endptr);
    if (endptr == arg) {
        fprintf(stderr, "Float argument expected, get %s instead\n", arg);
        dohelp(1);
    }
    return f;
}
int main(int argc, char **argv) {
    imageLibraryError (*filter)(
            imgRawImage* lpInput,
            imgRawImage** lpOutput) = NULL;
    if (argc < 3) {
        dohelp(1);
    } else {
        int idx = 1;
        if (*argv[1] == '-') {
            switch (argv[1][idx]) {
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
                case 'h': filter = hsvFilterNormal;
                    idx++;
                    if (idx >= argc) {
                        dohelp(1);
                    }
                    mainHSVFilter.h = getFloatArg(argv[idx]);
                    break;
                default:
                    fprintf(stderr, "Bad filter name (%s)\n", argv[1]);
                    break;
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
