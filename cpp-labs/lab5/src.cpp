#include <lab5.hpp>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>
#include <ctime>


namespace lab5 {

    struct Pos { size_t x,  y; };
    std::ostream& operator<<(std::ostream& os, const Pos &pos) {
        return os << pos.x << "," << pos.y;
    }

    class ITarget;
    class IEffect {
        public:
            virtual void apply(ITarget *target) = 0;
            virtual void lose(ITarget *target) {}
            virtual void display(std::ostream &os) const { os << "IEffect"; }
            virtual ~IEffect() {}
    };
    std::ostream &operator<<(std::ostream &os, const IEffect &effect) {
        os << "Effect: ";
        effect.display(os);
        return os;
    }

    enum class Team: int { Blue = 0, Orange = 1 };
    class ITarget {
        public:
            virtual size_t getHP(void) const noexcept = 0;
            virtual size_t getMP(void) const noexcept = 0;
            virtual Team getTeam(void) const noexcept = 0;
            virtual Pos getPos(void) const noexcept = 0;
            virtual bool isSleep(void) const noexcept = 0;

            virtual void decMP(size_t) noexcept = 0;
            virtual void incMP(size_t) noexcept = 0;
            virtual void decHP(size_t) noexcept = 0;
            virtual void incHP(size_t) noexcept = 0;
            virtual void setSleep(bool) noexcept = 0;
    };

    class DamageEffect: public IEffect {
        size_t _damage;
        public:
            DamageEffect(size_t damage): _damage(damage) {}
            virtual void apply(ITarget *target) override {
                target->decHP(_damage); 
            }
            virtual void display(std::ostream &os) const override {
                os << "Damage `" << _damage << "`";
            }
    };

    class HealEffect: public IEffect {
        size_t _heal;
        public:
            HealEffect(size_t heal): _heal(heal) {}
            virtual void apply(ITarget *target) override {
                target->incHP(_heal); 
            }
            virtual void display(std::ostream &os) const override {
                os << "Heal `" << _heal  << "`";
            }
    };

    class SleepEffect: public IEffect {
        public:
            SleepEffect() {}
            virtual void apply(ITarget *target) override {
                target->setSleep(true);
            }
            virtual void lose(ITarget *target) override {
                target->setSleep(false);
            }
            virtual void display(std::ostream &os) const override {
                os << "Sleep";
            }
    };

    class Spell {
        protected:
            size_t _mana_cost;
            size_t _hardness;
            size_t _apply_time;
            size_t _distance;
            size_t _effect_duration;
            std::vector<IEffect*> _effects; 
        public:
            struct Result {
                std::vector<IEffect*> effects;
                size_t duration;
            };

            virtual Result cast() {
                return Result { _effects, _effect_duration };
            }
            virtual bool canCast(ITarget* owner, ITarget* target) const noexcept {
                Pos owner_pos = owner->getPos(), target_pos = target->getPos();
                size_t distance = (owner_pos.x - target_pos.x)*(owner_pos.x - target_pos.x) 
                                + (owner_pos.y - target_pos.y)*(owner_pos.y - target_pos.y);

                if (distance > _distance * _distance) return false;
                if (owner->getMP() < _mana_cost) return false;
                return true;
            };


            size_t getManaCost(void) { return _mana_cost; }

        protected:
            virtual void display(std::ostream&) const = 0;
            Spell(): _mana_cost(std::rand()%100+1), _hardness(std::rand()%10+1), _apply_time(std::rand()%3600),
                _distance(std::rand()%100+1), _effect_duration(std::rand()%5+1)
            {
                size_t effects_len = std::rand()%10 + 1;
                std::vector<size_t> effets (effects_len);
                for (size_t i = 0; i < effects_len; i++) {
                    switch (rand()%3) {
                    case 0: _effects.push_back(new DamageEffect(rand()%30+5)); break;
                    case 1: _effects.push_back(new HealEffect(rand()%30+5)); break;
                    case 2: _effects.push_back(new SleepEffect()); break;
                    default:
                        break;
                    }
                }
            }

