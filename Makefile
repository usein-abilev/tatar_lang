exec = bin/compiler
compiler = gcc
sources =$(wildcard src/*.c src/utils/*.c)
objects =$(sources:.c=.o)
flags = -I include/lang.h -g -Wall -std=c99

$(exec): $(objects)
	$(compiler) -o $(exec) $(objects) $(flags) 
	$(MAKE) clean

%.o: %.c
	$(compiler) -c $(flags) $< -o $@

run: 
	$(exec)

clean:
	find . -name "*.o" -delete

.PHONY: clean 