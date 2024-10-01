#pragma once

#include <exception>
#include <string>
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
        void executeTTYCommands(std::vector<std::string_view> command, game::Game& game);

        class CommandException: public std::exception {
            std::string _name; std::string _msg;
            public:
                virtual const char * what(void) const noexcept override;
        };

        class Command {
            public:
                virtual ~Command() {}
                virtual constexpr bool validateName(std::string_view name) const = 0;
                virtual void call(game::Game& game, std::vector<std::string_view> args) = 0;
        };

        /*
         * prints help msg.
         */
        class DisplayHelpCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * prints value of the target.
         * Targets  can   be:  Mage [id], BattleGround,
         * Graveyard, Exile, All.
         */
        class DisplayPrintCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Prints current game state.
         */
        class DisplayStateCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Prints battle field with mages on it.
         */
        class DisplayBattleFieldCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Finish creation of current team and enter to the next.
         */
        class NextTeamCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Print command of current team.
         */
        class CurrTeamCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Generate <n> mages in the current team.
         */
        class GenMagesCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Create mage at current command.
         */
        class MakeMageCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Clear input.
         */
        class ClearCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Start Gui session.
         */
        class StartGuiCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Start game.
         */
        class NewGameCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Set size of the battle field.
         */
        class SetSizeCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };

        /*
         * Exit from the lab command.
         */
        class ExitCommand: public Command {
            public:
                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(game::Game& game, std::vector<std::string_view> args) override;
        };
    }
}
