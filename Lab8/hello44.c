/*
se show how to use erase, time, and draw for animation
*/

#include <stdio.h>
#include <curses.h>

#define delay 1000000
#define g 1.5


main()
{
	int i;
	int  change_delay = delay;
	initscr();
		clear();
	int col = getmaxx(stdscr)-1;
	int j = 4;	
		for(i = 1; (i+i) < col; i++)
		{
	
		/*	if (i>=col)
			{
			break;
			}
		*/
			if ((i) < col)
			{
				move(10, i+i);
			
				if(i%2 == 1)
				{
					standout();
				}
			
				addstr("Hello, world");

				if (i%2 == 1)
				{
					standend();
				}

			/*	if (i-12 >= col)
				{
					break;
				}*/

				refresh();
			//	change_delay = delay;
				change_delay = (int)(delay/j);
				usleep(change_delay);
				
				move(10, i+i);
				addstr("            ");
			j++;
			}
		}

		//usleep(delay);

		refresh();		
		move(5,col);
		addch('H');
		move(6,col);
		addch('e');
		move(7,col);
		addch('l');		
		move(8, col);
		addch('l');
		move(9,col);
		addch('o');
		move(10,col);
		addch(',');
		move(11,col);
		addch('w');
		move(12,col);
		addch('o');
		move(13,col);
		addch('r');
		move(14,col);
		addch('l');
		move(15,col);
		addch('d');
		refresh();

		//pause for greatness ;D
		usleep(delay);
		usleep(delay);
		usleep(delay);
		usleep(delay);
		usleep(delay);

		move(5,40);

		

				
	endwin();
}
