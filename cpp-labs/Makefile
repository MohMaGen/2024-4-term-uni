
target := target/

labs := $(wildcard lab*/)
include-dirs := $(patsubst %, -I %, $(labs))

sources := $(patsubst %, %src.cpp, $(labs))
objects := $(patsubst %/src.cpp, $(target)%.o, $(sources)) $(target)main.o

flags := -g -v -Wall -Werror -std=c++23

main: $(objects)
	echo "$(labs): $(include-dirs): $(sources): $(objects)"
	clang++ -o $(target)run-labs $(objects) $(flags) $(include-dirs)

$(objects): $(target)%.o: %/src.cpp
	clang++ -o $@ -c $< $(flags) $(include-dirs)

