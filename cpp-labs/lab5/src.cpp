#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <queue>
#include <string_view>
#include <unordered_map>
#include <vector>

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
        enum { Single, Splash } type;
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
            MageId mage_id;
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

                    SpellBuilder& withManaCost(MP value) { this->spell->setManaCost(value); return *this; }
                    SpellBuilder& withCost(CP value) { this->spell->setCost(value); return *this; }
                    SpellBuilder& withApplyDuration(Dur value) { this->spell->setApplyDuration(value); return *this; }
                    SpellBuilder& withEffectDuration(Dur value) { this->spell->setEffectDuration(value); return *this; }
                    SpellBuilder& withDistance(Coord value) { this->spell->setDistance(value); return *this; }
                    SpellBuilder& withTargetArea(TargetArea value) { this->spell->setTargetArea(value); return *this; }
                    SpellBuilder& withEffect(Effect effect) { this->spell->pushEffect(effect); return *this; }
                    Spell& mk(void) {
                        auto &ret = *this->spell->clone();
                        return ret;
                    }
                    Spell* alloc(void) {
                        auto ret = this->spell->clone();
                        return ret;
                    }
            };
            friend SpellBuilder;
    };

    std::ostream& operator<<(std::ostream& os, const Spell &spell) {
        os << "Spell { "
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

            virtual HP getHP(void) const override { return this->hp_m; };
            virtual MP getMP(void) const override { return this->mp_m; };
            virtual CP getCP(void) const override { return this->cp_m; };

            virtual void addEffect(Dur turns, Effect effects) override {
                this->curr_effects_m.push_back({ .effect = effects, .turns = turns });
            }
            virtual void addToHistory(Spell *spell) override {
                this->spell_history_m.push_back(spell);
            }

            virtual TargetType getType(void) const override { return TargetType::Active; }

            virtual Team getTeam(void) const override { return this->team_m; }
            friend std::ostream& operator<<(std::ostream& os, Mage mage);
    };
    std::ostream& operator<<(std::ostream& os, Mage mage) {
        os << "Mage { ( " << mage.hp_m << " ) ( " << mage.mp_m << " ) ( " << mage.cp_m << " ) ( " << mage.team_m << " ) ( " << mage.pos_m << " ) ( CurrEffects [ ";
        for (auto [turns, effect] : mage.curr_effects_m) os << "( " << turns << ", " << effect << " )";
        os << " ] ) ( KnownSpells [ ";
        for (auto spell : mage.known_spells_m) os << "( " << spell << " )";
        os << " ] ) ( History [ ";
        for (auto spell : mage.spell_history_m) os << "( " << spell << " )";
        return os << " ] )";
    }



    class MageGenerator {
        size_t last_idx = 0;
        public:
            std::pair<MageId, Mage> getMage(Team team) {
                Mage mage { team };
                return { last_idx++, mage };
            };
    };

    class LongRangeSpell: public Spell {
        LongRangeSpell(): Spell() {}
        public:
            static SpellBuilder build() { return SpellBuilder(new LongRangeSpell()); }

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
    };

    class ShortRangeSpell: public Spell {
        ShortRangeSpell(): Spell() {}
        public:
            static SpellBuilder build() { return SpellBuilder(new ShortRangeSpell()); }

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
    };

    class SupportSpell: public Spell {
        SupportSpell(): Spell() {}
        public:
            static SpellBuilder build() { return SpellBuilder(new SupportSpell()); }

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
    };

    class CurseSpell: public Spell {
        CurseSpell(): Spell() {}
        public:
            static SpellBuilder build() { return SpellBuilder(new CurseSpell()); }

            virtual bool checkCast(const ITarget& owner, const ITarget &target) const  noexcept override  {
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return false;
                if (owner.getTeam() == target.getTeam()) return false;

                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {

            };
            virtual Spell* clone(void) const override { return new CurseSpell(*this); }
            virtual void setDistance(Coord dist) override { this->distance_m = bounds<Coord>(dist, 50, 100); }
    };


    class Game {
        std::unordered_map<MageId, Mage> battle_ground_pull_m, graveyard_pull_m, exile_pull_m;
        CoordSize battle_ground_size_m;

        public:
            enum GameState { BlueTeamInit, OrangeTeamInit, InGame, Exit };

            Game() : battle_ground_size_m( { 0, 0 } ), game_state_m( BlueTeamInit ) {}

            GameState getState(void) const noexcept { return this->game_state_m; }
            void exit(void) noexcept { this->game_state_m = Exit; }

            bool shouldExit(void) {
                return this->game_state_m == Exit;
            }

        private:
            GameState game_state_m;
        friend std::ostream& operator<<(std::ostream& os, Game game);
    };
    std::ostream& operator<<(std::ostream& os, Game::GameState game_state) {
        os << "GameState ";
        switch (game_state) {
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

    void runLab5(void) {
        Game game;
        char buffer[256] { 0 };

        while (!game.shouldExit()) {
            std::cout << "\x1b[1;34m[ game ]\x1b[0m>";
            std::cout.flush();

            do std::cin.getline(buffer, 256); while (std::strlen(buffer) == 0);

            auto command = parseCommand(buffer);
            auto name = command[0];

            if (view_eq(name, "exit" ) || view_eq(name, "e" )) {
                game.exit();
            } else if (view_eq(name, "help" ) || view_eq(name, "h" )) {
                std::cout << " lab5 magic:\n\n"
                    << " DISPLAY COMMANDS: \n"
                    << "    - help, h              --- prints help command.\n"
                    << "    - print, b [target]    --- prints value of the target.\n"
                    << "                    Targets  can   be:  Mage [id], BattleGround,\n"
                    << "                    Graveyard, Exile.\n"
                    << "\n"
                    << " GAME CONTROLL COMMANDS: \n"
                    << "    - exit, e              --- exit lab5.\n"
                    << "\n";
            } else if (view_eq(name, "print" ) || view_eq(name, "p" )) {
                auto target_name = command[1];
                if (view_eq(target_name, "Mage")) {

                }
            } else {
                std::cout << "Wrong command: " << std::quoted(name) << std::endl;
            }
        }

    }
}
