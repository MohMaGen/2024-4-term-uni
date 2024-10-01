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
    }
}
