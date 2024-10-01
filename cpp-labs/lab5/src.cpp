#include <cstdint>
#include <iostream>
#include <ostream>
#include <raylib.h>


namespace lab5 {


    void runLab5(void) {
        Game game;
        char buffer[256] { 0 };

        while (!game.shouldExit()) {
            std::cout << "\x1b[1;34mgame\x1b[0m> ";
            std::cout.flush();

            do std::cin.getline(buffer, 256); while (std::strlen(buffer) == 0);

            auto command = tty::parseCommand(buffer);
            tty::executeTTYCommand(command, game);

            std::cin.clear();
        }

    }
}

#ifdef LAB5_GUI
int main() {
    lab5::gui::gui_main();
    return 0;
}
#endif
