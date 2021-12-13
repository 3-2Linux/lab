/* perror() function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void my_perror(char *front_str) 
{
	if (front_str == NULL) {
		printf("%s\n", strerror(errno));
	}
	else {
		printf("%s: %s\n", front_str, strerror(errno));
	}
	return;
}

void main(int argc, char *argv[])
{
	FILE *f;
	
	// Exception
	if (argc < 2) {
		printf("Usage: perror_use file_name\n");
		exit(1);
	}
	
	if ((f=fopen(argv[1], "r")) == NULL) {
	// Use perror library function
		perror(NULL);
		perror("fopen");
		exit(1);
	}
	
	printf("Open a file \%s\".\n", argv[1]);
	
	fclose(f);
	return;
}
