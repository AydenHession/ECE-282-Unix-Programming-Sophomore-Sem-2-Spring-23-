/* sigdemo1.c - shows how a signal handler works.
 *            - run this and press Ctrl-C a few times
 */

#include	<stdio.h>
#include	<signal.h>
#include <stdlib.h>
//recieivng 0 signals no matter what

int num_sigs = 0;
int max_sigs = 0;

void f(int signum)			/* this function is called */
{

	num_sigs = num_sigs + 1;

	
	
	printf("OUCH!\n");
	
	int j;	
	//error with loop
	for(j = 0; j < num_sigs; j++)
	{
		printf("!");
	}

	printf("\n");

	signal(SIGINT, f);
	
}


main(int ac, char *av[])
{
//	void	f(int);		
//	/* declare the handler	*/
	int	i;
//	int max;
	
	if(ac != 2)
	{
		fprintf(stderr, "ussage: %s <max>\n\n\n", av[0]);
		exit(1);
	}	

	max_sigs = atoi(av[1]);


	signal( SIGINT, f );	/* install the handler	*/


	for(i=0; i<5; i++ ){		/* do something else	*/
		printf("hello\n");
		sleep(1);
	}
/*
	if(num_sigs <= max)
	{
		printf("Recieved %d signals\n\n", num_sigs);
		exit(0);
	}
	*/
	return 0;
}

