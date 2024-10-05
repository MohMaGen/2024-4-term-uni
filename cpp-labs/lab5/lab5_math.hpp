#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>


namespace lab5 {
    namespace math {
        template<typename T>
        inline T bounds(T value, T min, T max) {
            if (value < min) return min;
            if (value > max) return max;
            return value;
        }

        using MageId = size_t;

        struct HP { std::uint8_t v; HP(int v): v(v) {}};
        struct MP { std::uint8_t v; MP(int v): v(v) {}};
        struct CP { std::uint8_t v; CP(int v): v(v) {}};
        struct Dur { std::uint16_t v; Dur(int v): v(v) {}};
        struct Coord { std::int32_t v; Coord(int v): v(v) {}};

        std::ostream& operator<<(std::ostream& os, const HP &value);
        std::ostream& operator<<(std::ostream& os, const MP &value);
        std::ostream& operator<<(std::ostream& os, const CP &value);
        std::ostream& operator<<(std::ostream& os, const Dur &value);
        std::ostream& operator<<(std::ostream& os, const Coord &value);

        std::istream& operator>>(std::istream& is, HP &value);
        std::istream& operator>>(std::istream& is, MP &value);
        std::istream& operator>>(std::istream& is, CP &value);
        std::istream& operator>>(std::istream& is, Dur &value);
        std::istream& operator>>(std::istream& is, Coord &value);

        HP operator+(const HP& fst, const HP& snd);
        MP operator+(const MP& fst, const MP& snd);
        CP operator+(const CP& fst, const CP& snd);
        Dur operator+(const Dur& fst, const Dur& snd);
        Coord operator+(const Coord& fst, const Coord& snd);

        HP operator-(const HP& fst, const HP& snd);
        MP operator-(const MP& fst, const MP& snd);
        CP operator-(const CP& fst, const CP& snd);
        Dur operator-(const Dur& fst, const Dur& snd);
        Coord operator-(const Coord& fst, const Coord& snd);

        HP operator*(const HP& fst, const HP& snd);
        MP operator*(const MP& fst, const MP& snd);
        CP operator*(const CP& fst, const CP& snd);
        Dur operator*(const Dur& fst, const Dur& snd);
        Coord operator*(const Coord& fst, const Coord& snd);

        HP operator*(const HP& fst, int v);
        MP operator*(const MP& fst, int v);
        CP operator*(const CP& fst, int v);
        Dur operator*(const Dur& fst, int v);
        Coord operator*(const Coord& fst, int v);

        HP operator/(const HP& fst, int v);
        MP operator/(const MP& fst, int v);
        CP operator/(const CP& fst, int v);
        Dur operator/(const Dur& fst, int v);
        Coord operator/(const Coord& fst, int v);

        HP operator/(const HP& fst, const HP& snd);
        MP operator/(const MP& fst, const MP& snd);
        CP operator/(const CP& fst, const CP& snd);
        Dur operator/(const Dur& fst, const Dur& snd);
        Coord operator/(const Coord& fst, const Coord& snd);

        bool operator==(const HP& fst, const HP& snd);
        bool operator==(const MP& fst, const MP& snd);
        bool operator==(const CP& fst, const CP& snd);
        bool operator==(const Dur& fst, const Dur& snd);
        bool operator==(const Coord& fst, const Coord& snd);

        bool operator>(const HP& fst, const HP& snd);
        bool operator>(const MP& fst, const MP& snd);
        bool operator>(const CP& fst, const CP& snd);
        bool operator>(const Dur& fst, const Dur& snd);
        bool operator>(const Coord& fst, const Coord& snd);

        bool operator<(const HP& fst, const HP& snd);
        bool operator<(const MP& fst, const MP& snd);
        bool operator<(const CP& fst, const CP& snd);
        bool operator<(const Dur& fst, const Dur& snd);
        bool operator<(const Coord& fst, const Coord& snd);

        bool operator>=(const HP& fst, const HP& snd);
        bool operator>=(const MP& fst, const MP& snd);
        bool operator>=(const CP& fst, const CP& snd);
        bool operator>=(const Dur& fst, const Dur& snd);
        bool operator>=(const Coord& fst, const Coord& snd);

        bool operator<=(const HP& fst, const HP& snd);
        bool operator<=(const MP& fst, const MP& snd);
        bool operator<=(const CP& fst, const CP& snd);
        bool operator<=(const Dur& fst, const Dur& snd);
        bool operator<=(const Coord& fst, const Coord& snd);

        struct TargetArea {
            enum { Splash, Single } type;
            std::uint32_t radius;

            TargetArea();
            TargetArea(std::uint32_t radius);
        };

        std::ostream& operator<<(std::ostream& os, TargetArea a);


        struct Position { Coord x, y; };
        Position operator+(const Position &fst, const Position &snd);
        Position operator-(const Position &fst, const Position &snd);
        Position operator*(const Position &fst, std::int32_t v);
        std::ostream& operator<<(std::ostream &os, Position pos);
        std::istream& operator>>(std::istream &is, Position pos);
        bool operator==(const Position &fst, const Position &snd);

        struct Size { Coord width, height; };
        Size operator+(const Size &fst, const Size &snd);
        Size operator-(const Size &fst, const Size &snd);
        Size operator*(const Size &fst, std::int32_t v);
        std::ostream& operator<<(std::ostream &os, Size pos);
        std::istream& operator>>(std::istream &is, Size pos);
        bool operator==(const Size &fst, const Size &snd);

        struct Rect {
            Position pos;
            Size size;

            Rect(Size size);
            Rect(Position pos, Size size);

            bool chckInside(Position pos);
            Position getRand(void) const;
        };
    }
}
