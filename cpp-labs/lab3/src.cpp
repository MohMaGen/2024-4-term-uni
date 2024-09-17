#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include "lab3.hpp"

namespace lab3 {

    /*
     * Перечисление Месяцев.
     */
    enum class Month: unsigned char {
        January = 0,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December,
    };

    /*
     * Дата.
     */
    struct Date {
        unsigned short year;
        Month month;
        unsigned char day;
    };

    /*
     * Полное имя.
     */
    struct FullName {
        char *given_name;
        char *family_name;
        char *third_name;
    };

    enum class Gender: unsigned char {
        Male,
        Female,
    };

    struct Employee {
        FullName full_name;
        Gender gender;
        Date birth_date;
    };

    const unsigned char MALE_NAMES_LEN = 9;
    char MALE_NAMES[][32] = {
        "Ivan",
        "Vladimir",
        "Lev",
        "Mark",
        "Gleb",
        "Sergey",
        "Bob",
        "Robert",
        "Sem"
    };

    const unsigned char FEMALE_NAMES_LEN = 5;
    char FEMALE_NAMES[][32] = {
        "Vlada",
        "Olga",
        "Vera",
        "Maria",
        "Veronika",
    };

    const unsigned char FAMILY_NAMES_LEN = 9;
    char FAMILY_NAMES[][32] = {
        "Mokhov",
        "Shpet",
        "Dubov",
        "Mashinov",
        "Solncev",
        "Tckachev",
        "Voronin",
        "Reshetnikov",
        "Grachev"
    };

    /*
     * Заполняет массив сотрудников случайно сгенерированными данными.
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     */
    void generateEmployees(Employee *employees, size_t len) {
        srand(time(NULL));

        Gender gender { Gender::Male };
        Date birth_date { 0, Month::July, 0 };
        FullName full_name { nullptr, nullptr, nullptr };


        for (size_t i = 0; i < len; i++) {
            full_name.given_name  = new char [32];
            full_name.family_name = new char [32];
            full_name.third_name  = new char [32];

            if (rand() % 2) {
                strcpy(full_name.given_name,  MALE_NAMES   [rand() % MALE_NAMES_LEN]);
                strcpy(full_name.family_name, FAMILY_NAMES [rand() % FAMILY_NAMES_LEN]);
                strcpy(full_name.third_name,  MALE_NAMES   [rand() % MALE_NAMES_LEN]);
                strcpy(full_name.third_name + strlen(full_name.third_name), "ovich");

                gender = Gender::Male;
            } else {
                strcpy(full_name.given_name,  FEMALE_NAMES [rand() % FEMALE_NAMES_LEN]);
                strcpy(full_name.family_name, FAMILY_NAMES [rand() % FAMILY_NAMES_LEN]);
                strcpy(full_name.third_name,  MALE_NAMES   [rand() % MALE_NAMES_LEN]);

                strcpy(full_name.family_name + strlen(full_name.family_name), "a");
                strcpy(full_name.third_name + strlen(full_name.third_name), "ovna");

                gender = Gender::Female;
            }

            birth_date.day   = rand() % 26 + 1;
            birth_date.year  = rand() % 26 + 1975;
            birth_date.month = Month( rand() % 12 );

            employees[i] = Employee { full_name, gender, birth_date };
        }
    }

    /*
     * Красиво выводит массив сотрудника.
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     */
    void printEmployee(Employee employee) {
            std::cout << "(\x1b[3;31mEmployee\x1b[0m) {\n"
                << "\t(\x1b[32mFullName\x1b[0m) { \x1b[1;34m"
                    << employee.full_name.family_name << " "
                    << employee.full_name.given_name << " "
                    << employee.full_name.third_name << " \x1b[0m}\n"

                << "\t(\x1b[32mGender\x1b[0m) \x1b[1;34m"
                    << (employee.gender == Gender::Male ? "male" : "female") << "\x1b[0m\n"

                << "\t(\x1b[32mBirthdate\x1b[0m) { \x1b[1;34m"
                    << (int) employee.birth_date.day << "."
                    << (int) employee.birth_date.month + 1 << "."
                    << (int) employee.birth_date.year << " \x1b[0m}\n}"

                << std::endl;
    }

    /*
     * Красиво выводит массив сотрудников.
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     */
    void printEmployees(Employee* employees, size_t len) {
        for (size_t i = 0; i < len; i++) {
            printEmployee(employees[i]);
        }
    }


