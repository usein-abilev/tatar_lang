exec = bin/compiler
compiler = gcc
sources =$(wildcard src/*.c src/utils/*.c)
objects =$(sources:.c=.o)
flags = -I include/lang.h -g -std=c99

all: $(exec) clean 

$(exec): $(objects)
	$(compiler) -o $(exec) $(objects)
	
%.o: %.c
	$(compiler) -c $(flags) $< -o $@

run: 
	$(exec)

debug: 
	valgrind --leak-check=full --track-origins=yes $(exec) 

clean:
	rm -f $(objects)

.PHONY: clean 