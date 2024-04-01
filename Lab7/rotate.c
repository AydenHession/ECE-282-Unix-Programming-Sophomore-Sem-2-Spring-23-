/* rotate.c : map a->b, b->c, .. z->a
 *   purpose: useful for showing tty modes
 */

#include   <stdio.h>
#include   <ctype.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

//error with struct default mode
static struct termios default_mode;

void restore()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &default_mode);
}

void handle_sig(int sig)
{
	restore();
	exit(0);
}


int main()
{
	struct termios new_mode;

	tcgetattr(STDIN_FILENO, &default_mode);
	
	atexit(restore);


	//ignoring keyboard si
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	signal(SIGTERM, handle_sig);

	//setting the new terminal mode
	tcgetattr(STDIN_FILENO, &new_mode);
	new_mode.c_lflag &= ~(ICANON | ECHO);

	//error with TCSNAOW
	tcsetattr(STDIN_FILENO, TCSANOW, &new_mode);

    int c;
    while ( ( c=getchar() ) != EOF ){
       	
	if(c == 'Q')
	{
		restore();
		exit(0);
	}

	if ( c == 'z' )
	{  
            c = 'a';
	}
        else if (islower(c))
	{
            c++;
	}
	
        putchar(c);
    }

	restore();
	return 0;

}
