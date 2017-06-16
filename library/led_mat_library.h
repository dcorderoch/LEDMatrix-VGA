
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

/* Return the number characters of int_num in an array. */
char *
int_to_char_array ( uint8_t * int_num );

/* Wait a specified amount of milliseconds. */
void
milli_sleep ( unsigned long milliseconds );

/* Write a byte to the LED matrix row specified by dev_fd. */
void
write_to_led_matrix ( FILE ** dev_fd, uint8_t data );

/* Open the LED matrix row specified by filename
   and assign it to dev_fd. */
void
open_device ( FILE ** dev_fd, char * filename );

/* Close the LED matrix row specified by dev_fd. */
void
close_device ( FILE ** dev_fd );

/* Display a symbol on the LED Matrix. */
void
display_symbol ( uint8_t * symbol_data, uint8_t length );

/* Turn all LEDs off. */
void
clear_led_mat ( void );

/* Print all allowed characters on the LED matrix. */
void
print_test ( void );

/* Print the A character on the LED matrix. */
void
print_a( void );

/* Print the B character on the LED matrix. */
void
print_b( void );

/* Print the C character on the LED matrix. */
void
print_c( void );

/* Print the D character on the LED matrix. */
void
print_d( void );

/* Print the E character on the LED matrix. */
void
print_e( void );

/* Print the F character on the LED matrix. */
void
print_f( void );

/* Print the G character on the LED matrix. */
void
print_g( void );

/* Print the H character on the LED matrix. */
void
print_h( void );

/* Print the I character on the LED matrix. */
void
print_i( void );

/* Print the J character on the LED matrix. */
void
print_j( void );

/* Print the K character on the LED matrix. */
void
print_k( void );

/* Print the L character on the LED matrix. */
void
print_l( void );

/* Print the M character on the LED matrix. */
void
print_m( void );

/* Print the N character on the LED matrix. */
void
print_n( void );

/* Print the O character on the LED matrix. */
void
print_o( void );

/* Print the P character on the LED matrix. */
void
print_p( void );

/* Print the Q character on the LED matrix. */
void
print_q( void );

/* Print the R character on the LED matrix. */
void
print_r( void );

/* Print the S character on the LED matrix. */
void
print_s( void );

/* Print the T character on the LED matrix. */
void
print_t( void );

/* Print the U character on the LED matrix. */
void
print_u( void );

/* Print the V character on the LED matrix. */
void
print_v( void );

/* Print the W character on the LED matrix. */
void
print_w( void );

/* Print the X character on the LED matrix. */
void
print_x( void );

/* Print the Y character on the LED matrix. */
void
print_y( void );

/* Print the Z character on the LED matrix. */
void
print_z( void );

/* Print the 1 character on the LED matrix. */
void
print_1( void );

/* Print the 2 character on the LED matrix. */
void
print_2( void );

/* Print the 3 character on the LED matrix. */
void
print_3( void );

/* Print the 4 character on the LED matrix. */
void
print_4( void );

/* Print the 5 character on the LED matrix. */
void
print_5( void );

/* Print the 6 character on the LED matrix. */
void
print_6( void );

/* Print the 7 character on the LED matrix. */
void
print_7( void );

/* Print the 8 character on the LED matrix. */
void
print_8( void );

/* Print the 9 character on the LED matrix. */
void
print_9( void );

/* Print the 0 character on the LED matrix. */
void
print_0( void );

/* Print the smile emoji on the LED matrix. */
void
print_smile ( void );

/* Print the frown emoji on the LED matrix. */
void
print_frown ( void );

/* Print the serious emoji on the LED matrix. */
void
print_serious ( void );

/* Print the heart emoji on the LED matrix. */
void
print_heart ( void );

/* Print the arrow emoji on the LED matrix. */
void
print_arrow ( void );

/* Print the dollar emoji on the LED matrix. */
void
print_dollar ( void );

/* Print the note emoji on the LED matrix. */
void
print_note ( void );

/* Print the mars emoji on the LED matrix. */
void
print_mars ( void );

/* Print the venus emoji on the LED matrix. */
void
print_venus ( void );

/* Print the nomouth emoji on the LED matrix. */
void
print_nomouth ( void );

/* High level abstract text print function, uses the previous functions
   to "print" characters in the LED Matrix. */
void
led_mat_print ( int argc, char ** argv );

#endif /* LED_MAT_LIBRARY_H */
