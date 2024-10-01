#include <stdio.h>
#include <string.h>

#define NOBUILD_IMPLEMENTATION
#include "./nobuild-repo/nobuild.h"



int main(int argc, char **argv) {
    GO_REBUILD_URSELF((size_t)argc, argv);
    FOREACH_FILE_IN_DIR(name, "./", {
        if (IS_DIR(name) && memcmp(name, "lab", 3) == 0) {
        } else {
            printf("file: %s\n", name);
        }
    });

    return 0;
}
