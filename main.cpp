#include <devices/serial.h>
#include <stdint.h>

extern "C" [[noreturn]] void kernel_main() {
    serial::init();
    serial::write("Hello from SaltKrnl!\n");
    for (;;) {
        asm volatile("hlt");
    }
}
