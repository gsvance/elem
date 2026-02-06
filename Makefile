# Makefile for the elem program

# Compile the elem binary
elem: main.c symbols.c names.c
	gcc main.c -o elem

# Delete the elem binary
clean:
	rm -f elem
