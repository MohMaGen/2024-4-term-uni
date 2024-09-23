
target := target/

labs := $(wildcard lab*/)
include-dirs := $(patsubst %, -I %, $(labs))

sources := $(patsubst %, %src.cpp, $(labs))
objects := $(patsubst %/src.cpp, $(target)%.o, $(sources)) $(target)main.o

flags := -g3 -Wall -Werror -std=c++23 -pedantic -pedantic-errors

run: main
	$(target)run-labs

debug: main
	gdb $(target)run-labs

main: $(objects)
	@clang++ -o $(target)run-labs $(objects) $(flags) $(include-dirs)

$(objects): $(target)%.o: %/src.cpp
	@clang++ -o $@ -c $< $(flags) $(include-dirs)

