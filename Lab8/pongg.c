#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

#define BALL_SYMBOL "O"
#define BORDER  "+"
#define PADDLE "H"
#define SLEEP_TIME 20000


struct Paddle 
{
   	int x;
	int y;
	int l;
	int score;
	int  point;
};

struct Ball
 {
	int x; 
	int y; 
	int tx; 
	int ty;
};

int main(void){
	
	int quit = 0;
   	int frame = 1;
   	int max_x = 0;
   	int max_y = 0;

	struct Paddle p1, p2;
   	struct Ball b;
	
	system("clear");

	
	srand(time(NULL));
	initscr();
   
	curs_set(0);
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	nodelay(stdscr,1);
	start_color();

	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);

	getmaxyx(stdscr, max_y, max_x);

	p1.l = 7;
	p1.x = max_x -3;
	p1.y = (max_y/2) - (p1.l/2);
  
	p1.point = 0;

	p2.l = 7;
	p2.x = 2;
	p2.y = (max_y/2) - (p2.l/2);
  
	p2.point = 0;

	b.x = max_x/33;
	b.y = max_y/23;
	b.tx = rand() & 1 ? -1 : 1;
	b.ty = rand() & 1 ? -1 : 1;


	while (!quit) 
	{

        	clear();

        	getmaxyx(stdscr, max_y, max_x);
        	mvprintw(0, max_x/2 - 30,"PLAYER 1: %d                                PLAYER 2: %d", p1.point, p2.point);
     
	
		attron(COLOR_PAIR(3));

        	int i;
	
		int mid_x = max_x / 2;
	
		for (i = 1; i < max_y - 1; i++) 
		{
    			mvprintw(i, mid_x, BORDER);
		}	

	
        	for (i = 0; i < max_x; i++) 
		{
            		mvprintw(1, i, BORDER);
            		mvprintw(max_y - 1, i, BORDER);
        	}

       
		attroff(COLOR_PAIR(3));

        	attron(COLOR_PAIR(1));
        	p1.x = max_x-3;
	

        	for (i = 0; i < p1.l; i++) 
		{
            		mvprintw(p1.y + i, p1.x, PADDLE);
        	}	
	
        	attroff(COLOR_PAIR(1));

        	attron(COLOR_PAIR(1));
          	p2.x = 2;


        	for (i = 0; i < p2.l; i++) 
		{
            		mvprintw(p2.y + i, p2.x, PADDLE);
        	}        


        	attroff(COLOR_PAIR(1));

        	attron(COLOR_PAIR(2));
        
        	mvprintw(b.y, b.x, BALL_SYMBOL);
        	attroff(COLOR_PAIR(2));

        	if ((b.x + b.tx) < 1 && b.x > 0)
		{
            		b.tx *= -1;
		}

        	if ((b.y + b.ty) < 2 || (b.y + b.ty) > max_y - 2)
		{
            		b.ty *= -1;
		}

        	if ((b.x + b.tx == p1.x) && (b.y + b.ty >= p1.y) && (b.y + b.ty <= (p1.y + p1.l))) 
		{
	    
	     		beep();

           
			b.tx *= -1;
        	}
   	
		if ((b.x + b.tx == p2.x) && (b.y + b.ty >= p2.y) && (b.y + b.ty <= (p2.y + p2.l))) 
		{
    
                   	beep();


    			b.tx *= -1;
		}

	
        	if (b.x > max_x) 
		{
           
	    		p1.point++;	
           
            		b.x = max_x / 33;
            		b.y = max_y / 23;
            		b.tx = rand() & 1 ? -1 : 1;
            		b.ty = rand() & 1 ? -1 : 1;
       
            		mvprintw(0, max_x/2 - 25,"PLAYER 1: %d                                  PLAYER 2: %d", p1.point, p2.point);
            
            		refresh();
		}
        
		if (b.x < 3) 
		{
        
	        	p2.point++;	
    			b.x = max_x / 33;
    			b.y = max_y / 23;
    			b.tx = rand() & 1 ? -1 : 1;
    			b.ty = rand() & 1 ? -1 : 1;
		
                	mvprintw(0, max_x/2 - 25,"PLAYER 1: %d                              PLAYER 2: %d", p1.point, p2.point);
              
    			refresh();
		}
        
	if(frame %4 == 0)
	{
		b.x += b.tx;
		b.y += b.ty;
	}
        
	
	int key = getch();
        switch (key) 
	{

        case 'i':
			if (p1.y - 1 > 1)
			{
        	        	p1.y -= 1;
	            	}
			break;

        case 'k':
            		if ((p1.y + p1.l) + 1 < max_y)
			{
                		p1.y += 1;
			}
			break;
 
	case 'w':
        		if (p2.y - 1 > 1)
			{
            			p2.y -= 1;
        		}
			break;

    	case 's':
        		if ((p2.y + p2.l) + 1 < max_y)
			{
           			p2.y += 1;
        		}
			break;     

        case 'Q':
        	quit = 1;
            	
		break;
        }

	frame++;        
        
	usleep(SLEEP_TIME);

	}	

	endwin();

	system("clear");

	return 0;

}


	






