#include "text_print.h"

void
tabbed_print ( char * text, int tab_number )
{
  if ( tab_number == 2 )
    {
      printf ( "\t" );
    }
  printf ( "\t%s", text );
}

void
print_newline ( void )
{
  printf ( "\n" );
}

