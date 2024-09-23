#include "lab4.hpp"
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


namespace lab4 {
    class Cat {
        std::string name_m;
        std::uint8_t age_m;
        std::uint8_t starvness_m;
        std::uint8_t tiredness_m;
        bool         sleep_m;

        public:
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
                sleep_m = false;
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

                *this = Cat(names[rand()%15], rand() % 15 + 1, rand() % 100, rand() % 20);
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


            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setName(const std::string &new_name) noexcept     { this->name_m = new_name; }
            void setStarvness(std::uint8_t new_starvness) noexcept { this->starvness_m = (new_starvness > 100) ? 100 : new_starvness; }
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
            /*
             * Создаёт собаку с определёнными параметрами.
             *
             * @param name      --- имя.
             * @param age       --- возраст.
             * @param starvness --- сытость.
             * @param tiredness --- усталость.
             */
            Dog(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                this->setName(name);
                this->setAge(age);
                this->setStarvness(starvness);
                this->setTiredness(tiredness);
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


            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setName(const std::string &new_name) noexcept     { this->name_m = new_name; }
            void setStarvness(std::uint8_t new_starvness) noexcept { this->starvness_m = (new_starvness > 100) ? 100 : new_starvness; }
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
            /*
             * Создаёт вомбота с определёнными параметрами.
             *
             * @param name      --- имя.
             * @param age       --- возраст.
             * @param starvness --- сытость.
             * @param tiredness --- усталость.
             */
            Wombat(std::string name, std::uint8_t age, std::uint8_t starvness, std::uint8_t tiredness) {
                this->setName(name);
                this->setAge(age);
                this->setStarvness(starvness);
                this->setTiredness(tiredness);
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


            void setAge(std::uint8_t new_age) noexcept             { this->age_m = new_age; }
            void setName(const std::string &new_name) noexcept     { this->name_m = new_name; }
            void setStarvness(std::uint8_t new_starvness) noexcept { this->starvness_m = (new_starvness > 100) ? 100 : new_starvness; }
            void setTiredness(std::uint8_t new_tiredness) noexcept { this->tiredness_m = new_tiredness; }
            void setSleep(bool is_sleep) noexcept { this->sleep_m = is_sleep; }
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
            /*
             * Общии для всех животных характеристики.
             */
            struct AnimalStats { std::string name; std::uint8_t age, starvness, tiredness; bool sleep; };


            Animal() = delete;

            /*
             * Создаёт животное -- кошку.
             *
             * @param cat --- значение кошки, которое будет скопированно.
             */
            Animal(const Cat &cat):        type_m(AnimalType::Cat),    animal_ptr_m(new Cat(cat)) {}

            /*
             * Создаёт животное -- собаку.
             *
             * @param dog --- значение собаки, которое будет скопированно.
             */
            Animal(const Dog &dog):        type_m(AnimalType::Dog),    animal_ptr_m(new Dog(dog)) {}

            /*
             * Создаёт животное -- вомбыта.
             *
             * @param wombat --- значение вомбыта, которое будет скопированно.
             */
            Animal(const Wombat &wombat):  type_m(AnimalType::Wombat), animal_ptr_m(new Wombat(wombat)) {}

            ~Animal() {
                switch (this->type_m) {
                    case AnimalType::Dog:    delete (Dog *)this->animal_ptr_m;    break;
                    case AnimalType::Cat:    delete (Cat *)this->animal_ptr_m;    break;
                    case AnimalType::Wombat: delete (Wombat *)this->animal_ptr_m; break;
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
             * Проверяет спитли животное.
             */
            bool isSleep(void) const noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    return ((Dog *)this->animal_ptr_m)->isSleep();
                    case AnimalType::Cat:    return ((Cat *)this->animal_ptr_m)->isSleep();
                    case AnimalType::Wombat: return ((Wombat *)this->animal_ptr_m)->isSleep();
                }
            }

            /*
             * Усыпить животное.
             */
            void makeSleep(void) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->setSleep(true);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->setSleep(true);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->setSleep(true); break;
                }
            }

            /*
             * Разбудить животное.
             */
            void wakeupSleep(void) noexcept {
                switch (this->type_m) {
                    case AnimalType::Dog:    ((Dog *)this->animal_ptr_m)->setSleep(false);    break;
                    case AnimalType::Cat:    ((Cat *)this->animal_ptr_m)->setSleep(false);    break;
                    case AnimalType::Wombat: ((Wombat *)this->animal_ptr_m)->setSleep(false); break;
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
                            ((Dog *)this->animal_ptr_m)->isSleep(),
                        };
                    case AnimalType::Cat:
                        return AnimalStats {
                            ((Cat *)this->animal_ptr_m)->getName(),
                            ((Cat *)this->animal_ptr_m)->getAge(),
                            ((Cat *)this->animal_ptr_m)->getStarvness(),
                            ((Cat *)this->animal_ptr_m)->isSleep(),
                        };
                    case AnimalType::Wombat:
                        return AnimalStats {
                            ((Wombat *)this->animal_ptr_m)->getName(),
                            ((Wombat *)this->animal_ptr_m)->getAge(),
                            ((Wombat *)this->animal_ptr_m)->getStarvness(),
                            ((Wombat *)this->animal_ptr_m)->getTiredness(),
                            ((Wombat *)this->animal_ptr_m)->isSleep(),
                        };
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
                    + std::to_string(stats.tiredness) + " "
                    + (stats.sleep ? "спит" : "бодрутствует");
            }

            AnimalType type_m;
            void *animal_ptr_m;
    };


    class ContactZoo {
        public:
            using AnimalPtr = Animal *;
            using Animals = std::vector<Animal>;
            using AnimalsRef = const Animals &;

            /*
             * Создать контактный зоопарк с указанным количеством случайно
             * сгенерированных животных.
             *
             * @param animals_len --- количество случайно сгенерированных животных.
             */
            ContactZoo(size_t animals_len) {
                animals = std::vector<Animal> ();

                for (size_t i = 0; i < animals_len; i++) {
                    using Type = Animal::AnimalType;

                    auto kind = (i < 3) ? Type(i) : Type(rand() % 3);
                    switch (kind) {
                        case Type::Cat:    animals.push_back(Cat());    break;
                        case Type::Dog:    animals.push_back(Dog());    break;
                        case Type::Wombat: animals.push_back(Wombat()); break;
                    }
                }
            }

            ~ContactZoo() {
            }

            /*
             * Добавляет животное в контактный зоопакр.
             *
             * @param animal --- животное.
             */
            void insertAnimal(Animal animal) noexcept { this->animals.push_back(animal); }

            /*
             * Возвращает указатель на масив животных.
             */
            AnimalsRef getAnimals(void) const noexcept { return this->animals; }

        private:
            Animals animals;
    };

    void runLab4(void) {
        srand(time(nullptr));
        int zoo_init_len;
        std::cin >> zoo_init_len;


        ContactZoo zoo (zoo_init_len);

        std::cout << "Зоопарк:" << std::endl;
        for (const auto &animal : zoo.getAnimals()) {
            std::cout << animal.toString() << std::endl;
        }
    }
}
