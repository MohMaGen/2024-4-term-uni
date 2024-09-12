#pragma once
#include <cstdint>
#include <exception>
#include <vector>

// Вариант 4
// Требуется написать программу, которая будет вычислять список простых
// чисел при помощи алгоритма решета Эратосфена. Согласно этому алгоритму
// требуется сгенерировать последовательность чисел и пройдя по ней
// вычеркнуть из нее все не простые числа. По итогу, нужно вывести
// последовательность простых чисел.

namespace lab1 {
    /*
     * Функция -- предикат, проверяющая является ли число
     * простым.
     *
     * @param1 value -- число для проверки.
     * @return bool  -- true - число простое, false - число не простое.
     */
    auto isPrime(std::uint32_t value) -> bool;

    /*
     * Функция выполняет алгоритм Эратофена на заданном диапазоне.
     *
     * @param1 output -- вектор в который записаоть результат.
     * @param2 from   -- начало диапазона.
     * @param3 to     -- конец диапазона.
     *
     * если диапазон задан некоректно (from >= to), вернётся ошибка класса [[EraspherAlgorythmError]].
     */
    auto eraspherAlgorythm(std::vector<std::uint32_t> &output, std::uint32_t from, std::uint32_t to) -> void;

    /*
     * EraspherAlgorythmError -- ошибка, которую возвращает [eraspherAlgorythm]
     */
    struct EraspherAlgorythmError: public std::exception {
        EraspherAlgorythmError();
        virtual ~EraspherAlgorythmError() {}

        virtual const char* what() const noexcept override;


        std::uint32_t from, to;
    };
}
