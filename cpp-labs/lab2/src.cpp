#include <cstdio>
#include <iostream>
#include <cstddef>

#include "lab2.hpp"


namespace lab2 {
    /*
     * Выводит квадратный 2-х мерный массив в `stdout`.
     *
     * @param array --- указатель на массив данных [NxN].
     * @param n     --- n размер стороны массива.
     */
    void printArray(int **array, size_t n) {
        for (size_t i = 0; i < n; i++) {
            std::cout << "| ";
            for (size_t j = 0; j < n; j++) {
                printf("%5d ", array[i][j]);
            }
            std::cout << "  |" << "\n";
        }
        std::cout << std::endl;
    }

    /*
     * Заполнает массив данными от 1 до N*N в прямом порядке.
     *
     * @param array --- указатель на массив данных [NxN].
     * @param n     --- n размер стороны массива.
     */
    void fillInDirectOrder(int **array, size_t n) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                array[i][j] = i * n + j + 1;
            }
        }
    }

    /*
     * Заполнает массив данными от 1 до N*N в обратном порядке.
     *
     * @param array --- указатель на массив данных [NxN].
     * @param n     --- n размер стороны массива.
     */
    void fillInReverseOrder(int **array, size_t n) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                array[i][j] = n*n - i * n - j;
            }
        }
    }

    /*
     * Заполнает массив данными от 1 до N*N вдоль главной диагонали.
     *
     * @param array --- указатель на массив данных [NxN].
     * @param n     --- n размер стороны массива.
     */
    void fillAlongMainDiagonal(int **array, size_t n) {
        size_t i = 0, j = 0, curr = 1;
        while (curr <= n*n) {
            array[i][j] = curr++;

            if (j == n-1) {
                j = i + 1;
                i = n - 1;
                continue;
            }
            if (i == 0) {
                i = j+1;
                j = 0;
                continue;
            }
            i--;
            j++;
        }
    }

    /*
     * Заполнает массив данными от 1 до N*N вдоль побочной диагонали.
     *
     * @param array --- указатель на массив данных [NxN].
     * @param n     --- n размер стороны массива.
     */
    void fillAlongSideDiagonal(int **array, size_t n) {
        size_t i = 0, j = n-1, curr = 1;
        while (curr <= n*n) {
            array[i][j] = curr++;

            if (j == 0) {
                j = n - 2 - i;
                i = n - 1;
                continue;
            }
            if (i == 0) {
                i = n - j;
                j = n - 1;
                continue;
            }
            i--;
            j--;
        }
    }

    /*
     * Заполнает массив данными от 1 до N*N по спирали.
     *
     * @param array --- указатель на массив данных [NxN].
     * @param n     --- n размер стороны массива.
     */
    void fillWithHelix(int **array, size_t n) {
        size_t i = 0, j = 0, curr = 1;
        enum { Left2Right, Top2Down, Right2Left, Down2Top } dir = Left2Right;
        size_t paddings[4] = { 0, 0, 0, 0 }; // left, top, right, bottom.

        while (curr <= n*n) {
            array[i][j] = curr++;

            switch (dir) {
            case Left2Right:
                j++;
                if (j == n - 1 - paddings[2]) {
                    paddings[1]++;
                    dir = Top2Down;
                }
                break;
            case Top2Down:
                i++;
                if (i == n - 1 - paddings[3]) {
                    paddings[2]++;
                    dir = Right2Left;
                }
                break;
            case Right2Left:
                j--;
                if (j == paddings[0]) {
                    paddings[3]++;
                    dir = Down2Top;
                }
                break;
            case Down2Top:
                i--;
                if (i == paddings[1]) {
                    paddings[0]++;
                    dir = Left2Right;
                }
                break;
            }
        }
    }

    void runLab2(void) {
        size_t n;
        std::cin >> n;
        int **array = new int*[n];
        for (size_t i = 0; i < n; i++) { array[i] = new int[n]; }

        fillInDirectOrder(array, n);
        printArray(array, n);

        const char options_msg[] =
            "\nChosse option:\n"
            "\t'help'      -- print this message.\n"
            "\t'dir'       -- fill array in direct order.\n"
            "\t'rev'       -- fill array in reverse order.\n"
            "\t'main-dig'  -- fill array along main diagonal.\n"
            "\t'side-dig'  -- fill array along side diagonal.\n"
            "\t'helix'     -- fill array with helix stats at [0,0].\n"
            "\t'exit'      -- exit lab2 process.";
        std::string choosed_option;

        std::cout << options_msg << std::endl;

        while (true) {
            std::cout << "lab2> ";
            std::cin >> choosed_option;
            if (choosed_option == "dir") {
                fillInDirectOrder(array, n);
                std::cout << "\tcomplete 'dir' option" << std::endl;
            }
            else if (choosed_option == "rev") {
                fillInReverseOrder(array, n);
                std::cout << "\tcomplete 'rev' option" << std::endl;
            }
            else if (choosed_option == "main-dig") {
                fillAlongMainDiagonal(array, n);
                std::cout << "\tcomplete 'main-dig' option" << std::endl;
            }
            else if (choosed_option == "side-dig") {
                fillAlongSideDiagonal(array, n);
                std::cout << "\tcomplete 'side-dig' option" << std::endl;
            }
            else if (choosed_option == "helix") {
                fillWithHelix(array, n);
                std::cout << "\tcomplete 'helix' option" << std::endl;
            }
            else if (choosed_option == "help") {
                std::cout << options_msg << std::endl;
            }
            else if (choosed_option == "exit") {
                break;
            }
            else {
                std::cout << "invalid option" << std::endl;
            }
            std::cout << "\t\t---- Curr array: -----" << std::endl;
            printArray(array, n);
        }


        for (size_t i = 0; i < n; i++) { delete[] array[i]; }
        delete[] array;
    }



}

