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
uint8_t CLEAR_LEDS[SYMBOL_LENGTH] =
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
uint8_t A[SYMBOL_LENGTH] =
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
uint8_t B[SYMBOL_LENGTH] =
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
uint8_t C[SYMBOL_LENGTH] =
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

#ifndef D_CHAR
#define D_CHAR
uint8_t D[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00011111,
  0B00110110,
  0B01100110,
  0B01100110,
  0B01100110,
  0B00110110,
  0B00011111
};
#endif /* D_CHAR */

#ifndef E_CHAR
#define E_CHAR
uint8_t E[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111111,
  0B01000110,
  0B00010110,
  0B00011110,
  0B00010110,
  0B01000110,
  0B01111111
};
#endif /* E_CHAR */

#ifndef F_CHAR
#define F_CHAR
uint8_t F[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111111,
  0B01000110,
  0B00010110,
  0B00011110,
  0B00010110,
  0B00000110,
  0B00001111
};
#endif /* F_CHAR */

#ifndef G_CHAR
#define G_CHAR
uint8_t G[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111100,
  0B01100110,
  0B00000011,
  0B00000011,
  0B01110011,
  0B01100110,
  0B01111100
};
#endif /* G_CHAR */

#ifndef H_CHAR
#define H_CHAR
uint8_t H{SYMBOL_LENGTH] =
{
  0B00000000,
  0B00110011,
  0B00110011,
  0B00110011,
  0B00111111,
  0B00110011,
  0B00110011,
  0B00110011
};
#endif /* H_CHAR */

#ifndef I_CHAR
#define I_CHAR
uint8_t I[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00011110,
  0B00001100,
  0B00001100,
  0B00001100,
  0B00001100,
  0B00001100,
  0B00011110
};
#endif /* I_CHAR */

#ifndef J_CHAR
#define J_CHAR
uint8_t J[SYMBOL_LENGTH] =
{
  0B00000000,
  0B11110000,
  0B01100000,
  0B01100000,
  0B01100000,
  0B01100110,
  0B01100110,
  0B00111100
};
#endif /* J_CHAR */

#ifndef K_CHAR
#define K_CHAR
uint8_t K[SYMBOL_LENGTH] =
{
  0B00000000,
  0B11001110,
  0B11001100,
  0B01101100,
  0B00111100,
  0B01101100,
  0B11001100,
  0B11001110
};
#endif /* K_CHAR */

#ifndef L_CHAR
#define L_CHAR
uint8_t L[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00001111,
  0B00000110,
  0B00000110,
  0B00000110,
  0B01000110,
  0B01100110,
  0B01111111
};
#endif /* L_CHAR */

#ifndef M_CHAR
#define M_CHAR
uint8_t M[SYMBOL_LENGTH] =
{
  0B00000000,
  0B11000110,
  0B11101110,
  0B11111110,
  0B11111110,
  0B11010110,
  0B11000110,
  0B11000110
};
#endif /* M_CHAR */

#ifndef N_CHAR
#define N_CHAR
uint8_t N[SYMBOL_LENGTH] =
{
  0B00000000,
  0B11000110,
  0B11001110,
  0B11011110,
  0B11110110,
  0B11100110,
  0B11000110,
  0B11000110
};
#endif /* N_CHAR */

#ifndef O_CHAR
#define O_CHAR
uint8_t O[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111000,
  0B01101100,
  0B11000110,
  0B11000110,
  0B11000110,
  0B01101100,
  0B00111000
};
#endif /* O_CHAR */

#ifndef P_CHAR
#define P_CHAR
uint8_t P[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111110,
  0B11001100,
  0B11001100,
  0B01111100,
  0B00001100,
  0B00001100,
  0B00011110
};
#endif /* P_CHAR */

#ifndef Q_CHAR
#define Q_CHAR
uint8_t Q[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111000,
  0B11001100,
  0B11001100,
  0B11001100,
  0B11101100,
  0B01111000,
  0B11100000
};
#endif /* Q_CHAR */

#ifndef R_CHAR
#define R_CHAR
uint8_t R[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111111,
  0B01100110,
  0B01100110,
  0B00111110,
  0B00110110,
  0B01100110,
  0B11100111
};
#endif /* R_CHAR */

