#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <functional>
#include <iostream>
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

            size_t get_bullets_count(void) { return _bullets_count; }
            size_t get_mag_capacity(void) { return _mag_capacity; }

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
                size_t mag_cap =  guns[*curr_gun]->get_mag_capacity();
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
