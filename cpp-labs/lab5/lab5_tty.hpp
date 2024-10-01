#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string_view>
#include <vector>
#include <lab5_back.hpp>

namespace lab5 {
    namespace tty {
        std::vector<std::string_view> parseCommand(const char *buffer) {
            std::vector<std::string_view> vec;
            size_t start = 0, curr = 0;

            bool parse_string = false;

            const auto push = [&vec, &buffer, &curr, &start]() {
                if (curr != start) vec.push_back({ buffer + start, curr - start });
                start = curr + 1;
            };
            const auto switch_parse_string = [&] () {
                    parse_string = true;
                    push();
            };

            do {
                if (!parse_string) {
                    if (buffer[curr] == '"') switch_parse_string();
                    if (buffer[curr] == ' ') push();
                } else if (buffer[curr] == '"') switch_parse_string();
            } while (buffer[curr++] != '\0');

            if (curr != start) push();

            return vec;
        }

        bool view_eq(std::string_view view, const char *value) {
            return std::equal(view.begin(), view.end(), std::string_view{value}.begin());
        }


        const char HELP_MSG[] = " lab5 magic:\n\n"
            "\x1b[1;34mUSAGE:\x1b[0m\n"
            " [command] ([command_args])\n"
            "\n"
            "\x1b[1;34mDISPLAY COMMANDS:\x1b[0m \n"
            "    - help, h              --- prints help command.\n"
            "    - print, b [<target>]  --- prints value of the target.\n"
            "                    Targets  can   be:  Mage [id], BattleGround,\n"
            "                    Graveyard, Exile, All.\n"
            "    - state                --- prints current game state\n"
            "    - battle_field         --- prints battle field with mages.\n"
            "\n"
            "\x1b[1;34mGAME INIT COMMANDS:\x1b[0m ( only in InitBlue & InitOrange states )\n"
            "    - next_team            --- finish creation of current team\n"
            "                    and enter to next.\n"
            "    - curr_team            --- print current team.\n"
            "    - gen_mages <n>        --- generate <n> mages for current team\n"
            "    - make_mage            --- run mage builder.\n"
            "\n"
            "\x1b[1;34mUI COMMANDS:\x1b[0m\n"
            "    - clear                --- clear\n"
            "    - gui                  --- turn into gui mod.\n"
            "\n"
            "\x1b[1;34mGAME CONTROLL COMMANDS:\x1b[0m\n"
            "    - new_game             --- start game\n"
            "    - set_size <width> <height>\n"
            "                           --- set size of the battle field.\n "
            "                    This will exile all mages outside of the\n"
            "                    new battle field.\n"
            "    - exit, e              --- exit lab5.\n"
            "\n";

