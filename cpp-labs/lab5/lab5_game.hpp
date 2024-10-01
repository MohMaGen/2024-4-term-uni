#include <functional>
#include <iomanip>
#include <lab5_back.hpp>
#include <unordered_map>

namespace lab5 {
    namespace game {


    /*
     * Main game class. Owns mages and process Game Commands.
     */
    class Game {
        std::unordered_map<math::MageId, back::Mage*> battle_ground_pull_m, graveyard_pull_m, exile_pull_m;
        math::Size battle_ground_size_m;

        public:
            enum GameState { NoGame, BlueTeamInit, OrangeTeamInit, InGame, Exit };

            class CommandError: public std::exception {
                public:
                    std::string name;
                    CommandError(const std::string &name): name(name) {}

                    virtual const char * what() const noexcept override {
                        char *res = new char[name.size() + 1];
                        std::strcpy(res, name.c_str());
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
                     * @param state -- new sate
                     */
                    void setState(Game& game, GameState state) { game.game_state_m = state; }
                    /*
                     * Set size of the battle field and exile all mages outside the
                     * field.
                     *
                     * @param size -- new size.
                     */
                    void setSize(Game& game, math::Size size);

                    /*
                     * Vector of all mages.
                     *
                     */
                    std::vector<std::pair<math::MageId, back::Mage*>> allMages(Game& game) {
                        std::vector<std::pair<math::MageId, back::Mage*>> mages;
                        for (auto mage: game.battle_ground_pull_m) mages.push_back(mage);
                        for (auto mage: game.graveyard_pull_m) mages.push_back(mage);
                        for (auto mage: game.exile_pull_m) mages.push_back(mage);
                        return mages;
                    }
                    /*
                     * Create vector of all mages that in game.
                     */
                    std::vector<std::pair<math::MageId, back::Mage*>> inGameMages(Game& game) {
                        std::vector<std::pair<math::MageId, back::Mage*>> mages;
                        for (auto mage: game.battle_ground_pull_m) mages.push_back(mage);
                        return mages;
                    }
                    /*
                     * Create vector of all dead mages.
                     *
                     */
                    std::vector<std::pair<math::MageId, back::Mage*>> deadMages(Game& game) {
                        std::vector<std::pair<math::MageId, back::Mage*>> mages;
                        for (auto mage: game.graveyard_pull_m) mages.push_back(mage);
                        return mages;
                    }
                    /*
                     * Create vector of all exiled mages.
                     *
                     */
                    std::vector<std::pair<math::MageId, back::Mage*>> exiledMages(Game& game) {
                        std::vector<std::pair<math::MageId, back::Mage*>> mages;
                        for (auto mage: game.exile_pull_m) mages.push_back(mage);
                        return mages;
                    }

                    /*
                     * Add new mage to game via mage generator.
                     *
                     */
                    void newMage(Game& game, back::Mage::MageBuilder& builder) {
                        auto [id, mage] = game.generator_m.getMage(builder);
                        game.battle_ground_pull_m.insert({id, mage});
                    }

                    /*
                     * Get size of the battle ground.
                     */
                    math::Size getSize(Game& game) const { return game.battle_ground_size_m; }

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

            Game() : battle_ground_size_m( { 0, 0 } ), game_state_m( NoGame ) {}

            GameState getState(void) const noexcept { return this->game_state_m; }
            void exit(void) noexcept { this->game_state_m = Exit; }

            /*
             * Call command and write to history.
             */
            void callCommand(GameCommand *cmd) {
                try {
                    (*cmd)(*this);
                    this->commands_history_m.push_back(cmd);
                } catch (CommandError &e) {
                    std::cout << "Command " << std::quoted(e.name) << " failed with: " << e.what() << std::endl;
                } catch (std::exception &e) {
                    std::cout << "Command failed with: " << e.what() << std::endl;
                } catch (void *e) {
                    std::cout << "Command failed with unknown error" << std::endl;
                }
            }

            /*
             * Checks if game exit flag is stated.
             */
            bool shouldExit(void) {
                return this->game_state_m == Exit;
            }

            class MageGenerator {
                size_t last_idx = 0;
                public:
                std::pair<math::MageId, back::Mage*> getMage(back::Mage::MageBuilder& builder) {
                    return { last_idx++, builder.make() };
                };
            };


        private:
            GameState game_state_m;
            std::vector<GameCommand*> commands_history_m;
            MageGenerator generator_m;
        public:
            ~Game() {
                for (auto cmd : commands_history_m) delete cmd;
            }

        friend std::ostream& operator<<(std::ostream& os, Game game);
    };
    std::ostream& operator<<(std::ostream &os, Game::GameCommand &cmd) {
        cmd.display(os);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Game::GameState game_state) {
        os << "GameState ";
        switch (game_state) {
            case Game::GameState::NoGame: return os << "NoGame";
            case Game::GameState::OrangeTeamInit: return os << "OrangeTeamInit";
            case Game::GameState::BlueTeamInit: return os << "BlueTeamInit";
            case Game::GameState::InGame: return os << "InGame";
            case Game::GameState::Exit: return os << "Exit";
        }
    }

