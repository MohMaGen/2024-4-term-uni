#include <cstdlib>
#include <ctime>
#include <iostream>
#include <lab7.hpp>
#include <stdexcept>
#include <vector>
#include <array>

namespace lab8 {
    template<typename Type>
    struct Maybe {
        enum { Just=0, Nothing } variant;
        union { Type just; bool _; };

        Maybe(): variant(Nothing), _(false) {}
        Maybe(Type value): variant(Just), just(value) {}

        bool hasSome() { return variant != Nothing; }
        explicit operator bool() { return hasSome(); }

        const Type& operator*() const {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return just;
        }

        Type& operator*() {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return just;
        }

        const Type* operator->() const {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return &just;
        }

        Type* operator->() {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return &just;
        }
    };


    class Customer {
        public:
            enum CustomerType { Junior=0, Middle, Senior } type;
            size_t time_to_serve;

            Customer() = delete;
            static Maybe<Customer> Generate() {
                double chance = (double)std::rand() / (double)RAND_MAX;

                if (chance < 0.05) return { Customer{ Junior, (size_t)std::rand()%5+5 } };
                if (chance < 0.45) return { Customer{ Middle, (size_t)std::rand()%3+2 } };
                if (chance < 0.75) return { Customer{ Senior, (size_t)std::rand()%2+7 } };

                return { };
            }
        private:
            Customer(CustomerType type, size_t time_to_serve): type{ type }, time_to_serve(time_to_serve) {}
    };

    class Window {
        public:

    };

    class Institution {
        lab7::Queue<Customer> _e_queue { 10 }, _l_queue { 10 };
        std::vector<Window> _windows; 

        size_t _inst_time = 0;
        size_t _time_to_next_cutomer_wave = 0;

        void _new_customers() {
            for (size_t i = 0; i < 3; i++) {
                auto customer = Customer::Generate();
                if (!customer) continue;


                double chance = (double)std::rand() / (double)RAND_MAX;

                switch (customer->type) {
                case Customer::Junior: {
                    if (chance <= 0.2)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                case Customer::Middle: {
                    if (chance <= 0.7)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                case Customer::Senior: {
                    if (chance <= 0.05)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                }
            }

        }

        void _update() {
            if (_time_to_next_cutomer_wave == 0) {
                _new_customers();
                _time_to_next_cutomer_wave = 5;
            }
        }


        public:
            Institution() { }

            void tick() {
                _update();

                _time_to_next_cutomer_wave--;
                _inst_time++;
            }
    };


    void runLab8(void) {
        Institution institution { };

        while (true) {
            std::cout << "Next or not? ";
            char ans;
            std::cin >> ans;
            if (ans != 'y') break;

            institution.tick();
        }
    }
}
