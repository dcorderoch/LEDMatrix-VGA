#include "led_mat_library.h"

void
display_symbol ( uint8_t * symbol_data )
{
  int led_mat_fd;
  char led_mat_filename[40];
  uint8_t buf[2];

  /*sprintf ( led_mat_filename, "/sys/bus/i2c/drivers/ledMatc/1-0070/mat_led" );*/
  sprintf ( led_mat_filename, "/dev/i2c-1" );
  if ( (led_mat_fd = open ( led_mat_filename, O_RDWR )) < 0 )
    {
      printf ( "Failed to open the bus.\n" );
      exit ( EXIT_FAILURE );
    }
  if ( ioctl (led_mat_fd, I2C_SLAVE, LED_MAT_ADDRESS ) < 0 )
    {
      printf ( "Failed to acquire bus access and/or talk to slave.\n" );
      exit ( EXIT_FAILURE );
    }

  uint8_t reg = LED_MAT_PRIME_REG;
  buf[0] = reg;

  int i;
  for ( i = 0 ; i < SYMBOL_LENGTH ; ++i )
  {
    buf[1] = symbol_data[i];

    if ( write ( led_mat_fd, buf, 2 ) != 2 )
      {
        printf ( "Failed to acquire bus access and/or talk to slave.\n" );
        exit ( EXIT_FAILURE );
      }
  }

  if ( (close ( led_mat_fd )) < 0 )
    {
      printf ( "Failed to close the bus.\n" );
      exit ( EXIT_FAILURE );
    }
}

void
print_a ( void )
{
  display_symbol ( A );
}

void
led_mat_led_array_on ( uint8_t * array_state, uint8_t length )
{
  int led_mat_fd;
  char led_mat_filename[40];
  uint8_t buf[10];

  /*sprintf ( led_mat_filename, "/sys/bus/i2c/drivers/ledMatc/1-0070/mat_led" );*/
  sprintf ( led_mat_filename, "/dev/i2c-1" );
  if ( (led_mat_fd = open ( led_mat_filename, O_RDWR )) < 0 )
    {
      printf ( "Failed to open the bus.\n" );
      exit ( EXIT_FAILURE );
    }
  if ( ioctl (led_mat_fd, I2C_SLAVE, LED_MAT_ADDRESS ) < 0 )
    {
      printf ( "Failed to acquire bus access and/or talk to slave.\n" );
      exit ( EXIT_FAILURE );
    }

  uint8_t reg = 0x00;
  buf[0] = reg;
  buf[1] = 0xff;

  if ( write ( led_mat_fd, buf, 2 ) != 2 )
    {
      printf ( "Failed to acquire bus access and/or talk to slave.\n" );
      exit ( EXIT_FAILURE );
    }

  if ( (close ( led_mat_fd )) < 0 )
    {
      printf ( "Failed to close the bus.\n" );
      exit ( EXIT_FAILURE );
    }
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
