#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "abi.h"
#include "os.h"

typedef bool (*fnptr_is_odd_jitted)(uint64_t value);

static fnptr_is_odd_jitted emitted_code;

#if __x86_64
static fnptr_is_odd_jitted compile() {
    // the maximum size for the generated function is equal to:
    //      - for each value...
    //          - 5 bytes for CMP
    //          - 6 bytes for JE rel32
    //      - ...and for the two outcomes:
    //          - even:
    //              - xor rax, rax      3 bytes
    //              - ret               1 byte
    //          - odd:
    //              - mov rax, 1        7 bytes
    //              - ret               1 byte
    // we could encode the JE as rel8 or rel16, but this would complicate matters
    // (calculation of jump distances would be harder), and I really cannot be bothered! ;3c

    uint32_t max_size = ((5 + 6) * 0xffff) + 8 + 4;

    void *memory = malloc(max_size);
    uint8_t *current = memory;

    for (uint16_t i = 0; i < 0xffff; i++) {
        // CMP r/m16, imm16 [81 /7 iw]
        *current++ = X86_OPSIZE_OVERRIDE;
        *current++ = 0x81;
        *current++ = 0b11111000 | CALLCONV_ARG1;
        *(uint16_t*)current = i;
        current += sizeof(uint16_t);

        uint32_t jmp_distance = (0xffff - i) * (5 + 6) - 11;
        uint32_t target = (i % 2 == 0) ? 0 : 4; // even? then offset is 0; else, skip "xor rax, rax" and "ret"

        // JE imm32 [0F 84 cd]
        *current++ = 0x0F;
        *current++ = 0x84;
        *(uint32_t*)current = jmp_distance + target;
        current += sizeof(uint32_t);
    }

    // Emit return functions

    // +0   even:
    *current++ = 0x48;  // xor rax, rax
    *current++ = 0x31;
    *current++ = 0xC0;

    *current++ = 0xC3;  // ret

    // +4   odd: 
    *current++ = 0x48;  // mov rax, 1
    *current++ = 0xC7;
    *current++ = 0xC0;
    *(uint32_t*)current = 1;
    current += sizeof(uint32_t);

    *current++ = 0xC3;  // ret
    
    // Convert the read-write memory to read-execute (will copy)
    void *fn = os_make_executable(max_size, memory);
    free(memory);
    return fn;
}
#else
    #error Code generation is not defined for this architecture.
#endif

bool is_odd(uint64_t value) {
    if (emitted_code != NULL)
        return emitted_code(value); // function was JIT-ted before

    fnptr_is_odd_jitted func = compile();
    emitted_code = func;
    return func(value);
}

