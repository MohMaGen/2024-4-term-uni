#include "lab4.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>


namespace lab4 {
    class Cat {
        std::string name_m;
        std::uint8_t age_m;
        std::uint8_t starvness_m;
        std::uint8_t tiredness_m;

        public:
            static const std::uint8_t SLEEP_HOURS = 2;

            /*
             * Создаёт кошку с определёнными параметрами.
             *
             * @param name      --- имя.
             * @param age       --- возраст.
             */
            Cat(std::string name, std::uint8_t age) {
                name_m = name;
                age_m = age;
                starvness_m = 100;
                tiredness_m = 0;
            }

            /*
             * Создаёт кошку со случайными параметрами.
             */
            Cat() {
                const char names[][32] = {
                    "Izzy\0", "Marlow\0", "Kona\0", "Stevie\0", "Arya\0",
                    "Aspen\0", "Jade\0", "Fern\0", "Liza\0", "Frida\0",
                    "Tux\0", "Charlie\0", "Dre\0", "Hendrix\0", "Atari\0",
                    "Bowser\0", "Boba\0", "Lincoln\0", "Lux\0", "Niko\0",
                };

                this->name_m = names[rand()%20];
                this->age_m = rand() % 15 + 1;
                this->starvness_m = rand() % 20 + 80;
                this->tiredness_m = rand() % 20;
            }

            void starve(float zoo_intencity) {
                static const int STARVE_PER_HOUR = 10;
                if (this->starvness_m <= zoo_intencity * STARVE_PER_HOUR)
                    this->starvness_m = 0;
                else
                    this->setStarvness(this->starvness_m - zoo_intencity * STARVE_PER_HOUR);
            }

            void tire(float zoo_intencity) {
                static const int TIRE_PER_HOUR = 10;
                this->setTiredness(this->tiredness_m += zoo_intencity * TIRE_PER_HOUR);

            }

            std::string  getName(void) const noexcept      { return this->name_m; }
            std::uint8_t getAge(void) const noexcept       { return this->age_m; }
            std::uint8_t getStarvness(void) const noexcept { return this->starvness_m; }
            std::uint8_t getTiredness(void) const noexcept { return this->tiredness_m; }

            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setName(const std::string &new_name) noexcept     { this->name_m = new_name; }
            void setStarvness(std::uint8_t new_starvness) noexcept { this->starvness_m = (new_starvness > 100) ? 100 : new_starvness; }
            void setTiredness(std::uint8_t new_tiredness) noexcept { this->tiredness_m = (new_tiredness > 100) ? 100 : new_tiredness; }
    };

    class Dog {
        std::string name_m;
        std::uint8_t age_m;
        std::uint8_t starvness_m;
        std::uint8_t tiredness_m;

        public:
            static const std::uint8_t SLEEP_HOURS = 3;

            /*
             * Создаёт собаку с определёнными параметрами.
             *
             * @param name      --- имя.
             * @param age       --- возраст.
             */
            Dog(std::string name, std::uint8_t age) {
                name_m = name;
                age_m = age;
                starvness_m = 100;
                tiredness_m = 10;
            }

            /*
             * Создаёт кошку со случайными параметрами.
             */
            Dog() {
                const char names[][32] = {
                    "Atlas\0", "Barkus\0", "Beef\0", "Bixby\0", "Busy\0", "Cat\0",
                    "Cinder\0", "Gimbal\0", "Hopper\0", "Kaboom\0", "Neo\0",
                    "Nimrod\0", "Qwerty\0", "Renegade\0", "Repo\0", "Ritz\0",
                    "Sativa\0", "Tails\0", "Toaster\0", "Tugs\0",
                };

                this->name_m = names[rand()%20];
                this->age_m = rand() % 15 + 1;
                this->starvness_m = rand() % 10 + 90;
                this->tiredness_m = rand() % 20;
            }

            void starve(float zoo_intencity) {
                static const int STARVE_PER_HOUR = 30;
                if (this->starvness_m <= zoo_intencity * STARVE_PER_HOUR)
                    this->starvness_m = 0;
                else
                    this->setStarvness(this->starvness_m - zoo_intencity * STARVE_PER_HOUR);
            }

