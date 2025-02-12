CFLAGS = -Wall -c

all: main.o init.o
	gcc init.o main.o -lc -o out.o

main.o: main.c daemonProcess.h
	gcc $(CFLAGS) main.c -o main.o

init.o: init.c daemonProcess.h
	gcc $(CFLAGS) init.c -o init.o