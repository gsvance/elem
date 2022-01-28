# Makefile for the elem program

# compile the binary
elem: main.c symbols.c names.c symbols.h names.h
	gcc main.c names.c symbols.c -o elem

# delete the binary
clean:
	rm -f elem
