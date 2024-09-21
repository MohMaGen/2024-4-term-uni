#include "lab4.hpp"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>


namespace lab4 {
    class Cat {
        std::string name_m;
        std::uint8_t age_m;
        std::uint8_t starvness_m;
        std::uint8_t tiredness_m;
        bool         sleep_m;

        public:
            Cat(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                this->setName(name);
                this->setAge(age);
                this->setStarvness(starvness);
                this->setTiredness(tiredness);
            }

            Cat() {
                srand(time(nullptr));
                const char names[][32] = {
                    "Izzy", "Marlow", "Kona", "Stevie", "Arya",
                    "Aspen", "Jade", "Fern", "Liza", "Frida",
                    "Tux", "Charlie", "Dre ", "Hendrix ", "Atari",
                    "Bowser ", "Boba ", "Lincoln", "Lux ", "Niko ",
                };

                *this = Cat(names[rand()%20], rand() % 15 + 1, rand() % 100, rand() % 20);
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
            bool         isSleep(void) const noexcept      { return this->sleep_m; }


            void setName(std::string new_name) noexcept            { this->name_m = new_name; }
            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setStarvness(std::uint8_t new_starvness) noexcept {
                this->starvness_m = (new_starvness > 100) ? 100 : new_starvness;
            }
            void setTiredness(std::uint8_t new_tiredness) noexcept { this->tiredness_m = new_tiredness; }
            void setSleep(bool is_sleep) noexcept { this->sleep_m = is_sleep; }
    };

    class Dog {
        std::string name_m;
        std::uint8_t age_m;
        std::uint8_t starvness_m;
        std::uint8_t tiredness_m;
        bool         sleep_m;

        public:
            Dog(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                this->setName(name);
                this->setAge(age);
                this->setStarvness(starvness);
                this->setTiredness(tiredness);
            }

            Dog() {
                srand(time(nullptr));
                const char names[][32] = {
                    "Atlas", "Barkus", "Beef", "Bixby", "Busy", "Cat",
                    "Cinder", "Gimbal", "Hopper", "Kaboom", "Neo",
                    "Nimrod", "Qwerty", "Renegade", "Repo", "Ritz",
                    "Sativa", "Tails", "Toaster", "Tugs",
                };

                *this = Dog(names[rand()%20], rand() % 15 + 1, rand() % 100, rand() % 20);
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
            bool         isSleep(void) const noexcept      { return this->sleep_m; }


            void setName(std::string new_name) noexcept            { this->name_m = new_name; }
            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setStarvness(std::uint8_t new_starvness) noexcept {
                this->starvness_m = (new_starvness > 100) ? 100 : new_starvness;
            }
            void setTiredness(std::uint8_t new_tiredness) noexcept { this->tiredness_m = new_tiredness; }
            void setSleep(bool is_sleep) noexcept { this->sleep_m = is_sleep; }
    };

    class Wombat {
        std::string name_m;
        std::uint8_t age_m;
        std::uint8_t starvness_m;
        std::uint8_t tiredness_m;
        bool         sleep_m;

        public:
            Wombat(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                this->setName(name);
                this->setAge(age);
                this->setStarvness(starvness);
                this->setTiredness(tiredness);
            }

            Wombat() {
                srand(time(nullptr));
                const char names[][32] = {
                    "Burrowman", "Hector", "Missy", "King",
                    "Supplanter", "Jewel", "Mac", "Trust", "Evidence",
                    "Max", "Wayne", "Zayn", "Justice", "Rebecca",
                    "Liam", "Sharon", "Perceive", "Royal",
                };

                *this = Wombat(names[rand()%18], rand() % 15 + 1, rand() % 100, rand() % 20);
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
            bool         isSleep(void) const noexcept      { return this->sleep_m; }


            void setName(std::string new_name) noexcept            { this->name_m = new_name; }
            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setStarvness(std::uint8_t new_starvness) noexcept {
                this->starvness_m = (new_starvness > 100) ? 100 : new_starvness;
            }
            void setTiredness(std::uint8_t new_tiredness) noexcept { this->tiredness_m = new_tiredness; }
            void setSleep(bool is_sleep) noexcept { this->sleep_m = is_sleep; }
    };

