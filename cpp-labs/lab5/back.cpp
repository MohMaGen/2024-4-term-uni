#include <lab5_back.hpp>

namespace lab5 {
    namespace back {

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
        std::ostream& operator<<(std::ostream& os, Mage mage) {
            os << "Mage { ( " << mage.hp_m << " ) ( " << mage.mp_m << " ) ( "
                << mage.cp_m << " ) ( " << mage.team_m << " ) ( " << mage.pos_m << " ) ( CurrEffects [ ";
            for (auto [turns, effect] : mage.curr_effects_m) 
                os << "( " << turns << ", " << effect << " )";

            os << " ] ) ( KnownSpells [ ";
            for (auto spell : mage.known_spells_m)
                if (spell != nullptr) os << "( " << *spell << " )";
            os << " ] ) ( History [ ";
            for (auto spell : mage.spell_history_m)
                if (spell != nullptr) os << "( " << *spell << " )";
            return os << " ] )";
        }
    }
}
