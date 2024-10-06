#pragma once

#include "lab5_math.hpp"
#include <functional>
#include <lab5_back.hpp>
#include <unordered_map>

namespace lab5 {
    namespace game {

        /*
         * Main game class. Owns mages and process Game Commands.
         */
        class Game {
            public:
                using MagePtr = back::Mage*;

                using MageMap = std::unordered_map<math::MageId, MagePtr>;

                using MagePair = std::pair<math::MageId, MagePtr>;
                using MageVec = std::vector<MagePair>;

                enum GameState { NoGame, BlueTeamInit, OrangeTeamInit, InGame, Exit };

                class CommandError: public std::exception {
                    public:
                        std::string _name, _err;
                        CommandError(const std::string &name, const std::string &err): _name(name), _err(err) {}

                        virtual const char * what() const noexcept override {
                            char *res = new char[_name.size() + _err.size() + 3];
                            std::strcpy(res, (_name + ": " + _err).c_str());
                            return res;
                        }

                        virtual ~CommandError() {}
                };

                /*
                 * Commands that manipulate Games logics.
                 */
                class GameCommand {
                    friend Game;

                    public:
                        virtual ~GameCommand() {}

                    protected:
                        /*
                         * Set state of the game.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param state -- new sate
                         */
                        void setState(Game& game, GameState state) { game._game_state = state; }


                        /*
                         * Set size of the battle field and exile all mages outside the
                         * field.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param game -- game state to change by command.
                         * @param size -- new size.
                         */
                        void setSize(Game& game, math::Size size);


                        /*
                         * Vector of all mages.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param game -- game state to change by command.
                         */
                        MageVec allMages(Game& game);


                        /*
                         * Create vector of all mages that in game.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param game -- game state to change by command.
                         */
                        MageVec inGameMages(Game& game);


                        /*
                         * Create vector of all dead mages.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param game -- game state to change by command.
                         */
                        MageVec deadMages(Game& game);

                        /*
                         * Create vector of all exiled mages.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param game -- game state to change by command.
                         */
                        MageVec exiledMages(Game& game);


                        /*
                         * Get current mage. Works in @GameState::InGame state.
                         * Otherwise return MageId(0).
                         *
                         * @param game -- game state to change by command.
                         * @return @math::MageId -- mage id.
                         */
                        math::MageId getCurrMage(const Game& game) const;


                        /*
                         * Get current team. Works in @GameState::InGame state.
                         * Otherwise return Team::Blue.
                         *
                         * @param game -- game state to change by command.
                         * @return @back::Team -- team.
                         */
                        back::Team getCurrTeam(const Game& game) const;


                        /*
                         * Get current battle order.
                         * 
                         * @param game -- game state to change by command.
                         * @return mages -- reference to order vector..
                         */
                        std::vector<MagePair> getCurrOrder(Game& game);


                        /*
                         * Start battle.
                         * 
                         * @param game -- game state to change by command.
                         */
                        void startBattle(Game& game);


                        /*
                         * Add new mage to game via mage generator.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param game -- game state to change by command.
                         */
                        void newMage(Game& game, back::Mage::MageBuilder& builder);

                        /*
                         * Get size of the battle ground.
                         *
                         * This function used by inherit classes to work with game.
                         *
                         * @param game -- game state to change by command.
                         */
                        math::Size getSize(Game& game) const { return game._battle_ground_size; }


                        /*
                         * Execute command. This function runned by Game.
                         *
                         *
                         * @param game -- The game reference, passed by @Game::callCommand(Game::GameCommand*).
                         *
                         * @throw must throw exception inherited of CommandError. But
                         *      will not break if throw somethign else.
                         */
                        virtual void operator()(Game &) = 0;

                        /*
                         * display to ostream.
                         */
                        virtual void display(std::ostream &os) const = 0;
                    friend std::ostream& operator<<(std::ostream &os, GameCommand &cmd);
                };
                friend GameCommand;

                Game() : _battle_ground_size( { 0, 0 } ), _game_state( NoGame ) {}

                GameState getState(void) const noexcept { return this->_game_state; }
                void exit(void) noexcept { this->_game_state = Exit; }

                /*
                 * Call command and write to history.
                 */
                void callCommand(GameCommand *cmd);

                /*
                 * Checks if game exit flag is stated.
                 */
                bool shouldExit(void) {
                    return this->_game_state == Exit;
                }

                /*
                 * Sipmle back::Mage fabric to create mages with index.
                 */
                class MageGenerator {
                    // starts with 1, so mages with id 0 is nullptr.
                    size_t last_idx = 1;

                    public:
                    MagePair getMage(back::Mage::MageBuilder& builder) {
                        auto mage = builder.make();

                        return { last_idx++, mage };
                    };
                };


            private:
                // Contains mages that can cast spells.
                MageMap _battle_ground_pull;

                // Contains killed/dead mages.
                MageMap _graveyard_pull;

                // Contains exiled mages.
                MageMap _exile_pull;

                // Size of the battle ground.
                math::Size _battle_ground_size;

                // Current state of the game.
                GameState _game_state;

                // History of all game commands.
                std::vector<GameCommand*> _commands_history;

                // Generator.
                MageGenerator _generator;


                // Current team.
                back::Team _current_team;

                // BattleOrder
                std::vector<math::MageId> _battle_order { 0 };

                // Current mage.
                size_t _current_mage { 0 };


