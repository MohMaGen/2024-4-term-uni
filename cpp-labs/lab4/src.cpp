#include "lab4.hpp"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
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
             * @param starvness --- сытость.
             * @param tiredness --- усталость.
             */
            Cat(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                name_m = name;
                age_m = age;
                starvness_m = starvness;
                tiredness_m = tiredness;
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
                this->starvness_m = rand() % 100;
                this->tiredness_m = rand() % 20;
            }

            void starve(float zoo_intencity) {
                static const int STARVE_PER_HOUR = 10;
                this->starvness_m -= 10.0 * zoo_intencity * STARVE_PER_HOUR;
            }

            void tire(float zoo_intencity) {
                static const int TIRE_PER_HOUR = 10;
                this->tiredness_m += 10.0 * zoo_intencity * TIRE_PER_HOUR;

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
             * @param starvness --- сытость.
             * @param tiredness --- усталость.
             */
            Dog(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                name_m = name;
                age_m = age;
                starvness_m = starvness;
                tiredness_m = tiredness;
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
                this->starvness_m = rand() % 100;
                this->tiredness_m = rand() % 20;
            }

            void starve(float zoo_intencity) {
                static const int STARVE_PER_HOUR = 30;
                this->starvness_m -= 10.0 * zoo_intencity * STARVE_PER_HOUR;
            }

            void tire(float zoo_intencity) {
                static const int TIRE_PER_HOUR = 15;
                this->tiredness_m += 10.0 * zoo_intencity * TIRE_PER_HOUR;

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
             * @param starvness --- сытость.
             * @param tiredness --- усталость.
             */
            Wombat(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                name_m = name;
                age_m = age;
                starvness_m = starvness;
                tiredness_m = tiredness;
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
                this->starvness_m = rand() % 100;
                this->tiredness_m = rand() % 20;
            }

            void starve(float zoo_intencity) {
                static const int STARVE_PER_HOUR = 9;
                this->starvness_m -= 10.0 * zoo_intencity * STARVE_PER_HOUR;
            }

            void tire(float zoo_intencity) {
                static const int TIRE_PER_HOUR = 40;
                this->tiredness_m += 10.0 * zoo_intencity * TIRE_PER_HOUR;

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

            AnimalState state_m;
            std::uint8_t hours_in_state_m;

            void *animal_ptr_m;
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
            ContactZoo(size_t animals_len) : zoo_intencity_m(0.2), curr_hour_m(0) {
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
            void skip_hour(void) noexcept {
                this->updateAnimals();

                float distance = 1 - this->zoo_intencity_m;
                float hour_sign = (this->curr_hour_m > 6) ? -1.0 : 1.0;
                float random_step = (double)(rand() % 10) / 10.f;

                this->zoo_intencity_m += hour_sign *(random_step + distance * 0.1);
                this->applyHour();
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

        std::cout << "Зоопарк:" << std::endl;
        for (const auto &animal : zoo.getAnimals()) {
            std::cout << animal->toString() << std::endl;
        }

        const std::string help_msg =
            "lab4:\n"
            "    \x1B[1;34mskip\x1b[0m - skip one hour changing nothing.\n"
            "    \x1B[1;34add\x1b[0m <type> <name> <age> - add animal. (type must be one of Dog | Cat | Wombat)\n"
            "    \x1B[1;34exit\x1b[0m";
        std::string command = "";

        std::cout << help_msg << std::endl;
        std::cout << "\x1B[1;34lab4\x1b[0m>";

        while (true) {
            std::cin >> command;

            if (command == "skip") {

            } else if (command == "add") {

            } else if (command == "exit") {
                break;
            }

            command = "";
        }
    }
}
