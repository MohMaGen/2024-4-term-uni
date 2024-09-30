#include <algorithm>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <utility>
#include <vector>
#include <raylib.h>

namespace lab5 {
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

    struct TargetArea {
        enum { Single = 0, Splash } type;
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


    using Position = std::pair<Coord, Coord>;
    using CoordSize = Position;
    Position operator+(const Position &fst, const Position &snd) {
        return { fst.first + snd.first, fst.second + snd.second };
    }
    Position operator-(const Position &fst, const Position &snd) {
        return { fst.first - snd.first, fst.second - snd.second };
    }
    Position operator*(const Position &fst, std::int32_t v) {
        return {  fst.first * v, fst.second * v };
    }
    std::ostream& operator<<(std::ostream &os, Position pos) {
        return os << "Position { " << pos.first << " " << pos.second << " }";
    }
    std::istream& operator>>(std::istream &is, Position pos) {
        return is >> pos.first >> pos.second;
    }

    struct Rect {
        Position pos;
        CoordSize size;
        Rect(CoordSize size) : pos{0, 0}, size{size} {}
        bool chckInside(Position pos) {
            if ((pos.first >= this->pos.first + this->size.first) ||
                    (pos.first < this->pos.first) ||
                    (pos.second >= this->pos.second + this->size.second)||
                    (pos.second < this->pos.second)) return false;
            return true;
        }
    };

    struct Effect {
        enum {
            Heal,           // @hp
            Death,          // nothing
            Arise,          // @hp
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
            MageId mage_id;
            struct { size_t mage_id; std::uint8_t percent; } life_link;
        };
    };

    std::istream& operator>>(std::istream &is, Effect& e) {
        std::string name;
        is >> name;

        if (name == "Heal") {
            e.variant = Effect::Heal;
            is >> e.hp;
        } else if (name == "Death") {
            e.variant = Effect::Death;
        } else if (name == "Arise") {
            e.variant = Effect::Arise;
        } else if (name == "Damage") {
            e.variant = Effect::Damage;
            is >> e.hp;
        } else if (name == "Poison") {
            e.variant = Effect::Poison;
            is >> e.hp;
        } else if (name == "LifeLink") {
            e.variant = Effect::LifeLink;
            int percent;
            is >> percent;
            e.life_link.percent = percent;
        } else if (name == "SkipTurn") {
            e.variant = Effect::SkipTurn;
        } else if (name == "ManaRestore") {
            e.variant = Effect::ManaRestore;
            is >> e.mp;
        } else {
            std::cin.setstate(std::ios_base::failbit);
        }

        return is;
    }


    std::ostream& operator<<(std::ostream &os, Effect e) {
        switch (e.variant) {
            case Effect::Heal:          return os << "Effect :: Heal { "   << e.hp << " }";
            case Effect::Death:         return os << "Effect :: Death";
            case Effect::Arise:         return os << "Effect :: Arise { " << e.hp << " }";
            case Effect::Damage:        return os << "Effect :: Damage { " << e.hp << " }";
            case Effect::Poison:        return os << "Effect :: Poison { " << e.hp << " }";
            case Effect::LifeLink:      return os << "Effect :: LifeLink { " << e.life_link.mage_id << " " << e.life_link.percent << " }";
            case Effect::SkipTurn:      return os << "Effect :: SkipTurn";
            case Effect::ManaRestore:   return os << "Effect :: ManaRestor { " << e.mp << " }";
        }
    }

    class ITarget;
    class Spell {
        protected:
            MP mana_cost_m = 1;
            CP cost_m = 1;
            Dur apply_duration_m = 1;
            Dur effect_duration_m = 1;
            Coord distance_m = 1;
            TargetArea target_area_m = 1;
            std::vector<Effect> effects_m = {};


        public:
            virtual ~Spell() {}

            friend std::ostream& operator<<(std::ostream& os, const Spell &spell);

            virtual Spell* clone(void) const = 0;

            virtual bool checkCast(const ITarget& owner, const ITarget &target) const noexcept = 0;
            virtual void cast(ITarget& owner, ITarget &target) const = 0;

            virtual void setManaCost(MP value) { this->mana_cost_m = bounds<MP>(value, 1, 100); }
            virtual void setCost(CP value) { this->cost_m = bounds<CP>(value, 1, 10); }
            virtual void setApplyDuration(Dur value) { this->apply_duration_m = bounds<Dur>(value, 1, 3600); }
            virtual void setEffectDuration(Dur value) { this->effect_duration_m = bounds<Dur>(value, 1, 10); }
            virtual void setDistance(Coord value) { this->distance_m = bounds<Coord>(value, 1, 100); }
            virtual void setTargetArea(TargetArea value) { this->target_area_m = value; }
            virtual void pushEffect(Effect effect) { this->effects_m.push_back(effect); }

            MP getManaCost(void) const noexcept { return this->mana_cost_m; }
            CP getCost(void) const noexcept { return this->cost_m; }
            Dur getApplyDuration(void) const noexcept { return this->apply_duration_m; }
            Dur getEffectDuration(void) const noexcept { return this->effect_duration_m; }
            Coord getDistance(void) const noexcept { return this->distance_m; }
            TargetArea getTargetArea(void) const noexcept { return this->target_area_m; }
            const std::vector<Effect> &getEffects(void) const noexcept { return this->effects_m; }

