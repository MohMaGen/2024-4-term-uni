#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>
#include <stdexcept>
#include <vector>
#include <string>

namespace lab6 {

    double sigmoid(double x, double start, double intensity) {
        double arg = -intensity * (x - start - 2 * std::exp(1) / intensity);
        return std::exp(arg) / (1 + std::exp(arg));
    }

    class Gun {
        public:
            Gun(const std::string &name, size_t mag_capacity, double sighting_range, double accuracy_lossing_rate): _name(name),
                _mag_capacity(mag_capacity), _bullets_count(0), _sighting_range(sighting_range), _accuracy_lossing_rate(accuracy_lossing_rate) {}
            virtual ~Gun() {}

            using Stats = std::vector<std::pair<std::string, std::string>>;

            virtual double reaload(size_t bullets) noexcept = 0;

            virtual size_t fire(size_t distance) noexcept {
                size_t count = 0;

                for (size_t i = 0; i < _bullets_count; i++) {
                    double chance = sigmoid(distance, _sighting_range, _accuracy_lossing_rate); 
                    count += ((double)(std::rand()%RAND_MAX) / (double)RAND_MAX) <= chance ? 1 : 0;
                }
                _bullets_count = 0;

                return count;
            };
            virtual Stats display(void) const noexcept {
                return {
                    {  "name",                  _name                                  },
                    {  "mag cap",               std::to_string(_mag_capacity)          },
                    {  "bullets count",         std::to_string(_bullets_count)         },
                    {  "sighting range",        std::to_string(_sighting_range)        },
                    {  "accuracy lossing rate", std::to_string(_accuracy_lossing_rate) },
                };
            };

            size_t getBulletsCount(void) { return _bullets_count; }
            size_t getMagCapacity(void)  { return _mag_capacity; }
            std::string getName(void)    { return _name; }

        protected:
            std::string _name;
            size_t _mag_capacity;
            size_t _bullets_count;
            double _sighting_range; // meters
            double _accuracy_lossing_rate;
    };

    class ShotGun: public Gun {
        public:
            ShotGun(const std::string &name, size_t mag_capacity, double sighting_range, double accuracy_lossing_rate, double bullet_load_time):
                Gun(name, mag_capacity, sighting_range, accuracy_lossing_rate), _bullet_load_time(bullet_load_time) {} 

            virtual double reaload(size_t bullets) noexcept override {
                if (_bullets_count + bullets > _mag_capacity) {
                    _bullets_count = _mag_capacity;
                    return 0.f;
                }
                _bullets_count += bullets;
                return (double)_bullets_count * _bullet_load_time;
            }

            virtual Stats display(void) const noexcept override {
                auto stats = Gun::display();
                stats.push_back({"bullet load time", std::to_string(_bullet_load_time)});
                return stats;
            };

        private:
            double _bullet_load_time;
    };

    class Pistol: public Gun {
        public:
            Pistol(const std::string &name, size_t mag_capacity, double sighting_range, double accuracy_lossing_rate, double mag_reload_time):
                Gun(name, mag_capacity, sighting_range, accuracy_lossing_rate), _mag_reload_time(mag_reload_time) {} 

            virtual double reaload(size_t bullets) noexcept override {
                _bullets_count = bullets > _mag_capacity ? _mag_capacity : bullets;
                return _mag_reload_time;
            }

            virtual Stats display(void) const noexcept override {
                auto stats = Gun::display();
                stats.push_back({"mag reload time", std::to_string(_mag_reload_time)});
                return stats;
            };
        private:
            double _mag_reload_time;
    };

    class SniperRifle: public Gun {
        public:
            SniperRifle(const std::string &name, size_t mag_capacity, double sighting_range, double accuracy_lossing_rate, double bullet_load_time):
                Gun(name, mag_capacity, sighting_range, accuracy_lossing_rate), _bullet_load_time(bullet_load_time) {}

            virtual double reaload(size_t bullets) noexcept override {
                if (_bullets_count + bullets > _mag_capacity) {
                    _bullets_count = _mag_capacity;
                    return 0.f;
                }
                _bullets_count += bullets;
                return (double)_bullets_count * _bullet_load_time;
            }
            virtual Stats display(void) const noexcept override {
                auto stats = Gun::display();
                stats.push_back({"bullet load time", std::to_string(_bullet_load_time)});
                return stats;
            };
        private:
            double _bullet_load_time;
    };

