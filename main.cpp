#include <stdint.h>

namespace {

constexpr uint16_t kCom1 = 0x3f8;

static inline void out8(uint16_t port, uint8_t value) { asm volatile("outb %0, %1" : : "a"(value), "Nd"(port)); }

static inline uint8_t in8(uint16_t port) {
    uint8_t value;
    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static void serial_init() {
    out8(kCom1 + 1, 0x00);
    out8(kCom1 + 3, 0x80);
    out8(kCom1 + 0, 0x03);
    out8(kCom1 + 1, 0x00);
    out8(kCom1 + 3, 0x03);
    out8(kCom1 + 2, 0xc7);
    out8(kCom1 + 4, 0x0b);
}

static void serial_putc(char character) {
    while ((in8(kCom1 + 5) & 0x20) == 0)
        ;

    out8(kCom1, static_cast<uint8_t>(character));
}

static void serial_write(const char *text) {
    while (*text != '\0') {
        if (*text == '\n') {
            serial_putc('\r');
        }
        serial_putc(*text++);
    }
}

} // namespace

extern "C" [[noreturn]] void kernel_main() {
    serial_init();
    serial_write("Hello World\n");
    for (;;) {
        asm volatile("hlt");
    }
}
