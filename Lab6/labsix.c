#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int lock_passwd(char *);

//LAB C function
int unlockpasswd(char *);

int main(int ac, char *av[])
{
	if (ac != 3)
	{
		printf("ussage: %s\n", av[0]);
		return 1;
	}

	const char* filename = av[1];
	const char* line = av[2];

	int tries = 10;

	while ((lock_passwd(filename) != 0) && (tries-- >  0))
	{
		sleep(1);
	}

	if (tries < 0)
	{
		printf("couldn't get locked file \n");
		return 1;		
	}

	int failer = open(filename, O_WRONLY | O_APPEND);

	if(failer == -1)
	{
		printf("failed to open for writing: %s \n", strerror(errno));
		return 1;
	}

	if (write(failer, line, strlen(line)) == -1)
	{
		printf("failed to write in file: %s \n", strerror(errno));
		close(failer);
		return 1;		
	}

	if (close(failer) == -1)
	{
		printf("failded to close: %s\n", strerror(errno));
		return 1;
	}

	if (unlockpasswd(filename) == -1)
	{
		printf("failed to unlock file %s \n", strerror(errno));
		return 1;
	}
	
	return 0;
}

int lock_passwd(char* filename)
{
	int rv = 0;
	if(link(filename,strcat(filename, ".LCK")) == -1)
	{
		rv = (errno == EEXIST ? 1 : 2);
	}

	return rv;
}


//part C function
int unlockpasswd( char* filename)
{
	char lockedfile[strlen(filename) + 5];
	sprintf(lockedfile, "%s.LCK", filename);
	return unlink(lockedfile);	
}