    class AssaultRifle: public Gun {
        public:
            enum class FireMode: char { OneRound, Burst, Automatic };
            friend std::string to_string(const FireMode&);

            AssaultRifle(const std::string &name, size_t mag_capacity, double sighting_range, double accuracy_lossing_rate,
                         size_t burst_size, double mag_reload_time, double chained_fire_acc_lossing): 
               Gun(name, mag_capacity, sighting_range, accuracy_lossing_rate), _burst_size(burst_size),
               _mag_reload_time(mag_reload_time), _chained_fire_acc_lossing(chained_fire_acc_lossing) {}

            void setFireMode(FireMode mode) noexcept { _fire_mode = mode; }

            virtual double reaload(size_t bullets) noexcept override {
                _bullets_count = bullets > _mag_capacity ? _mag_capacity : bullets;
                return _mag_reload_time;
            }
            virtual size_t fire(size_t distance) noexcept override {
                switch (_fire_mode) {
                case FireMode::OneRound: {
                    return Gun::fire(distance);
                }
                case FireMode::Burst: {
                    size_t count = 0;

                    for (size_t i = 0; i < _bullets_count; i++) {
                        double chance = sigmoid(distance, _sighting_range, _accuracy_lossing_rate) * std::pow(1.0 - _chained_fire_acc_lossing, i % _burst_size); 
                        count += ((double)(std::rand()%RAND_MAX) / (double)RAND_MAX) <= chance ? 1 : 0;
                    }
                    _bullets_count = 0;

                    return count;
                }
                case FireMode::Automatic:
                    size_t count = 0;

                    for (size_t i = 0; i < _bullets_count; i++) {
                        double chance = sigmoid(distance, _sighting_range, _accuracy_lossing_rate) * std::pow(1.0 - _chained_fire_acc_lossing, i); 
                        count += ((double)(std::rand()%RAND_MAX) / (double)RAND_MAX) <= chance ? 1 : 0;
                    }
                    _bullets_count = 0;

                    return count;
                }
            }
            virtual Stats display(void) const noexcept override {
                auto stats = Gun::display();
                stats.push_back({ "fire mode", to_string(_fire_mode) });
                stats.push_back({ "burst size", std::to_string(_burst_size) });
                stats.push_back({ "mag reload time", std::to_string(_mag_reload_time) });    
                stats.push_back({ "chained fire acc lossing", std::to_string(_chained_fire_acc_lossing) });
                return stats;
            };

        private:
            FireMode _fire_mode = FireMode::OneRound;
            size_t _burst_size;
            double  _mag_reload_time;    
            double _chained_fire_acc_lossing;
    };
    std::ostream& operator<<(std::ostream& os, const Gun& gun) {
        auto stats = gun.display();
        os << "Gun:\n";
        for (auto stat : stats) {
            std::cout << "\t- `" << stat.first << "`: `" << stat.second << "`.\n";
        } 
        return os;
    }
    std::string to_string(const AssaultRifle::FireMode& mode) {
        switch (mode) {
        case AssaultRifle::FireMode::OneRound:  return "One Round";
        case AssaultRifle::FireMode::Burst:     return "Burst";
        case AssaultRifle::FireMode::Automatic: return "Automatic";
        }
    }

    class RifleRange {
        std::vector<Gun*> _guns;
        std::set<size_t> _targets;
        public:
            RifleRange(): 
                _guns {
                    new ShotGun { "Mega Valbina 3000", 5,  300, 0.07,  0.85 },
                    new ShotGun { "Mega Valbina 2000", 3,  300, 0.08,  0.95 },
                    new SniperRifle { "Karabiner 98k", 5,  800, 0.02,  0.60 },
                    new SniperRifle { "SVD",           10, 800, 0.009, 0.80 },
                    new Pistol { "Glock 17",           17, 50,  0.1,  1.50 },
                    new Pistol { "Glock 19",           19, 50,  0.15,  1.50 },
                    new AssaultRifle { "AKM",          30, 350, 0.028,  3, 1.4, 0.05},
                    new AssaultRifle { "M16",          30, 550, 0.025, 4, 1.4, 0.05},
                },
                _targets { 50, 150, 300, 400, 500, 800, 1000, 1250, 1500 }
                {}

            void addTarget(size_t distance) {
                _targets.insert(distance);
            }