        friend std::ostream& operator<<(std::ostream& os, const Spell& spell);
    };
    std::ostream& operator<<(std::ostream& os, const Spell& spell) {
        os << "Spell: ";
        spell.display(os);
        os << ": (mp: `" << spell._mana_cost << "` hrnds: `" << spell._hardness << "` dist: `" << spell._distance
           << "` time: `" << spell._apply_time << "sec` effects dur: `" << spell._effect_duration << "`)\n";
        for (auto effect : spell._effects) {
            if (effect == NULL) continue;
            os << "\t- " << *effect << "\n";
        }
        return os;
    }


    class LongRangeSpell: public Spell {
        public:
            LongRangeSpell() {
                _distance = rand()%51 + 50;

                std::vector<IEffect*> new_effects = { _effects[0] };
                for (size_t i = 1; i < new_effects.size(); i++) delete _effects[i];
                _effects = new_effects;
            }
            virtual void display(std::ostream& os) const override { os << "Long Range"; };
    };
    class ShortRangeSpell: public Spell {
        public:
            ShortRangeSpell() {
                _distance = rand()%10 + 1;
                if (_effects.size() > 2) {
                    std::vector<IEffect*> new_effects = { _effects[0], _effects[1] };
                    for (size_t i = 2; i < new_effects.size(); i++) delete _effects[i];
                    _effects = new_effects;
                }
            }
            virtual void display(std::ostream& os) const override { os << "Short Range"; };
    };
    class SupportSpell: public Spell {
        public:
            SupportSpell() {
                _distance = rand()%50 + 1;
            }
            virtual bool canCast(ITarget *owner, ITarget *target) const noexcept override {
                if (!Spell::canCast(owner,  target)) return false;
                if (owner->getTeam() != target->getTeam()) return false;

                return true;
            }
            virtual void display(std::ostream& os) const override { os << "Support"; };
    };
    class CurseSpell: public Spell {
        public:
            CurseSpell() {
                _distance = rand()%50 + 1;
            }
            virtual bool canCast(ITarget *owner, ITarget *target) const noexcept override {
                if (!Spell::canCast(owner,  target)) return false;
                if (owner->getTeam() == target->getTeam()) return false;

                return true;
            }
            virtual void display(std::ostream& os) const override { os << "Curse"; };
    };

    enum class SpellType: unsigned char { Long, Short, Support, Curse, }; 
    Spell* createSpell(SpellType type) {
        switch (type) {
        case SpellType::Long:    return new LongRangeSpell();
        case SpellType::Short:   return new ShortRangeSpell();
        case SpellType::Support: return new SupportSpell();
        case SpellType::Curse:   return new CurseSpell();
        }
    }


    class Mage: public ITarget {
        size_t _hp;
        size_t _mp;
        bool _sleep;
        Pos _pos;
        Team _team;
        struct Effect{ size_t dur; IEffect *ptr; };
        std::vector<Effect> _effects;
        std::vector<Spell*> _available_spells;
        std::vector<Spell*> _history;

        public:
            using Changes = std::vector<Effect>;

            Spell* getSpell(size_t id) const noexcept { return _available_spells[id]; }
            std::vector<size_t> availableSpells(void) const noexcept {
                std::vector<size_t> spells;

                for (size_t i = 0; i < _available_spells.size(); i++) {
                    if (_available_spells[i]->getManaCost() <= _mp )
                        spells.push_back(i);
                } 

                return spells;
            }
            Changes showLastChanges(void) const noexcept {
                std::vector<Effect> changes;
                for (auto [dur, effect] : _effects) {
                    if (dur == 0) continue;
                    changes.push_back({dur, effect});
                }
                return changes;
            }

            size_t getHP(void) { return _hp; }

            void applySpells(std::vector<Spell*> spells) {
                for (auto spell : spells) {
                    auto [effects, dur] = spell->cast();
                    for (auto effect : effects) {
                        if (effect == NULL) continue;
                        _effects.push_back({dur, effect});
                    }
                }

            }
            void applyEffects(void) {
                _sleep = false;
                for (auto &[dur, effect] : _effects) {
                    if (dur == 0) continue;
                    effect->apply(this); 
                    dur--;
                }

            }