    std::ostream& operator<<(std::ostream& os, Game game) {
        os << "Game {  " << game.game_state_m << " ) ( Battleground: " << game.battle_ground_size_m << " [ ";

        for (const auto [id, mage] : game.battle_ground_pull_m) {
            os << "( " << id << " " << mage << " )";
        }
        os << " ] ) ( Graveyard: [ ";
        for (const auto [id, mage] : game.graveyard_pull_m) {
            os << "( " << id << " " << mage << " )";
        }
        os << " ] ) ( Exile: [ ";
        for (const auto [id, mage] : game.exile_pull_m) {
            os << "( " << id << " " << mage << " )";
        }
        os << " ] )";

        return os;
    }



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
            virtual void operator()(Game &game) override {
                for (auto [id, mage] : this->inGameMages(game)) {
                    if (mage == nullptr) continue;
                    if (pred(id, mage, BG)) iter = { id, mage };
                }

                for (auto [id, mage] : this->deadMages(game)) {
                    if (mage == nullptr) continue;
                    if (pred(id, mage, GY)) iter = { id, mage };
                }

                for (auto [id, mage] : this->exiledMages(game)) {
                    if (mage == nullptr) continue;
                    if (pred(id, mage, EL)) iter = { id, mage };
                }

            }

            virtual void display(std::ostream &os) const override {
                os << "Query Command";
            }

        private:
            Iter iter;
            Pred pred;
    };

    class NewGameCommand: public Game::GameCommand {
        public:
            NewGameCommand() {}
        protected:
            virtual void operator()(Game &game) override {
                this->setState(game, Game::GameState::BlueTeamInit);
            }
            void display(std::ostream &os) const override {
                os << "NewGame";
            }
    };

    class AddMage: public Game::GameCommand {
        back::Mage::MageBuilder& builder;

        public:
            AddMage(back::Mage::MageBuilder& builder): builder(builder) {}
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

    class GetBattleFieldCOmmand: public Game::GameCommand {
        public:
            using BattleField = std::vector<std::pair<math::MageId, back::Mage*>>;
            using Iter = std::back_insert_iterator<BattleField>;
            GetBattleFieldCOmmand(Iter iter, math::Size &size):  iter(iter), size(size) {}

        protected:
            virtual void operator()(Game &game) override {
                QueryCommand::MagesQuery query;
                game.callCommand(new QueryCommand(std::back_inserter(query),
                            [](auto, auto, auto place){ return place == QueryCommand::BG;}));

                math::Size game_size = this->getSize(game);
                this->size = game_size;

                for (size_t y = 0; y < game_size.height; y++) {
                    for (size_t x = 0; x < game_size.width; x++) {
                        auto res = std::find_if(query.begin(), query.end(), [y, x](auto pair){
                                    return pair.second->getPos() == math::Position { y, x };
                                });
                        if (res == query.end()) {
                            this->iter = std::pair { 0, nullptr };
                        } else {
                            this->iter = std::pair { res->first, res->second };
                        }
                    }
                }
            }
            void display(std::ostream &os) const override {
                os << "Set Size";
            }

        private:
            Iter iter;
            CoordSize &size;
    };
    }
}