            void addGun(Gun *gun) {
                _guns.push_back(gun);
            }

            const std::vector<Gun*>& getGuns(void) const {
                return _guns;
            }
            const std::set<size_t>& getTargets(void) const {
                return _targets;
            }
            std::vector<size_t> getTargetsVectored(void) const {
                std::vector<size_t> targets;
                for (auto target: _targets) targets.push_back(target);
                return targets;
            }

    };

    template<typename Type>
    struct Slice {
        Type *ptr;
        size_t len;

        Type operator[](size_t idx) {
            if (idx > len) throw std::out_of_range("Index out of range.");
            return this->ptr[idx];
        }
    };



    struct Command {
        std::string long_name, short_name, description;
        void *data;
        std::function<void (Command* self)> call_func; 

        bool valid(std::string name) const noexcept {
            if (name == long_name || name == short_name) return true;
            return false;
        }
        void call() {
            this->call_func(this);
        }
    };

    void helpCommand(Command* self) {
        Slice<Command> cmds = *(Slice<Command> *)self->data;
        std::cout << "Choose command:\n";
        for (size_t i = 0; i < cmds.len; i++) {
            std::cout << "\t- " << cmds[i].long_name << ", " << cmds[i].short_name << "    ---- " << cmds[i].description << "\n";
        }
        std::cout << std::endl;
    }

    void exitRifleRange(Command *self) {
        *((int*)self->data) = true;
    }

    void clear(Command* self) {
        system("clear");
    }

    void showGuns(Command *self) {
        RifleRange* rifle_range = (RifleRange*)self->data;
        size_t i = 0;
        for (auto gun : rifle_range->getGuns()) {
            std::cout << " :: [ " << i++ << " ] " << *gun << "\n";
        }
        std::cout << std::endl;
    }

    void showTargets(Command *self) {
        RifleRange* rifle_range = (RifleRange*)self->data;
        size_t i = 0;
        for (auto target : rifle_range->getTargets()) {
            std::cout << " :: [ " << i++ << " ] " << target << "\n";
        }
        std::cout << std::endl;
    }

    void addTarget(Command *self) {
        RifleRange* rifle_range = (RifleRange*)self->data;
        std::cout << "Enter targets distance: ";
        size_t distance;
        std::cin >> distance;
        rifle_range->addTarget(distance);
    }