#ifndef S_CHAR
#define S_CHAR
uint8_t S[S_CHAR uint8_t
{
  0B00000000,
  0B00111100,
  0B01100110,
  0B00001110,
  0B00011100,
  0B01110000,
  0B01100110,
  0B00111100
};
#endif /* S_CHAR */

#ifndef T_CHAR
#define T_CHAR
uint8_t T[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111110,
  0B01011010,
  0B00011000,
  0B00011000,
  0B00011000,
  0B00011000,
  0B00111100
};
#endif /* T_CHAR */

#ifndef U_CHAR
#define U_CHAR
uint8_t U[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01100110,
  0B01100110,
  0B01100110,
  0B01100110,
  0B01100110,
  0B01111110,
  0B01111100
};
#endif /* U_CHAR */

#ifndef V_CHAR
#define V_CHAR
uint8_t V[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01100110,
  0B01100110,
  0B01100110,
  0B01100110,
  0B01100110,
  0B00111100,
  0B00011000
};
#endif /* V_CHAR */

#ifndef W_CHAR
#define W_CHAR
uint8_t W[SYMBOL_LENGTH] =
{
  0B00000000,
  0B11000110,
  0B11000110,
  0B11000110,
  0B11010110,
  0B11111110,
  0B11101110,
  0B11000110
};
#endif /* W_CHAR */

#ifndef X_CHAR
#define X_CHAR
uint8_t X[SYMBOL_LENGTH] =
{
  0B11000110,
  0B11000110,
  0B01101100,
  0B00111000,
  0B00111000,
  0B01101100,
  0B11000110,
  0B11000110
};
#endif /* X_CHAR */

#ifndef Y_CHAR
#define Y_CHAR
uint8_t Y[SYMBOL_LENGTH] =
{
  0B00000000,
  0B11100111,
  0B01100110,
  0B01100110,
  0B00111100,
  0B00011000,
  0B00011000,
  0B00111100
};
#endif /* Y_CHAR */

#ifndef Z_CHAR
#define Z_CHAR
uint8_t Z[SYMBOL_LENGTH] =
{
  B00000000,
  B01111111,
  B01100011,
  B01000110,
  B00001100,
  B00011001,
  B00110011,
  B01111111
};
#endif /* Z_CHAR */

#ifndef ONE_N
#define ONE_N
uint8_t ONE[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00011000,
  0B00011100,
  0B00011000,
  0B00011000,
  0B00011000,
  0B00011000,
  0B00111100
};
#endif /* ONE_N */

#ifndef TWO_N
#define TWO_N
uint8_t TWO[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111100,
  0B01100110,
  0B01100000,
  0B00111000,
  0B00001100,
  0B01100110,
  0B01111110
};
#endif /* TWO_N */

#ifndef THREE_N
#define THREE_N
uint8_t THREE[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111100,
  0B01100110,
  0B01100000,
  0B00111000,
  0B01100000,
  0B01100110,
  0B00111100
};
#endif /* THREE_N */

#ifndef FOUR_N
#define FOUR_N
uint8_t FOUR[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01110000,
  0B01111000,
  0B01101100,
  0B01100110,
  0B11111110,
  0B01100000,
  0B11110000
};
#endif /* FOUR_N */

#ifndef FIVE_N
#define FIVE_N
uint8_t FIVE[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111110,
  0B00000110,
  0B00111110,
  0B01100000,
  0B01100000,
  0B01100110,
  0B00111100
};
#endif /* FIVE_N */

#ifndef SIX_N
#define SIX_N
uint8_t SIX[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111000,
  0B00001100,
  0B00000110,
  0B00111110,
  0B01100110,
  0B01100110,
  0B00111100
};
#endif /* SIX_N */


#ifndef SEVEN_N
#define SEVEN_N
uint8_t SEVEN[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111110,
  0B01100110,
  0B01100000,
  0B00110000,
  0B00011000,
  0B00011000,
  0B00011000
};
#endif /* SEVEN_N */

#ifndef EIGHT_N
#define EIGHT_N
uint8_t EIGHT[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111100,
  0B01100110,
  0B01100110,
  0B00111100,
  0B01100110,
  0B01100110,
  0B00111100
};
#endif /* EIGHT_N */

#ifndef NINE_N
#define NINE_N
uint8_t NINE[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111100,
  0B01100110,
  0B01100110,
  0B01111100,
  0B01100000,
  0B00110000,
  0B00011100
};
#endif /* NINE_N */

#ifndef ZERO_N
#define ZERO_N
uint8_t ZERO_N[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01111100,
  0B11000110,
  0B11100110,
  0B11110110,
  0B11011110,
  0B11001110,
  0B01111100
};
#endif /* ZERO_N */

#ifndef SMILE_E
#define SMILE_E
uint8_t SMILE[SYMBOL_LENGTH] =
{
  0B00111100,
  0B01000010,
  0B10100101,
  0B10000001,
  0B10100101,
  0B10011001,
  0B01000010,
  0B00111100
};
#endif /* SMILE_E */

#ifndef FROWN_E
#define FROWN_E
uint8_t FROWN[SYMBOL_LENGTH] =
{
  0B00111100,
  0B01000010,
  0B10100101,
  0B10000001,
  0B10011001,
  0B10100101,
  0B01000010,
  0B00111100
};
#endif /* FROWN */

#ifndef SERIOUS_E
#define SERIOUS_E
uint8_t SERIOUS[SYMBOL_LENGTH] =
{
  0B00111100,
  0B01000010,
  0B10100101,
  0B10000001,
  0B10000001,
  0B10111101,
  0B01000010,
  0B00111100
};
#endif /* SERIOUS */

#ifndef HEART_E
#define HEART_E
uint8_t HEART[SYMBOL_LENGTH] =
{
  0B00000000,
  0B01000100,
  0B11101110,
  0B11111110,
  0B11111110,
  0B01111100,
  0B00111000,
  0B00010000
};
#endif /* HEART_E */

#ifndef ARROW_E
#define ARROW_E
uint8_t ARROW[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00010000,
  0B00111000,
  0B01111100,
  0B11111110,
  0B00111000,
  0B00111000,
  0B00111000
};
#endif /* ARROW_E */

#ifndef DOLLAR_E
#define DOLLAR_E
uint8_t DOLLAR[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00010000,
  0B01111000,
  0B00000100,
  0B00111000,
  0B01000000,
  0B00111100,
  0B00010000
};
#endif /* DOLLAR_E */

#ifndef NOTE_E
#define NOTE_E
uint8_t NOTE[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00000000,
  0B00110000,
  0B01010000,
  0B00010000,
  0B00011000,
  0B00011100,
  0B00001100
};
#endif /* NOTE_E */

#ifndef MARS_E
#define MARS_E
uint8_t MARS[SYMBOL_LENGTH] =
{
  0B00000000,
  0B11110000,
  0B11000000,
  0B10100000,
  0B10011100,
  0B00010010,
  0B00010010,
  0B00001100
};
#endif /* MARS */

#ifndef VENUS_E
#define VENUS_E
uint8_t VENUS[SYMBOL_LENGTH] =
{
  0B00000000,
  0B00111000,
  0B01000100,
  0B01000100,
  0B00111000,
  0B00010000,
  0B00111000,
  0B00010000
};
#endif /* VENUS_E */

#ifndef NOMOUTH_E
#define NOMOUTH_E
uint8_t NOMOUTH[SYMBOL_LENGTH] =
{
  0B00111100,
  0B01000010,
  0B10100101,
  0B10000001,
  0B10000001,
  0B10000001,
  0B01000010,
  0B00111100
};
#endif /* NOMOUTH_E */

#ifndef CHAR_SET_LENGTH
#define CHAR_SET_LENGTH 46
#endif /* CHAR_SET_LENGTH */

#ifndef CHARACTERS
#define CHARACTERS
uint8_t * CHARS[CHAR_SET_LENGTH] =
{
  A, B, C, D, E, F, G, H, I ,J, K, L, M,
  N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  ONE, TWO, THREE, FOUR, FIVE,
  SIX, SEVEN, EIGHT, NINE, ZERO,
  SMILE, FROWN, SERIOUS, HEART, ARROW,
  DOLLAR, NOTE, MARS, VENUS, NOMOUTH
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
  if ( (led_mat_fd = open ( DEV_FILENAME, O_WRONLY )) < 0 )
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
    uint8_t reg = i ? i * 2 : LED_MAT_PRIME_REG;
    uint8_t data = symbol_data[i];

    open_device ( &led_mat_fd );
    set_device_as_slave ( &led_mat_fd );
    write_byte ( &led_mat_fd, reg, data );
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
  int i = 0;
  for ( ; i < 3 ; i++ )
    {
      display_symbol ( CHARS[i], SYMBOL_LENGTH );
      clear_led_mat ();
    }
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
