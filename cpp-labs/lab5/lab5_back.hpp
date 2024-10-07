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



        class Spell;
        class ITarget;
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

                virtual void addMP(math::MP) = 0;
                virtual void decMP(math::MP) = 0;
                virtual void addCP(math::CP) = 0;
                virtual void decCP(math::CP) = 0;

                virtual void addEffect(math::Dur turns, Effect effect) = 0;
                virtual void addToHistory(Spell *) = 0;

                virtual ~ITarget() {}
        };
        class Spell {
            protected:
                math::MP _mana_cost = 1;
                math::CP _cost = 1;
                math::Dur _apply_duration = 1;
                math::Dur _effect_duration = 1;
                math::Coord _distance = 1;
                math::TargetArea _target_area = 1;
                std::vector<Effect> _effects = {};


            public:
                virtual ~Spell() {}
                friend std::ostream& operator<<(std::ostream& os, const Spell &spell);

                virtual Spell* clone(void) const = 0;

                virtual bool checkCast(ITarget &owner, ITarget &target) const noexcept = 0;

                virtual void cast(ITarget& owner, ITarget &target) const {
                    auto effects = this->getEffects();
                    const auto dur = this->getEffectDuration();
                    owner.decMP(this->getManaCost());
                    owner.decCP(this->getCost());

                    for (const auto effect : effects) target.addEffect(dur, effect);
                };

                virtual void setManaCost(math::MP value) { _mana_cost = bounds<math::MP>(value, 1, 100); }
                virtual void setCost(math::CP value) { _cost = bounds<math::CP>(value, 1, 10); }
                virtual void setApplyDuration(math::Dur value) { _apply_duration = bounds<math::Dur>(value, 1, 3600); }
                virtual void setEffectDuration(math::Dur value) { _effect_duration = bounds<math::Dur>(value, 1, 10); }
                virtual void setDistance(math::Coord value) { _distance = bounds<math::Coord>(value, 1, 100); }
                virtual void setTargetArea(math::TargetArea value) { _target_area = value; }
                virtual void pushEffect(Effect effect) { _effects.push_back(effect); }

                virtual math::MP getManaCost(void) const noexcept { return _mana_cost; }
                virtual math::CP getCost(void) const noexcept { return _cost; }
                virtual math::Dur getApplyDuration(void) const noexcept { return _apply_duration; }
                virtual math::Dur getEffectDuration(void) const noexcept { return _effect_duration; }
                virtual math::Coord getDistance(void) const noexcept { return _distance; }
                virtual math::TargetArea getTargetArea(void) const noexcept { return _target_area; }
                virtual const std::vector<Effect> &getEffects(void) const noexcept { return _effects; }

                class SpellBuilder {
                    Spell *_spell;

                    public:
                    SpellBuilder(Spell *spell) : _spell(spell) { }
                    SpellBuilder() = delete;
                    ~SpellBuilder() { /*delete _spell;*/ }

                    SpellBuilder* withManaCost(math::MP value) { _spell->setManaCost(value); return this; }
                    SpellBuilder* withCost(math::CP value) { _spell->setCost(value); return this; }
                    SpellBuilder* withApplyDuration(math::Dur value) { _spell->setApplyDuration(value); return this; }
                    SpellBuilder* withEffectDuration(math::Dur value) { _spell->setEffectDuration(value); return this; }
                    SpellBuilder* withDistance(math::Coord value) { _spell->setDistance(value); return this; }
                    SpellBuilder* withTargetArea(math::TargetArea value) { _spell->setTargetArea(value); return this; }
                    SpellBuilder* withEffect(Effect effect) { _spell->pushEffect(effect); return this; }
                    Spell* alloc(void) {
                        return _spell;
                    }
                };
                friend SpellBuilder;
            protected:
                virtual std::string spellType(void) const noexcept = 0;
        };
        std::ostream& operator<<(std::ostream& os, const Spell &spell);



        std::ostream& operator<<(std::ostream& os, Team team);
        std::ostream& operator<<(std::ostream& os, TargetType type);

        class Mage: public ITarget {
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

                virtual void addMP(math::MP v) override { _mp += v; }
                virtual void decMP(math::MP v) override { _mp -= v; }
                virtual void addCP(math::CP v) override { _cp += v; }
                virtual void decCP(math::CP v) override { _cp -= v; }

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
                        return _mage;
                    }
                    ~MageBuilder() { /*delete _mage;*/ }
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
            virtual bool checkCast(ITarget &owner, ITarget &target) const  noexcept override  {
                math::Coord dist = math::distance_sq(owner.getPos(), target.getPos()); 
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return 0;
                if ( dist < 50*50 || dist > this->getDistance().v*this->getDistance().v ) return 0;
                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {
            };

            virtual void setDistance(math::Coord dist) override { _distance = bounds<math::Coord>(dist, 50, 100); }
            virtual void pushEffect(Effect effect) override { if (_effects.size() < 1) _effects.push_back(effect); }
            virtual void setEffectDuration(math::Dur value) override { _effect_duration = 1; }

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
            virtual bool checkCast(ITarget &owner, ITarget &target) const  noexcept override  {
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return false;
                math::Coord dist = math::distance_sq(owner.getPos(), target.getPos()); 
                if ( dist > this->getDistance().v*this->getDistance().v ) return 0;

                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {

            };
            virtual void setDistance(math::Coord dist) override { _distance = bounds<math::Coord>(dist, 1, 10); }
            virtual void pushEffect(Effect effect) override { if (_effects.size() < 2) _effects.push_back(effect); }
            virtual void setEffectDuration(math::Dur value) override { _effect_duration = 1; }

            protected:
            virtual std::string spellType(void) const noexcept override {
                return "Short";
            }
        };

        class SupportSpell: public Spell {
            SupportSpell(): Spell() {}
            public:
            static SpellBuilder* build() { return new SpellBuilder(new SupportSpell()); }

            virtual bool checkCast(ITarget &owner, ITarget &target) const  noexcept override  {
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return false;
                if (owner.getTeam() != target.getTeam()) return false;
                math::Coord dist = math::distance_sq(owner.getPos(), target.getPos()); 
                if ( dist > this->getDistance().v*this->getDistance().v ) return 0;

                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {
                for (auto effect : _effects) {
                    target.addEffect(_effect_duration, effect);
                }

            };
            virtual Spell* clone(void) const override { return new SupportSpell(*this); }
            virtual void setDistance(math::Coord dist) override { _distance = bounds<math::Coord>(dist, 50, 100); }

            protected:
            virtual std::string spellType(void) const noexcept override {
                return "Support";
            }
        };

        class CurseSpell: public Spell {
            CurseSpell(): Spell() {}
            public:
            static SpellBuilder* build() { return new SpellBuilder(new CurseSpell()); }

            virtual bool checkCast(ITarget &owner, ITarget &target) const  noexcept override  {
                if (owner.getCP() < this->getCost() || owner.getMP() < this->getManaCost()) return false;
                if (owner.getTeam() == target.getTeam()) return false;

                return true;
            }
            virtual void cast(ITarget& owner, ITarget &target) const override {

            };
            virtual Spell* clone(void) const override { return new CurseSpell(*this); }
            virtual void setDistance(math::Coord dist) override { _distance = bounds<math::Coord>(dist, 50, 100); }

            protected:
            virtual std::string spellType(void) const noexcept override {
                return "Curse";
            }
        };
    }
}
