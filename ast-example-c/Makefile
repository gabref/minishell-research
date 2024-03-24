exec = hello
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
	gcc $(flags) -o $@ $^

%.o: %.c inc/%.h
	gcc $(flags) -c $< -o $@

install:
	make
	cp ./hello /usr/local/bin/hello

run: $(exec)
	./hello

clean:
	rm -f $(objects) $(exec)