    class Animal {
        public:
            enum class AnimalType { Cat, Dog, Wombat };
            struct AnimalStats { std::string name; std::uint8_t age, starvness, tiredness; };

            Animal(Cat cat): type_m(AnimalType::Cat), animal_ptr_m((void*)new Cat(cat)) {}
            Animal(Dog cat): type_m(AnimalType::Dog), animal_ptr_m((void*)new Dog(cat)) {}
            Animal(Wombat cat): type_m(AnimalType::Wombat), animal_ptr_m((void*)new Wombat(cat)) {}

            ~Animal() {
                switch (this->type_m) {
                    case AnimalType::Dog:    delete (Dog *)this->animal_ptr_m;    break;
                    case AnimalType::Cat:    delete (Cat *)this->animal_ptr_m;    break;
                    case AnimalType::Wombat: delete (Wombat *)this->animal_ptr_m; break;
                }
            }

            void starve(float zoo_intencity) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->starve(zoo_intencity);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->starve(zoo_intencity);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->starve(zoo_intencity); break;
                }
            }
            void tire(float zoo_intencity) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->tire(zoo_intencity);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->tire(zoo_intencity);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->tire(zoo_intencity); break;
                }
            }

            bool isSleep(void) const noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    return ((Dog *)this->animal_ptr_m)->isSleep();
                    case AnimalType::Cat:    return ((Cat *)this->animal_ptr_m)->isSleep();
                    case AnimalType::Wombat: return ((Wombat *)this->animal_ptr_m)->isSleep();
                }
            }

            void makeSleep(void) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->setSleep(true);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->setSleep(true);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->setSleep(true); break;
                }
            }

            void wakeupSleep(void) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->setSleep(false);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->setSleep(false);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->setSleep(false); break;
                }
            }

            AnimalStats get_stats(void) const noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:
                        return AnimalStats {
                            ((Dog *)this->animal_ptr_m)->getName(),
                            ((Dog *)this->animal_ptr_m)->getAge(),
                            ((Dog *)this->animal_ptr_m)->getStarvness(),
                            ((Dog *)this->animal_ptr_m)->getTiredness(),
                        };
                    case AnimalType::Cat:
                        return AnimalStats {
                            ((Cat *)this->animal_ptr_m)->getName(),
                            ((Cat *)this->animal_ptr_m)->getAge(),
                            ((Cat *)this->animal_ptr_m)->getStarvness(),
                            ((Cat *)this->animal_ptr_m)->getTiredness(),
                        };
                    case AnimalType::Wombat: 
                        return AnimalStats {
                            ((Wombat *)this->animal_ptr_m)->getName(),
                            ((Wombat *)this->animal_ptr_m)->getAge(),
                            ((Wombat *)this->animal_ptr_m)->getStarvness(),
                            ((Wombat *)this->animal_ptr_m)->getTiredness(),
                        };
                }
            }

        private:
            AnimalType type_m;
            void *animal_ptr_m;
    };


    class ContactZoo {
        std::vector<Animal> animals;
        public:
            using AnimalsRef = const std::vector<Animal> &;

            ContactZoo(size_t animals_len) {
                animals = std::vector<Animal>(animals_len);

                for (size_t i = 0; i < animals_len; i++) {
                    using Type = Animal::AnimalType;

                    auto kind = (i < 3) ? Type(i) : Type(rand() % 3);
                    switch (kind) {
                        case Type::Cat:    animals[i] = Animal(Cat());    break;
                        case Type::Dog:    animals[i] = Animal(Dog());    break;
                        case Type::Wombat: animals[i] = Animal(Wombat()); break;
                    }
                }
            }

            void insertAnimal(Animal animal) noexcept { this->animals.push_back(animal); }
            AnimalsRef get_animals(void) const noexcept { return this->animals; }
    };

    void runLab4(void) {
    }
}
