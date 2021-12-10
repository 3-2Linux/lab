#include <signal.h>
#include <stdio.h>

int main(){
	int a,b;
	
	a = 10;
	b = 0;
	if (b==0) /* devide 0 혹은 부동소수점 오류 시 */
		raise(SIGFPE);
	else{
		a = a/b;
		printf("%d",a);
	}
}