    enum class GunType: char { Pistol, Shotgun, SniperRifle, AssaultRifle }; 
    std::istream& operator>>(std::istream& is, GunType& type) {
        std::string buffer;
        is >> buffer;
        if      (buffer == "Pistol" || buffer == "p")        type = GunType::Pistol;
        else if (buffer == "ShotGun" || buffer == "s")       type = GunType::Shotgun;
        else if (buffer == "SniperRifle" || buffer == "sr")  type = GunType::SniperRifle;
        else if (buffer == "AssaultRifle" || buffer == "ar") type = GunType::AssaultRifle;
        else  is.setstate( std::ios_base::failbit ); 

        return is;
    }
    void addGun(Command *self) {
        RifleRange* rifle_range = (RifleRange*)self->data;

        while (true) {
            std::cout << "Enter gun type (one of Pistol|p, Shotgun|s, SniperRifle|sr, AssaultRifle|ar): ";
            GunType type;
            std::cin >> type;
            if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

            std::cout << "Enter gun name: ";
            char name[256] { '\0' };
            std::cin.getline(name, 256, '\n');
            std::cin.getline(name, 256, '\n');
            if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

            std::cout << "Enter mag capacity: ";
            size_t mag_capacity;
            std::cin >> mag_capacity;
            if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

            std::cout << "Enter sighting range: ";
            double sighting_range;
            std::cin >> sighting_range;
            if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

            std::cout << "Enter accuracy lossing rate: ";
            double accuracy_lossig_rate;
            std::cin >> accuracy_lossig_rate;
            if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }


            Gun *gun = nullptr;
            switch (type) {
            case GunType::Pistol: {
                std::cout << "Enter mag reload time: ";
                double mag_reload_time;
                std::cin >> mag_reload_time;
                if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

                gun = new Pistol(name, mag_capacity, sighting_range, accuracy_lossig_rate, mag_reload_time);
            } break;
            case GunType::Shotgun: {
                std::cout << "Enter bullet load time: ";
                double bullet_load_time;
                std::cin >> bullet_load_time;
                if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

                gun = new ShotGun(name, mag_capacity, sighting_range, accuracy_lossig_rate, bullet_load_time);
            } break;
            case GunType::SniperRifle: {
                std::cout << "Enter bullet load time: ";
                double bullet_load_time;
                std::cin >> bullet_load_time;
                if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

                gun = new SniperRifle(name, mag_capacity, sighting_range, accuracy_lossig_rate, bullet_load_time);
            } break;
            case GunType::AssaultRifle: {
                std::cout << "Enter burst size. ";
                size_t burst_size;
                std::cin >> burst_size;
                if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

                std::cout << "Enter mag reload time: ";
                double mag_reload_time;
                std::cin >> mag_reload_time;
                if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

                std::cout << "Enter chained file accuracy lossing: ";
                double chained_fire_acc_lossing;
                std::cin >> chained_fire_acc_lossing;
                if (!std::cin) { std::cin.clear(); std::cout << "Invalid input..."; continue; }

                gun = new AssaultRifle(name, mag_capacity, sighting_range, accuracy_lossig_rate,
                                        burst_size, mag_reload_time, chained_fire_acc_lossing);
            } break;
            }

            rifle_range->addGun(gun);
            break;
        }
    }

    void selectGun(Command* self) {
        std::cout << "Enter gun id: ";
        size_t *gun = (size_t*)self->data;
        scanf("%ld", gun); 
        std::cout << "New gun is " << *gun << std::endl;
    }

    void selectTarget(Command* self) {
        std::cout << "Enter target id: ";
        size_t *target = (size_t*)self->data;
        scanf("%ld", target); 
        std::cout << "New target is " << *target << std::endl;
    }

    void fire(Command* self) {
        struct Data { RifleRange*_0; size_t *_1, *_2; };
        auto [rifle_range, curr_gun_id, curr_target_id] = *(Data*)self->data;

        auto guns = rifle_range->getGuns();
        auto targets = rifle_range->getTargets();

        Gun* curr_gun = guns[*curr_gun_id];
        std::cout << "Current gun [ " << *curr_gun_id << " ]: " << *curr_gun << std::endl;

        size_t curr_target, i = 0;
        for (auto target : targets) {
            if (i++ == *curr_target_id) {
                curr_target = target;
                break;
            }
        }
        std::cout << "Current target [ " << *curr_target_id << " ] distance is `" << curr_target << "`m."<< std::endl;
        size_t hit_count = curr_gun->fire(curr_target); 
        std::cout << hit_count << " bullets hit the target." << std::endl;
    }

    void simulate(Command* self) {
        struct Data { RifleRange*_0; size_t *_1; };
        auto [rifle_range, curr_gun] = *(Data*)self->data;

        auto guns = rifle_range->getGuns();
        std::cout << "Current gun [ " << *curr_gun << " ]: " << guns[*curr_gun] << std::endl;
        for (auto target : rifle_range->getTargets()) {
            std::cout << "Current target " << target << "m away." << std::endl;
            guns[*curr_gun]->fire(target); // fire out all bullets. 

            size_t bullet_count = 100;
            size_t hits_count = 0;
            double time = 0.0;
            while (bullet_count > 0) {
                size_t mag_cap =  guns[*curr_gun]->getMagCapacity();
                size_t mag = mag_cap > bullet_count ? bullet_count : mag_cap;
                bullet_count -= mag;
                std::cout << " :: Reload gun with " << mag << " bullets." << std::endl;
                time += guns[*curr_gun]->reaload(mag); 
                hits_count += guns[*curr_gun]->fire(target); 
            }
            std::cout << " :: Takes " << time << "sec to finish." << std::endl;
            std::cout << " :: " << hits_count << " hits to the target." << std::endl;
        }
    }

    void reload(Command* self) {
        struct Data { RifleRange*_0; size_t *_1; };
        auto [rifle_range, curr_gun_id] = *(Data*)self->data;

        auto guns = rifle_range->getGuns();
        auto curr_gun =  guns[*curr_gun_id];
        std::cout << "Current gun [ " << *curr_gun_id << " ]: " << *curr_gun << std::endl;

        while (true) {
            std::cout << "Enter number of bullets to reload: ";

            size_t bullets_count;
            std::cin >> bullets_count;
            if (!std::cin) { std::cout << "Ivalid input..."; continue; }

            double time_to_reload = curr_gun->reaload(bullets_count); 
            std::cout << "Reloading takes `" << time_to_reload  << "sec`." << std::endl;
            break;
        }
    }


    void runLab6(void) {
        RifleRange rifle_range { };

        std::cout << "Welcome to the rifle range!" << std::endl;
        Command commands[] = {
            /*           LONG NAME   SHORT NAME           DESCRIPTION             DATA      CALL FUNC   */
            Command { "help",          "h",     "print this message.",          nullptr, &helpCommand    },
            Command { "clear",         "c",     "clear console.",               nullptr, &clear          },
            Command { "exit",          "e",     "exit rifle range simulation.", nullptr, &exitRifleRange },
            Command { "guns",          "g",     "show available guns.",         nullptr, &showGuns       }, 
            Command { "targets",       "t",     "show available targets.",      nullptr, &showTargets    }, 
            Command { "add_target",    "at",    "add target.",                  nullptr, &addTarget      },
            Command { "add_gun",       "ag",    "add gun.",                     nullptr, &addGun         },
            Command { "select_gun",    "sg",    "select gun to shoot with.",    nullptr, &selectGun      },
            Command { "select_target", "st",    "select target to shoot at.",   nullptr, &selectTarget   },
            Command { "fire",          "f",     "shot from the gun.",           nullptr, &fire           },
            Command { "simulate",      "s",     "simulate 100 shots.",          nullptr, &simulate       },
            Command { "reload",        "r",     "reload current gun.",          nullptr, &reload         },
        };
        constexpr size_t commands_size = sizeof(commands) / sizeof(Command);
        Slice<Command> cmds { commands, commands_size };
        commands[0].data = &cmds;

        bool should_exit = false;
        commands[2].data = &should_exit;

        commands[3].data = &rifle_range;
        commands[4].data = &rifle_range;
        commands[5].data = &rifle_range;
        commands[6].data = &rifle_range;

        size_t curr_gun = 0;
        size_t curr_target = 0;
        commands[7].data = &curr_gun;
        commands[8].data = &curr_target;

        struct { RifleRange* rr; size_t *curr_gun, *curr_target; } fire_data { &rifle_range, &curr_gun, &curr_target };
        commands[9].data = &fire_data;

        struct { RifleRange* rr; size_t *curr_gun; } simulate_data { &rifle_range, &curr_gun };
        commands[10].data = &simulate_data;
        commands[11].data = &simulate_data;

        commands[0].call();
        char command[256] = { '\0' };
        while (!should_exit) {
            std::cout << "lab6> ";
            std::cin >> command;
            auto cmd = std::find_if(commands, commands + commands_size, [command](auto cmd) { return cmd.valid(command); });

            if (cmd >= commands + commands_size) {
                std::cout << "No matching command..." << std::endl;
                continue;
            }

            cmd->call();
        }
    }
}
namespace raylib {
    #include <raylib.h>
}

