#include "./lab1.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>

namespace lab1 {
    auto isPrime(std::uint32_t value) -> bool {
        if (value < 2) return true;

        for (std::uint32_t i = 2; i < value; i++) {
            if (value % i == 0) return false;
        }

        return true;
    }


    auto eraspherAlgorythm(std::vector<std::uint32_t> &output, std::uint32_t from, std::uint32_t to) -> void {
        if (from >= to) {
            std::cerr << "Invalid input parameters" << std::endl;
            throw new EraspherAlgorythmError();
        }

        std::vector<std::uint32_t> vec (to - from);

        const auto range_func = [=](void) {
            static std::uint32_t curr = from;
            return curr++;
        };
        std::generate(vec.begin(), vec.end(), range_func);

        std::copy_if(vec.begin(), vec.end(), std::back_inserter(output), isPrime);
    }

    EraspherAlgorythmError::EraspherAlgorythmError() { }
    const char* EraspherAlgorythmError::what() const noexcept {
        return "[lab1:eraspher_algorythm] Invalid input parameter.";
    }
}
