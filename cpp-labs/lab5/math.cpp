#include "lab5_math.hpp"

namespace lab5 {
    namespace math {

        std::ostream& operator<<(std::ostream& os, const HP &value) { return os << "HP " << (int) value.v; }
        std::ostream& operator<<(std::ostream& os, const MP &value) { return os << "MP " << (int) value.v; }
        std::ostream& operator<<(std::ostream& os, const CP &value) { return os << "CP " << (int) value.v; }
        std::ostream& operator<<(std::ostream& os, const Dur &value) { return os << "Dur " << (int) value.v; }
        std::ostream& operator<<(std::ostream& os, const Coord &value) { return os << "Coord " << (int) value.v; }

        std::istream& operator>>(std::istream& is, HP &value) {
            int v; is >> v;
            value.v = v;
            return is;
        }
        std::istream& operator>>(std::istream& is, MP &value) {
            int v; is >> v;
            value.v = v;
            return is;
        }
        std::istream& operator>>(std::istream& is, CP &value) {
            int v; is >> v;
            value.v = v;
            return is;
        }
        std::istream& operator>>(std::istream& is, Dur &value) {
            int v; is >> v;
            value.v = v;
            return is;
        }
        std::istream& operator>>(std::istream& is, Coord &value) {
            is >> value.v;
            return is;
        }

        HP operator+(const HP& fst, const HP& snd) { return HP ( fst.v + snd.v ); }
        MP operator+(const MP& fst, const MP& snd) { return MP ( fst.v + snd.v ); }
        CP operator+(const CP& fst, const CP& snd) { return CP ( fst.v + snd.v ); }
        Dur operator+(const Dur& fst, const Dur& snd) { return Dur ( fst.v + snd.v ); }
        Coord operator+(const Coord& fst, const Coord& snd) { return Coord ( fst.v + snd.v ); }

        HP operator-(const HP& fst, const HP& snd) { return HP ( fst.v - snd.v ); }
        MP operator-(const MP& fst, const MP& snd) { return MP ( fst.v - snd.v ); }
        CP operator-(const CP& fst, const CP& snd) { return CP ( fst.v - snd.v ); }
        Dur operator-(const Dur& fst, const Dur& snd) { return Dur ( fst.v - snd.v ); }
        Coord operator-(const Coord& fst, const Coord& snd) { return Coord ( fst.v - snd.v ); }

        HP operator*(const HP& fst, const HP& snd) { return HP ( fst.v * snd.v ); }
        MP operator*(const MP& fst, const MP& snd) { return MP ( fst.v * snd.v ); }
        CP operator*(const CP& fst, const CP& snd) { return CP ( fst.v * snd.v ); }
        Dur operator*(const Dur& fst, const Dur& snd) { return Dur ( fst.v * snd.v ); }
        Coord operator*(const Coord& fst, const Coord& snd) { return Coord ( fst.v * snd.v ); }

        HP operator*(const HP& fst, int v) { return HP ( fst.v * v ); }
        MP operator*(const MP& fst, int v) { return MP ( fst.v * v ); }
        CP operator*(const CP& fst, int v) { return CP ( fst.v * v ); }
        Dur operator*(const Dur& fst, int v) { return Dur ( fst.v * v ); }
        Coord operator*(const Coord& fst, int v) { return Coord ( fst.v * v ); }

        HP operator/(const HP& fst, int v) { return HP ( fst.v / v ); }
        MP operator/(const MP& fst, int v) { return MP ( fst.v / v ); }
        CP operator/(const CP& fst, int v) { return CP ( fst.v / v ); }
        Dur operator/(const Dur& fst, int v) { return Dur ( fst.v / v ); }
        Coord operator/(const Coord& fst, int v) { return Coord ( fst.v / v ); }

        HP operator/(const HP& fst, const HP& snd) { return HP ( fst.v / snd.v ); }
        MP operator/(const MP& fst, const MP& snd) { return MP ( fst.v / snd.v ); }
        CP operator/(const CP& fst, const CP& snd) { return CP ( fst.v / snd.v ); }
        Dur operator/(const Dur& fst, const Dur& snd) { return Dur ( fst.v / snd.v ); }
        Coord operator/(const Coord& fst, const Coord& snd) { return Coord ( fst.v / snd.v ); }

