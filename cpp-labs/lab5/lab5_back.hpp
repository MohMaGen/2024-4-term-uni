#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <lab5_math.hpp>
#include <raylib.h>
#include <vector>

namespace lab5 {
    namespace back {
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
                math::HP hp;
                math::MP mp;
                math::MageId mage_id;
                struct { size_t mage_id; std::uint8_t percent; } life_link;
            };
        };
        std::istream& operator>>(std::istream &is, Effect& e);
        std::ostream& operator<<(std::ostream &os, Effect e);



        class ITarget;
        class Spell {
            protected:
                math::MP mana_cost_m = 1;
                math::CP cost_m = 1;
                math::Dur apply_duration_m = 1;
                math::Dur effect_duration_m = 1;
                math::Coord distance_m = 1;
                math::TargetArea target_area_m = 1;
                std::vector<Effect> effects_m = {};


            public:
                virtual ~Spell() {}
                friend std::ostream& operator<<(std::ostream& os, const Spell &spell);

                virtual Spell* clone(void) const = 0;

                virtual bool checkCast(const ITarget& owner, const ITarget &target) const noexcept = 0;
                virtual void cast(ITarget& owner, ITarget &target) const = 0;

                virtual void setManaCost(math::MP value) { this->mana_cost_m = bounds<math::MP>(value, 1, 100); }
                virtual void setCost(math::CP value) { this->cost_m = bounds<math::CP>(value, 1, 10); }
                virtual void setApplyDuration(math::Dur value) { this->apply_duration_m = bounds<math::Dur>(value, 1, 3600); }
                virtual void setEffectDuration(math::Dur value) { this->effect_duration_m = bounds<math::Dur>(value, 1, 10); }
                virtual void setDistance(math::Coord value) { this->distance_m = bounds<math::Coord>(value, 1, 100); }
                virtual void setTargetArea(math::TargetArea value) { this->target_area_m = value; }
                virtual void pushEffect(Effect effect) { this->effects_m.push_back(effect); }

                math::MP getManaCost(void) const noexcept { return this->mana_cost_m; }
                math::CP getCost(void) const noexcept { return this->cost_m; }
                math::Dur getApplyDuration(void) const noexcept { return this->apply_duration_m; }
                math::Dur getEffectDuration(void) const noexcept { return this->effect_duration_m; }
                math::Coord getDistance(void) const noexcept { return this->distance_m; }
                math::TargetArea getTargetArea(void) const noexcept { return this->target_area_m; }
                const std::vector<Effect> &getEffects(void) const noexcept { return this->effects_m; }

                class SpellBuilder {
                    Spell *spell;

                    public:
                    SpellBuilder(Spell *spell) : spell(spell) {}
                    SpellBuilder() = delete;
                    ~SpellBuilder() { delete spell; }

                    SpellBuilder* withManaCost(math::MP value) { this->spell->setManaCost(value); return this; }
                    SpellBuilder* withCost(math::CP value) { this->spell->setCost(value); return this; }
                    SpellBuilder* withApplyDuration(math::Dur value) { this->spell->setApplyDuration(value); return this; }
                    SpellBuilder* withEffectDuration(math::Dur value) { this->spell->setEffectDuration(value); return this; }
                    SpellBuilder* withDistance(math::Coord value) { this->spell->setDistance(value); return this; }
                    SpellBuilder* withTargetArea(math::TargetArea value) { this->spell->setTargetArea(value); return this; }
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
        std::ostream& operator<<(std::ostream& os, const Spell &spell);


        enum class Team { Orange, Blue, Neutral };
        enum class TargetType { Active, Wall, Cell };
        class ITarget {
            public:

                virtual Team getTeam(void) const = 0;
                virtual TargetType getType(void) const = 0;
                virtual math::HP getHP(void) const = 0;
                virtual math::MP getMP(void) const = 0;
                virtual math::CP getCP(void) const = 0;
                virtual math::Position getPos(void) const = 0;

                virtual void addEffect(math::Dur turns, Effect effect) = 0;
                virtual void addToHistory(Spell *) = 0;

                virtual ~ITarget() {}
        };

        std::ostream& operator<<(std::ostream& os, Team team);
        std::ostream& operator<<(std::ostream& os, TargetType type);

        class Mage: ITarget {
            math::HP _hp;
            math::MP _mp;
            math::CP _cp;
            Team _team;
            math::Position _pos;

            struct EffectInTime { Effect effect; math::Dur turns; };
            std::vector<EffectInTime> _curr_effects;

            std::vector<Spell*> _spell_history;
            std::vector<Spell*> _known_spells;

            public:
            explicit Mage(Team team):
                _hp{ 100 },
                _mp{ 100 },
                _cp{ 5 },
                _team{ team },
                _pos{ math::Position { 0, 0 } },
                _curr_effects{},
                _spell_history{} {}
            ~Mage() {
                for (auto spell : _spell_history) delete spell;
                for (auto spell : _known_spells) delete spell;
            }

            std::vector<Spell*> getAvailableSpells(void);

            virtual math::HP getHP(void) const override { return _hp; };
            virtual math::MP getMP(void) const override { return _mp; };
            virtual math::CP getCP(void) const override { return _cp; };
            virtual math::Position getPos(void) const override { return _pos; };

            virtual void addEffect(math::Dur turns, Effect effects) override {
                _curr_effects.push_back({ .effect = effects, .turns = turns });
            }
            virtual void addToHistory(Spell *spell) override {
                _spell_history.push_back(spell);
            }


            virtual TargetType getType(void) const override { return TargetType::Active; }

            virtual Team getTeam(void) const override { return _team; }
            friend std::ostream& operator<<(std::ostream& os, Mage mage);

            class MageBuilder {
                Mage *_mage;
                public:
                MageBuilder(Team team) : _mage(new Mage(team)) {}

                MageBuilder& withPos(math::Position pos) {
                    _mage->_pos = pos;
                    return *this;
                }

                MageBuilder& appendSpell(Spell *spell) {
                    if (_mage->_known_spells.size() == 10) return *this;
                    _mage->_known_spells.push_back(spell);
                    return *this;
                }

                Mage* make(void) {
                    return new Mage(*_mage);
                }
                ~MageBuilder() { delete _mage; }
            };
            friend MageBuilder;
        };
        std::ostream& operator<<(std::ostream& os, Mage mage);
        std::string to_string(const Team& team);


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

            virtual void setDistance(math::Coord dist) override { this->distance_m = bounds<math::Coord>(dist, 50, 100); }
            virtual void pushEffect(Effect effect) override { if (this->effects_m.size() < 1) this->effects_m.push_back(effect); }
            virtual void setEffectDuration(math::Dur value) override { this->effect_duration_m = 1; }
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
            virtual void setDistance(math::Coord dist) override { this->distance_m = bounds<math::Coord>(dist, 1, 10); }
            virtual void pushEffect(Effect effect) override { if (this->effects_m.size() < 2) this->effects_m.push_back(effect); }
            virtual void setEffectDuration(math::Dur value) override { this->effect_duration_m = 1; }

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
            virtual void setDistance(math::Coord dist) override { this->distance_m = bounds<math::Coord>(dist, 50, 100); }

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
            virtual void setDistance(math::Coord dist) override { this->distance_m = bounds<math::Coord>(dist, 50, 100); }

            protected:
            virtual std::string spellType(void) const noexcept override {
                return "Curse";
            }
        };
    }
}
