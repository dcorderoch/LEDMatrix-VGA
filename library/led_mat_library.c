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
  wait ( 2000 );
  close_device ( &dev_fd );
}

void
open_device ( int * dev_fd )
{
  int led_mat_fd = 0;
  if ( (led_mat_fd = open ( FILENAME, O_WRONLY | O_RSYNC )) < 0 )
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
  int led_mat_fd;
  char led_mat_filename[40];

  sprintf ( led_mat_filename, FILENAME );

  open_device ( &led_mat_fd );

  set_device_as_slave ( &led_mat_fd );

  int i;
  for ( i = 0 ; i < length ; i++ )
  {
    printf ( "iteration:%d\n", i );
    uint8_t value = i ? 1 << i : LED_MAT_PRIME_REG;
    printf ( "value:%d\n", value );
    write_byte ( &led_mat_fd, value, symbol_data[i] );
    wait ( 2000 );
  }

  wait ( 2000 );
  close_device ( &led_mat_fd );
}

void
print_a ( void )
{
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
