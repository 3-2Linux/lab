OBJECTS = add.o subtract.o multiply.o divide.o

libtest : libtest.a
	cd ..; gcc -I./lib -L./lib main.c -ltest

add.o : add.c
	cd lib; gcc -c add.c

subtract.o : subtract.c
	gcc -c subtract.c

multiply.o : multiply.c
	gcc -c multiply.c
	
divide.o : divide.c
	gcc -c divide.c

libtest.a : $(OBJECTS)
	ar rcs libtest.a divide.o add.o subtract.o multiply.o
	
clean :
	rm -f libtest; cd lib; rm -f libtest.a $(OBJECTS)
	
#Debug Option
	SET ( CMAKE_BUILD_TYPE Debug )
	SET ( CMAKE_BUILD_TYPE RelWithDebinfo )
