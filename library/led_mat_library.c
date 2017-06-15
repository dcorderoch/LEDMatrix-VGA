#include "led_mat_library.h"

#ifndef DEV_FILENAME
#define DEV_FILENAME "/sys/bus/i2c/drivers/ledMatc/1-0070/mat_led"
#endif /* DEV_FILENAME */

#ifndef FILENAME
#define FILENAME "/dev/i2c-1"
#endif /* FILENAME */

#ifndef LED_MAT_ADDRESS
#define LED_MAT_ADDRESS 0x70
#endif /* LED_MAT_ADDRESS */

#ifndef LED_MAT_PRIME_REG
#define LED_MAT_PRIME_REG 0x00
#endif /* LED_MAT_PRIME_REG */

#ifndef LED_BLINK_REG
#define LED_BLINK_REG 0x81
#endif /* LED_BLINK_REG */

#ifndef SYMBOL_LENGTH
#define SYMBOL_LENGTH 8
#endif /* SYMBOL_LENGTH */

#ifndef WRITE_BUFFER_SIZE
#define WRITE_BUFFER_SIZE 2
#endif /* BYTE_WRITE_BUFFER_SIZE */

#ifndef CLEAR
#define CLEAR
uint8_t CLEAR_LEDS[8] =
{
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000,
  0B00000000
};
#endif /* CLEAR */

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

#ifndef B_CHAR
#define B_CHAR
uint8_t B[8] =
{
  0B00000000,
  0B00111111,
  0B01100110,
  0B01100110,
  0B00111110,
  0B01100110,
  0B01100110,
  0B00111111
};
#endif /* B_CHAR */

#ifndef C_CHAR
#define C_CHAR
uint8_t C[8] =
{
  0B00000000,
  0B00111100,
  0B01100110,
  0B00000011,
  0B00000011,
  0B00000011,
  0B01100110,
  0B00111100
};
#endif /* C_CHAR */

#ifndef CHARACTERS
#define CHARACTERS
uint8_t * CHARS[3] =
{
  A,
  B,
  C
};
#endif /* CHARACTERS */

void
wait ( unsigned long milliseconds )
{
  unsigned long millisecs = milliseconds;
  struct timespec req = { 0 };
  time_t sec = (int)(millisecs / 1000);
  millisecs = millisecs - (sec * 1000);
  req.tv_sec = sec;
  req.tv_nsec = millisecs * 1000000L;
  nanosleep ( &req, &req );
}

void
read_byte ( int * dev_fd, uint8_t dev_register, uint8_t data, uint8_t * buffer )
{
  uint8_t buf[WRITE_BUFFER_SIZE] = { dev_register, data };

  if ( (*buffer = read ( *dev_fd, buf, WRITE_BUFFER_SIZE )) != WRITE_BUFFER_SIZE )
    {
      printf ( "read byte Failed to acquire bus access and/or talk to slave.\n" );
      exit ( EXIT_FAILURE );
    }
  printf ( "the value of the buffer is now:%d\n", *buffer );
}

void
write_byte ( int * dev_fd, uint8_t dev_register, uint8_t data )
{
  uint8_t buf[WRITE_BUFFER_SIZE] = { dev_register, data };

  if ( write ( *dev_fd, buf, WRITE_BUFFER_SIZE ) != WRITE_BUFFER_SIZE )
    {
      printf ( "Failed to acquire bus access and/or talk to slave.\n" );
      exit ( EXIT_FAILURE );
    }
}

void
set_blink_off ( void )
{
  int dev_fd = 0;
  open_device ( &dev_fd );
  set_device_as_slave ( &dev_fd );
  uint8_t blink_disable = 0xff; /* All bits on to disable. */
  write_byte ( &dev_fd, LED_BLINK_REG, blink_disable );
  wait ( 500 );
  close_device ( &dev_fd );
}

void
open_device ( int * dev_fd )
{
  int led_mat_fd = 0;
  if ( (led_mat_fd = open ( FILENAME, O_WRONLY )) < 0 )
    {
      printf ( "Failed to open the bus.\n" );
      exit ( EXIT_FAILURE );
    }
  *dev_fd = led_mat_fd;
}

void
close_device ( int * dev_fd )
{
  if ( (close ( *dev_fd )) < 0 )
    {
      printf ( "Failed to close the bus.\n" );
      exit ( EXIT_FAILURE );
    }
}

void
set_device_as_slave ( int * dev_fd )
{
  if ( ioctl ( *dev_fd, I2C_SLAVE, LED_MAT_ADDRESS ) < 0 )
    {
      printf ( "Failed to acquire bus access and/or talk to slave.\n" );
      exit ( EXIT_FAILURE );
    }
}

void
display_symbol ( uint8_t * symbol_data, uint8_t length )
{
  set_blink_off ();
  int led_mat_fd;

  int i;
  for ( i = 0 ; i < length ; i++ )
  {
    uint8_t value = i ? i * 2 : LED_MAT_PRIME_REG;
    uint8_t data = symbol_data[i];

    open_device ( &led_mat_fd );
    set_device_as_slave ( &led_mat_fd );
    write_byte ( &led_mat_fd, value, data );
    close_device ( &led_mat_fd );


    wait ( 250 );
  }
}

void
clear_led_mat ( void )
{
  display_symbol ( CLEAR_LEDS, SYMBOL_LENGTH );
}

void
print_test ( void )
{
  display_symbol ( A, SYMBOL_LENGTH );
  clear_led_mat ();
  display_symbol ( B, SYMBOL_LENGTH );
  clear_led_mat ();
}

void
print_a ( void )
{
  clear_led_mat ();
  display_symbol ( A, SYMBOL_LENGTH );
}

void
led_mat_print ( int argc, char ** argv )
{
  int start = 2;
  int end = argc;
  int i;

  printf ( "the message was:\n" );

  for ( i = start ; i < end ; i++ )
    {
      printf ( "%s ", argv[i] );
    }
  print_newline ();
}
