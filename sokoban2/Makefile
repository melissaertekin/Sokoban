CC = gcc
CFLAGS =  -Isrc/install_dir/include -Wall -Wextra -g -pedantic-errors -std=c11 -g3 -fsanitize=address
LDFLAGS = -lSDL2 -Lsrc/install_dir/lib
FILES = main.c grid.c grid.h player.h Makefile level1.txt level2.txt README.md

INSTALL = cd SDL2 && ./configure --prefix=$PWD/../install_dir


SRCPATH := ${workspaceFolder}src
INCPATH := ${workspaceFolder}include

make: main.o grid.o 
	$(INSTALL)
	install -j8
	@echo Compilation de game ...
	@$(CC) $(CFLAGS) main.o grid.o -o game
	@mv *.o obj

main.o : $(SRCPATH)/main.c 
	@$(CC) $(CFLAGS) -c $(SRCPATH)/main.c  $(LDFLAGS)
	@echo Compilation de main.c ...

grid.o: $(SRCPATH)/grid.c $(INCPATH)/grid.h $(INCPATH)/player.h
	@echo Compilation de grid.c ...
	@$(CC) $(CFLAGS) -c $(SRCPATH)/grid.c

sdl2.o: $(SRCPATH)/sdl2.c $(INCPATH)/sdl2.h
	$(INSTALL)
	@echo Compilation de sdl2.c
	@$(CC) $(CFLAGS)  -c $(SRCPATH)/sdl2.c

archive:
	tar -cf ERTEKIN_Melissa.tar.gz $(FILES)

doc:
	doxygen -g	#generate le fichier Doxyfile
	doxygen Doxyfile
	rm -r latex

clean:
	$(RM) -r game obj/*.o html Doxyfile* ERTEKIN_Melissa.tar.gz