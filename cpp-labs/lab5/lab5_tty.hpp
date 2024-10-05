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
                CommandException(const std::string &name, const std::string &msg):
                    _name(name), _msg(msg) {}

                virtual const char * what(void) const noexcept override;
        };

        class Command {
            protected:
                game::Game &_game;
                std::vector<std::string_view> &_args;
            public:

                Command(game::Game& game, std::vector<std::string_view> &args)
                    : _game(game), _args(args) {}
                virtual ~Command() {}

                virtual constexpr bool validateName(std::string_view name) const = 0;
                virtual void call() const = 0;
        };

        /*
         * prints help msg.
         */
        class DisplayHelpCommand: public Command {
            public:
                DisplayHelpCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * prints value of the target.
         * Targets  can   be:  Mage [id], BattleGround,
         * Graveyard, Exile, All.
         */
        class DisplayPrintCommand: public Command {
            public:
                DisplayPrintCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Prints current game state.
         */
        class DisplayStateCommand: public Command {
            public:
                DisplayStateCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Prints battle field with mages on it.
         */
        class DisplayBattleFieldCommand: public Command {
            public:
                DisplayBattleFieldCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Finish creation of current team and enter to the next.
         */
        class NextTeamCommand: public Command {
            public:
                NextTeamCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Print command of current team.
         */
        class CurrTeamCommand: public Command {
            public:
                CurrTeamCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Generate <n> mages in the current team.
         */
        class GenMagesCommand: public Command {
            public:
                GenMagesCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Create mage at current command.
         */
        class MakeMageCommand: public Command {
            public:
                MakeMageCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Clear input.
         */
        class ClearCommand: public Command {
            public:
                ClearCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Start Gui session.
         */
        class StartGuiCommand: public Command {
            public:
                StartGuiCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Start game.
         */
        class NewGameCommand: public Command {
            public:
                NewGameCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Set size of the battle field.
         */
        class SetSizeCommand: public Command {
            public:
                SetSizeCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };

        /*
         * Exit from the lab command.
         */
        class ExitCommand: public Command {
            public:
                ExitCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) const override;
        };
    }
}
