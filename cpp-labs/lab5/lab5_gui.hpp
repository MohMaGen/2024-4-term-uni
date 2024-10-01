#include <cstdint>
#include <raylib.h>

namespace lab5 {
    namespace gui {
        struct Color {
            union {
                ::Color rgba;
                std::uint32_t hex;
            };
            ::Color rl() { return this->rgba; }
            Color(std::uint32_t hex);

            ::Color operator+() {
                return this->rgba;
            }
        };

        void gui_main(void);
    }
}