            class SpellBuilder {
                Spell *spell;

                public:
                    SpellBuilder(Spell *spell) : spell(spell) {}
                    SpellBuilder() = delete;
                    ~SpellBuilder() { delete spell; }

                    SpellBuilder* withManaCost(MP value) { this->spell->setManaCost(value); return this; }
                    SpellBuilder* withCost(CP value) { this->spell->setCost(value); return this; }
                    SpellBuilder* withApplyDuration(Dur value) { this->spell->setApplyDuration(value); return this; }
                    SpellBuilder* withEffectDuration(Dur value) { this->spell->setEffectDuration(value); return this; }
                    SpellBuilder* withDistance(Coord value) { this->spell->setDistance(value); return this; }
                    SpellBuilder* withTargetArea(TargetArea value) { this->spell->setTargetArea(value); return this; }
                    SpellBuilder* withEffect(Effect effect) { this->spell->pushEffect(effect); return this; }
                    Spell* alloc(void) {
                        auto ret = this->spell->clone();
                        return ret;
                    }
            };
            friend SpellBuilder;
        protected:
            virtual std::string spellType(void) const noexcept = 0;
    };

    std::ostream& operator<<(std::ostream& os, const Spell &spell) {
        os << "Spell " << spell.spellType() << " { "
                << spell.mana_cost_m << ", "
                << spell.cost_m << ", "
                << spell.apply_duration_m << ", "
                << spell.distance_m << ", "
                << spell.target_area_m << ", "
                << "Effects [ ";
        for (auto effect : spell.effects_m) os << effect << " ";
        os << "] ";
        return os << "}";
    }

    enum class Team { Orange, Blue, Neutral };
    enum class TargetType { Active, Wall, Cell };
    class ITarget {
        public:

            virtual Team getTeam(void) const = 0;
            virtual TargetType getType(void) const = 0;
            virtual HP getHP(void) const = 0;
            virtual MP getMP(void) const = 0;
            virtual CP getCP(void) const = 0;
            virtual Position getPos(void) const = 0;

            virtual void addEffect(Dur turns, Effect effect) = 0;
            virtual void addToHistory(Spell *) = 0;

            virtual ~ITarget() {}
    };

    std::ostream& operator<<(std::ostream& os, Team team) {
        switch (team) {
            case Team::Neutral: return os << "Team Neutral";
            case Team::Orange: return os << "Team Orange";
            case Team::Blue: return os << "Team Blue";
        }
    }

    std::ostream& operator<<(std::ostream& os, TargetType type) {
        switch (type) {
            case TargetType::Active: return os << "TargetType Active";
            case TargetType::Cell: return os << "TargetType Cell";
            case TargetType::Wall: return os << "TargetType Wall";
        }
    }


    class Mage: ITarget {
        HP hp_m;
        MP mp_m;
        CP cp_m;
        Team team_m;
        Position pos_m;

        struct EffectInTime { Effect effect; Dur turns; };
        std::vector<EffectInTime> curr_effects_m;

        std::vector<Spell*> spell_history_m;
        std::vector<Spell*> known_spells_m;

        public:
            explicit Mage(Team team):
                hp_m{ 100 },
                mp_m{ 100 },
                cp_m{ 5 },
                team_m{ team },
                pos_m{ Position { 0, 0 } },
                curr_effects_m{},
                spell_history_m{} {}
            ~Mage() {
                for (auto spell : spell_history_m) delete spell;
                for (auto spell : known_spells_m) delete spell;
            }

            virtual HP getHP(void) const override { return this->hp_m; };
            virtual MP getMP(void) const override { return this->mp_m; };
            virtual CP getCP(void) const override { return this->cp_m; };
            virtual Position getPos(void) const override { return this->pos_m; };

            virtual void addEffect(Dur turns, Effect effects) override {
                this->curr_effects_m.push_back({ .effect = effects, .turns = turns });
            }
            virtual void addToHistory(Spell *spell) override {
                this->spell_history_m.push_back(spell);
            }

            virtual TargetType getType(void) const override { return TargetType::Active; }

            virtual Team getTeam(void) const override { return this->team_m; }
            friend std::ostream& operator<<(std::ostream& os, Mage mage);

            class MageBuilder {
                Mage *mage;
                public:
                    MageBuilder(Team team) : mage(new Mage(team)) {}

                    MageBuilder& withPos(Position pos) {
                        this->mage->pos_m = pos;
                        return *this;
                    }

                    MageBuilder& appendSpell(Spell *spell) {
                        if (this->mage->known_spells_m.size() == 10) return *this;
                        this->mage->known_spells_m.push_back(spell);
                        return *this;
                    }

