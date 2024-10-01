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
    }
}
