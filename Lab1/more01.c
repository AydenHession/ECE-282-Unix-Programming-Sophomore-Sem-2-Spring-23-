/* more01.c - version 0.1 of more
* read and print 24 lines then pause for a few special commands
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGELEN 24
#define LINELEN 512
//reference 240 lab 3 for file
//global variables defined to hold names of the files
FILE OUTFILE[50];
FILE INFILE[50];
void do_more(FILE *);
int see_more();
int main( int ac , char *av[] )
{
FILE *fp;
// FILE *outFile;
if ( ac == 1 )
{
do_more( stdin );
}
else
{
//set up functions to ensure the -o can go whereever
if(strcmp(av[1], "-o") == 0)
{
//based on the location of the -o the other two inputs should be
the input and output files
//this logic is continued for the other -o locations
//this is because the output file is supposed to always show up
after the INFILE
strcpy(INFILE, av[2]);
strcpy(OUTFILE, av[3]);
}
else if(strcmp(av[2], "-o") ==0)
{
strcpy(INFILE, av[1]);
strcpy(OUTFILE, av[3]);
}
else if(strcmp(av[3], "-o") ==0)
{
strcpy(INFILE, av[1]);
strcpy(OUTFILE, av[2]);
}
else //this means the written statement is either too long or that "-o"
isnt in it and then the statement shouldn't run
{
exit(1);
}
//will run until the exit command is stated.. which is just the eof
stuff
while (--ac)
{
//opens file to actually run the commands
if ( (fp = fopen( *++av , "r" )) != NULL )
{
do_more( fp ) ;
fclose( fp );
}
else
{
exit(1);
}
}
}
return 0;
}
void do_more( FILE *fp )
/*
* read PAGELEN lines, then call see_more() for further instructions
*/
{
char line[LINELEN];
int num_of_lines = 0;
int see_more(), reply;
FILE* tempFile; //this file will have stuff written in it and get it placed
in our output file.
tempFile = fopen(OUTFILE, "w");
while ( fgets( line, LINELEN, fp ) )
{ /* more input */
if ( num_of_lines == PAGELEN )
{ /* full screen? */
reply = see_more();
/* y: ask user */
if ( reply == 0 )
{ /* n: done */
break;
}
num_of_lines -= reply; /* reset count */
}
if ( fputs( line, stdout ) == EOF )
{ /* show line */
exit(1);
} /* or die */
num_of_lines++; /* count it */
}
//gotta be closing these files frfr.
fclose(tempFile);
}
int see_more()
/*
* print message, wait for response, return # of lines to advance
* q means no, space means yes, CR means one line
*/
{
int c;
printf("\033[7m more? \033[m"); /* reverse on a vt100 */
while( (c=getchar()) != EOF ) /* get response */
{
if ( c == 'q' ) /* q -> N */
return 0;
if ( c == ' ' ) /* ' ' => next page */
return PAGELEN; /* how many to show */
if ( c == '\n' ) /* Enter key => 1 line */
return 1;
}
return 0;
}