            public:
                ~Game() {
                    for (auto cmd : _commands_history) delete cmd;
                }

            friend std::ostream& operator<<(std::ostream& os, Game game);
        };




        /*
         * Exit command. Set game flag to exit.
         */
        class ExitCommand: public Game::GameCommand {
            protected:
                virtual void operator()(Game &game) override { game.exit(); }

                virtual void display(std::ostream &os) const override {
                    os << "Exit Command";
                }
        };

        /*
         * Game Command to query through mages of game;
         *
         * @type Pred -- predicate to filter mages.
         * @type Iter -- type of resulting query containter.
         */
        class QueryCommand: public Game::GameCommand {
            public:
                enum Place { BG = 0b001, GY = 0b010, EL = 0b100 };
                using MagesQuery = std::vector<std::pair<math::MageId, back::Mage*>>;
                using Iter = std::back_insert_iterator<MagesQuery>;
                using Pred = std::function<bool (math::MageId,back::Mage*,Place)>;

                /*
                 * Create Query.
                 *
                 * @param Iter iter - resulting iterator to insert mage.
                 * @param Pred pred - predicate function to filter mages.
                 *
                 * @USAGE
                 * ```cpp
                 * QueryCommand::MagesQuery query;
                 * game.callCommand(QueryCommand(std::back_inserter(query),
                 *                  [](auto id, auto, auto) { return id % 2 == 0; }));
                 *
                 * // Mages with even id.
                 * for (auto [id, mage] : query) {
                 *      std::cout << "Id: " << id << ", " << "Mage: " << mage << std::endl;
                 * }
                 * ```
                 */
                explicit QueryCommand(Iter iter, Pred pred): iter(iter), pred(pred) {}

            protected:
                virtual void operator()(Game &game) override;

                virtual void display(std::ostream &os) const override {
                    os << "Query Command";
                }

            private:
                Iter iter;
                Pred pred;
        };

        class NewGameCommand: public Game::GameCommand {
            public:

                // Current mage.
                math::MageId current_mage;


                NewGameCommand() {}
            protected:
                virtual void operator()(Game &game) override {
                    this->setState(game, Game::GameState::BlueTeamInit);
                }
                void display(std::ostream &os) const override {
                    os << "NewGame";
                }
        };

        class AddMageCommand: public Game::GameCommand {
            back::Mage::MageBuilder& builder;

            public:
                AddMageCommand(back::Mage::MageBuilder& builder): builder(builder) {}
            protected:
                virtual void operator()(Game &game) override {
                    this->newMage(game, this->builder);
                }
                void display(std::ostream &os) const override {
                    os << "Add Mage";
                }
        };

        class NextTeamCommand: public Game::GameCommand {
            public:
                NextTeamCommand(void) {}
            protected:
                virtual void operator()(Game &game) override {
                    if (game.getState() == Game::GameState::BlueTeamInit)
                        this->setState(game, Game::GameState::OrangeTeamInit);
                }
                void display(std::ostream &os) const override {
                    os << "Add Mage";
                }
        };

        class SetGameSizeCommand: public Game::GameCommand {
            math::Size size;
            public:
                SetGameSizeCommand(math::Size size): size(size) {}

            protected:
                virtual void operator()(Game &game) override {
                    this->setSize(game, this->size);
                }
                void display(std::ostream &os) const override {
                    os << "Set Size";
                }

        };

        class GetBattleFieldCommand: public Game::GameCommand {
            public:
                using BattleField = std::vector<std::pair<math::MageId, back::Mage*>>;
                using Iter = std::back_insert_iterator<BattleField>;
                GetBattleFieldCommand(Iter iter, math::Size &size):
                    _iter(iter), _size(size) {}

            protected:
                virtual void operator()(Game &game) override;

                void display(std::ostream &os) const override {
                    os << "Get Battle Field";
                }

            private:
                Iter _iter;
                math::Size &_size;
        };

        class GenMageCommand: public Game::GameCommand {
            back::Team _team;
            public:
                GenMageCommand(back::Team team): _team(team) {}

            protected:
                virtual void operator()(Game &game) override;

                void display(std::ostream &os) const override {
                    os << "Gen Mage";
                }
        };

        class GetCurrentMageCommand: public Game::GameCommand {
            size_t& _curr_mage;
            public:
                GetCurrentMageCommand(size_t& curr_mage): _curr_mage(curr_mage) {}

            protected:
                virtual void operator()(Game &game) override;

                void display(std::ostream &os) const override {
                    os << "Get Current Mage";
                }
        };

        class GetCurrentOrderCommand: public Game::GameCommand {
            std::vector<Game::MagePair>& _mages;
            public:
                GetCurrentOrderCommand(std::vector<Game::MagePair> &mages): _mages(mages) {}

            protected:
                virtual void operator()(Game &game) override;

                void display(std::ostream &os) const override {
                    os << "Get Current Battle Order";
                }
        };

        class GetCurrentTeamCommand: public Game::GameCommand {
            back::Team& _team;
            public:
                GetCurrentTeamCommand(back::Team& team): _team(team) {}

            protected:
                virtual void operator()(Game &game) override;

                void display(std::ostream &os) const override {
                    os << "Get Current Team Order";
                }
        };

        class StartBattleCommand: public Game::GameCommand {
            public:
                StartBattleCommand() {}

            protected:
                virtual void operator()(Game &game) override;

                void display(std::ostream &os) const override {
                    os << "Start Battle";
                }
        };
    }
}
