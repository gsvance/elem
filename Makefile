# Makefile for the elem program

# compile the binary
elem: main.c symbols.c names.c
	gcc main.c -o elem

# delete the binary
clean:
	rm -f elem
