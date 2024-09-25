#include <cstdint>
#include <iostream>
#include <ostream>
#include <vector>

namespace lab5 {
    template<typename T>
    inline T bounds(T value, T min, T max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    struct HP { std::uint8_t v; HP(int v): v(v) {}};
    struct MP { std::uint8_t v; MP(int v): v(v) {}};
    struct CP { std::uint8_t v; CP(int v): v(v) {}};
    struct Dur { std::uint16_t v; Dur(int v): v(v) {}};
    struct Coord { std::int32_t v; Coord(int v): v(v) {}};
    std::ostream& operator<<(std::ostream& os, const HP &value) { return os << "HP " << (int) value.v; }
    std::ostream& operator<<(std::ostream& os, const MP &value) { return os << "MP " << (int) value.v; }
    std::ostream& operator<<(std::ostream& os, const CP &value) { return os << "CP " << (int) value.v; }
    std::ostream& operator<<(std::ostream& os, const Dur &value) { return os << "Dur " << (int) value.v; }
    std::ostream& operator<<(std::ostream& os, const Coord &value) { return os << "Coord " << (int) value.v; }

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


    struct TargetArea {
        enum { Splash, Single } type;
        std::uint32_t radius;

        TargetArea(): type(Single), radius(0) {}
        TargetArea(std::uint32_t radius) : type(Splash), radius(radius) {}
    };

    std::ostream& operator<<(std::ostream& os, TargetArea a) {
        switch (a.type) {
            case TargetArea::Splash: return os << "TargetArea :: Splash { " << a.radius << " }";
            case TargetArea::Single: return os << "TargetArea :: Single";
        }
    }


    struct Position { Coord x, y; };
    Position operator+(const Position &fst, const Position &snd) {
        return Position { .x = fst.x + snd.x, .y = fst.y + snd.y };
    }
    Position operator-(const Position &fst, const Position &snd) {
        return Position { .x = fst.x - snd.x, .y = fst.y - snd.y };
    }
    Position operator*(const Position &fst, std::int32_t v) {
        return Position { .x = fst.x * v, .y = fst.y * v };
    }
    std::ostream& operator<<(std::ostream &os, Position pos) {
        return os << "Position { " << pos.x << " " << pos.y << " }";
    }

    struct Effect {
        enum {
            Heal,           // @hp
            Death,          // nothing
            Arise,          // @position
            Damage,         // @hp
            Poison,         // @hp
            LifeLink,       // @life_link
            SkipTurn,       // nothing
            ManaRestore,    // @mp
        } variant;

        union {
            int _;
            HP hp;
            MP mp;
            size_t mage_id;
            Position pos;
            struct { size_t mage_id; std::uint8_t percent; } life_link;
        };
    };


    std::ostream& operator<<(std::ostream &os, Effect e) {
        switch (e.variant) {
            case Effect::Heal:          return os << "Effect :: Heal { "   << e.hp << " }";
            case Effect::Death:         return os << "Effect :: Death";
            case Effect::Arise:         return os << "Effect :: Arise { " << e.pos << " }";
            case Effect::Damage:        return os << "Effect :: Damage { " << e.hp << " }";
            case Effect::Poison:        return os << "Effect :: Poison { " << e.hp << " }";
            case Effect::LifeLink:      return os << "Effect :: LifeLink { " << e.life_link.mage_id << " " << e.life_link.percent << " }";
            case Effect::SkipTurn:      return os << "Effect :: SkipTurn";
            case Effect::ManaRestore:   return os << "Effect :: ManaRestor { " << e.mp << " }";
        }
    }

    class Spell {
        MP mana_cost_m;
        CP cost_m;
        Dur apply_duration_m;
        Coord distance_m;
        TargetArea target_area_m;
        std::vector<Effect> effects_m;

        public:
            Spell() = delete;
            friend std::ostream& operator<<(std::ostream& os, const Spell &spell);

            virtual void setManaCost(MP value) { this->mana_cost_m = value; }
            virtual void setCost(CP value) { this->cost_m = value; }
            virtual void setApplyDurationM(Dur value) { this->apply_duration_m = value; }
            virtual void setDistanceM(Coord value) { this->distance_m = value; }
            virtual void setTargetAreaM(TargetArea value) { this->target_area_m = value; }

            class SpellBuilder {
                Spell *spell;
                SpellBuilder(Spell *spell) : spell(spell) {}

                public:
                    SpellBuilder() = delete;

                    SpellBuilder& withManaCost(MP mana_cost) {
                        this->spell->setManaCost(mana_cost);
                        return *this;
                    };
            };
            friend SpellBuilder;
    };

    std::ostream& operator<<(std::ostream& os, const Spell &spell) {
        os << "Spell { "
                << spell.mana_cost_m << " "
                << spell.cost_m << " "
                << spell.apply_duration_m << " "
                << spell.distance_m << " "
                << spell.target_area_m << " "
                << "Effects ";
        for (auto effect : spell.effects_m) os << effect << " ";
        return os << "}";
    }

    class LongRangeSpell: public Spell {
    };

    class ShortRangeSpell: public Spell {
    };

    class Support: public Spell {
    };


    void runLab5(void) {

        Effect damage { .variant = Effect::Damage, .hp = 10 };
        std::cout << damage << std::endl;

        Effect arise { .variant = Effect::Arise, .pos = Position { .x = Coord { 10 }, .y = Coord { 15 } } };
        std::cout << arise << std::endl;

        Effect death { .variant = Effect::Death };
        std::cout << death << std::endl;
    }
}
