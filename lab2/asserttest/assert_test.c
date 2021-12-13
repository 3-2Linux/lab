/*my_assert() function */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *filename = NULL;

void my_assert(int expr)
{
	if(expr==0) {
		fprintf(stderr, "%s: %s:%d: %s: Assertion '((num>=0) && (num <= 100))' failed. ", filename, __FILE__, __LINE__, __func__);
		abort();
	}
}

void foo(int num)
{
        my_assert(((num >=0) && (num <=100)));
        printf("foo : num = %d\n", num);
}

void main(int argc, char *argv[]) {
        int num;

	filename = strtok(argv[0], "./");
	
        if (argc<2) {
                fprintf(stderr,"Usage : assert_test a Number\n(0 <= aNumber <=100)\n");
                exit(1);
        }

        num = atoi(argv[1]);
        foo(num);
}
