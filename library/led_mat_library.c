#include "led_mat_library.h"

void
print ( int argc, char ** argv )
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
