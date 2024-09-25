#include <cstdint>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>
#include <lab1.hpp>
#include <lab2.hpp>
#include <lab3.hpp>
#include <lab4.hpp>
#include <lab5.hpp>

const char HELP_MESSAGE[] =
    "\t\t _       _                                                \n"
    "\t\t| | __ _| |__  ___   _ __ _   _ _ __  _ __   ___ _ __     \n"
    "\t\t| |/ _` | '_ \\/ __| | '__| | | | '_ \\| '_ \\ / _ \\ '__|\n"
    "\t\t| | (_| | |_) \\__ \\ | |  | |_| | | | | | | |  __/ |     \n"
    "\t\t|_|\\__,_|_.__/|___/ |_|   \\__,_|_| |_|_| |_|\\___|_|    \n"
    "\t\t                                                          \n"
    "Enter command:\n"
    "\thelp for this message.\n"
    "\tlab1 <from> <to> -- for lab1 process.\n"
    "\tlab2 <n>         -- for lab2 process.\n"
    "\tlab3 <n>         -- for lab3 process.\n"
    "\tlab4 <zoo_len>   -- for lab4 process.\n"
    "\tlab5             -- for lab5 process.\n"
    "\tquit -- to quit from lab runner.";

void runFirstLab(void) {
    std::uint32_t from, to;
    std::fflush(stdin);
    std::cin >> from >> to;

    std::vector<uint32_t> result;
    try {
        lab1::eraspherAlgorythm(result, from, to);

        std::cout << "[ ";
        for (auto &prim : result) {
            std::cout << prim << " ";
        }
        std::cout << " ]" << std::endl;;
    } catch (lab1::EraspherAlgorythmError *err) {
        std::cout << "Failed to process lab1:\n";
        std::cout << err->what() << std::endl;
    }
}


auto main(void) -> int {
    std::string command;
    std::cout << HELP_MESSAGE << std::endl;

    while (true) {
        std::cout << "> ";
        std::cin >> command;
        if (command == "lab1") {
            runFirstLab();
        } else if (command == "lab2") {
            lab2::runLab2();
        } else if (command == "lab3") {
            lab3::runLab3();
        } else if (command == "lab4") {
            lab4::runLab4();
        } else if (command == "lab5") {
            lab5::runLab5();
        } else if (command == "help") {
            std::cout << HELP_MESSAGE << std::endl;
        } else if (command == "quit") {
            std::cout << "Goodbye :)" << std::endl;
            break;
        } else {
            std::cout << "Invalid command: " << std::quoted(command) << std::endl;;
        }
        command = std::string();
    }
    return 0;
}
