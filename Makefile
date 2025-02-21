CFLAGS = -Wall -c -Iinclude

all: build build/main.o build/init.o build/checkingPorts.o
	gcc build/checkingPorts.o build/init.o build/main.o -lc -o out.o

build:
	mkdir build

build/main.o: src/main.c include/daemonProcess.h include/portsTable.h
	gcc $(CFLAGS) src/main.c -o build/main.o

build/init.o: src/init.c include/daemonProcess.h
	gcc $(CFLAGS) src/init.c -o build/init.o

build/checkingPorts.o: src/checkingPorts.c include/portsTable.h
	gcc $(CFLAGS) src/checkingPorts.c -o build/checkingPorts.o