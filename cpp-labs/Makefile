target := target/

labs := $(wildcard lab*/)
include-dirs := $(patsubst %, -I %, $(labs)) -I./raylib/src/
ld-flags := -L./target -lraylib

sources := $(patsubst %, %src.cpp, $(labs))
objects := $(patsubst %/src.cpp, $(target)%.o, $(sources)) $(target)main.o

flags := -g3 -Wall -Werror -std=c++23 -pedantic -pedantic-errors -Wno-nested-anon-types

run: main
	$(target)run-labs

run-lab5-gui:
	clang++ -o $(target)lab5-gui ./lab5/src.cpp $(flags) $(include-dirs) $(ld-flags) -DLAB5_GUI=1 -fuse-ld=mold
	./$(target)lab5-gui

debug: main
	gdb $(target)run-labs

chck-mem: main
	valgrind --leak-check=full $(target)run-labs

main: raylib $(objects)
	clang++ -o $(target)run-labs $(objects) $(flags) $(include-dirs) $(ld-flags)  -fuse-ld=mold

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