            virtual bool   isSleep(void) const noexcept override { return _sleep; };
            virtual Team   getTeam(void)   const noexcept override { return _team; };
            virtual size_t getHP(void)     const noexcept override { return _hp; }
            virtual size_t getMP(void)     const noexcept override { return _mp; }
            virtual Pos    getPos(void)    const noexcept override { return _pos; }


            virtual void decMP(size_t v)  noexcept override { 
                if (v > _mp) _mp = 0;
                else _mp -= v; 
            }
            virtual void incMP(size_t v)  noexcept override { 
                if (_mp + v > 100 ) _mp = 100;
                else _mp += v;
            }
            virtual void decHP(size_t v)  noexcept override { 
                if (v >= _hp) _hp = 0;
                else _hp -= v;
            }
            virtual void incHP(size_t v)  noexcept override { _hp += v; }
            virtual void setSleep(bool v) noexcept override { _sleep = v; };
            Mage(Team team, size_t width, size_t height) {
                _hp = 100;
                _mp = rand()%4 * 100 + 100;
                _team = team;
                switch (team) {
                case Team::Blue:   _pos = { rand()%(width/2), rand()%height }; break;
                case Team::Orange: _pos = { rand()%(width/2) + width/2, rand()%height }; break;
                }
                size_t first_type = rand()%4;
                size_t second_type = rand()%4;
                if (second_type == first_type) second_type = (second_type + 1)%4;

                size_t first_spells_count = rand()%4 + 1;
                for (size_t i = 0; i < first_spells_count; i++)
                    _available_spells.push_back(createSpell(SpellType(first_type)));

                size_t second_spells_count = rand()%4 + 1;
                for (size_t i = 0; i < second_spells_count; i++)
                    _available_spells.push_back(createSpell(SpellType(second_type)));
            }
            virtual ~Mage() {}

        friend std::ostream& operator<<(std::ostream& os, const Mage& mage);
    };

    std::ostream& operator<<(std::ostream& os, const Team& team) {
        switch (team) {
        case Team::Blue: return os << "Blue";
        case Team::Orange: return os << "Orange";
        }
    }

