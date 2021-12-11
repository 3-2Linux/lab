#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
	void *handle;
	int (*add)(int,int), (*divide)(int,int),
	    (*subtract)(int,int),(*multiply)(int,int);
	char *error;
  
	handle = dlopen("./lib/libtest.so.1.0.1", RTLD_LAZY);
  	if (!handle) {
    		fputs(dlerror(), stderr);
    		exit(1);
  	}

  	add = dlsym(handle, "add");
  	if ((error = dlerror()) != NULL){
    		fprintf (stderr, "%s", error);
    		exit(1);
  	}
  	
  	subtract = dlsym(handle, "subtract");
  	if ((error = dlerror()) != NULL){
    		fprintf (stderr, "%s", error);
    		exit(1);
  	}
  	
  	multiply = dlsym(handle, "multiply");
  	if ((error = dlerror()) != NULL){
    		fprintf (stderr, "%s", error);
    		exit(1);
  	}
  	
  	divide = dlsym(handle, "divide");
  	if ((error = dlerror()) != NULL){
    		fprintf (stderr, "%s", error);
    		exit(1);
  	}
  
	printf("ADD : %d \n", (*add)(3,1));
	printf("SUBTRACT : %d \n", (*subtract)(3,1));
	printf("MULTIPLY : %d \n", (*multiply)(3,1));
	printf("DIVIDE : %d \n", (*divide)(3,1));
	
	dlclose(handle);
}
