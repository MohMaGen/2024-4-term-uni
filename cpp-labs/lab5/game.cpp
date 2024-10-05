#include "lab5_math.hpp"
#include <algorithm>
#include <lab5_game.hpp>

namespace lab5 {
    namespace game {
        void Game::GameCommand::setSize(Game& game, math::Size size) {
            game._battle_ground_size = size;
            std::vector<std::pair<math::MageId, back::Mage*>> mages_to_exile;

            for (auto [id, mage]: game._battle_ground_pull) {
                if (!math::Rect(size).chckInside(mage->getPos())) {
                    mages_to_exile.push_back({id, mage});
                }
            }

            for (auto [id, mage] : mages_to_exile) {
                game._battle_ground_pull.erase(id);
                game._exile_pull.insert({id, mage});
            }

        }


        Game::MageVec Game::GameCommand::allMages(Game& game) {
            MageVec mages;
            for (auto mage: game._battle_ground_pull) mages.push_back(mage);
            for (auto mage: game._graveyard_pull) mages.push_back(mage);
            for (auto mage: game._exile_pull) mages.push_back(mage);
            return mages;
        }

        Game::MageVec Game::GameCommand::inGameMages(Game& game) {
            MageVec mages;
            for (auto mage: game._battle_ground_pull) mages.push_back(mage);
            return mages;
        }

        Game::MageVec Game::GameCommand::deadMages(Game& game) {
            MageVec mages;
            for (auto mage: game._graveyard_pull) mages.push_back(mage);
            return mages;
        }

        Game::MageVec Game::GameCommand::exiledMages(Game& game) {
            MageVec mages;
            for (auto mage: game._exile_pull) mages.push_back(mage);
            return mages;
        }

        math::MageId Game::GameCommand::getCurrMage(const Game& game) const {
            if (game._game_state != Game::GameState::InGame)
                throw Game::CommandError { "get Current Mage", "Battle wasnot started!" };

            if (game._battle_order.size() >= game._current_mage)
                throw Game::CommandError { "get Current Mage", "-- Somehow --  Invalid currant mage value!" };

            return game._battle_order[game._current_mage];
        }

        back::Team Game::GameCommand::getCurrTeam(const Game& game) const {
            if (game._game_state != Game::GameState::InGame)
                throw Game::CommandError { "get Current Team", "Battle wasnot started!" };

            return game._current_team;
        }

        std::vector<Game::MagePair> Game::GameCommand::getCurrOrder(Game& game) {
            if (game._game_state != Game::GameState::InGame)
                throw Game::CommandError { "get Current Order", "Battle wasnot started!" };

            std::vector<Game::MagePair> order;
            for (auto id : game._battle_order) try {
                auto mage = game._battle_ground_pull.at(id);
                order.push_back({ id, mage });
            } catch (...) { continue; }

            return order;
        }

        void Game::GameCommand::startBattle(Game& game) {
            if (game._game_state != Game::GameState::OrangeTeamInit)
                throw Game::CommandError { "Start Battle", "Had to init Orange team, before stats battle!" };

            this->setState(game, Game::GameState::InGame);
            game._battle_order = std::vector<math::MageId> {};

            for (auto [id, mage] : game._battle_ground_pull)
                if (mage->getTeam() == back::Team::Blue) game._battle_order.push_back(id);

            for (auto [id, mage] : game._battle_ground_pull)
                if (mage->getTeam() == back::Team::Orange) game._battle_order.push_back(id);
        }



        void Game::GameCommand::newMage(Game& game, back::Mage::MageBuilder& builder) {
            auto [id, mage] = game._generator.getMage(builder);
            const auto mages = this->inGameMages(game);
            if (std::find_if(mages.begin(), mages.end(),
                        [&mage](auto bg_mage) { return mage->getPos() == bg_mage.second->getPos(); }) != mages.end()) {
                throw CommandError("newMageError", "Mage with this name exists.");
            }

            game._battle_ground_pull.insert({id, mage});
        }


        void Game::callCommand(GameCommand *cmd) {
            if (cmd == nullptr) {
                std::cout << "Command is nullptr!!!!" << std::endl;
                return;
            }

            (*cmd)(*this);
            this->_commands_history.push_back(cmd);
        }


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
            os << "Game {  " << game._game_state << " ) ( Battleground: " << game._battle_ground_size << " [ ";

            for (const auto [id, mage] : game._battle_ground_pull) {
                os << "( " << id << " " << mage << " )";
            }
            os << " ] ) ( Graveyard: [ ";
            for (const auto [id, mage] : game._graveyard_pull) {
                os << "( " << id << " " << mage << " )";
            }
            os << " ] ) ( Exile: [ ";
            for (const auto [id, mage] : game._exile_pull) {
                os << "( " << id << " " << mage << " )";
            }
            os << " ] )";

            return os;
        }

        void QueryCommand::operator()(Game &game) {
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
        void GetBattleFieldCommand::operator()(Game &game) {
            QueryCommand::MagesQuery query;
            game.callCommand(new QueryCommand(std::back_inserter(query),
                        [](auto, auto, auto place){ return place == QueryCommand::BG;}));

            math::Size game_size = this->getSize(game);
            _size = game_size;

            for (size_t y = 0; y < game_size.height; y++) {
                for (size_t x = 0; x < game_size.width; x++) {
                    auto res = std::find_if(query.begin(), query.end(), [y, x](auto pair){
                            return pair.second->getPos() == math::Position { y, x };
                            });
                    if (res == query.end()) {
                        _iter = std::pair { 0, nullptr };
                    } else {
                        _iter = std::pair { res->first, res->second };
                    }
                }
            }
        }

        void GenMageCommand::operator()(Game &game) {
            auto size = this->getSize(game);

            back::Mage::MageBuilder builder (_team);
            math::Rect bounds { math::Size{size.width / 2, size.height } };

            if (_team == back::Team::Blue) {
                bounds.pos = { 0, 0 };
            }
            if (_team == back::Team::Orange) {
                bounds.pos = { size.width / 2, 0 };
            }

            while (true) try { 
                builder.withPos(bounds.getRand());
                this->newMage(game, builder);
                break;
            } catch (Game::CommandError &e) {}
        }
    }
}
