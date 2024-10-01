#include <iostream>
#include <ostream>
#include <raylib.h>
#include <lab5_game.hpp>
#include <lab5_tty.hpp>


namespace lab5 {

    void runLab5(void) {
        game::Game game;
        char buffer[256] { 0 };

        while (!game.shouldExit()) {
            std::cout << "\x1b[1;34mgame\x1b[0m> ";
            std::cout.flush();

            do std::cin.getline(buffer, 256); while (std::strlen(buffer) == 0);

            auto command = tty::parseCommand(buffer);
            tty::executeTTYCommands(command, game);

            std::cin.clear();
        }

    }
}

#ifdef LAB5_GUI
#include <lab5_gui.hpp>
int main() {
    lab5::gui::gui_main();
    return 0;
}
#endif
