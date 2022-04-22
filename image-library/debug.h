//
// Created by bernard on 22/04/22.
//

#ifndef ONE_COLOR_DEBUG_H
#define ONE_COLOR_DEBUG_H

#define DBG()   fprintf(stdout, "DEBUG %5d %-32s %s\n", \
                    __LINE__, __FILE_NAME__, __func__)

#endif //ONE_COLOR_DEBUG_H
