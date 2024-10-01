#include <iomanip>
#include <lab5_game.hpp>

namespace lab5 {
    namespace game {
        void Game::GameCommand::setSize(Game& game, math::Size size) {
            game.battle_ground_size_m = size;
            std::vector<std::pair<math::MageId, back::Mage*>> mages_to_exile;

            for (auto [id, mage]: game.battle_ground_pull_m) {
                if (!math::Rect(size).chckInside(mage->getPos())) {
                    mages_to_exile.push_back({id, mage});
                }
            }

            for (auto [id, mage] : mages_to_exile) {
                game.battle_ground_pull_m.erase(id);
                game.exile_pull_m.insert({id, mage});
            }

        }


        Game::MageVec Game::GameCommand::allMages(Game& game) {
            MageVec mages;
            for (auto mage: game.battle_ground_pull_m) mages.push_back(mage);
            for (auto mage: game.graveyard_pull_m) mages.push_back(mage);
            for (auto mage: game.exile_pull_m) mages.push_back(mage);
            return mages;
        }

        Game::MageVec Game::GameCommand::inGameMages(Game& game) {
            MageVec mages;
            for (auto mage: game.battle_ground_pull_m) mages.push_back(mage);
            return mages;
        }

        Game::MageVec Game::GameCommand::deadMages(Game& game) {
            MageVec mages;
            for (auto mage: game.graveyard_pull_m) mages.push_back(mage);
            return mages;
        }

        Game::MageVec Game::GameCommand::exiledMages(Game& game) {
            MageVec mages;
            for (auto mage: game.exile_pull_m) mages.push_back(mage);
            return mages;
        }


        void Game::GameCommand::newMage(Game& game, back::Mage::MageBuilder& builder) {
            auto [id, mage] = game.generator_m.getMage(builder);
            game.battle_ground_pull_m.insert({id, mage});
        }


        void Game::callCommand(GameCommand *cmd) {
            if (cmd == nullptr) {
                std::cout << "Command is nullptr!!!!" << std::endl;
                return;
            }

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
    }
}