                    Mage* make(void) {
                        return new Mage(*this->mage);
                    }
                    ~MageBuilder() { delete this->mage; }
            };
            friend MageBuilder;
    };
    std::ostream& operator<<(std::ostream& os, Mage mage) {
        os << "Mage { ( " << mage.hp_m << " ) ( " << mage.mp_m << " ) ( "
            << mage.cp_m << " ) ( " << mage.team_m << " ) ( " << mage.pos_m << " ) ( CurrEffects [ ";
        for (auto [turns, effect] : mage.curr_effects_m) os << "( " << turns << ", " << effect << " )";
        os << " ] ) ( KnownSpells [ ";
        for (auto spell : mage.known_spells_m) os << "( " << *spell << " )";
        os << " ] ) ( History [ ";
        for (auto spell : mage.spell_history_m) os << "( " << *spell << " )";
        return os << " ] )";
    }



    class LongRangeSpell: public Spell {
        LongRangeSpell(): Spell() {}
        public:
            static SpellBuilder* build() { return new SpellBuilder(new LongRangeSpell()); }

            virtual Spell* clone(void) const override { return new LongRangeSpell(*this); }
            virtual bool checkCast(const ITarget& owner, const ITarget &target) const  noexcept override  {
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return 0;
                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {
            };

            virtual void setDistance(Coord dist) override { this->distance_m = bounds<Coord>(dist, 50, 100); }
            virtual void pushEffect(Effect effect) override { if (this->effects_m.size() < 1) this->effects_m.push_back(effect); }
            virtual void setEffectDuration(Dur value) override { this->effect_duration_m = 1; }
        protected:
            virtual std::string spellType(void) const noexcept override {
                return "Long";
            }
    };

    class ShortRangeSpell: public Spell {
        ShortRangeSpell(): Spell() {}
        public:
            static SpellBuilder* build() { return new SpellBuilder(new ShortRangeSpell()); }

            virtual Spell* clone(void) const override { return new ShortRangeSpell(*this); }
            virtual bool checkCast(const ITarget& owner, const ITarget &target) const  noexcept override  { 
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return false;

                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {

            };
            virtual void setDistance(Coord dist) override { this->distance_m = bounds<Coord>(dist, 1, 10); }
            virtual void pushEffect(Effect effect) override { if (this->effects_m.size() < 2) this->effects_m.push_back(effect); }
            virtual void setEffectDuration(Dur value) override { this->effect_duration_m = 1; }

        protected:
            virtual std::string spellType(void) const noexcept override {
                return "Short";
            }
    };

    class SupportSpell: public Spell {
        SupportSpell(): Spell() {}
        public:
            static SpellBuilder* build() { return new SpellBuilder(new SupportSpell()); }

            virtual bool checkCast(const ITarget& owner, const ITarget &target) const  noexcept override  {
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return false;
                if (owner.getTeam() != target.getTeam()) return false;

                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {
                for (auto effect : this->effects_m) {
                    target.addEffect(this->effect_duration_m, effect);
                }

            };
            virtual Spell* clone(void) const override { return new SupportSpell(*this); }
            virtual void setDistance(Coord dist) override { this->distance_m = bounds<Coord>(dist, 50, 100); }

        protected:
            virtual std::string spellType(void) const noexcept override {
                return "Support";
            }
    };

    class CurseSpell: public Spell {
        CurseSpell(): Spell() {}
        public:
            static SpellBuilder* build() { return new SpellBuilder(new CurseSpell()); }

            virtual bool checkCast(const ITarget& owner, const ITarget &target) const  noexcept override  {
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return false;
                if (owner.getTeam() == target.getTeam()) return false;

                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {

            };
            virtual Spell* clone(void) const override { return new CurseSpell(*this); }
            virtual void setDistance(Coord dist) override { this->distance_m = bounds<Coord>(dist, 50, 100); }

        protected:
            virtual std::string spellType(void) const noexcept override {
                return "Curse";
            }
    };


    /*
     * Main game class. Owns mages and process Game Commands.
     */
    class Game {
        std::unordered_map<MageId, Mage*> battle_ground_pull_m, graveyard_pull_m, exile_pull_m;
        CoordSize battle_ground_size_m;

        public:
            enum GameState { NoGame, BlueTeamInit, OrangeTeamInit, InGame, Exit };

            class CommandError: public std::exception {
                public:
                    std::string name;
                    CommandError(const std::string &name): name(name) {}

                    virtual const char * what() const noexcept override {
                        char *res = new char[name.size() + 1];
                        std::strcpy(res, name.c_str());
                        return res;
                    }

                    virtual ~CommandError() {}
            };

            /*
             * Commands that manipulate Games logics.
             */
            class GameCommand {
                friend Game;
                public:
                    virtual ~GameCommand() {}
                protected:

                    /*
                     * Set state of the game.
                     *
                     * @param state -- new sate
                     */
                    void setState(Game& game, GameState state) { game.game_state_m = state; }
                    /*
                     * Set size of the battle field and exile all mages outside the
                     * field.
                     *
                     * @param size -- new size.
                     */
                    void setSize(Game& game, CoordSize size) {
                        game.battle_ground_size_m = size;
                        std::vector<std::pair<MageId, Mage*>> mages_to_exile;

                        for (auto [id, mage]: game.battle_ground_pull_m) {
                            if (!Rect(size).chckInside(mage->getPos())) {
                                mages_to_exile.push_back({id, mage});
                            }
                        }

                        for (auto [id, mage] : mages_to_exile) {
                            game.battle_ground_pull_m.erase(id);
                            game.exile_pull_m.insert({id, mage});
                        }
                    }