    /*
     * Проверяет начинается ли строка с префикса.
     *
     * Строка и префикс должны юыть валидными C-like строками.
     *
     * @param str    --- строка
     * @param prefix --- префикс
     */
    int strStartWith(char *str, char *prefix) {
        for (size_t i = 0; prefix[i] != '\0'; i++) {
            if (str[i] == '\0' || str[i] != prefix[i]) return 0;
        }
        return 1;
    }

    /*
     * Находит и ввыводит всех сотрудников соответстующих запросу
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     * @param query     --- запрос (C-like строка).
     */
    void find(Employee* employees, size_t len, char* query) {
        for (size_t i = 0; i < len; i++) {
            if ( strStartWith(employees[i].full_name.family_name, query) ) {
                std::cout << "\t\x1b[1;34m" << query << "\x1b[0;33m"
                    << employees[i].full_name.family_name + strlen(query) << " "
                    << employees[i].full_name.given_name << " "
                    << employees[i].full_name.third_name << "\x1b[0m\n";
                printEmployee(employees[i]);
                std::cout << "\n";

            } else if ( strStartWith(employees[i].full_name.given_name, query) ) {
                std::cout << "\t\x1b[0;33m"
                    << employees[i].full_name.family_name << " "
                    << "\x1b[1;34m" << query << "\x1b[0;33m"
                    << employees[i].full_name.given_name  + strlen(query)<< " "
                    << employees[i].full_name.third_name << "\x1b[0m\n";
                printEmployee(employees[i]);
                std::cout << "\n";

            } else if ( strStartWith(employees[i].full_name.third_name, query) ) {
                std::cout << "\t\x1b[0;33m"
                    << employees[i].full_name.family_name << " "
                    << employees[i].full_name.given_name << " "
                    << "\x1b[1;34m" << query << "\x1b[0;33m"
                    << employees[i].full_name.third_name  + strlen(query) << "\x1b[0m\n";
                printEmployee(employees[i]);
                std::cout << "\n";
            }
        }
    }


    /*
     * Выводит всех сотрудников родившихся до указанного года.
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     * @param year      --- год.
     */
    void older(Employee *employees, size_t len, int year) {
        for (size_t i = 0; i < len; i++) {
            if (employees[i].birth_date.year < year) {
                printEmployee(employees[i]);
            }
        }
    }

    /*
     * Выводит всех сотрудников родившихся после указанного года.
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     * @param year      --- год.
     */
    void yanger(Employee *employees, size_t len, int year) {
        for (size_t i = 0; i < len; i++) {
            if (employees[i].birth_date.year >= year) {
                printEmployee(employees[i]);
            }
        }
    }

    void runLab3(void) {
        size_t n;
        std::cin >> n;

        Employee* employees = new Employee[n];
        generateEmployees(employees, n);

        char help_msg[] =
            " ----------- LAB 3 -----------\n"
            "     - \x1b[1;33mhelp\x1b[0m --- print this message.\n"
            "     - \x1b[1;33mprint\x1b[0m --- print all employees.\n"
            "     - \x1b[1;33mfind\x1b[0m \x1b[3;34m<query>\x1b[0m --- find employee.\n"
            "     - \x1b[1;33molder\x1b[0m \x1b[3;34m<year>\x1b[0m --- list all employees that older <date>.\n"
            "     - \x1b[1;33myanger\x1b[0m \x1b[3;34m<year>\x1b[0m --- list all employees that yanger <date>.\n";

        char command[256] = { '\0' }, query[256] = { '\0' };

        std::cout << help_msg << std::endl;


        while (true) {
            std::cout << "\x1b[1;34mlab3\x1b[0m> ";
            std::cin >> command;
            if (strcmp(command, "help") == 0) {
                std::cout << help_msg << std::endl;

            } else if (strcmp(command, "find") == 0) {
                std::cin >> query;
                find(employees, n, query);
                std::cout << std::endl;

            } else if (strcmp(command, "older") == 0) {
                int year;
                std::cin >> year;
                older(employees, n, year);
                std::cout << std::endl;

            } else if (strcmp(command, "yanger") == 0) {
                int year;
                std::cin >> year;
                yanger(employees, n, year);
                std::cout << std::endl;

            }else if (strcmp(command, "print") == 0) {
                printEmployees(employees, n);
            }
        }
    }
}
