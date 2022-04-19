//
// Created by bernard on 19/04/22.
//

#include <stdbool.h>
#include <IL/il.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Ecore.h>
#include <Ecore_Evas.h>
#include <stdio.h>
#include <errno.h>
#include "evas-configuration.h"

const int default_width = 640;
const int default_height = 480;
const int dx = 5;
const int dy = 5;

char *program_name = NULL;
char *img_source = NULL;
char *img_base_source = NULL;
char *img_destination = NULL;

MainData main_data = {0};
EV_image mainImage;