                    /*
                     * Vector of all mages.
                     *
                     */
                    std::vector<std::pair<MageId, Mage*>> allMages(Game& game) {
                        std::vector<std::pair<MageId, Mage*>> mages;
                        for (auto mage: game.battle_ground_pull_m) mages.push_back(mage);
                        for (auto mage: game.graveyard_pull_m) mages.push_back(mage);
                        for (auto mage: game.exile_pull_m) mages.push_back(mage);
                        return mages;
                    }
                    /*
                     * Create vector of all mages that in game.
                     */
                    std::vector<std::pair<MageId, Mage*>> inGameMages(Game& game) {
                        std::vector<std::pair<MageId, Mage*>> mages;
                        for (auto mage: game.battle_ground_pull_m) mages.push_back(mage);
                        return mages;
                    }
                    /*
                     * Create vector of all dead mages.
                     *
                     */
                    std::vector<std::pair<MageId, Mage*>> deadMages(Game& game) {
                        std::vector<std::pair<MageId, Mage*>> mages;
                        for (auto mage: game.graveyard_pull_m) mages.push_back(mage);
                        return mages;
                    }
                    /*
                     * Create vector of all exiled mages.
                     *
                     */
                    std::vector<std::pair<MageId, Mage*>> exiledMages(Game& game) {
                        std::vector<std::pair<MageId, Mage*>> mages;
                        for (auto mage: game.exile_pull_m) mages.push_back(mage);
                        return mages;
                    }

                    /*
                     * Add new mage to game via mage generator.
                     *
                     */
                    void newMage(Game& game, Mage::MageBuilder& builder) {
                        auto [id, mage] = game.generator_m.getMage(builder);
                        game.battle_ground_pull_m.insert({id, mage});
                    }

                    /*
                     * Get size of the battle ground.
                     */
                    CoordSize getSize(Game& game) const { return game.battle_ground_size_m; }

                    /*
                     * Execute command. This function runned by Game.
                     *
                     *
                     * @param game -- The game reference, passed by @Game::callCommand(Game::GameCommand*).
                     *
                     * @throw must throw exception inherited of CommandError. But
                     *      will not break if throw somethign else.
                     */
                    virtual void operator()(Game &) = 0;

                    /*
                     * display to ostream.
                     */
                    virtual void display(std::ostream &os) const = 0;
                friend std::ostream& operator<<(std::ostream &os, GameCommand &cmd);
            };
            friend GameCommand;

            Game() : battle_ground_size_m( { 0, 0 } ), game_state_m( NoGame ) {}

            GameState getState(void) const noexcept { return this->game_state_m; }
            void exit(void) noexcept { this->game_state_m = Exit; }

            /*
             * Call command and write to history.
             */
            void callCommand(GameCommand *cmd) {
                try {
                    (*cmd)(*this);
                    this->commands_history_m.push_back(cmd);
                } catch (CommandError &e) {
                    std::cout << "Command " << std::quoted(e.name) << " failed with: " << e.what() << std::endl;
                } catch (std::exception &e) {
                    std::cout << "Command failed with: " << e.what() << std::endl;
                } catch (void *e) {
                    std::cout << "Command failed with unknown error" << std::endl;
                }
            }

            /*
             * Checks if game exit flag is stated.
             */
            bool shouldExit(void) {
                return this->game_state_m == Exit;
            }

            class MageGenerator {
                size_t last_idx = 0;
                public:
                std::pair<MageId, Mage*> getMage(Mage::MageBuilder& builder) {
                    return { last_idx++, builder.make() };
                };
            };


        private:
            GameState game_state_m;
            std::vector<GameCommand*> commands_history_m;
            MageGenerator generator_m;
        public:
            ~Game() {
                for (auto cmd : commands_history_m) delete cmd;
            }

        friend std::ostream& operator<<(std::ostream& os, Game game);
    };
    std::ostream& operator<<(std::ostream &os, Game::GameCommand &cmd) {
        cmd.display(os);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, Game::GameState game_state) {
        os << "GameState ";
        switch (game_state) {
            case Game::GameState::NoGame: return os << "NoGame";
            case Game::GameState::OrangeTeamInit: return os << "OrangeTeamInit";
            case Game::GameState::BlueTeamInit: return os << "BlueTeamInit";
            case Game::GameState::InGame: return os << "InGame";
            case Game::GameState::Exit: return os << "Exit";
        }
    }

    std::ostream& operator<<(std::ostream& os, Game game) {
        os << "Game {  " << game.game_state_m << " ) ( Battleground: " << game.battle_ground_size_m << " [ ";

        for (const auto [id, mage] : game.battle_ground_pull_m) {
            os << "( " << id << " " << mage << " )";
        }
        os << " ] ) ( Graveyard: [ ";
        for (const auto [id, mage] : game.graveyard_pull_m) {
            os << "( " << id << " " << mage << " )";
        }
        os << " ] ) ( Exile: [ ";
        for (const auto [id, mage] : game.exile_pull_m) {
            os << "( " << id << " " << mage << " )";
        }
        os << " ] )";

        return os;
    }