namespace gui {
    using Px = long;
	struct Rect {
        Px x, y, w, h;

        Rect center(Px w_x, Px w_y, Px w_w, Px w_h) {
            return Rect { w_x + (w_w - w) / 2, w_y + (w_h - h) / 2, w, h };
        }
        Rect center(Rect rect) {
            return center(rect.x, rect.y, rect.w, rect.h);
        }
        Rect down(Px dy) {
            return Rect { x, y + dy, w, h };
        }
        Rect right(Px dx) {
            return Rect { x + dx, y, w, h };
        }
        bool inside(Px vx, Px vy) {
            return  vx >= x && vx <= x + w && vy >= y && vy <= y + h;
        }
        bool inside(raylib::Vector2 v) {
            return inside(v.x, v.y);
        }

        int justifyX(Px len, Px min_mar, Px *out_count, Px *out_mar) {
            Px _w = w - len;
            if (_w <= 0) {
                *out_count = 0;
                *out_mar = 0;
                return 1;
            }

            *out_count = _w / (min_mar + len) + 1;
            *out_mar = *out_count == 1 ? 0 : _w % (min_mar + len) / (*out_count-1) + min_mar;
            return 0;
        } 
        int justifyY(Px len, Px min_mar, Px *out_count, Px *out_mar) {
            Px _h = h - len;
            if (_h <= 0) {
                *out_count = 0;
                *out_mar = 0;
                return 1;
            }

            *out_count = _h / (min_mar + len) + 1;
            *out_mar = *out_count == 1 ? 0 : _h % (min_mar + len) / (*out_count-1) + min_mar;
            return 0; 
        }
	};

