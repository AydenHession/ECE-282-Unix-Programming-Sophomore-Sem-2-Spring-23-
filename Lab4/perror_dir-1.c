#include <stdio.h>
#include <stdlib.h> // for exit() function
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
int fd;
if ( argc < 2 )
{
printf("Usage: %s <filename>\n", argv[0]);
printf("The file might exist or not.\n");
exit(1);
}
//fd = open(argv[1], O_RDONLY);
// printf will output user's formatted string, while perror will output
// the system error msg corresponding to errno
if (chdir(argb[1] == -1)
{
printf("Opening directory \"%s\" failed.\n", argv[1]);
}
else
{
printf("The directory \"%s\" was opened w/o problem.\n", argv[1]);
}
return 0;
}