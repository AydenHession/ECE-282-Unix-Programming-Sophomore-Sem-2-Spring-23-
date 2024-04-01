/* hello4.c
 *	purpose	show how to use erase, time, and draw for animation
 */
#include	<stdio.h>
#include	<curses.h>
#include	<unistd.h>
#include	<math.h>


#define PI 3.14159
#define AMPLITUDE 10 /* amplitude of motion */
#define PERIOD 20 /* period of motion */

main()
{
	int	i;
	initscr();
	clear();

	   for(i=0; i<LINES; i++ ){
		double phase = sin(2*PI*i/PERIOD);		
        	int offset = (int)(phase*AMPLITUDE); /* calculate offset */
        
		move( i, i+i );

		if ( i%2 == 1 ) 
			standout();

		addstr("Hello, world");

		if ( i%2 == 1 ) 
			standend();

		refresh();

		int delay = (int)(fabs(phase)*100000); /* calculate delay time */

		usleep(150000);

		move(i,i+i+offset);			/* move back	*/

		addstr("             ");	/* erase line	*/

	   }


	endwin();
}