	template<typename Type>
	Type bound(Type value, Type lower, Type upper) {
    	return value > upper ? upper : value < lower ? lower : value;
	}

    enum class GameState: char {
        MainMenu,
        Game,
        Exit,
    };
    class IUiElem {
        public:
            virtual ~IUiElem() {}
            virtual void draw() = 0;
            virtual bool isDown() = 0; 
            virtual bool isPressed() = 0;
            virtual bool isHover() = 0; 
            virtual Rect updateElem(Rect context, double deltaTime) = 0;
            virtual Rect updateElem(Rect context) = 0;
    };

    class RectUi: public IUiElem {
        public:
            Rect rect { };
            raylib::Color bg_color { 0x88, 0x88, 0x88, 0xFF };

            RectUi() {}
            RectUi(Rect rect): rect(rect) { }
            RectUi(Rect rect, raylib::Color bg_color): rect(rect), bg_color(bg_color)  { }

            virtual void draw(void) override {
                raylib::DrawRectangle(rect.x, rect.y, rect.w, rect.h, bg_color); 
            }

            virtual bool isHover(void) override {
                auto mouse = raylib::GetMousePosition();
                return rect.inside(mouse); 
            }

            virtual bool isDown(void) override {
                return isHover() && raylib::IsMouseButtonDown(raylib::MOUSE_BUTTON_LEFT);
            }

            virtual bool isPressed(void) override {
                return isHover() && raylib::IsMouseButtonPressed(raylib::MOUSE_BUTTON_LEFT);
            }
            virtual Rect updateElem(Rect context, double deltaTime) override { rect = rect.center(context); return rect; }
            virtual Rect updateElem(Rect context) override { rect = rect.center(context); return rect; };
    };

    class Button: public IUiElem {
        public:
            virtual ~Button() {}
            Rect rect;
            Px padding;
            std::string text;
            Button(Rect r, Px p, const std::string& text): rect{r}, padding{p}, text{text} { }
            Button() {}

            constexpr static const raylib::Color down_bg   = { 0x55, 0x55, 0x55, 0xFF };
            constexpr static const raylib::Color hover_bg  = { 0x88, 0x88, 0x88, 0xFF };
            constexpr static const raylib::Color normal_bg = { 0xAA, 0xAA, 0xAA, 0xFF };
            constexpr static const raylib::Color normal_fg = { 0x44, 0x44, 0x44, 0xFF };

            virtual void draw(void) override {
                const size_t text_size = rect.h - padding * 2;
                const size_t text_width = raylib::MeasureText(text.c_str(), text_size); 
                const raylib::Color color = isDown() ? down_bg : isHover() ? hover_bg : normal_bg;

                RectUi(rect, color).draw();
                raylib::DrawText(text.c_str(), rect.x + (rect.w - text_width) / 2., rect.y + padding, text_size, normal_fg); 
            }

            virtual bool isHover(void) override {
                return RectUi(rect).isHover();
            }

            virtual bool isDown(void) override {
                return RectUi(rect).isDown();
            }

            virtual bool isPressed(void) override {
                return RectUi(rect).isPressed();
            }
            virtual Rect updateElem(Rect context, double delta_time) override { rect = rect.center(context); return rect; }
            virtual Rect updateElem(Rect context) override { rect = rect.center(context); return rect; };
    };

    struct GameEnv {
        GameState curr_state = GameState::MainMenu;
    };


    template <class UiElem>
    class Hideble: public IUiElem {
        bool _is_hide = false;
        public:
            UiElem elem;
            Hideble<UiElem>(const UiElem &elem): elem(elem) { } 
            Hideble<UiElem>(): elem{} {} 

            void hide()      { _is_hide = true; }
            void reveal()    { _is_hide = false; }
            virtual void draw()      override { if (!_is_hide) elem.draw(); }
            virtual bool isDown()    override { return _is_hide ? false : elem.isDown(); }
            virtual bool isPressed() override { return _is_hide ? false : elem.isPressed(); }
            virtual bool isHover()   override { return _is_hide ? false : elem.isHover(); }

