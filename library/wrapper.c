#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void
print_string ( int args_count, char ** argv )
{
  led_mat_print ( args_count, argv );
}

void
configure_led_mat ( void )
{
  ;
}



void
display_help ( char ** argv )
{
  printf ( "At least one option must be selected\n" );
  printf ( "correct usage\n" );
  tabbed_print ( argv[0], 1 );
  printf ( "(-h|-c|-c <MESSAGE>)\n" );

  print_newline ();

  tabbed_print ( "OPTIONS:\n", 1 );
  tabbed_print ( "'-c' to configure the device\n", 1 );
  tabbed_print ( "'-p' to print a string on the device\n", 1 );
  tabbed_print ( "'-h' to display this help\n", 1 );

  print_newline ();

  tabbed_print ( "EXAMPLES:\n", 1 );
  tabbed_print ( argv[0], 1 );
  printf ( " -c\n" );
  tabbed_print ( "will reset the device configuration\n", 2 );
  tabbed_print ( argv[0], 1 );
  printf ( " -p <MESSAGE>\n" );
  tabbed_print ( "will display <MESSAGE> in the device\n", 2 );
  tabbed_print ( "provided it's conformed of valid characters\n", 2 );
}

int
main ( int argc, char ** argv )
{
  print_a ();
  if(argc>1 && argv[1][0] == '-')
    {
      switch (argv[1][1])
        {
          case 'p':
            print_string ( argc, argv );
            break;
          case 'c':
            configure_led_mat ();
            break;
          case 'h':
          default:
            display_help ( argv );
            break;
        }
    }
  else
    {
      display_help ( argv );
    }
  return 0;
}