    std::ostream& operator<<(std::ostream& os, const Mage::Changes& changes) {
        os << "Changes:\n";
        for (auto [dur, effect] : changes) {
            os << "\t- add effect `" << *effect << "` for " << dur << " turns.\n";
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Mage& mage) {
        return os << "Mage " << mage._team << " (hp: `" << mage._hp << "` mp: `" << mage._mp 
        << "` pos: `" << mage._pos << "`)";
    }

    void runLab5(void) {
        std::srand(std::time(nullptr));

        std::cout << "Enter battle_field size [<width> <height>]: "; 
        size_t width, height;
        std::cin >> width >> height;

        size_t team_size;
        std::cout << "Enter team size:";
        std::cin >> team_size;
        std::vector<Mage*> mages (team_size * 2);
        for (size_t i = 0; i < team_size; i++) {
            mages[i*2]   = new Mage(Team::Blue, width, height); 
            mages[i*2+1] = new Mage(Team::Orange, width, height); 
        }

        while (true) {
            std::cout << "Simulate battle?(y/n) ";
            char v;
            std::cin >> v;
            if (v != 'y') {
                for (size_t curr_id = 0; curr_id < mages.size(); curr_id++) {
                    if (mages[curr_id]->getHP() <= 0) continue;
                    if (mages[curr_id]->isSleep() ) {
                        std::cout << "[" << curr_id << "] Mage " << curr_id << " is sleeping..." << std::endl;
                        continue;
                    }
                    std::cout << "Curr mage: [" << curr_id << "] " << *mages[curr_id] << std::endl;

                    while (true) {
                        size_t spell_id;
                        std::cout << "Available spells:" << std::endl;
                        auto available_spells =  mages[curr_id]->availableSpells();
                        if (available_spells.size() == 0) {
                            std::cout << "Mage has no any available spells..." << std::endl;
                            continue;
                        }
                        for (auto spell : available_spells) 
                            std::cout << " :: [ " << spell << " ]: "
                                      << *mages[curr_id]->getSpell(spell) << std::endl; 
                        std::cout << " :: [ " << available_spells.size()   << " ]" << "skip." << std::endl;
                        std::cout << " :: [ " << available_spells.size()+1 << " ]" << "show mages." << std::endl;
                        std::cout << "Choose spell to cast: ";
                        std::cin >> spell_id;
                        if (!std::cin) continue;
                        if (spell_id == available_spells.size()) break;
                        if (spell_id == available_spells.size()+1) {
                            for (size_t i = 0; i < mages.size(); i++) {
                                std::cout << " :: [ " << i << " ] " << *mages[i] << std::endl;
                            }
                            continue;
                        }
                        if (spell_id > available_spells.size()+1) {
                            std::cout << "Inalid option" << std::endl;
                            continue;
                        }
                        Spell* curr_spell = mages[curr_id]->getSpell(spell_id); 

                        std::cout << "Available targets:\n";
                        size_t count = 0;
                        for (size_t target_id = 0; target_id < mages.size(); target_id++) {
                            if (mages[target_id]->getHP() <= 0) continue;
                            if (curr_spell->canCast(mages[curr_id], mages[target_id])) {
                                std::cout << "\t:: [ " << target_id << " ]: "
                                          << *mages[target_id] << std::endl;
                                count++;
                            }
                        }
                        if (count == 0) {
                            std::cout << "No available targets." << std::endl;
                            continue;
                        }
                        size_t target;
                        std::cout << "Choose target of spell cast: ";
                        std::cin >> target;
                        if (!std::cin) { continue; }
                        if (target >= mages.size()) break;
                        mages[target]->applySpells({ curr_spell });
                        break;
                    }
                }
            } else {
                for (size_t curr_mage = 0; curr_mage < mages.size(); curr_mage ++) {
                    if (mages[curr_mage]->getHP() <= 0) continue;
                    std::cout << " :: [ " << curr_mage << " ] " << *mages[curr_mage] << ": ";
                    if (mages[curr_mage]->isSleep()) {
                        std::cout << "sleep..." << std::endl;
                        continue;
                    }
                    auto available_spells = mages[curr_mage]->availableSpells();
                    if (available_spells.size() == 0) {
                        std::cout << "can't use any spell. skip turn..." << std::endl;
                        continue;
                    }
                    size_t curr_spell_id = rand()%available_spells.size();
                    size_t curr_cpell = available_spells[curr_spell_id];
                    std::cout << "mage choose spell [ " << curr_spell_id << " ]. ";
                    std::vector<Mage*> available_targets {};

                    for (auto target : mages) {
                        if (mages[curr_mage]->getSpell(curr_cpell)->canCast(mages[curr_mage], target))
                            available_targets.push_back(target);
                    }

                    if (available_targets.size() == 0) {
                        std::cout << "no avaliable targets. skip turn..." << std::endl;
                        continue;
                    }
                    size_t target_id = rand()%available_targets.size();
                    auto target = available_targets[target_id];
                    target->applySpells({ mages[curr_mage]->getSpell(curr_cpell) });
                    std::cout << "cast spell to " << target_id << std::endl;

                }
            }

            std::cout << "End of turn. Aplying effects..." << std::endl;
            for (size_t i = 0; i < mages.size(); i++) {
                std::cout << "Mage " << i << ": " << std::endl;
                std::cout << "Changes: " << mages[i]->showLastChanges() << std::endl;
                mages[i]->applyEffects();
            }

            std::vector<Mage*> new_mages;
            size_t count[2] = { 0, 0 };
            for (size_t i = 0; i < mages.size(); i++) {
                if (mages[i]->getHP() <= 0) {
                    std::cout << ":: Mage " << i << " [ R.I.P ]" << std::endl;
                    delete mages[i];
                    continue;
                }
                new_mages.push_back(mages[i]);
                count[(int)mages[i]->getTeam()]++;
            }
            mages = new_mages;

            if (count[0] == 0 && count[1] == 0) {
                std::cout << "Draw" << std::endl;
                break;
            } else if (count[0] == 0) {
                std::cout << "Blue team lose the game." << std::endl;
                break;
            } else if (count[1] == 0) {
                std::cout << "Orange team lose the game." << std::endl;
                break;
            }
            std::cout << "Next turn? ";
            char ans;
            std::cin >> ans;
            if (ans != 'y' && ans != 'Y') break;
        }
    }

}