            void tire(float zoo_intencity) {
                static const int TIRE_PER_HOUR = 15;
                this->setTiredness(this->tiredness_m += zoo_intencity * TIRE_PER_HOUR);

            }

            std::string  getName(void) const noexcept      { return this->name_m; }
            std::uint8_t getAge(void) const noexcept       { return this->age_m; }
            std::uint8_t getStarvness(void) const noexcept { return this->starvness_m; }
            std::uint8_t getTiredness(void) const noexcept { return this->tiredness_m; }


            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setName(const std::string &new_name) noexcept     { this->name_m = new_name; }
            void setStarvness(std::uint8_t new_starvness) noexcept { this->starvness_m = (new_starvness > 100) ? 100 : new_starvness; }
            void setTiredness(std::uint8_t new_tiredness) noexcept { this->tiredness_m = new_tiredness; }
    };

    class Wombat {
        std::string name_m;
        std::uint8_t age_m;
        std::uint8_t starvness_m;
        std::uint8_t tiredness_m;

        public:
            static const std::uint8_t SLEEP_HOURS = 1;

            /*
             * Создаёт вомбота с определёнными параметрами.
             *
             * @param name      --- имя.
             * @param age       --- возраст.
             */
            Wombat(std::string name, std::uint8_t age) {
                name_m = name;
                age_m = age;
            }

            /*
             * Создаёт кошку со случайными параметрами.
             */
            Wombat() {
                const char names[][32] = {
                    "Burrowman\0", "Hector\0", "Missy\0", "King\0",
                    "Supplanter\0", "Jewel\0", "Mac\0", "Trust\0", "Evidence\0",
                    "Max\0", "Wayne\0", "Zayn\0", "Justice\0", "Rebecca\0",
                    "Liam\0", "Sharon\0", "Perceive\0", "Royal\0",
                };

                this->name_m = names[rand()%18];
                this->age_m = rand() % 15 + 1;
                this->starvness_m = rand() % 10 + 90;
                this->tiredness_m = rand() % 20;
            }

            void starve(float zoo_intencity) {
                static const int STARVE_PER_HOUR = 9;
                if (this->starvness_m <= zoo_intencity * STARVE_PER_HOUR)
                    this->starvness_m = 0;
                else
                    this->setStarvness(this->starvness_m - zoo_intencity * STARVE_PER_HOUR);
            }

            void tire(float zoo_intencity) {
                static const int TIRE_PER_HOUR = 30;
                this->setTiredness(this->tiredness_m += zoo_intencity * TIRE_PER_HOUR);

            }

            std::string  getName(void) const noexcept      { return this->name_m; }
            std::uint8_t getAge(void) const noexcept       { return this->age_m; }
            std::uint8_t getStarvness(void) const noexcept { return this->starvness_m; }
            std::uint8_t getTiredness(void) const noexcept { return this->tiredness_m; }


            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setName(const std::string &new_name) noexcept     { this->name_m = new_name; }
            void setStarvness(std::uint8_t new_starvness) noexcept { this->starvness_m = (new_starvness > 100) ? 100 : new_starvness; }
            void setTiredness(std::uint8_t new_tiredness) noexcept { this->tiredness_m = new_tiredness; }
    };

    /*
     * Обший класс животного.
     *
     */
    class Animal {
        public:

            /*
             * Варианты животных.
             */
            enum class AnimalType { Cat, Dog, Wombat };
            enum class AnimalState { Main, Sleep, Feed };

            /*
             * Общии для всех животных характеристики.
             */
            struct AnimalStats {
                std::string name; std::uint8_t age, starvness, tiredness;
                AnimalState state; std::uint8_t hours_in_state; };


            Animal() = delete;

            /*
             * Создаёт животное -- кошку.
             *
             * @param cat --- значение кошки, которое будет скопированно.
             */
            Animal(Cat *cat):        type_m(AnimalType::Cat),    animal_ptr_m(cat), state_m(AnimalState::Main), hours_in_state_m(0) {}

            /*
             * Создаёт животное -- собаку.
             *
             * @param dog --- значение собаки, которое будет скопированно.
             */
            Animal(Dog *dog):        type_m(AnimalType::Dog),    animal_ptr_m(dog), state_m(AnimalState::Main), hours_in_state_m(0)  {}

