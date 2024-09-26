
target := target/

labs := $(wildcard lab*/)
include-dirs := $(patsubst %, -I %, $(labs)) -I ./raylib/src/

sources := $(patsubst %, %src.cpp, $(labs))
objects := $(patsubst %/src.cpp, $(target)%.o, $(sources)) $(target)main.o

flags := -g3 -Wall -Werror -std=c++23 -pedantic -pedantic-errors -Wno-nested-anon-types

run: main
	$(target)run-labs

debug: main
	gdb $(target)run-labs

chck-mem: main
	valgrind --leak-check=full $(target)run-labs

main: raylib $(objects)
	@clang++ -o $(target)run-labs $(objects) $(flags) $(include-dirs) -L $(target) -lraylib

$(objects): $(target)%.o: %/src.cpp
	@clang++ -o $@ -c $< $(flags) $(include-dirs)

raylib:
	@echo "build raylib"
	@make -C ./raylib/src clean
	@make CC=/bin/gcc -C ./raylib/src PLATFORM=PLATFORM_DESKTOP
	@mv ./raylib/src/libraylib* $(target)


compile-commands-src = $(patsubst %.cpp, cc_%, $(sources))

compile-commands: clear-cc $(compile-commands-src)

$(compile-commands-src): cc_%: %.cpp
	./scripts/add_obj_to_compile_commands.sh $< "clang++ -o $@ -c $< $(flags) $(include-dirs)"

clear-cc:
	@echo "[]" > ./compile_commands.json

