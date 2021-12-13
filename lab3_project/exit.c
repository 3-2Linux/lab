#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h> 
#include <sys/types.h>

#define BUFSIZE 256

void pwd();
void ls();
void cd(int narg, char **argv);
int getargs(char *cmd, char ** argv);
void mkdir_(int narg, char ** argv);
void rmdir_(int narg, char **argv);
void rmdir_rm(int narg, char ** argv);
void ln(int narg, char ** argv);
void cp(int narg, char **argv);
void mv(int narg, char **argv);
void cat(int narg, char ** argv);
void rm_(int narg, char ** argv);

void main() 
{
	char buf[256];
	char * argv[50];
	int narg;
	pid_t pid;
	int i = 0;
	while (1) {
		char *argv[50] = {'\0'} ;
 		printf("Shell> ");
		gets(buf);
		narg = getargs(buf, argv);
		
		if(!strcmp(buf,"exit") ||!strcmp(buf,"exit;"))
			break;
		else if(!strcmp(buf, "pwd")) {
			pwd();
		}
		else if(!strcmp(buf, "ls")) {
			ls();
		}
		else if(!strcmp(buf, "cd")) {
			cd(narg, argv);
		}
		else if(!strcmp(buf, "mkdir")) {
			 mkdir_(narg, argv);
		}
		else if(!strcmp(buf, "rmdir")) {
			 rmdir_(narg, argv);
		}
		else if(!strcmp(buf, "rm")) {
			 rm_(narg, argv);
		}
		else if(!strcmp(buf, "ln")) {
			 ln(narg, argv);
		}
		else if(!strcmp(buf, "cp")) {
			 cp(narg, argv);
		}
		else if(!strcmp(buf, "mv")) {
			 mv(narg, argv);
		}
		else if(!strcmp(buf, "cat")) {
			 cat(narg, argv);
		}
		else if(!strcmp(buf, "") ||!strcmp(buf,"\t")) 
			continue;
	 }
}

void pwd() {
	char *buf = (char *)malloc(sizeof(char)*(BUFSIZE));
 
 	if(getcwd(buf, BUFSIZE) ==NULL) {
 		perror("[ERROR] PWD");
 		exit(EXIT_FAILURE);
 	}
 	else
 		printf("%s \n",buf);
 
 	free(buf);
}



void ls(){
   DIR *dirp; // 현재 디렉토리를 가리키기 위해 선언
   struct dirent *dentry; 
   struct stat file_info; //파일 정보들 얻기 위해 선언
   int return_stat;
   char buf[100];

   /* 현재 디렉토리를 지정한다. */
   if((dirp = opendir("./"))==NULL) exit(1);
        while(dentry = readdir(dirp)){
            /* 숨김파일일 경우 출력하지 않는다. */
            if(dentry->d_name[0]=='.') continue;
            /* 숨김파일이 아닌 경우 출력한다. */
            else{
                /* inode가 0이 아닌경우 이름을 출력한다. */
                if(dentry->d_ino !=0) printf(" %s ",dentry->d_name );
            }
        }
        printf("\n");
        closedir(dirp);
}

int getargs(char *cmd, char ** argv) {
	int narg = 0;
	
	while(*cmd) {
		if(*cmd == ' ' || *cmd == '\t')
			*cmd ++ = '\0';
		else {
			argv[narg++] = cmd++;
			while(*cmd != '\0' && *cmd != ' ' && *cmd != '\t')
				cmd++;
		}
	}
	argv[narg] = NULL;
	return narg;
}

void cd(int narg, char **argv) {
 	if(narg == 1) {
 		chdir("HOME");
 	}
 	else{
 		if(chdir(argv[1]) ==-1){
 		printf("%s: No search file or directory\n", argv[1]);
 		}
	}
}

void mkdir_(int narg, char ** argv) {
 	umask(0);
 	if(argv)
 	
 	if(narg < 2)
 		fprintf(stderr, "PathName is not exists\n");
 	else {
 		if(mkdir(argv[1], 0755) < 0) {
 			perror("[ERROR] MKDIR");
 			exit(EXIT_FAILURE);
 		}
 	}
}

void rmdir_(int narg, char **argv) {
 	int i =0;
 	char temp[256];
 	if(narg ==1) {
 		printf("rmdir: missing operand\n");
 	}
 	else {
 		if (rmdir(argv[1]) ==-1) {
 			perror("rmdir");
 		}
 	}
}