            virtual Rect updateElem(Rect context, double delta_ime) override {
                if (!_is_hide) return elem.updateElem(context, delta_ime); 
                return { };
            }
            virtual Rect updateElem(Rect context) override {
                if (!_is_hide) return elem.updateElem(context);
                return { };
            };
    };
    enum class Direction: char {
        Horisontal, Vertical
    };
    template<typename UiElem>
    class ScrollBlock: public IUiElem {
        Hideble<Button> _scroll_down_button, _scroll_up_button;
        Px _scroll = 0;
        public:
            Rect rect;
            std::vector<Hideble<UiElem>> elems;
            Px margin;
            Direction  direction;

            ScrollBlock<UiElem>(const std::vector<UiElem> &_elems, Rect rect, Px margin, Direction dir): 
                rect(rect), elems{_elems.size()}, margin(margin), direction(dir) {
                for (size_t i = 0; i < _elems.size(); i++) {
                    elems[i] = _elems[i];
                }
            }

            virtual void draw() override {
                for (auto elem : elems) elem.draw();
                _scroll_down_button.draw();
                _scroll_up_button.draw();
            };
            virtual bool isDown() override {
                return RectUi(rect).isDown();
            }; 
            virtual bool isPressed() override {
                return RectUi(rect).isPressed();
            }
            virtual bool isHover() override {
                return RectUi(rect).isHover();
            } 
            virtual Rect updateElem(Rect context, double delta_time) override {
                return updateElem(context);
            }
            virtual Rect updateElem(Rect context) override { 
                rect.center(context);
                if (elems.size() == 0) return rect;
                _scroll_up_button.elem = { {rect.x + (rect.w - 50) / 2, rect.y, 50, 50}, 10, "/\\" }; 
                _scroll_down_button.elem = { {rect.x + (rect.w - 50) / 2, rect.y + rect.h - 50, 50, 50}, 10, "\\/" }; 



                if (_scroll_down_button.isPressed()) _scroll++;
                if (_scroll_up_button.isPressed()) _scroll--;
                if (isHover()) _scroll -= raylib::GetMouseWheelMove();

                Rect inner_rect = rect; 
                if (direction == Direction::Vertical) {
                    inner_rect.y += 60;
                    inner_rect.h -= 120;
                } else {
                    inner_rect.x += 60;
                    inner_rect.w -= 120;
                }

                Px count, mar;
                const Direction dir = direction;
                const Px len = std::accumulate(elems.begin(), elems.end(), Px{0}, [dir](Px acc, auto elem) {
                        elem.reveal();
                        Rect rect = elem.updateElem({ });
                        if (dir == Direction::Vertical) {
                            return rect.h + acc;
                        } else {
                            return rect.w + acc;
                        }
                    }) / Px(elems.size());
                inner_rect.justifyY(len, margin, &count, &mar); 
                _scroll = bound<Px>(_scroll, 0, elems.size() - count);


                if (count == 0) {
                    _scroll_up_button.hide(); 
                    _scroll_down_button.hide();
                } else {
                    _scroll_up_button.reveal(); 
                    _scroll_down_button.reveal();
                }



                Px curret = 0;
                for (size_t i = 0; i < elems.size(); i++) {
                    long column_id = (long)i - _scroll;
                    if (column_id < 0) { 
                        elems[i].hide();
                        continue;
                    }
                    if (column_id >= count) {
                        elems[i].hide();
                        continue;
                    }
                    elems[i].reveal();

                    Rect elem_rect = elems[i].updateElem({ }).center(inner_rect);
                    if (dir == Direction::Vertical) {
                        elem_rect.y = inner_rect.y + curret;
                        curret += mar + elem_rect.h;
                    } else {
                        elem_rect.x = inner_rect.x + curret;
                        curret += mar + elem_rect.w;
                    }
                    elem_rect = count == 1 ? elem_rect.center(elem_rect) : elem_rect;
                    elems[i].updateElem(elem_rect);
                }
                return rect;
            }
    };



    class MainMenu {
        constexpr static const Px BUTTON_WIDTH   = 800;
        constexpr static const Px BUTTON_HEIGHT  = 120;
        constexpr static const Px BUTTON_PADDING = 20;
        constexpr static const Px BUTTON_MARGIN  = 60;

