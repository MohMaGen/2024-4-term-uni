#include <iostream>
#include <vector>
#include <string>

namespace lab6 {

    class IWeapon {
        public:
            using Stats = std::vector<std::pair<std::string, std::string>>;

            virtual double realod(size_t bullets) noexcept = 0;
            virtual size_t fire(size_t distance) noexcept = 0;
            virtual Stats display(void) const noexcept = 0;
    };

    class ShotGun: public IWeapon {
        size_t _bullet_count;
        size_t _mag_capacity;
        double _bullet_reload;
        public:
    };

    class SmiperRifle: public IWeapon {
        bool loaded;
        double _bullet_load_time; 
        public:
    };

    class AssaultRifle: public IWeapon {

        public:
    };

    class Pistol: public IWeapon {
        public:
    };

    void runLab6(void) {
        std::cout << "Welcome to the fire field!" << std::endl;
    }
}
