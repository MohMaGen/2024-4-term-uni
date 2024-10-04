#include <charconv>
#include <iomanip>
#include <lab5_tty.hpp>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>


namespace lab5 {
    namespace tty {
        const char HELP_MSG[] = " lab5 magic:\n\n"
            "\x1b[1;34mUSAGE:\x1b[0m\n"
            " [command] ([command_args])\n"
            "\n"
            "\x1b[1;34mDISPLAY COMMANDS:\x1b[0m \n"
            "    - help, h              --- prints help msg.\n"
            "    - print, b [<target>]  --- prints value of the target.\n"
            "                    Targets  can   be:  Mage [id], BattleGround,\n"
            "                    Graveyard, Exile, All.\n"
            "    - state                --- prints current game state\n"
            "    - battle_field         --- prints battle field with mag,            "    - next_team            --- finish creation of current team\n"
            "                    and enter to next.\n"
            "    - curr_team            --- print current team.\n"
            "    - gen_mages <n>        --- generate <n> mages for current team\n"
            "    - make_mage            --- run mage build,            "    - clear                --- clear\n"
            "    - gui                  --- turn into gui m,            "    - new_game             --- start game\n"
            "    - set_size <width> <height>\n"
            "                           --- set size of the battle field.\n "
            "                    This will exile all mages outside of the\n"
            "                    new battle fie,b5,
        bool view_eq(std::string_view view, const char *value) ,       std::vector<std::string_view> parseCommand(const char,            const auto push = [&vec, &buffer, &curr,,              if ,        }

        void executeTTYCommands(std::vector<std::string_view> command, game::Game &game) {
			static const std::vector<Command*> commands {
        			new DisplayHelpCommand(),
                    new DisplayPrintCommand(),
                    new DisplayStateCommand(),
                    new DisplayBattleFieldCommand(),
                    new NextTeamCommand(),
                    new CurrTeamCommand(),
                    new GenMagesCommand(),
                    new MakeMageCommand(),
                    new ClearCommand(),
                    new StartGuiCommand(),
                    new NewGameCommand(),
                    new SetSizeCommand(),
                    new ExitCommand(),
			};

            if (command.size() == 0) {
                std::cout << std::endl;
                return;
            }
            auto name = command[0];
			command.erase(0);

			std::find_if(commands.begin(), commands.end(), [&name](auto cmd) { return cmd.validateName(name); });

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
        constexpr bool GenMagesCommand::validateName(std::string_view name) const {
            return view_eq(name, "gen_mages");
        }
        constexpr bool MakeMageCommand::validateName(std::string_view name) const {
            return view_eq(name, "make_mage");
        }
        constexpr bool ClearCommand::validateName(std::string_view name) const {
            return view_eq(name, "make_mage");
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


        void DisplayHelpCommand::call(game::Game& game, std::vector<std::string_view> args) {
            std::cout << HELP_MSG << std::endl;
        }
        void DisplayPrintCommand::call(game::Game& game, std::vector<std::string_view> args) {
       		auto query_func = [&] -> game::QueryCommand::Pred {
                const auto err = [](math::MageId, back::Mage*, game::QueryCommand::Place) { return false; };

                if (args.size() < 1) {
                    return [](auto, auto, auto){return true;};
                }
                auto target_name = args[0];

                if (view_eq(target_name, "Mage")) {
                    if (args.size() < 2) {
                        std::cout << "\nmust specify mage id to print mage... see help.\n" << HELP_MSG << std::endl;
                        return err;
                    }

                    math::MageId id;
                    if (std::from_chars(args[1].begin(), args[1].end(), id).ec != std::errc()) {
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
            game.callCommand(new game::QueryCommand(iter, query_func));

            if (query.size() == 0) {
                std::cout << "Nothing matches query." << std::endl;
            } else {
                for (auto [id, mage] : query)
                    if (mage != nullptr) std::cout << "   :: " << id << " " << *mage << std::endl;
            }

        }
        void DisplayStateCommand::call(game::Game& game, std::vector<std::string_view> args) {
            std::cout << game.getState() << std::endl;
        }
        void DisplayBattleFieldCommand::call(game::Game& game, std::vector<std::string_view> args) {
            game::GetBattleFieldCommand::BattleField bf;
            math::Size size { 0, 0 };

            game.callCommand(new game::GetBattleFieldCommand(std::back_inserter(bf), size));

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
            std::cout << "Battle field " << size << std::endl;
            nl();
            for (size_t y = 0; y < size.height; y++) {
                for (size_t x = 0; x < size.width; x++) {
                    if ((y + x) % 2) {
                        bg_color(7);
                    } else {
                        clear();
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
        void NextTeamCommand::call(game::Game& game, std::vector<std::string_view> args) {
            game.callCommand(new game::NextTeamCommand());
        }
        void CurrTeamCommand::call(game::Game& game, std::vector<std::string_view> args) {
            using GameState = game::Game::GameState;
            switch (game.getState()) {
                case GameState::BlueTeamInit: std::cout << "Blue Team" << std::endl; break;
                case GameState::OrangeTeamInit: std::cout << "Orange Team" << std::endl; break;
                default:
                    std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
            }
        }
        void GenMagesCommand::call(game::Game& game, std::vector<std::string_view> args) {
        }
        void MakeMageCommand::call(game::Game& game, std::vector<std::string_view> args) {
            back::Team curr_team_init;

            using GameState = game::Game::GameState;
            switch (game.getState()) {
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

            game.callCommand(new game::AddMage(builder));
        }
        void ClearCommand::call(game::Game& game, std::vector<std::string_view> args) {
        	std::cout << "\x1b[1;1H\x1b[2J";
        }
        void StartGuiCommand::call(game::Game& game, std::vector<std::string_view> args) {
        }
        void NewGameCommand::call(game::Game& game, std::vector<std::string_view> args) {
        	game.callCommand(new game::NewGameCommand());
        }
        void SetSizeCommand::call(game::Game& game, std::vector<std::string_view> args) {
            math::Size size { 0, 0 };
            if (args.size() < 1 ||
                    std::from_chars(args[0].begin(), args[0].end(), size.width.v).ec != std::errc{}) {
                std::cout << "Failed to parse <width>.\n" << HELP_MSG << std::endl;
                return;
            }
            if (args.size() < 2 ||
                    std::from_chars(args[1].begin(), args[1].end(), size.height.v).ec != std::errc{}) {
                std::cout << "Failed to parse <height>.\n" << HELP_MSG << std::endl;
                return;
            }
            if (!std::cin) {
                std::cout << "Invalid size input.\n" << HELP_MSG << std::endl;
                return;
            }
            std::cout << size << std::endl;
            game.callCommand(new game::SetGameSizeCommand(size));
        }
        void ExitCommand::call(game::Game& game, std::vector<std::string_view> args) {
            game..callCommand(new game::ExitCommand());
        }
    }
}