        Button _start_game { { .x=0, .y=0, .w=BUTTON_WIDTH, .h=BUTTON_HEIGHT }, BUTTON_PADDING, "START GAME" };
        Button _exit       { { .x=0, .y=0, .w=BUTTON_WIDTH, .h=BUTTON_HEIGHT }, BUTTON_PADDING, "EXIT" };
        GameEnv &_env;
        public:
            MainMenu(GameEnv &env): _env(env) { }
            void update() {
                Px w_w = raylib::GetScreenWidth();
                Px w_h = raylib::GetScreenHeight();


                _start_game.updateElem(Rect(0, 0, w_w, w_h).down(-BUTTON_MARGIN - _start_game.rect.h / 2));
                _exit.updateElem(Rect(0, 0, w_w, w_h).down(+BUTTON_MARGIN + _start_game.rect.h / 2));

                if (_start_game.isPressed()) _env.curr_state = GameState::Game;
                if (_exit.isPressed()) _env.curr_state = GameState::Exit;

                raylib::BeginDrawing();
                    raylib::ClearBackground({ 0xFF, 0xFF, 0xFF, 0xFF }); 
                    _start_game.draw();
                    _exit.draw();
                raylib::EndDrawing();
            }
    };

    class Game {
        Button _exit_button { { .x=10, .y=10, .w=100, .h=40 }, 5, "EXIT" };
        GameEnv &_env;
        lab6::RifleRange _rifle_range {};


        constexpr static const Px BUTTON_WIDTH       = 250;
        constexpr static const Px BUTTON_HEIGHT      = 80;
        constexpr static const Px BUTTON_PADDING     = 30;
        constexpr static const Px BUTTON_MARGIN      = 20;

        ScrollBlock<Button> _guns_choose;
        ScrollBlock<Button> _targets_choose;


        void _update_buttons() { }

        public:
            Game(GameEnv &env): 
                _env(env),
                _guns_choose({ }, { 20, 200, BUTTON_WIDTH, -1 }, 15, Direction::Vertical), 
                _targets_choose({ }, { 20 + BUTTON_WIDTH + 20, 200, BUTTON_WIDTH, -1 }, 15, Direction::Vertical)
                { }
            ~Game() { }

            void update() {
                Px w_h = raylib::GetScreenHeight();

                auto guns = _rifle_range.getGuns();
                auto targets = _rifle_range.getTargetsVectored();

                std::vector<Hideble<Button>> guns_buttons { guns.size() }, targets_buttons { targets.size() };

                for (size_t i = 0; i < guns.size(); i++) {
                    guns_buttons[i] = Hideble<Button>({ {0, 0, BUTTON_WIDTH, BUTTON_HEIGHT}, 30, guns[i]->getName()});
                }
                for (size_t i = 0; i < targets.size(); i++) {
                    targets_buttons[i] = Hideble<Button>({ {0, 0, BUTTON_WIDTH-100, BUTTON_HEIGHT}, 30, std::to_string(targets[i]) + "m"});
                }

                _guns_choose.elems = guns_buttons;
                _targets_choose.elems = targets_buttons;


                if (_exit_button.isPressed()) _env.curr_state = GameState::MainMenu;
                _update_buttons();

                _guns_choose.rect    = { 20, 200, BUTTON_WIDTH, w_h - 250 };
                _targets_choose.rect = { 20 + BUTTON_WIDTH + 20, 200, BUTTON_WIDTH - 100, w_h - 250 };

                _guns_choose.updateElem(_guns_choose.rect);
                _targets_choose.updateElem(_targets_choose.rect);


                raylib::BeginDrawing();
                    raylib::ClearBackground({ 0xFF, 0xFF, 0xFF, 0xFF }); 
                    _exit_button.draw();
                    _guns_choose.draw();
                    _targets_choose.draw();
                raylib::EndDrawing();
            }
    };

    void runGame(void) {
        raylib::InitWindow(400, 300, "Lab7 game"); 
        raylib::SetWindowState(raylib::FLAG_WINDOW_RESIZABLE); 

        GameEnv env { };
        MainMenu main_menu { env };
        Game game { env };

        while (!raylib::WindowShouldClose() && env.curr_state != GameState::Exit) {
            switch (env.curr_state) {
            case GameState::MainMenu: main_menu.update(); break;
            case GameState::Game: game.update(); break;
            case GameState::Exit: break;
            }
        }
        raylib::CloseWindow();
    }

}
#ifdef LAB6_GUI
int main(void) {
    gui::runGame();
}
#endif