        // process terminal input and run game commands.
        void executeTTYCommand(std::vector<std::string_view> command, back::Game &game) {
            if (command.size() == 0) {
                std::cout << std::endl;
                return;
            }
            auto name = command[0];

            if (view_eq(name, "exit" ) || view_eq(name, "e" )) {
                game.callCommand(new ExitCommand());

            } if (view_eq(name, "clear") || view_eq(name, "\x0C")) {
                std::cout << "\x1b[1;1H\x1b[2J";

            } else if (view_eq(name, "gui")) {
                gui::gui_main();

            } else if (view_eq(name, "help" ) || view_eq(name, "h" )) {
                std::cout << HELP_MSG << std::endl;

            } else if (view_eq(name, "state")) {
                std::cout << game.getState() << std::endl;

            } else if (view_eq(name, "battle_field")) {
                GetBattleFieldCOmmand::BattleField bf;
                CoordSize size { 0, 0 };

                game.callCommand(new GetBattleFieldCOmmand(std::back_inserter(bf), size));

                const size_t cell_size = 6;
                const size_t indent = 5;
                const auto nl = [](void){
                    std::cout << "\n" << std::string(indent, ' ');
                };
                const auto cnt = [](const std::string &str, size_t view){
                    if (view <= str.length()) {
                        std::cout << std::string_view(str.data(), view);
                    } else {
                        size_t left_padding = (view - str.length()) / 2;
                        size_t right_padding = (view - str.length()) / 2 + (view - str.length()) % 2;
                        std::cout << std::string(left_padding, ' ') << str << std::string(right_padding, ' ');
                    }
                };
                const auto clear  = [](){ std::cout << "\x1b[0m"; };
                const auto color = [](int id){ std::cout << "\x1b[3" << id << "m"; };
                const auto bg_color = [](int id){ std::cout << "\x1b[4" << id << "m"; };
                std::cout << "Battle field " << size.first << "x" << size.second << std::endl;
                nl();
                for (size_t i = 0; i < size.second; i++) {
                    for (size_t j = 0; j < size.first; j++) {
                        if ((i + j) % 2) {
                            bg_color(7);
                        } else {
                            clear();
                        }
                        const auto chck = [i, j](auto pair) {
                            if (pair.second == nullptr) return false;
                            return pair.second->getPos() == Position { j, i };
                        };
                        auto res = std::find_if(bf.begin(), bf.end(), chck);

                        if (res == bf.end()) {
                            std::cout << std::string(cell_size, ' ');
                            continue;
                        }
                        if (res->second->getTeam() == Team::Blue) {
                            color(4);
                        } else {
                            color(2);
                        }
                        cnt(std::to_string(res->first), cell_size);
                    }
                    clear();
                    nl();
                }
                clear();
                std::cout << std::endl;

            } else if (view_eq(name, "new_game")) {
                game.callCommand(new NewGameCommand());

            } else if (view_eq(name, "next_team")) {
                game.callCommand(new NextTeamCommand());

            } else if (view_eq(name, "set_size")) {
                CoordSize size { 0, 0 };
                if (command.size() < 2 ||
                        std::from_chars(command[1].begin(), command[1].end(), size.first.v).ec != std::errc{}) {
                    std::cout << "Failed to parse <width>.\n" << HELP_MSG << std::endl;
                    return;
                }
                if (command.size() < 3 ||
                        std::from_chars(command[2].begin(), command[2].end(), size.second.v).ec != std::errc{}) {
                    std::cout << "Failed to parse <height>.\n" << HELP_MSG << std::endl;
                    return;
                }
                if (!std::cin) {
                    std::cout << "Invalid size input.\n" << HELP_MSG << std::endl;
                    return;
                }
                std::cout << size << std::endl;
                game.callCommand(new SetGameSizeCommand(size));

            } else if (view_eq(name, "curr_team")) {
                using GameState = Game::GameState;
                switch (game.getState()) {
                    case GameState::BlueTeamInit: std::cout << "Blue Team" << std::endl; break;
                    case GameState::OrangeTeamInit: std::cout << "Orange Team" << std::endl; break;
                    default:
                        std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                }

            } else if (view_eq(name, "gen_team")) {
                Team curr_team_init;

                using GameState = Game::GameState;
                switch (game.getState()) {
                    case GameState::BlueTeamInit: curr_team_init = Team::Blue; break;
                    case GameState::OrangeTeamInit: curr_team_init = Team::Orange; break;
                    default:
                        std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                        return;
                }

                int n;
                if (command.size() < 2 || std::from_chars(command[1].begin(), command[1].end(), n).ec != std::errc{}) {
                    std::cout << "Failed to parse int <n>" << std::endl;
                    return;
                }

                Mage::MageBuilder builder (curr_team_init);
                if (curr_team_init == Team::Blue) {
                    //builder.withPos(Position pos)
                }


            } else if (view_eq(name, "make_mage")) {
                Team curr_team_init;

                using GameState = Game::GameState;
                switch (game.getState()) {
                    case GameState::BlueTeamInit: curr_team_init = Team::Blue; break;
                    case GameState::OrangeTeamInit: curr_team_init = Team::Orange; break;
                    default:
                        std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                        return;
                }

                Mage::MageBuilder builder (curr_team_init);
                std::cout << "\x1b[1;34menter pos: `x y`\x1b[0m> ";
                Position pos { 0, 0 };
                std::cin >> pos.first.v >> pos.second.v;
                if (!std::cin) {
                    std::string value;
                    std::cin >> value;
                    std::cout << "Incorect position: " << value << std::endl;
                }
                builder.withPos(pos);


                for (size_t i = 0; i < 2; i++) {
                    std::cout << "\x1b[1;34mchoose spell type " << i << "\x1b[0m> ";
                    std::string spell_type;
                    std::cin >> spell_type;

                    Spell::SpellBuilder* sb;
                    if (spell_type == "Long" || spell_type == "LongDist")
                        sb = LongRangeSpell::build();
                    else if (spell_type == "Short" || spell_type == "ShortDist")
                        sb = ShortRangeSpell::build();
                    else if (spell_type == "Support")
                        sb = SupportSpell::build();
                    else if (spell_type == "Curse")
                        sb = CurseSpell::build();
                    else {
                        std::cout << "Wrong Spell Type. Choose one of LongDist, ShortDist, Support, Curse." << std::endl;
                        i--;
                        continue;
                    }
                    size_t count = rand() % 5 + 1;
                    for (size_t i = 0; i < count; i++) {
                        Spell::SpellBuilder sb_cp (sb->alloc());
                        sb_cp.withManaCost(rand()%100 + 1)
                            ->withCost(rand()%10 + 1)
                            ->withApplyDuration(rand()%3600 + 1)
                            ->withEffectDuration(rand()%10 + 1)
                            ->withDistance(rand()%100 + 1)
                            ->withTargetArea([]{ return (rand()%2) ? TargetArea(rand()%10+1) : TargetArea(); }());

                        size_t count = rand()%10 + 1;
                        for (size_t i = 0; i <  count; i++)
                            sb_cp.withEffect([]{
                                switch (rand()%8) {
                                    case 0: return Effect { .variant = Effect::Heal, .hp = rand()%20 + 5};
                                    case 1: return Effect { .variant = Effect::Death };
                                    case 2: return Effect { .variant = Effect::Arise, .hp = rand()%20 + 20};
                                    case 3: return Effect { .variant = Effect::Damage, .hp = rand()%20 + 5};
                                    case 4: return Effect { .variant = Effect::Poison, .hp = rand()%5 + 1};
                                    case 5: return Effect { .variant = Effect::LifeLink,
                                        .life_link { .mage_id = 0, .percent = static_cast<uint8_t>(rand()%5 + 2)}};
                                    case 6: return Effect { .variant = Effect::SkipTurn };
                                    case 7:
                                    default: return Effect { .variant = Effect::ManaRestore, .mp = rand()%5 + 1};
                                }
                            }());

                        builder.appendSpell(sb_cp.alloc());
                    }
                }

                game.callCommand(new AddMage(builder));

            } else if (view_eq(name, "print" ) || view_eq(name, "p" )) {
                auto query_func = [&] -> QueryCommand::Pred {
                    const auto err = [](MageId, Mage*, QueryCommand::Place) { return false; };

                    if (command.size() < 2) {
                        return [](auto, auto, auto){return true;};
                    }
                    auto target_name = command[1];

                    if (view_eq(target_name, "Mage")) {
                        if (command.size() < 3) {
                            std::cout << "\nmust specify mage id to print mage... see help.\n" << HELP_MSG << std::endl;
                            return err;
                        }

                        MageId id;
                        if (std::from_chars(command[2].begin(), command[2].end(), id).ec != std::errc()) {
                            std::cout << "\nwrong Mage id: " << id << std::endl;
                            return err;
                        }
                        return [id](auto curr_id, auto, auto) { return id == curr_id; };
                    }
                    if (view_eq(target_name, "All"))
                        return [](auto, auto, auto) { return true; };

                    if (view_eq(target_name, "BattleGround") || view_eq(target_name, "BG"))
                        return [](auto, auto, auto place) { return place == QueryCommand::BG; };

                    if (view_eq(target_name, "Graveyard") || view_eq(target_name, "GY"))
                        return [](auto, auto, auto place) { return place == QueryCommand::GY; };

                    if (view_eq(target_name, "Exile") || view_eq(target_name, "Exile"))
                        return [](auto, auto, auto place) { return place == QueryCommand::EL; };

                    return err;
                }();

                QueryCommand::MagesQuery query;
                auto iter = std::back_inserter(query);
                game.callCommand(new QueryCommand(iter, query_func));

                if (query.size() == 0) {
                    std::cout << "Nothing matches query." << std::endl;
                } else {
                    for (auto [id, mage] : query)
                        if (mage != nullptr) std::cout << "   :: " << id << " " << *mage << std::endl;
                }

            } else {
                std::cout << "Wrong command: " << std::quoted(name) << std::endl;
                std::cout << HELP_MSG << std::endl;
            }
        }
    }
}
