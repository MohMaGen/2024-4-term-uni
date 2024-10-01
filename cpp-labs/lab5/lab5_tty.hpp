#pragma once

#include <string_view>
#include <vector>
#include <lab5_back.hpp>
#include <lab5_game.hpp>

namespace lab5 {
    namespace tty {
        /*
         * Parse command by views. It doesnot create new string or allocate smth.
         * Just create view of given buffer. O(N)
         *
         * @param buffer -- buffer to separate on views.
         * @return vector of views.
         */
        std::vector<std::string_view> parseCommand(const char *buffer);

        /*
         * Check if view equal to buffer. !VARNING O(N)
         */
        bool view_eq(std::string_view view, const char *value);

        /*
         * Execute TTY command.
         * Main function for tty frontend of the game.
         *
         * @param command -- command given to the frontend,
         * @param game -- current game state.
         */
        void executeTTYCommand(std::vector<std::string_view> command, game::Game &game);

    }
}
