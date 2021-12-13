/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <setjmp.h>

#define BUFSIZE 256

void ls(int narg, char **argv);

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
		if(!strcmp(argv[0], "ls")){
			ls(narg, argv);
		}
	 }
}

void ls(int narg, char **argv) {
 	char temp[256];
 	if(narg ==1) {
 		getcwd(temp, 256);
 		printf("%s", temp);
 		argv[1] = temp;
 	}
 	DIR *pdir;
 	struct dirent *pde;
 	int i =0;
 	if((pdir = opendir(argv[1])) <0) {
 		perror("[ERROR] OPENDIR: ");
 	}
 	printf("\n");
 	while((pde = readdir(pdir)) !=NULL) {
 		printf("%-20s", pde ->d_name);
 		if(++i %3 ==0)
 			printf("\n");
 	}
 	printf("\n");
 	closedir(pdir);
}


