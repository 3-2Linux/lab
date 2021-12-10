#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define PASSWORDSIZE 12

int main(void){
	int fd;
	int nread, cnt = 0, errcnt = 0;
	char ch, text[] = "The magic thing is that you can change it.";
	struct termios init_attr, new_attr;
	
	fd = open(ttyname(fileno(stdin)),O_RDWR);
	tcgetattr(fd, &init_attr);
	new_attr = init_attr;
	new_attr.c_lflag &= ~ICANON;
	new_attr.c_lflag &= ~ECHO;
	new_attr.c_cc[VMIN] = 1;
	new_attr.c_cc[VTIME] = 0;
	if(tcsetattr(fd, TCSANOW, &new_attr) != 0){
		fprintf(stderr, "can not set terminal option. \n");
	}
	printf("Typing next sentence. \n %s \n", text);
	while((nread = read(fd, &ch, 1)) > 0 && ch != '\n'){
		if(ch == text[cnt++])
			write(fd, &ch, 1);
		else{
			write(fd, "*", 1);
			errcnt++;
		}
	}
	printf("Count of Typing error = %d \n", errcnt);
	tcsetattr(fd, TCSANOW, &init_attr);
	close(fd);
}
