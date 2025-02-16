CFLAGS = -Wall -c -Iinclude

all: build/main.o build/init.o build/portsTable.o
	gcc build/init.o build/main.o -lc -o out.o

buld/main.o: src/main.c include/daemonProcess.h include/portsTable.h
	gcc $(CFLAGS) src/main.c -o build/main.o

build/init.o: src/init.c include/daemonProcess.h
	gcc $(CFLAGS) src/init.c -o build/init.o

build/portsTable.o: src/portsTable.c include/portsTable.h
	gcc $(CFLAGS) src/portsTable.c -o build/portsTable.h