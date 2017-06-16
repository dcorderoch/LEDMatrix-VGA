#ifndef LED_MAT_LIBRARY_H
#define LED_MAT_LIBRARY_H

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif /* STDIO */

#ifndef INTTYPES
#define INTTYPES
#include <inttypes.h>
#endif /* INTTYPES */

#ifndef STDBOOL
#define STDBOOL
#include <stdbool.h>
#endif /* STDBOOL */

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif /* STDLIB */

#ifndef UNISTD
#define UNISTD
#include <unistd.h>
#endif /* UNISTD */

#ifndef GLIB
#define GLIB
#include <glib.h>
#endif /* GLIB */

#ifndef GPRINTF
#define GPRINTF
#include <glib/gprintf.h>
#endif /* GPRINTF */

#ifndef ERRNO
#define ERRNO
#include <errno.h>
#endif /* ERRNO */

#ifndef STRING
#define STRING
#include <string.h>
#endif /* STRING */

#ifndef TIME
#define TIME
#include <time.h>
#endif /* TIME */

#ifndef TEXT_PRINT
#define TEXT_PRINT
#include "text_print.h"
#endif /* TEXT_PRINT */

/* uint8_t to char array conversion. */
char *
convert(uint8_t * a);

/* Wait a specified amount of milliseconds. */
void
wait( unsigned long milliseconds );

void
write_byte ( FILE ** dev_fd, uint8_t data );

void
open_device ( FILE ** dev_fd, char * filename );

void
close_device ( FILE ** dev_fd );

/* Display a symbol on the LED Matrix. */
void
display_symbol ( uint8_t * symbol_data, uint8_t length );

/* Turn all LEDs off. */
void
clear_led_mat ( void );

void
print_test ( void );

/* High level abstract text print function, uses the previous functions
   to "print" characters in the LED Matrix. */
void
led_mat_print ( int argc, char ** argv );

#endif /* LED_MAT_LIBRARY_H */
