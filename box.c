
// test
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
int rows, cols; 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


void gfxhline( int y1, int x1, int x2 )
{
    int foox ;
    for( foox = x1 ; foox <= x2 ; foox++) 
        mvaddch( y1 , foox , ACS_HLINE );
}




////////////////////////////////
void ncurses_runcmd( char *thecmd   )
{
       char rncmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( rncmdi , "  " , PATH_MAX );
       strncat( rncmdi , thecmd , PATH_MAX - strlen( rncmdi ) -1 );
       strncat( rncmdi , " " , PATH_MAX - strlen( rncmdi ) -1 );
       system( rncmdi );
       reset_prog_mode();
}



////////////////////////////////
void ncurses_runwith( char *thecmd , char *thestrfile  ) //thecmd first
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       printf( "<NDESK CMD: Command...>\n" );
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thestrfile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\" " , PATH_MAX - strlen( cmdi ) -1 );
       printf( "<NDESk CMD: %s>\n", cmdi );
       system( cmdi );
       reset_prog_mode();
}




void gfxframe( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
        mvaddch( fooy , foo , ACS_VLINE );
    foo = x2;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
         mvaddch( fooy , foo , ACS_VLINE );
    foo = y1;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    foo = y2;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    mvaddch( y1 , x1 , ACS_ULCORNER );
    mvaddch( y1 , x2 , ACS_URCORNER );
    mvaddch( y2 , x1 , ACS_LLCORNER );
    mvaddch( y2 , x2 , ACS_LRCORNER );
}


void mvcenter( int myposypass, char *mytext )
{
      mvprintw( myposypass, cols/2 - strlen( mytext )/2  , "%s", mytext );
}






int main()
{

  char cwd[PATH_MAX];

  chdir( getcwd( cwd, PATH_MAX ) );
  system( " setfont  /usr/share/consolefonts/Lat15-TerminusBold32x16.psf.gz    " );

  initscr();	
  getmaxyx( stdscr, rows, cols);
  curs_set( 0 );
  noecho();            
  keypad( stdscr, TRUE );  // for F...
  start_color();
  init_pair(0,  COLOR_WHITE,     COLOR_BLACK);
  init_pair(1,  COLOR_RED,     COLOR_BLACK);
  init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
  init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
  init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
  init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
  init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
  init_pair(8,  COLOR_BLUE,    COLOR_RED);

  int ch ; 

  int gameover = 0; 
  while ( gameover == 0  )
  {

    attroff( A_REVERSE );
    attroff( A_BOLD );
    color_set( 0, NULL );
    int foo, fooy , foox ;
    int y1 = 0; int x1=0; 
    int y2 = rows-1; int x2= cols -1 ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
    for( foox = x1 ; foox <= x2 ; foox++) 
    {
      attron( A_REVERSE );
      color_set( 7, NULL );
      mvprintw( fooy , foox , "A" );
      refresh();
      attroff( A_REVERSE );
      color_set( 0, NULL );
      mvprintw( fooy , foox , " " );
    }

    color_set( 7, NULL ); attron( A_REVERSE ); 
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
    for( foox = x1 ; foox <= x2 ; foox++) 
      mvprintw( fooy , foox , " " );

    color_set( 7, NULL ); attron( A_REVERSE ); 
    gfxframe( 0, 0 , rows-1, cols -1 );
    color_set( 8, NULL ); 
    attroff( A_BOLD ); mvcenter( 2, "[---------------]");
    attroff( A_BOLD ); mvcenter( 3, "[ BOX Press Key ]" );
    attroff( A_BOLD ); mvcenter( 4, "[---------------]");
    color_set( 7, NULL ); 
    //gfxhline( 1, 0 , cols-1);
    //gfxhline( 3, 0 , cols-1);
    color_set( 7, NULL ); 
    mvcenter( rows/2 -1-3 , "[ 1: Press 1 Key to start KODI ]" );
    mvcenter( rows/2 +1-3 , "[ 2: Press 2 Key to start X11 ]" );
    mvcenter( rows/2 +3-3 , "[ 5: Press 5 Key to start NDESK ]" );
    mvcenter( rows/2 +5-3 , "[ 0: Press 0 Key to start reboot ]" );
    mvcenter( rows/2 +7-3 , "[ q: Press q Key to Quit ]" );
    ch = getch();

    if      ( ch == '1' ) ncurses_runcmd( "  kodi " );
    else if ( ch == '2' ) ncurses_runcmd( "  startx  " );
    else if ( ch == '5' ) ncurses_runcmd( "  ndesk  " );
    else if ( ch == '0' ) ncurses_runcmd( "  sudo reboot  " );
    else if ( ch == 'q' ) gameover = 1;

   }

   curs_set( 4 ) ;
   attroff( A_BOLD ); attroff( A_REVERSE ); curs_set( 1 );
   endwin();		/* End curses mode  */
   return 0;
}



