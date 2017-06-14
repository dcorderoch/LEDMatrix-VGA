#ifndef LED_MAT_LIB_H
#define LED_MAT_LIB_H

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif /* STDIO */

#ifndef TEXT_PRINT
#define TEXT_PRINT
#include "text_print.h"
#endif /* TEXT_PRINT */

void
led_mat_print ( int argc, char ** argv );

#endif /* LED_MAT_LIB_H */
