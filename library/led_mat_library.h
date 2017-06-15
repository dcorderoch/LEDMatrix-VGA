#ifndef LED_MAT_LIB_H
#define LED_MAT_LIB_H

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif /* STDIO */

#ifndef FCNTL
#define FCNTL
#include <fcntl.h>
#endif /* FCNTL */

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

#ifndef TEXT_PRINT
#define TEXT_PRINT
#include "text_print.h"
#endif /* TEXT_PRINT */

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

#ifndef I2C_DEV
#define I2C_DEV
#include <linux/i2c-dev.h>
#endif /* I2C_DEV */

#ifndef IOCTL
#define IOCTL
#include <sys/ioctl.h>
#endif /* IOCTL */

#ifndef SYS_TYPES
#define SYS_TYPES
#include <sys/types.h>
#endif /* SYS_TYPES */

#ifndef SYS_STAT
#define SYS_STAT
#include <sys/stat.h>
#endif /* SYS_STAT */

#ifndef LED_MAT_ADDRESS
#define LED_MAT_ADDRESS 0x70
#endif /* LED_MAT_ADDRESS */

#ifndef LED_MAT_PRIME_REG
#define LED_MAT_PRIME_REG 0x00
#endif /* LED_MAT_PRIME_REG */

#ifndef SYMBOL_LENGTH
#define SYMBOL_LENGTH 8
#endif /* SYMBOL_LENGTH */

#ifndef A_CHAR
#define A_CHAR
uint8_t A[8] =
  {
    0B00000000,
    0B00001100,
    0B00011110,
    0B00110011,
    0B00110011,
    0B00111111,
    0B00110011,
    0B00110011
  };
#endif /* A_CHAR */

/* Display a symbol on the LED Matrix. */
void
display_symbol ( uint8_t * symbol_data );

/* Print 'a' on the LED Matrix. */
void
print_a ( void );

/* Print a byte array on the LED Matrix. */
void
led_mat_led_array_on ( uint8_t * array_state, uint8_t length );

/* High level abstract text print function, uses the previous functions
   to "print" characters in the LED Matrix.
 */
void
led_mat_print ( int argc, char ** argv );

#endif /* LED_MAT_LIB_H */
