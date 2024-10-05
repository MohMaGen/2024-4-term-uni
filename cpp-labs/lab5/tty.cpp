#include "lab5_game.hpp"
#include <charconv>
#include <iomanip>
#include <lab5_tty.hpp>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string_view>
#include <vector>


namespace lab5 {
    namespace tty {
        const char HELP_MSG[] =
            "lab5 magic:\n\n"
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
            "\x1b[1;34mBATTLE COMMANDS:\x1b[0m\n"
            "     - show                --- show current game state.\n"
            "     - choose_spell <id>   --- chose spell with <id>.\n"
            "     - targets             --- highlight targets of choosen spell.\n"
            "     - cast <id>           --- cast speel to the target with <id>.\n"
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

        bool view_eq(std::string_view view, const char *value) {
            return std::equal(view.begin(), view.end(), std::string_view { value } .begin());
        }

        std::vector<std::string_view> parseCommand(const char *buffer)  {
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

        void executeTTYCommands(std::vector<std::string_view> command_args, game::Game &game) {
            std::array<Command*, 13> commands {
                new DisplayHelpCommand(game, command_args),
                new DisplayPrintCommand(game, command_args),
                new DisplayStateCommand(game, command_args),
                new DisplayBattleFieldCommand(game, command_args),
                new NextTeamCommand(game, command_args),
                new CurrTeamCommand(game, command_args),
                new GenTeamCommand(game, command_args),
                new MakeMageCommand(game, command_args),
                new ClearCommand(game, command_args),
                new StartGuiCommand(game, command_args),
                new NewGameCommand(game, command_args),
                new SetSizeCommand(game, command_args),
                new ExitCommand(game, command_args),
            };
            if (command_args.size() == 0) {
                std::cout << std::endl;
                return;
            }
            auto name = command_args[0];
            command_args.erase(command_args.begin());

            auto res = std::find_if(commands.begin(), commands.end(),
                    [&name](auto const &cmd) { return cmd->validateName(name); });

            if (res == commands.end()) {
                std::cout << "wront command name: " << std::quoted( name ) << std::endl;
                return;
            }

            try { (*res)->call(); }
            catch ( CommandException &e ) {
                std::cout << "Failed with: " << e.what() << std::endl;
            }
        }
        constexpr bool DisplayHelpCommand::validateName(std::string_view name) const {
            return view_eq(name, "help") || view_eq(name, "h");
        }
        constexpr bool DisplayPrintCommand::validateName(std::string_view name) const {
            return view_eq(name, "print") || view_eq(name, "p");
        }
        constexpr bool DisplayStateCommand::validateName(std::string_view name) const {
            return view_eq(name, "state");
        }
        constexpr bool DisplayBattleFieldCommand::validateName(std::string_view name) const {
            return view_eq(name, "battle_field");
        }
        constexpr bool NextTeamCommand::validateName(std::string_view name) const {
            return view_eq(name, "next_team");
        }
        constexpr bool CurrTeamCommand::validateName(std::string_view name) const {
            return view_eq(name, "curr_team");
        }
        constexpr bool GenTeamCommand::validateName(std::string_view name) const {
            return view_eq(name, "gen_mages");
        }
        constexpr bool MakeMageCommand::validateName(std::string_view name) const {
            return view_eq(name, "make_mage");
        }
        constexpr bool ClearCommand::validateName(std::string_view name) const {
            return view_eq(name, "clear") || view_eq(name, "\x0C");
        }
        constexpr bool StartGuiCommand::validateName(std::string_view name) const {
            return view_eq(name, "gui");
        }
        constexpr bool NewGameCommand::validateName(std::string_view name) const {
            return view_eq(name, "new_game");
        }
        constexpr bool SetSizeCommand::validateName(std::string_view name) const {
            return view_eq(name, "set_size");
        }
        constexpr bool ExitCommand::validateName(std::string_view name) const {
            return view_eq(name, "exit") || view_eq(name, "e");
        }
        constexpr bool ShowCommand::validateName(std::string_view name) const {
            return view_eq(name, "show");
        }

        constexpr bool ChooseSpellCommand::validateName(std::string_view name) const {
            return view_eq(name, "choose_spell");
        }

        constexpr bool DisplayTargetsCommand::validateName(std::string_view name) const {
            return view_eq(name, "targets");
        }

        constexpr bool CastSpelLCommand::validateName(std::string_view name) const {
            return view_eq(name, "cast");
        }


        void DisplayHelpCommand::call(void) const {
            std::cout << HELP_MSG << std::endl;
        }
        void DisplayPrintCommand::call(void) const {
            auto query_func = [&] -> game::QueryCommand::Pred {
                const auto err = [](math::MageId, back::Mage*, game::QueryCommand::Place) { return false; };

                if (_args.size() < 1) {
                    return [](auto, auto, auto){return true;};
                }
                auto target_name = _args[0];

                if (view_eq(target_name, "Mage")) {
                    if (_args.size() < 2) {
                        std::cout << "\nmust specify mage id to print mage... see help.\n" << HELP_MSG << std::endl;
                        return err;
                    }

                    math::MageId id;
                    if (std::from_chars(_args[1].begin(), _args[1].end(), id).ec != std::errc()) {
                        std::cout << "\nwrong Mage id: " << id << std::endl;
                        return err;
                    }
                    return [id](auto curr_id, auto, auto) { return id == curr_id; };
                }
                if (view_eq(target_name, "All"))
                    return [](auto, auto, auto) { return true; };

                if (view_eq(target_name, "BattleGround") || view_eq(target_name, "BG"))
                    return [](auto, auto, auto place) { return place == game::QueryCommand::BG; };

                if (view_eq(target_name, "Graveyard") || view_eq(target_name, "GY"))
                    return [](auto, auto, auto place) { return place == game::QueryCommand::GY; };

                if (view_eq(target_name, "Exile") || view_eq(target_name, "Exile"))
                    return [](auto, auto, auto place) { return place == game::QueryCommand::EL; };

                return err;
            }();

            game::QueryCommand::MagesQuery query;
            auto iter = std::back_inserter(query);
            _game.callCommand(new game::QueryCommand(iter, query_func));

            if (query.size() == 0) {
                std::cout << "Nothing matches query." << std::endl;
            } else {
                for (auto [id, mage] : query)
                    if (mage != nullptr) std::cout << "   :: " << id << " " << *mage << std::endl;
            }

        }
        void DisplayStateCommand::call(void) const {
            std::cout << _game.getState() << std::endl;
        }
        void DisplayBattleFieldCommand::call(void) const {
            game::GetBattleFieldCommand::BattleField bf;
            math::Size size { 0, 0 };

            _game.callCommand(new game::GetBattleFieldCommand(std::back_inserter(bf), size));

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
            const auto bg_color = [](int r, int g, int b){ std::cout << "\x1b[48;2;" << r << ";" << g << ";" << b  << "m"; };
            std::cout << "Battle field " << size << std::endl;
            nl();
            for (size_t y = 0; y < size.height; y++) {
                for (size_t x = 0; x < size.width; x++) {
                    if ((y + x) % 2) {
                        clear();
                        bg_color(85, 139, 47);
                    } else {
                        clear();
                        bg_color(46, 125, 50);
                    }
                    const auto chck = [y, x](auto pair) {
                        if (pair.second == nullptr) return false;
                        return pair.second->getPos() == math::Position { x, y };
                    };
                    auto res = std::find_if(bf.begin(), bf.end(), chck);

                    if (res == bf.end()) {
                        std::cout << std::string(cell_size, ' ');
                        continue;
                    }
                    if (res->second->getTeam() == back::Team::Blue) {
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

        }
        void NextTeamCommand::call(void) const {
            _game.callCommand(new game::NextTeamCommand());
        }
        void CurrTeamCommand::call(void) const {
            using GameState = game::Game::GameState;
            switch (_game.getState()) {
                case GameState::BlueTeamInit: std::cout << "Blue Team" << std::endl; break;
                case GameState::OrangeTeamInit: std::cout << "Orange Team" << std::endl; break;
                default:
                                                std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
            }
        }
        void GenTeamCommand::call(void) const {
            back::Team curr_team_init;

            using GameState = game::Game::GameState;
            switch (_game.getState()) {
                case GameState::BlueTeamInit: curr_team_init = back::Team::Blue; break;
                case GameState::OrangeTeamInit: curr_team_init = back::Team::Orange; break;
                default:
                    std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                    return;
            }

            int n;
            if (_args.size() < 1 || std::from_chars(_args[0].begin(), _args[0].end(), n).ec != std::errc{}) {
                std::cout << "Failed to parse int <n>" << std::endl;
                return;
            }
            try {
                for (size_t i = 0; i < n; i++) {
                    _game.callCommand(new game::GenMageCommand(curr_team_init));
                }
            } catch ( game::Game::CommandError &e ) {
                std::cout << "Failed to create Team: " << e.what() << std::endl;
            }
        }
        void MakeMageCommand::call(void) const {
            back::Team curr_team_init;

            using GameState = game::Game::GameState;
            switch (_game.getState()) {
                case GameState::BlueTeamInit: curr_team_init = back::Team::Blue; break;
                case GameState::OrangeTeamInit: curr_team_init = back::Team::Orange; break;
                default:
                                                std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                                                return;
            }

            back::Mage::MageBuilder builder (curr_team_init);
            std::cout << "\x1b[1;34menter pos: `x y`\x1b[0m> ";
            math::Position pos { 0, 0 };
            std::cin >> pos.x >> pos.y;
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

                back::Spell::SpellBuilder* sb;
                if (spell_type == "Long" || spell_type == "LongDist")
                    sb = back::LongRangeSpell::build();
                else if (spell_type == "Short" || spell_type == "ShortDist")
                    sb = back::ShortRangeSpell::build();
                else if (spell_type == "Support")
                    sb = back::SupportSpell::build();
                else if (spell_type == "Curse")
                    sb = back::CurseSpell::build();
                else {
                    std::cout << "Wrong Spell Type. Choose one of LongDist, ShortDist, Support, Curse." << std::endl;
                    i--;
                    continue;
                }
                size_t count = rand() % 5 + 1;
                for (size_t i = 0; i < count; i++) {
                    back::Spell::SpellBuilder sb_cp (sb->alloc());
                    sb_cp.withManaCost(rand()%100 + 1)
                        ->withCost(rand()%10 + 1)
                        ->withApplyDuration(rand()%3600 + 1)
                        ->withEffectDuration(rand()%10 + 1)
                        ->withDistance(rand()%100 + 1)
                        ->withTargetArea([]{ return (rand()%2) ? math::TargetArea(rand()%10+1) : math::TargetArea(); }());

                    size_t count = rand()%10 + 1;
                    for (size_t i = 0; i <  count; i++)
                        sb_cp.withEffect([]{
                                switch (rand()%8) {
                                case 0: return back::Effect { .variant = back::Effect::Heal, .hp = rand()%20 + 5};
                                case 1: return back::Effect { .variant = back::Effect::Death };
                                case 2: return back::Effect { .variant = back::Effect::Arise, .hp = rand()%20 + 20};
                                case 3: return back::Effect { .variant = back::Effect::Damage, .hp = rand()%20 + 5};
                                case 4: return back::Effect { .variant = back::Effect::Poison, .hp = rand()%5 + 1};
                                case 5: return back::Effect { .variant = back::Effect::LifeLink,
                                .life_link { .mage_id = 0, .percent = static_cast<uint8_t>(rand()%5 + 2)}};
                                case 6: return back::Effect { .variant = back::Effect::SkipTurn };
                                case 7:
                                default: return back::Effect { .variant = back::Effect::ManaRestore, .mp = rand()%5 + 1};
                                }
                                }());

                    builder.appendSpell(sb_cp.alloc());
                }
            }

            try {
                _game.callCommand(new game::AddMageCommand(builder));
            } catch ( game::Game::CommandError &e ) {
                std::cout << "failed to create mage. " << e.what() << std::endl;
            }
        }
        void ClearCommand::call(void) const {
            std::cout << "\x1b[1;1H\x1b[2J";
        }
        void StartGuiCommand::call(void) const {
        }
        void NewGameCommand::call(void) const {
            _game.callCommand(new game::NewGameCommand());
        }
        void SetSizeCommand::call(void) const {
            math::Size size { 0, 0 };
            if (_args.size() < 1 ||
                    std::from_chars(_args[0].begin(), _args[0].end(), size.width.v).ec != std::errc{}) {
                std::cout << "Failed to parse <width>.\n" << HELP_MSG << std::endl;
                return;
            }
            if (_args.size() < 2 ||
                    std::from_chars(_args[1].begin(), _args[1].end(), size.height.v).ec != std::errc{}) {
                std::cout << "Failed to parse <height>.\n" << HELP_MSG << std::endl;
                return;
            }
            if (!std::cin) {
                std::cout << "Invalid size input.\n" << HELP_MSG << std::endl;
                return;
            }
            std::cout << size << std::endl;
            _game.callCommand(new game::SetGameSizeCommand(size));
        }
        void ExitCommand::call(void) const {
            _game.callCommand(new game::ExitCommand());
        }

        void ShowCommand::call(void) const {

        }

        void ChooseSpellCommand::call(void) const {
        }

        void DisplayTargetsCommand::call(void) const {
        }

        void CastSpelLCommand::call(void) const {
        }

        const char * CommandException::what(void) const noexcept {
            char *buf = new char[_msg.size() + _name.size() + 4];
            std::strcat(buf, _name.c_str());
            std::strcat(buf, ": ");
            std::strcat(buf, _msg.c_str());
            return buf;
        }
    }
}
