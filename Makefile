CFLAGS = -g -Wall -DNDEBUG

SOURCES=src/gofind.c src/dbg.h src/simple_header.h
all: $(SOURCES)
	@mkdir bin	
	gcc $(CFLAGS) $(SOURCES) -o bin/gofind
clean:
	@rm -r bin/


	