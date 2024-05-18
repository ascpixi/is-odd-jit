#include <stdint.h>
#include <stdio.h>

#include "../include/isodd.h"

int main() {
    while (1) {
        printf("input: ");

        uint16_t value;
        if (scanf("%hu", &value) != 1) {
            fprintf(stderr, "invalid input, exiting\n");
            return 1;
        }

        printf(is_odd(value) ? "%hu is odd\n" : "%hu is even\n", value);
    }
}