    /*
     * Exit command. Set game flag to exit.
     */
    class ExitCommand: public Game::GameCommand {
        protected:
            virtual void operator()(Game &game) override { game.exit(); }

            virtual void display(std::ostream &os) const override {
                os << "Exit Command";
            }
    };

    /*
     * Game Command to query through mages of game;
     *
     * @type Pred -- predicate to filter mages.
     * @type Iter -- type of resulting query containter.
     */
    class QueryCommand: public Game::GameCommand {
        public:
            enum Place { BG = 0b001, GY = 0b010, EL = 0b100 };
            using MagesQuery = std::vector<std::pair<MageId, Mage*>>;
            using Iter = std::back_insert_iterator<MagesQuery>;
            using Pred = std::function<bool (MageId,Mage*,Place)>;

            /*
             * Create Query.
             *
             * @param Iter iter - resulting iterator to insert mage.
             * @param Pred pred - predicate function to filter mages.
             *
             * @USAGE
             * ```cpp
             * QueryCommand::MagesQuery query;
             * game.callCommand(QueryCommand(std::back_inserter(query),
             *                  [](auto id, auto, auto) { return id % 2 == 0; }));
             *
             * // Mages with even id.
             * for (auto [id, mage] : query) {
             *      std::cout << "Id: " << id << ", " << "Mage: " << mage << std::endl;
             * }
             * ```
             */
            explicit QueryCommand(Iter iter, Pred pred): iter(iter), pred(pred) {}

        protected:
            virtual void operator()(Game &game) override {
                for (auto [id, mage] : this->inGameMages(game)) {
                    if (mage == nullptr) continue;
                    if (pred(id, mage, BG)) iter = { id, mage };
                }

                for (auto [id, mage] : this->deadMages(game)) {
                    if (mage == nullptr) continue;
                    if (pred(id, mage, GY)) iter = { id, mage };
                }

                for (auto [id, mage] : this->exiledMages(game)) {
                    if (mage == nullptr) continue;
                    if (pred(id, mage, EL)) iter = { id, mage };
                }

            }

            virtual void display(std::ostream &os) const override {
                os << "Query Command";
            }

        private:
            Iter iter;
            Pred pred;
    };

    class NewGameCommand: public Game::GameCommand {
        public:
            NewGameCommand() {}
        protected:
            virtual void operator()(Game &game) override {
                this->setState(game, Game::GameState::BlueTeamInit);
            }
            void display(std::ostream &os) const override {
                os << "NewGame";
            }
    };

    class AddMage: public Game::GameCommand {
        Mage::MageBuilder& builder;

        public:
            AddMage(Mage::MageBuilder& builder): builder(builder) {}
        protected:
            virtual void operator()(Game &game) override {
                this->newMage(game, this->builder);
            }
            void display(std::ostream &os) const override {
                os << "Add Mage";
            }
    };

    class NextTeamCommand: public Game::GameCommand {
        public:
            NextTeamCommand(void) {}
        protected:
            virtual void operator()(Game &game) override {
                if (game.getState() == Game::GameState::BlueTeamInit)
                    this->setState(game, Game::GameState::OrangeTeamInit);
            }
            void display(std::ostream &os) const override {
                os << "Add Mage";
            }
    };

    class SetGameSizeCommand: public Game::GameCommand {
        CoordSize size;
        public:
            SetGameSizeCommand(CoordSize size): size(size) {}

        protected:
            virtual void operator()(Game &game) override {
                this->setSize(game, this->size);
            }
            void display(std::ostream &os) const override {
                os << "Set Size";
            }

    };

    class GetBattleFieldCOmmand: public Game::GameCommand {
        public:
            using BattleField = std::vector<std::pair<MageId, Mage*>>;
            using Iter = std::back_insert_iterator<BattleField>;
            GetBattleFieldCOmmand(Iter iter, CoordSize &size):  iter(iter), size(size) {}

        protected:
            virtual void operator()(Game &game) override {
                QueryCommand::MagesQuery query;
                game.callCommand(new QueryCommand(std::back_inserter(query),
                            [](auto, auto, auto place){ return place == QueryCommand::BG;}));
                CoordSize game_size = this->getSize(game);
                this->size = game_size;

                for (size_t i = 0; i < game_size.second; i++) {
                    for (size_t j = 0; j < game_size.first; j++) {
                        auto res = std::find_if(query.begin(), query.end(), [i, j](auto pair){
                                    return pair.second->getPos() == Position { i, j };
                                });
                        if (res == query.end()) {
                            this->iter = std::pair { 0, nullptr };
                        } else {
                            this->iter = std::pair { res->first, res->second };
                        }
                    }
                }
            }
            void display(std::ostream &os) const override {
                os << "Set Size";
            }

        private:
            Iter iter;
            CoordSize &size;
    };


