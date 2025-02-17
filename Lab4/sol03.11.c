/** sol03.11.c 
 ** ------------------------------------------------------------
	A corrected version of ls2.c 
	is: sol03.11.c.
	This program combines the directory name with the filename
	as an argument to stat so stat can find the file.
	The listing only shows the filename, though.

 ** ------------------------------------------------------------
 **
 **
 *
 * ls2.c - corrected
 *
 *	purpose  list contents of directory or directories
 *	action   if no args, use .  else list files in args
 *	note     uses stat and pwd.h and grp.h 
 *	
 *	build: cc sol03.11.c -o sol03.11
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<sys/types.h>
#include	<dirent.h>
#include	<sys/stat.h>

void do_ls_r(char[]); //adding for -R 
void do_ls(char[]);
void dostat(char *,char *);
void show_file_info( char *, struct stat *);
void mode_to_letters( int , char [] );
char *uid_to_name( uid_t );
char *gid_to_name( gid_t );

main(int ac, char *av[])
{
	char* directory;
	
	if ( ac == 1 )
	{
		do_ls( "." );
	}
	else if  ((strcmp(av[1], "-R") == 0) ||(strcmp(av[2], "-R") == 0)) //checks if a -R is in the second or third spot to call recursive function
	{
		if (strcmp(av[1], "-R") == 0)
		{
			directory = av[2];
		}	
		else
		{
			directory = av[1];
		}
		do_ls_r(directory);	
	}
	else
		while ( --ac ){
			printf("%s:\n", *++av );
			do_ls( *av );
		}
}

void do_ls_r(char dirname[])
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */
	char		*fullpath;
	char 		*subpath;
	
	fullpath = (char *)malloc(strlen(dirname) + 1 + MAXNAMLEN + 1);

	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
	{
		fprintf(stderr,"ls2: cannot open %s\n", dirname);
	}
	else
	{
		while ( ( direntp = readdir( dir_ptr ) ) != NULL )
		{
			sprintf(fullpath,"%s/%s",dirname,direntp->d_name);
			

			if ((direntp->d_type) == DT_REG)
                        {
				dostat(fullpath, direntp->d_name);
                        }
			
			//check if directory and then recursive part
			if ((direntp->d_type) == DT_DIR)
			{
				//infinite recursion check to not kill iupui's precious servers
				if ((strcmp(direntp->d_name, ".") != 0) && (strcmp(direntp->d_name, "..") != 0))
				{
					subpath = (char*)malloc(strlen(fullpath) + 1);
					strcpy(subpath, fullpath);
						
					printf("\n%s:\n", subpath);
					do_ls_r(subpath);
					free(subpath);
				}
			}
		}	
		closedir(dir_ptr);
	}
	free(fullpath);
	

}

void do_ls( char dirname[] )
/*
 *	list files in directory called dirname
 */
{
	DIR		*dir_ptr;		/* the directory */
	struct dirent	*direntp;		/* each entry	 */
	char		*fullpath;

	fullpath = (char *)malloc(strlen(dirname) + 1 + MAXNAMLEN + 1);
	if ( ( dir_ptr = opendir( dirname ) ) == NULL )
		fprintf(stderr,"ls2: cannot open %s\n", dirname);
	else
	{
		while ( ( direntp = readdir( dir_ptr ) ) != NULL )
		{
			sprintf(fullpath,"%s/%s",dirname,direntp->d_name);
			dostat(fullpath, direntp->d_name);
		}	
		closedir(dir_ptr);
	}
	free(fullpath);
}

void dostat( char *fullpath, char *filename )
{
	struct stat info;

	if ( stat(fullpath, &info) == -1 )		/* cannot stat	 */
		perror(filename);			/* say why	 */
	else					/* else show info	 */
		show_file_info(filename, &info);
}

void show_file_info( char *filename, struct stat *info_p )
/*
 * display the info about 'filename'.  The info is stored in struct at *info_p
 */
{
	char	*uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void	mode_to_letters();
        char    modestr[11];

	mode_to_letters( info_p->st_mode, modestr );

	printf( "%s"    , modestr );
	printf( "%4d "  , (int) info_p->st_nlink);	
	printf( "%-8s " , uid_to_name(info_p->st_uid) );
	printf( "%-8s " , gid_to_name(info_p->st_gid) );
	printf( "%8ld " , (long)info_p->st_size);
	printf( "%.12s ", 4+ctime(&info_p->st_mtime));
	printf( "%s\n"  , filename );

}

/*
 * utility functions
 */

/*
 * This function takes a mode value and a char array
 * and puts into the char array the file type and the 
 * nine letters that correspond to the bits in mode.
 * NOTE: It does not code setuid, setgid, and sticky
 * codes
 */
void mode_to_letters( int mode, char str[] )
{
    strcpy( str, "----------" );           /* default=no perms */

    if ( S_ISDIR(mode) )  str[0] = 'd';    /* directory?       */
    if ( S_ISCHR(mode) )  str[0] = 'c';    /* char devices     */
    if ( S_ISBLK(mode) )  str[0] = 'b';    /* block device     */

    if ( mode & S_IRUSR ) str[1] = 'r';    /* 3 bits for user  */
    if ( mode & S_IWUSR ) str[2] = 'w';
    if ( mode & S_IXUSR ) str[3] = 'x';

    if ( mode & S_IRGRP ) str[4] = 'r';    /* 3 bits for group */
    if ( mode & S_IWGRP ) str[5] = 'w';
    if ( mode & S_IXGRP ) str[6] = 'x';

    if ( mode & S_IROTH ) str[7] = 'r';    /* 3 bits for other */
    if ( mode & S_IWOTH ) str[8] = 'w';
    if ( mode & S_IXOTH ) str[9] = 'x';
}

#include	<pwd.h>

char *uid_to_name( uid_t uid )
/* 
 *	returns pointer to username associated with uid, uses getpw()
 */	
{
	struct	passwd *getpwuid(), *pw_ptr;
	static  char numstr[10];

	if ( ( pw_ptr = getpwuid( uid ) ) == NULL ){
		sprintf(numstr,"%d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name ;
}

#include	<grp.h>

char *gid_to_name( gid_t gid )
/*
 *	returns pointer to group number gid. used getgrgid(3)
 */
{
	struct group *getgrgid(), *grp_ptr;
	static  char numstr[10];

	if ( ( grp_ptr = getgrgid(gid) ) == NULL ){
		sprintf(numstr,"%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
