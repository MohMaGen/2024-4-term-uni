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
                virtual void call() = 0;
        };

        /*
         * prints help msg.
         */
        class DisplayHelpCommand: public Command {
            public:
                DisplayHelpCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
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
                virtual void call(void) override;
        };

        /*
         * Prints current game state.
         */
        class DisplayStateCommand: public Command {
            public:
                DisplayStateCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Prints battle field with mages on it.
         */
        class DisplayBattleFieldCommand: public Command {
            math::MageId _curr_mage;
            std::vector<math::MageId> _selected;

            public:
                DisplayBattleFieldCommand(game::Game& game, std::vector<std::string_view> &args,
                                          math::MageId curr_mage, std::vector<math::MageId> selected)
                    :Command(game, args), _curr_mage{ curr_mage }, _selected{ selected } {}

                DisplayBattleFieldCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args), _curr_mage{ 0 }, _selected{ 0 } {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Finish creation of current team and enter to the next.
         */
        class NextTeamCommand: public Command {
            public:
                NextTeamCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Print command of current team.
         */
        class CurrTeamCommand: public Command {
            public:
                CurrTeamCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Generate <n> mages in the current team.
         */
        class GenTeamCommand: public Command {
            public:
                GenTeamCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Create mage at current command.
         */
        class MakeMageCommand: public Command {
            public:
                MakeMageCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Clear input.
         */
        class ClearCommand: public Command {
            public:
                ClearCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Start Gui session.
         */
        class StartGuiCommand: public Command {
            public:
                StartGuiCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Start game.
         */
        class NewGameCommand: public Command {
            public:
                NewGameCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Set size of the battle field.
         */
        class SetSizeCommand: public Command {
            public:
                SetSizeCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Exit from the lab command.
         */
        class ExitCommand: public Command {
            public:
                ExitCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Start battle.
         */
        class StartBattleCommand: public Command {
            public:
                StartBattleCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Show battle state, current mage and available spells.
         */
        class ShowCommand: public Command {
            public:
                ShowCommand(game::Game& game, std::vector<std::string_view> &args)
                    :Command(game, args) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Choose spell as target.
         */
        class ChooseSpellCommand: public Command {
            size_t &_curr_spell;
            public:
                ChooseSpellCommand(game::Game& game, std::vector<std::string_view> &args, size_t &curr_spell)
                    :Command(game, args), _curr_spell(curr_spell) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };

        /*
         * Show available targets of current spell.
         */
        class DisplayTargetsCommand: public Command {
            size_t _curr_spell;

            public:
                DisplayTargetsCommand(game::Game& game, std::vector<std::string_view> &args, size_t curr_spell)
                    :Command(game, args), _curr_spell(curr_spell) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };


        /*
         * Cast spell.
         */
        class CastSpelLCommand: public Command {
            size_t _curr_spell;
            public:
                CastSpelLCommand(game::Game& game, std::vector<std::string_view> &args, size_t curr_spell)
                    :Command(game, args), _curr_spell(curr_spell) {}

                virtual constexpr bool validateName(std::string_view name) const override;
                virtual void call(void) override;
        };
    }
}