    namespace gui {
        struct Color {
            union {
                ::Color rgba;
                std::uint32_t hex;
            };
            ::Color rl() { return this->rgba; }
            Color(std::uint32_t hex) {
                uint8_t r,g,b,a;
                if (hex > 0xffffff) {
                    r = hex / 0x1000000; hex %= 0x1000000;
                    g = hex / 0x10000; hex %= 0x10000;
                    b = hex / 0x100; hex %= 0x100;
                    a = hex;
                } else if (hex > 0xffff) {
                    r = hex / 0x10000; hex %= 0x10000;
                    g = hex / 0x100; hex %= 0x100;
                    b = hex;
                    a = 0xff;
                } else if (hex > 0xfff) {
                    r = (hex / 0x1000) * 0x10 + hex / 0x1000; hex %= 0x1000;
                    g = (hex / 0x100) * 0x10 + hex / 0x100; hex %= 0x100;
                    b = (hex / 0x10) * 0x10 + hex / 0x10; hex %= 0x10;
                    a = hex * 0x10 + hex;
                } else if (hex > 0xff) {
                    r = (hex / 0x100) * 0x10 + hex / 0x100; hex %= 0x100;
                    g = (hex / 0x10) * 0x10 + hex / 0x10; hex %= 0x10;
                    b = hex * 0x10 + hex;
                    a = 0xFF;
                } else if (hex > 0xf) {
                    r = hex;
                    g = hex;
                    b = hex;
                    a = hex;
                } else {
                    r = hex * 0x10 + hex;
                    g = hex * 0x10 + hex;
                    b = hex * 0x10 + hex;
                    a = hex * 0x10 + hex;
                }
                this->rgba = ::Color { r, g, b, a };
            }

            ::Color operator+() {
                return this->rgba;
            }
        };

        void gui_main() {
            InitWindow(800, 600, "( Lab5: Mages )");
            SetWindowState(FLAG_WINDOW_RESIZABLE);

            while(!WindowShouldClose()) {
                BeginDrawing();
                ClearBackground(+Color(0x272E33FF));
                DrawRectangle(320, 240, 160, 120, +Color(0xFFA2B3));
                EndDrawing();
            }
            CloseWindow();
        }
    }

    namespace tty {
        std::vector<std::string_view> parseCommand(const char *buffer) {
            std::vector<std::string_view> vec;
            size_t start = 0, curr = 0;

            bool parse_string = false;

            const auto push = [&vec, &buffer, &curr, &start]() {
                if (curr != start) vec.push_back({ buffer + start, curr - start });
                start = curr + 1;
            };
            const auto switch_parse_string = [&] () {
                    parse_string = true;
                    push();
            };

            do {
                if (!parse_string) {
                    if (buffer[curr] == '"') switch_parse_string();
                    if (buffer[curr] == ' ') push();
                } else if (buffer[curr] == '"') switch_parse_string();
            } while (buffer[curr++] != '\0');

            if (curr != start) push();

            return vec;
        }

        bool view_eq(std::string_view view, const char *value) {
            return std::equal(view.begin(), view.end(), std::string_view{value}.begin());
        }


        const char HELP_MSG[] = " lab5 magic:\n\n"
            "\x1b[1;34mUSAGE:\x1b[0m\n"
            " [command] ([command_args])\n"
            "\n"
            "\x1b[1;34mDISPLAY COMMANDS:\x1b[0m \n"
            "    - help, h              --- prints help command.\n"
            "    - print, b [<target>]  --- prints value of the target.\n"
            "                    Targets  can   be:  Mage [id], BattleGround,\n"
            "                    Graveyard, Exile, All.\n"
            "    - state                --- prints current game state\n"
            "    - battle_field         --- prints battle field with mages.\n"
            "\n"
            "\x1b[1;34mGAME INIT COMMANDS:\x1b[0m ( only in InitBlue & InitOrange states )\n"
            "    - next_team            --- finish creation of current team\n"
            "                    and enter to next.\n"
            "    - curr_team            --- print current team.\n"
            "    - gen_mages <n>        --- generate <n> mages for current team\n"
            "    - make_mage            --- run mage builder.\n"
            "\n"
            "\x1b[1;34mUI COMMANDS:\x1b[0m\n"
            "    - clear                --- clear\n"
            "    - gui                  --- turn into gui mod.\n"
            "\n"
            "\x1b[1;34mGAME CONTROLL COMMANDS:\x1b[0m\n"
            "    - new_game             --- start game\n"
            "    - set_size <width> <height>\n"
            "                           --- set size of the battle field.\n "
            "                    This will exile all mages outside of the\n"
            "                    new battle field.\n"
            "    - exit, e              --- exit lab5.\n"
            "\n";

