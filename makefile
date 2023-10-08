CFLAGS=-std=c11 -pedantic -Wall -Wvla -Werror -D_DEFAULT_SOURCE

all  : zombie controller labo

utils_v2.o : utils_v2.h utils_v2.c
	gcc $(CFLAGS) -c utils_v2.c

zombie.o : zombie.c utils_v2.h network.h zombie.h
	gcc $(CFLAGS) -c zombie.c

controller.o : controller.c utils_v2.h network.h controller.h
	gcc $(CFLAGS) -c controller.c

network.o : network.c utils_v2.h network.h
	gcc $(CFLAGS) -c network.c

labo.o : labo.c utils_v2.h 
	gcc $(CFLAGS) -c labo.c

network : network.o utils_v2.o
	gcc $(CFLAGS) -o network network.o utils_v2.o
		
zombie : zombie.o utils_v2.o network.o
	gcc $(CFLAGS) -o zombie zombie.o utils_v2.o network.o

controller : controller.o utils_v2.o network.o
	gcc $(CFLAGS) -o controller controller.o utils_v2.o network.o

labo : labo.o utils_v2.o
	gcc $(CFLAGS) -o labo labo.o utils_v2.o

clean :
	rm -f *.o
	rm -f zombie
	rm -f controller
	rm -f labo	
	
