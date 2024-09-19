#include <cstddef>
#include <cstdio>
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

    int cmpDate(Date fst, Date snd) {
        if (fst.year > snd.year) return 1;
        if (snd.year > fst.year) return -1;

        if (fst.month > snd.month) return 1;
        if (snd.month > fst.month) return -1;

        if (fst.day > snd.day) return 1;
        if (snd.day > fst.day) return -1;

        return 0;
    }

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
    const unsigned int AGE_GENERATION_RANGE = 60;
    const unsigned int AGE_GENERATION_START = 1950;

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
            birth_date.year  = rand() % AGE_GENERATION_RANGE + AGE_GENERATION_START;
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
     * Выводиьт Сотрудников в краткой форме с индексами.
     *
     * @param employee  --- сотрудник.
     * @param i         --- номер сотрудника.
     */
    void printEmployeeShort(Employee employee, int i) {
        printf("\t%4d: %s %s %s %d.%d.%d\n", i,
                employee.full_name.family_name, employee.full_name.given_name, employee.full_name.third_name,
                (int)employee.birth_date.day, (int)employee.birth_date.month, (int)employee.birth_date.year
              );
    }

    /*
     * Выводит массив сотрудника в краткой форме с индексами.
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     */
    void printEmployeesShort(Employee* employees, size_t len) {
        for (size_t i = 0; i < len; i++) {
            printEmployeeShort(employees[i], i);
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
                printEmployeeShort(employees[i], i);
                std::cout << "\n";

            } else if ( strStartWith(employees[i].full_name.given_name, query) ) {
                std::cout << "\t\x1b[0;33m"
                    << employees[i].full_name.family_name << " "
                    << "\x1b[1;34m" << query << "\x1b[0;33m"
                    << employees[i].full_name.given_name  + strlen(query)<< " "
                    << employees[i].full_name.third_name << "\x1b[0m\n";
                printEmployeeShort(employees[i], i);
                std::cout << "\n";

            } else if ( strStartWith(employees[i].full_name.third_name, query) ) {
                std::cout << "\t\x1b[0;33m"
                    << employees[i].full_name.family_name << " "
                    << employees[i].full_name.given_name << " "
                    << "\x1b[1;34m" << query << "\x1b[0;33m"
                    << employees[i].full_name.third_name  + strlen(query) << "\x1b[0m\n";
                printEmployeeShort(employees[i], i);
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

    inline void swapEmployee(Employee *fst, Employee *snd) {
        Employee tmp;

        tmp = *fst;
        *fst = *snd;
        *snd = tmp;
    }

    void employeeQuickSortByDate(Employee *employees, long from, long to) {
        if (from >= to || from < 0) return;

        Employee *pivot = employees + to;

        size_t pivot_idx = from;
        for (size_t j = from; j < to; j++) {
            if (cmpDate(employees[j].birth_date, pivot->birth_date) < 1 ) {
                swapEmployee(employees + pivot_idx, employees + j);
                pivot_idx++;
            }
        }
        swapEmployee(employees + pivot_idx, pivot);

        employeeQuickSortByDate(employees, from, pivot_idx - 1);
        employeeQuickSortByDate(employees, pivot_idx + 1, to);
    }

    void sortByDate(Employee *employees, size_t len) {
        employeeQuickSortByDate(employees, 0, len-1);
    }

    /*
     * Находит сотрудника с наименьшей датой рождения, которая больше или равна
     * введённому значению года, в отсортированном массиве. [ O(log(N)) ]
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     * @param year      --- год, больше которого надо найти дату рождения сотрудинка.
     * @return указатель на, соответствующего условию, сотрудника  или нулевой указатель,
     *      если такого нет.
     */
    Employee* upperBoundSorted(Employee *employees, size_t len, size_t year) {
        Employee *curr = employees + len / 2, *end = employees + len, *start = employees;

        while (curr > start && curr < end && (curr->birth_date.year < year || (curr-1)->birth_date.year >= year)) {
            if (curr->birth_date.year >= year) {
                end = curr;
                curr -= (curr - start) / 2 - (curr - start) % 2;
            } else {
                start = curr;
                curr += (end - curr) / 2 + (end - curr) % 2;
            }
        }
        return (curr == employees + len) ? nullptr : curr;
    }

    /*
     * Выводит всех сотрудников распределяя их по полу и возрастным группам
     *
     * @param employees --- указатель на массив.
     * @param len       --- длина массива.
     */
    void printByGender(Employee *employees, size_t len) {
        Employee *employees_copy = new Employee[len];
        for (size_t i = 0; i < len; i++)
            employees_copy[i] = employees[i];

        sortByDate(employees_copy, len);
        Date min = employees_copy[0].birth_date, max = employees_copy[len-1].birth_date;

        const int RANGE = 10;
        int date_range = max.year - min.year;
        int groups_len = date_range / RANGE + (date_range % RANGE != 0 ? 1 : 0);

        Employee *from = employees_copy, *to, *curr;
        for (size_t i = 0; i < groups_len; i++) {
            to = upperBoundSorted(employees_copy, len, min.year + RANGE * (i+1));
            if (to == nullptr) to = employees_copy + len;

            printf("( employees from %ld to %ld ) {\n", (int)min.year + RANGE * (i), (int)min.year + RANGE * (i+1));
            puts("  males:");
            curr = from-1;
            while (++curr != to) {
                if (curr->gender == Gender::Male) printEmployeeShort(*curr, curr - employees_copy);
            }

            puts("  females:");
            curr = from-1;
            while (++curr != to) {
                if (curr->gender == Gender::Female) printEmployeeShort(*curr, curr - employees_copy);
            }
            puts("}");

            from = to;
        }

        delete[] employees_copy;
    }

    const char HELP_MSG[] =
            " ----------- LAB 3 -----------\n"
            "     - \x1b[1;33mhelp\x1b[0m --- print this message.\n"
            "     - \x1b[1;33mprint\x1b[0m --- print all employees.\n"
            "     - \x1b[1;33mfind\x1b[0m \x1b[3;34m<query>\x1b[0m --- find employee.\n"
            "     - \x1b[1;33molder\x1b[0m \x1b[3;34m<year>\x1b[0m --- list all employees that older <date>.\n"
            "     - \x1b[1;33myanger\x1b[0m \x1b[3;34m<year>\x1b[0m --- list all employees that yanger <date>.\n"
            "     - \x1b[1;33msort-by-date\x1b[0m  --- sort employees array by date.\n"
            "     - \x1b[1;33mby-gender\x1b[0m  --- list all employess by age groups and genders.\n"
            "     - \x1b[1;33mexit\x1b[0m  --- exit from lab.\n";

    const char LAB3_SHELL_INPUT[] = "\x1b[1;34mlab3\x1b[0m> ";

    void runLab3(void) {
        size_t n;
        std::cin >> n;

        Employee* employees = new Employee[n];
        generateEmployees(employees, n);


        char command[256] = { '\0' }, query[256] = { '\0' };

        std::cout << HELP_MSG << std::endl;


        while (true) {
            std::cout << LAB3_SHELL_INPUT;
            std::cin >> command;
            if (strcmp(command, "help") == 0) {
                std::cout << HELP_MSG << std::endl;

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

            } else if (strcmp(command, "sort-by-date") == 0) {
                sortByDate(employees, n);
                printEmployeesShort(employees, n);
                std::cout << std::endl;

            } else if (strcmp(command, "by-gender") == 0) {
                printByGender(employees, n);
                std::cout << std::endl;
            } else if (strcmp(command, "print") == 0) {
                printEmployees(employees, n);

            } else if (strcmp(command, "exit") == 0) {
                break;
            }
        }

        for (size_t i = 0; i < n; i++) {
            delete[] employees[i].full_name.third_name;
            delete[] employees[i].full_name.given_name;
            delete[] employees[i].full_name.family_name;
        }
        delete[] employees;
    }
}
