CC = gcc
CFLAGS = -Wall -Wextra -g -pedantic-errors -std=c11 -g3 -fsanitize=address
FILES = main.c grid.c grid.h player.h Makefile level1.txt level2.txt README.md

make: main.o grid.o
	$(CC) $(CFLAGS) main.o grid.o -o game

main.o : main.c 
	$(CC) $(CFLAGS) -c main.c 

grid.o: grid.c grid.h player.h
	$(CC) $(CFLAGS) -c grid.c 

archive:
	tar -cf ERTEKIN_Melissa.tar.gz $(FILES)
doc:
	doxygen -g	#generate le fichier Doxyfile
	doxygen Doxyfile
	rm -r latex

clean:
	$(RM) -r game *.o html Doxyfile* ERTEKIN_Melissa.tar.gz