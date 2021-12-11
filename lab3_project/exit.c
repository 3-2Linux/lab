#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>


void main() 
{
	char buf[256];
	char * argv[50];
	int narg;
	pid_t pid;
	int i =0;
	while (1) {
		char *argv[50] = {'\0'} ;
 		printf("shell> ");
		gets(buf);
		if(!strcmp(buf,"exit") ||!strcmp(buf,"exit;"))
			break;
 
		else if(!strcmp(buf,"") ||!strcmp(buf,"\t")) 
			continue;
 
		//narg = getargs(buf, argv);
	 }
}