        // process terminal input and run game commands.
        void executeTTYCommand(std::vector<std::string_view> command, Game &game) {
            if (command.size() == 0) {
                std::cout << std::endl;
                return;
            }
            auto name = command[0];

            if (view_eq(name, "exit" ) || view_eq(name, "e" )) {
                game.callCommand(new ExitCommand());

            } if (view_eq(name, "clear") || view_eq(name, "\x0C")) {
                std::cout << "\x1b[1;1H\x1b[2J";

            } else if (view_eq(name, "gui")) {
                gui::gui_main();

            } else if (view_eq(name, "help" ) || view_eq(name, "h" )) {
                std::cout << HELP_MSG << std::endl;

            } else if (view_eq(name, "state")) {
                std::cout << game.getState() << std::endl;

            } else if (view_eq(name, "battle_field")) {
                GetBattleFieldCOmmand::BattleField bf;
                CoordSize size { 0, 0 };

                game.callCommand(new GetBattleFieldCOmmand(std::back_inserter(bf), size));

                const size_t cell_size = 6;
                const size_t indent = 5;
                const auto nl = [](void){
                    std::cout << "\n" << std::string(indent, ' ');
                };
                const auto cnt = [](const std::string &str, size_t view){
                    if (view <= str.length()) {
                        std::cout << std::string_view(str.data(), view);
                    } else {
                        size_t left_padding = (view - str.length()) / 2;
                        size_t right_padding = (view - str.length()) / 2 + (view - str.length()) % 2;
                        std::cout << std::string(left_padding, ' ') << str << std::string(right_padding, ' ');
                    }
                };
                const auto clear  = [](){ std::cout << "\x1b[0m"; };
                const auto color = [](int id){ std::cout << "\x1b[3" << id << "m"; };
                const auto bg_color = [](int id){ std::cout << "\x1b[4" << id << "m"; };
                std::cout << "Battle field " << size.first << "x" << size.second << std::endl;
                nl();
                for (size_t i = 0; i < size.second; i++) {
                    for (size_t j = 0; j < size.first; j++) {
                        if ((i + j) % 2) {
                            bg_color(7);
                        } else {
                            clear();
                        }
                        const auto chck = [i, j](auto pair) {
                            if (pair.second == nullptr) return false;
                            return pair.second->getPos() == Position { i, j };
                        };
                        auto res = std::find_if(bf.begin(), bf.end(), chck);

                        if (res == bf.end()) {
                            std::cout << std::string(cell_size, ' ');
                            continue;
                        }
                            if (res->second->getTeam() == Team::Blue) {
                                color(4);
                            } else {
                                color(1);
                            }
                            cnt(std::to_string(res->first), cell_size);
                    }
                    clear();
                    nl();
                }
                clear();
                std::cout << std::endl;

            } else if (view_eq(name, "new_game")) {
                game.callCommand(new NewGameCommand());

            } else if (view_eq(name, "next_team")) {
                game.callCommand(new NextTeamCommand());

            } else if (view_eq(name, "set_size")) {
                CoordSize size { 0, 0 };
                if (command.size() < 2 ||
                        std::from_chars(command[1].begin(), command[1].end(), size.first.v).ec != std::errc{}) {
                    std::cout << "Failed to parse <width>.\n" << HELP_MSG << std::endl;
                    return;
                }
                if (command.size() < 3 ||
                        std::from_chars(command[2].begin(), command[2].end(), size.second.v).ec != std::errc{}) {
                    std::cout << "Failed to parse <height>.\n" << HELP_MSG << std::endl;
                    return;
                }
                if (!std::cin) {
                    std::cout << "Invalid size input.\n" << HELP_MSG << std::endl;
                    return;
                }
                std::cout << size << std::endl;
                game.callCommand(new SetGameSizeCommand(size));

            } else if (view_eq(name, "curr_team")) {
                using GameState = Game::GameState;
                switch (game.getState()) {
                    case GameState::BlueTeamInit: std::cout << "Blue Team" << std::endl; break;
                    case GameState::OrangeTeamInit: std::cout << "Orange Team" << std::endl; break;
                    default:
                        std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                }

            } else if (view_eq(name, "gen_team")) {
                Team curr_team_init;

                using GameState = Game::GameState;
                switch (game.getState()) {
                    case GameState::BlueTeamInit: curr_team_init = Team::Blue; break;
                    case GameState::OrangeTeamInit: curr_team_init = Team::Orange; break;
                    default:
                        std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                        return;
                }

                if (command.size() == 1) {
                    std::cout << "Enter amount of mages ot generate\n" << HELP_MSG << std::endl;
                    return;
                }

                int n;
                if (std::from_chars(command[1].begin(), command[1].end(), n).ec != std::errc{}) {
                    std::cout << "Failed to parse int <n>" << std::endl;
                    return;
                }
                Mage::MageBuilder builder (curr_team_init);
                if (curr_team_init == Team::Blue) {
                }


            } else if (view_eq(name, "make_mage")) {
                Team curr_team_init;

                using GameState = Game::GameState;
                switch (game.getState()) {
                    case GameState::BlueTeamInit: curr_team_init = Team::Blue; break;
                    case GameState::OrangeTeamInit: curr_team_init = Team::Orange; break;
                    default:
                        std::cout << "GAME INIT COMMANDS allowed only in InitBlue and InitOrange states." << std::endl;
                        return;
                }

                Mage::MageBuilder builder (curr_team_init);
                std::cout << "\x1b[1;34menter pos: `x y`\x1b[0m> ";
                Position pos { 0, 0 };
                std::cin >> pos;
                builder.withPos(pos);


                for (size_t i = 0; i < 2; i++) {
                    std::cout << "\x1b[1;34mchoose spell type " << i << "\x1b[0m> ";
                    std::string spell_type;
                    std::cin >> spell_type;

                    Spell::SpellBuilder* sb;
                    if (spell_type == "Long" || spell_type == "LongDist")
                        sb = LongRangeSpell::build();
                    else if (spell_type == "Short" || spell_type == "ShortDist")
                        sb = ShortRangeSpell::build();
                    else if (spell_type == "Support")
                        sb = SupportSpell::build();
                    else if (spell_type == "Curse")
                        sb = CurseSpell::build();
                    else {
                        std::cout << "Wrong Spell Type. Choose one of LongDist, ShortDist, Support, Curse." << std::endl;
                        i--;
                        continue;
                    }
                    size_t count = rand() % 5 + 1;
                    for (size_t i = 0; i < count; i++) {
                        Spell::SpellBuilder sb_cp (sb->alloc());
                        sb_cp.withManaCost(rand()%100 + 1)
                            ->withCost(rand()%10 + 1)
                            ->withApplyDuration(rand()%3600 + 1)
                            ->withEffectDuration(rand()%10 + 1)
                            ->withDistance(rand()%100 + 1)
                            ->withTargetArea([]{ return (rand()%2) ? TargetArea(rand()%10+1) : TargetArea(); }());

                        size_t count = rand()%10 + 1;
                        for (size_t i = 0; i <  count; i++)
                            sb_cp.withEffect([]{
                                switch (rand()%8) {
                                    case 0: return Effect { .variant = Effect::Heal, .hp = rand()%20 + 5};
                                    case 1: return Effect { .variant = Effect::Death };
                                    case 2: return Effect { .variant = Effect::Arise, .hp = rand()%20 + 20};
                                    case 3: return Effect { .variant = Effect::Damage, .hp = rand()%20 + 5};
                                    case 4: return Effect { .variant = Effect::Poison, .hp = rand()%5 + 1};
                                    case 5: return Effect { .variant = Effect::LifeLink,
                                        .life_link { .mage_id = 0, .percent = static_cast<uint8_t>(rand()%5 + 2)}};
                                    case 6: return Effect { .variant = Effect::SkipTurn };
                                    case 7:
                                    default: return Effect { .variant = Effect::ManaRestore, .mp = rand()%5 + 1};
                                }
                            }());

                        builder.appendSpell(sb_cp.alloc());
                    }
                }

                game.callCommand(new AddMage(builder));

            } else if (view_eq(name, "print" ) || view_eq(name, "p" )) {
                auto query_func = [&] -> QueryCommand::Pred {
                    const auto err = [](MageId, Mage*, QueryCommand::Place) { return false; };

                    if (command.size() < 2) {
                        return [](auto, auto, auto){return true;};
                    }
                    auto target_name = command[1];

                    if (view_eq(target_name, "Mage")) {
                        if (command.size() < 3) {
                            std::cout << "\nmust specify mage id to print mage... see help.\n" << HELP_MSG << std::endl;
                            return err;
                        }

                        MageId id;
                        if (std::from_chars(command[2].begin(), command[2].end(), id).ec != std::errc()) {
                            std::cout << "\nwrong Mage id: " << id << std::endl;
                            return err;
                        }
                        return [id](auto curr_id, auto, auto) { return id == curr_id; };
                    }
                    if (view_eq(target_name, "All"))
                        return [](auto, auto, auto) { return true; };

                    if (view_eq(target_name, "BattleGround") || view_eq(target_name, "BG"))
                        return [](auto, auto, auto place) { return place == QueryCommand::BG; };

                    if (view_eq(target_name, "Graveyard") || view_eq(target_name, "GY"))
                        return [](auto, auto, auto place) { return place == QueryCommand::GY; };

                    if (view_eq(target_name, "Exile") || view_eq(target_name, "Exile"))
                        return [](auto, auto, auto place) { return place == QueryCommand::EL; };

                    return err;
                }();

                QueryCommand::MagesQuery query;
                auto iter = std::back_inserter(query);
                game.callCommand(new QueryCommand(iter, query_func));

                if (query.size() == 0) {
                    std::cout << "Nothing matches query." << std::endl;
                } else {
                    for (auto [id, mage] : query)
                        if (mage != nullptr) std::cout << "   :: " << id << " " << *mage << std::endl;
                }

            } else {
                std::cout << "Wrong command: " << std::quoted(name) << std::endl;
                std::cout << HELP_MSG << std::endl;
            }
        }
    }

    void runLab5(void) {
        Game game;
        char buffer[256] { 0 };

        while (!game.shouldExit()) {
            std::cout << "\x1b[1;34mgame\x1b[0m> ";
            std::cout.flush();

            do std::cin.getline(buffer, 256); while (std::strlen(buffer) == 0);

            auto command = tty::parseCommand(buffer);
            tty::executeTTYCommand(command, game);
        }

    }
}

#ifdef LAB5_GUI
int main() {
    lab5::gui::gui_main();
    return 0;
}
#endif
