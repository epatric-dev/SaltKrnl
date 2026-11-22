#include <devices/io.h>
#include <devices/serial.h>

#include <stdint.h>

namespace serial {
namespace {

constexpr uint16_t kCom1 = 0x3f8;

} // namespace

void init() {
    out8(kCom1 + 1, 0x00);
    out8(kCom1 + 3, 0x80);
    out8(kCom1 + 0, 0x03);
    out8(kCom1 + 1, 0x00);
    out8(kCom1 + 3, 0x03);
    out8(kCom1 + 2, 0xc7);
    out8(kCom1 + 4, 0x0b);
}

void putc(char character) {
    while ((in8(kCom1 + 5) & 0x20) == 0) {
    }

    out8(kCom1, static_cast<uint8_t>(character));
}

void write(const char *text) {
    while (*text != '\0') {
        if (*text == '\n') {
            putc('\r');
        }
        putc(*text++);
    }
}

} // namespace serial