        bool operator==(const HP& fst, const HP& snd) { return fst.v == snd.v; }
        bool operator==(const MP& fst, const MP& snd) { return fst.v == snd.v; }
        bool operator==(const CP& fst, const CP& snd) { return fst.v == snd.v; }
        bool operator==(const Dur& fst, const Dur& snd) { return fst.v == snd.v; }
        bool operator==(const Coord& fst, const Coord& snd) { return fst.v == snd.v ; }

        bool operator>(const HP& fst, const HP& snd) { return fst.v > snd.v; }
        bool operator>(const MP& fst, const MP& snd) { return fst.v > snd.v; }
        bool operator>(const CP& fst, const CP& snd) { return fst.v > snd.v; }
        bool operator>(const Dur& fst, const Dur& snd) { return fst.v > snd.v; }
        bool operator>(const Coord& fst, const Coord& snd) { return fst.v > snd.v ; }

        bool operator<(const HP& fst, const HP& snd) { return fst.v < snd.v; }
        bool operator<(const MP& fst, const MP& snd) { return fst.v < snd.v; }
        bool operator<(const CP& fst, const CP& snd) { return fst.v < snd.v; }
        bool operator<(const Dur& fst, const Dur& snd) { return fst.v < snd.v; }
        bool operator<(const Coord& fst, const Coord& snd) { return fst.v < snd.v ; }

        bool operator>=(const HP& fst, const HP& snd) { return fst.v >= snd.v; }
        bool operator>=(const MP& fst, const MP& snd) { return fst.v >= snd.v; }
        bool operator>=(const CP& fst, const CP& snd) { return fst.v >= snd.v; }
        bool operator>=(const Dur& fst, const Dur& snd) { return fst.v >= snd.v; }
        bool operator>=(const Coord& fst, const Coord& snd) { return fst.v >= snd.v ; }

        bool operator<=(const HP& fst, const HP& snd) { return fst.v <= snd.v; }
        bool operator<=(const MP& fst, const MP& snd) { return fst.v <= snd.v; }
        bool operator<=(const CP& fst, const CP& snd) { return fst.v <= snd.v; }
        bool operator<=(const Dur& fst, const Dur& snd) { return fst.v <= snd.v; }
        bool operator<=(const Coord& fst, const Coord& snd) { return fst.v <= snd.v ; }

        TargetArea::TargetArea(void) : type(TargetArea::Single), radius(0) {}
        TargetArea::TargetArea(std::uint32_t value) : type(TargetArea::Splash), radius(value) {}

        std::ostream& operator<<(std::ostream& os, TargetArea a) {
            switch (a.type) {
                case TargetArea::Splash: return os << "TargetArea :: Splash;";
                case TargetArea::Single: return os << "TargetArea :: Single";
            }
        }

        Position operator+(const Position &fst, const Position &snd) {
            return { fst.x + snd.x, fst.y + snd.y };
        }
        Position operator-(const Position &fst, const Position &snd) {
            return { fst.x - snd.x, fst.y - snd.y };
        }
        Position operator*(const Position &fst, std::int32_t v) {
            return {  fst.x * v, fst.y * v };
        }
        std::ostream& operator<<(std::ostream &os, Position pos) {
            return os << "Position { " << pos.x << " " << pos.y << " }";
        }
        std::istream& operator>>(std::istream &is, Position pos) {
            return is >> pos.x >> pos.y;
        }
        Position operator==(const Position &fst, const Position &snd) {
            return fst.x == snd.x && fst.y == snd.y;
        }

        Size operator+(const Size &fst, const Size &snd) {
            return { fst.width + snd.width, fst.height + snd.height };
        }
        Size operator-(const Size &fst, const Size &snd) {
            return { fst.width - snd.width, fst.height - snd.height };
        }
        Size operator*(const Size &fst, std::int32_t v) {
            return {  fst.width * v, fst.height * v };
        }
        std::ostream& operator<<(std::ostream &os, Size pos) {
            return os << "Size { " << pos.width << " " << pos.height << " }";
        }
        std::istream& operator>>(std::istream &is, Size pos) {
            return is >> pos.width >> pos.height;
        }


        Rect::Rect(Size size): size { size }, pos {0, 0} {}
        Rect::Rect(Position pos, Size size): size { size }, pos { pos } {}
        bool Rect::chckInside(Position pos) {
            if ((pos.x >= this->pos.x + this->size.width) || (pos.x < this->pos.x) ||
                    (pos.y >= this->pos.y + this->size.height)|| (pos.y < this->pos.y))
                return false;
            else
                return true;
        }
    }
}