            /*
             * Создаёт животное -- вомбыта.
             *
             * @param wombat --- значение вомбыта, которое будет скопированно.
             */
            Animal(Wombat *wombat):  type_m(AnimalType::Wombat), animal_ptr_m(wombat), state_m(AnimalState::Main), hours_in_state_m(0)  {}

            ~Animal() {
                switch (this->type_m) {
                    case AnimalType::Dog:    delete (Dog *)this->animal_ptr_m;    break;
                    case AnimalType::Cat:    delete (Cat *)this->animal_ptr_m;    break;
                    case AnimalType::Wombat: delete (Wombat *)this->animal_ptr_m; break;
                }
            }

            void setState(AnimalState state) noexcept { 
                this->state_m = state;
                this->hours_in_state_m = 0;
            }

            void incHoursInState(void) noexcept {
                this->hours_in_state_m++;
            }

            void feed(void) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->setStarvness(100);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->setStarvness(100);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->setStarvness(100); break;
                }
            }

            void rest(void) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->setTiredness(0);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->setTiredness(0);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->setTiredness(0); break;
                }
            }

            /*
             * Обновляет сытость животного за час.
             *
             * @param zoo_intencity --- загруженность зоопарка в прошедшем часу.
             */
            void starve(float zoo_intencity) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->starve(zoo_intencity);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->starve(zoo_intencity);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->starve(zoo_intencity); break;
                }
            }

            /*
             * Обновляет усталость животного за час.
             *
             * @param zoo_intencity --- загруженность зоопарка в прошедшем часу.
             */
            void tire(float zoo_intencity) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->tire(zoo_intencity);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->tire(zoo_intencity);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->tire(zoo_intencity); break;
                }
            }



            /*
             * Возвращает общие для всех видов животных характеристики.
             */
            AnimalStats getStats(void) const noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:
                        return AnimalStats {
                            ((Dog *)this->animal_ptr_m)->getName(),
                            ((Dog *)this->animal_ptr_m)->getAge(),
                            ((Dog *)this->animal_ptr_m)->getStarvness(),
                            ((Dog *)this->animal_ptr_m)->getTiredness(),
                            this->state_m, this->hours_in_state_m
                        };
                    case AnimalType::Cat:
                        return AnimalStats {
                            ((Cat *)this->animal_ptr_m)->getName(),
                            ((Cat *)this->animal_ptr_m)->getAge(),
                            ((Cat *)this->animal_ptr_m)->getStarvness(),
                            ((Cat *)this->animal_ptr_m)->getTiredness(),
                            this->state_m, this->hours_in_state_m
                        };
                    case AnimalType::Wombat:
                        return AnimalStats {
                            ((Wombat *)this->animal_ptr_m)->getName(),
                            ((Wombat *)this->animal_ptr_m)->getAge(),
                            ((Wombat *)this->animal_ptr_m)->getStarvness(),
                            ((Wombat *)this->animal_ptr_m)->getTiredness(),
                            this->state_m, this->hours_in_state_m
                        };
                }
            }

            std::uint8_t getMaxSleepHours(void) {
                switch (this->type_m) {
                    case AnimalType::Cat:       return Cat::SLEEP_HOURS;
                    case AnimalType::Dog:       return Dog::SLEEP_HOURS;
                    case AnimalType::Wombat:    return Wombat::SLEEP_HOURS;
                }
            }


            /*
             * Переводит животное в строку.
             */
            std::string toString(void) const noexcept{
                std::ostringstream out;

                switch (this->type_m) {
                    case AnimalType::Dog: {
                            out << "\x1b[1;34mDog\x1b[0m ( \x1b[1;32m";
                            out << statsToString();
                            out << " \x1b[0;m)";
                        } break;
                    case AnimalType::Cat: {
                            out << "\x1b[1;34mCat\x1b[0m ( \x1b[1;32m";
                            out << statsToString();
                            out << " \x1b[0;m)";
                        } break;
                    case AnimalType::Wombat:  {
                            out << "\x1b[1;34mWombat\x1b[0m ( \x1b[1;32m";
                            out << statsToString();
                            out << " \x1b[0;m)";
                        } break;
                }

                return out.str();
            }

            AnimalType getType(void) { return this->type_m; }

        private:
            std::string statsToString(void) const {
                AnimalStats stats = this->getStats();
                return std::string()
                    + "\"" + stats.name + "\" "
                    + std::to_string(stats.age) + " "
                    + std::to_string(stats.starvness) + " "
                    + std::to_string(stats.tiredness) + " ";
            }

            AnimalType type_m;

            void *animal_ptr_m;

            AnimalState state_m;
            std::uint8_t hours_in_state_m;

    };


    class ContactZoo {
        public:
            using AnimalPtr = Animal *;
            using Animals = std::vector<Animal*>;
            using AnimalsRef = const Animals &;

            /*
             * Создать контактный зоопарк с указанным количеством случайно
             * сгенерированных животных.
             *
             * @param animals_len --- количество случайно сгенерированных животных.
             */
            ContactZoo(size_t animals_len) : zoo_intencity_m(0.2), curr_hour_m(1) {
                animals = std::vector<Animal*> ();

                for (size_t i = 0; i < animals_len; i++) {
                    using Type = Animal::AnimalType;

                    auto kind = (i < 3) ? Type(i) : Type(rand() % 3);
                    switch (kind) {
                        case Type::Cat:    animals.push_back(new Animal(new Cat()));    break;
                        case Type::Dog:    animals.push_back(new Animal(new Dog()));    break;
                        case Type::Wombat: animals.push_back(new Animal(new Wombat())); break;
                    }
                }
            }

            ~ContactZoo() {
                for (size_t i = 0; i < this->animals.size(); i++) {
                    delete this->animals[i];
                }
            }

            /*
             * Добавляет животное в контактный зоопакр.
             *
             * @param animal --- животное.
             */
            void insertAnimal(Animal *animal) noexcept { this->animals.push_back(animal); }

            /*
             * Возвращает указатель на масив животных.
             */
            AnimalsRef getAnimals(void) const noexcept { return this->animals; }

            /*
             */
            void skipHour(void) noexcept {
                this->updateAnimals();

                float distance = 1.0 - this->zoo_intencity_m;
                float hour_sign = (this->curr_hour_m > 6) ? -1.0 : 1.0;
                float random_step = (double)(rand() % 100) * 0.001f;

                this->zoo_intencity_m += hour_sign *(random_step + distance * 0.05);
                this->applyHour();

                if (this->curr_hour_m == 12) {
                    this->curr_hour_m = 1;
                    this->zoo_intencity_m  = (double)(rand() % 100) * 0.001f + 0.15;
                    for (auto animal : this->animals) {
                        animal->feed();
                        animal->rest();
                        animal->setState(Animal::AnimalState::Main);
                    }
                } else {
                    this->curr_hour_m++;
                }
            }

            void displayZoo() const noexcept {
                const auto kind2str = [](Animal::AnimalType kind){
                    using Type = Animal::AnimalType;
                    switch (kind) {
                        case Type::Cat:     return std::string("Cat");
                        case Type::Dog:     return std::string("Dog");
                        case Type::Wombat:  return std::string("Wombat");
                    }
                };

                const auto state2str = [](Animal::AnimalState state) {
                    using State = Animal::AnimalState;
                    switch (state) {
                        case State::Feed:   return std::string("Feed");
                        case State::Main:   return std::string("Zoo");
                        case State::Sleep:  return std::string("Sleep");
                    }
                };

                const size_t len = 70;
                const size_t indent = 10;

                const auto nl = [](void){
                    std::cout << "\n" << std::string(indent, ' ');
                };
                const auto hr = [&nl](void){
                    std::cout << "  " << std::string(len - 4, '-'); nl();
                };
                const auto double_hr = [&nl](void){
                    std::cout << std::string(len, '='); nl();
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
                const auto b  = [](){ std::cout << "\x1b[1m"; };
                const auto i  = [](){ std::cout << "\x1b[3m"; };
                const auto clear  = [](){ std::cout << "\x1b[0m"; };
                const auto color = [](int id){ std::cout << "\x1b[3" << id << "m"; };


                nl();
                b();
                double_hr();
                cnt("---- Contact Zoo ----", len); nl();
                cnt(std::to_string(this->curr_hour_m) + "h, " + std::to_string(this->zoo_intencity_m), len); nl();
                clear();
                double_hr();

                const size_t
                    name_size = 40,
                    state_size = 15,
                    stats_size = len - name_size - state_size;

                b();
                color(3);
                cnt("Name", name_size);
                cnt("State", state_size);
                cnt("A", stats_size / 3);
                cnt("S", stats_size / 3);
                cnt("T", stats_size / 3 + stats_size % 3);
                clear();
                nl();

                for (const auto animal : this->animals) {
                    const auto stats = animal->getStats();
                    hr();
                    i();
                    color(2);
                    cnt(kind2str(animal->getType()) + " \"" + stats.name + "\"",
                            name_size);

                    cnt(state2str(stats.state), state_size);

                    color(4);
                    cnt(std::to_string(stats.age),
                            stats_size / 3);
                    cnt(std::to_string(stats.starvness) + "%",
                            stats_size / 3);
                    cnt(std::to_string(stats.tiredness),
                            stats_size / 3 + stats_size % 3);
                    clear();
                    nl();
                }
                nl();
            }


        private:
            void updateAnimals(void) {
                for (auto &animal : this->animals) {
                    auto stats = animal->getStats();

                    using State = Animal::AnimalState;

                    switch (stats.state) {
                        case State::Main: {
                                if (stats.starvness < 10) animal->setState(State::Feed);
                                else if (stats.tiredness >= 80) animal->setState(State::Sleep);
                            } break;
                        case State::Feed: {
                                if (stats.hours_in_state == 1) animal->setState(State::Main);
                            } break;
                        case State::Sleep: {
                                if (stats.hours_in_state >= animal->getMaxSleepHours()) animal->setState(State::Main);
                            } break;
                    }
                }
            }

            void applyHour(void) {
                for (auto &animal : this->animals) {
                    animal->incHoursInState();

                    using State = Animal::AnimalState;

                    auto stats = animal->getStats();
                    switch (stats.state) {
                        case State::Main: {
                                animal->starve(this->zoo_intencity_m);
                                animal->tire(this->zoo_intencity_m);
                            } break;
                        case State::Feed: {
                                animal->feed();
                            } break;
                        case State::Sleep: {
                                animal->rest();
                            } break;
                    }
                }
            }

            Animals animals;
            float zoo_intencity_m;
            size_t curr_hour_m;
    };

    void runLab4(void) {
        srand(time(nullptr));
        int zoo_init_len;
        std::cin >> zoo_init_len;

        Animal dog { new Dog };
        std::cout << dog.getStats().name << std::endl;

        ContactZoo zoo (zoo_init_len);

        zoo.displayZoo();

        const std::string help_msg =
            "lab4:\n"
            "    \x1B[1;34mskip\x1b[0m - skip one hour changing nothing.\n"
            "    \x1B[1;34madd\x1b[0m <type> <name> <age> - add animal. (type must be one of Dog | Cat | Wombat)\n"
            "    \x1B[1;34mskipn\x1b[0m <n> - skip n hours."
            "    \x1B[1;34mexit\x1b[0m";
        std::string command = "";

        std::cout << help_msg << std::endl;

        while (true) {
            std::cout << "\n\x1B[1;34mlab4\x1b[0m>";
            std::cin >> command;

            if (command == "skip") {
                zoo.skipHour();
                std::cout << std::endl;

                zoo.displayZoo();
                std::cout << std::endl;
            } else if (command == "skipn") {
                int n;
                std::cin >> n;
                for (size_t i = 0; i < n; i++){
                    zoo.skipHour();
                    std::cout << std::endl;

                    zoo.displayZoo();
                    std::cout << std::endl;
                }
            } else if (command == "add") {
                std::string type, name;
                int age;
                std::cin >> type >> name >> age;

                if (type == "Dog") {
                    zoo.insertAnimal(new Animal(new Dog(name, age)));
                } else if (type == "Cat") {
                    zoo.insertAnimal(new Animal(new Cat(name, age)));
                } else if (type == "Wombat") {
                    zoo.insertAnimal(new Animal(new Wombat(name, age)));
                } else {
                    std::cout << "invalid animal type: \"" << type << "\"" << std::endl;
                }
                std::cout << std::endl;

                zoo.displayZoo();
                std::cout << std::endl;
            } else if (command == "exit") {
                break;
            }

            command = "";
        }
    }
}
