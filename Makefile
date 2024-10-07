all: main

main: main.o functions.o
	gcc -o main main.o functions.o -lpthread

main.o: main.c header.h
	gcc -c main.c

functions.o: functions.c header.h
	gcc -c functions.c

clean:
	rm *.o main