void rm_(int narg, char ** argv) {
 	if(narg < 2)
 		fprintf(stderr, "Path is not exists\n");
 	else {
 		if(remove(argv[1]) <0) {
 			perror("[ERROR] RM/RMDIR");
 			exit(EXIT_FAILURE);
 		}
 	}
}

void ln(int narg, char ** argv) {
 	char cmd;
 	char *src; 
 	char *target;
 	if (narg <2) {
 		fprintf(stderr, "Usage: ln [u,s] ...\n");
 		fprintf(stderr, " ln src target\n");
 		fprintf(stderr, " ln u[nlink] filename\n");
 		fprintf(stderr, " ln s[ymlink] src target\n");
 		exit(1);
 	}
 
 	if (!strcmp(argv[1],"-s")) {
 		if (narg <4) {
 			fprintf(stderr, "ln l src target [link]\n");
 			exit(1);
 		}
 		src = argv[2];
 		target = argv[3]; 
 		if (symlink(src, target) <0) {
 			perror("symlink");
 			exit(1);
 		}
 	}
 	else if (!strcmp(argv[1],"-u")) {
 		src = argv[2];
 		if (unlink(src) <0) {
 			perror("unlink");
 			exit(1);
 		}
 	}
 	else if (narg ==3) {
 		src = argv[1];
 		target = argv[2];
 		if (link(src, target) <0) {
 			perror("link");
 			exit(1);
 		}
 	}
 	else {
 		fprintf(stderr, "Unknown command...\n");
 	}
}

void cp(int narg, char **argv) {
 	int src_fd; 
 	int dst_fd;
 	char buf[256];
 	ssize_t rcnt;
 	ssize_t tot_cnt =0;
 	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 
 	
 	if (narg <3){
 		fprintf(stderr, "Usage: file_copy src_file dest_file\n");
 		exit(1);
 	}
 	if ((src_fd = open(argv[1], O_RDONLY)) ==-1){
 		perror("[ERROR]SRC OPEN");
 		exit(1);
 	}
 	if ((dst_fd = creat(argv[2], mode)) ==-1){
 		perror("[ERROR]DST OPEN");
 		exit(1);
 	}
 	while ((rcnt = read(src_fd, buf, 256)) >0){
 		tot_cnt += write(dst_fd, buf, rcnt);
 	}
 	if (rcnt <0){
 		perror("[ERROR]READ");
 		exit(1);
 	}
 	close(src_fd);
 	close(dst_fd);
}

void mv(int narg, char **argv) {
 	struct stat buf;
 	char *target;
 	char *src_file_name_only;
 	if (narg <3) {
 		fprintf(stderr, "Usage: file_rename src target\n");
 		exit(1);
 	}
 	// Check argv[1] (src) whether it has directory info or not.
 	if (access(argv[1], F_OK) <0) {
 		fprintf(stderr, "%s not exists\n", argv[1]);
 		exit(1);
 	}
 	else {
 		char *slash = strrchr(argv[1], '/');
 		src_file_name_only = argv[1];
 		if (slash !=NULL) {
 			src_file_name_only = slash +1;
 		}
 	}
 
 	target = (char *)calloc(strlen(argv[2]) +1, sizeof(char));
 	strcpy(target, argv[2]);
 	if (access(argv[2], F_OK) ==0) {
 		if (lstat(argv[2], &buf) <0) {
 			perror("lstat");
 			exit(1);
 		}
 		else {
 			if (S_ISDIR(buf.st_mode)) {
 				free(target);
 				target = (char *)calloc(strlen(argv[1]) + strlen(argv[2]) +2, sizeof(char));
 				strcpy(target, argv[2]);
 				strcat(target, "/");
 				strcat(target, src_file_name_only);
 			}
 		}
 	}
 	printf("target = %s\n", target);
 	if (rename(argv[1], target) <0){
 		perror("rename");
 		exit(1);
 	}
 	free(target);
}

void cat(int narg, char ** argv) {
 	FILE *file[narg -1];
 	int loop;
 	char buf;
 	if (narg <1) {
  		fprintf(stderr, "Please Input Files \n");
 		exit(1);
 	}
 	for(loop =0; loop <narg -1; loop ++) {
 		file[loop] = fopen(argv[loop +1],"r");
 		if(file[loop] ==NULL) {
 			printf("cat : %s : No such file or directory \n",argv[loop +1]);
 		}
 		else {
 			while((buf = fgetc(file[loop])) != EOF) {
 				printf("%c",buf);
 			}
 			if((fclose(file[loop])) !=0) {
 				perror("CAT");
 			}
 		}
 	}
 	printf("\n");
}
