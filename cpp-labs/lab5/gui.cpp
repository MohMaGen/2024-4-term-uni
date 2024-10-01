#include <lab5_gui.hpp>

namespace lab5 {
    namespace gui {
        Color::Color(std::uint32_t hex) {
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

        void gui_main(void) {
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
}
