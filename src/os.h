#pragma once

#include <stdint.h>

// Allocates an executable memory region, copies the memory region described by
// "bytes" and "buffer", and changes the allocated buffer to be read-only.
//
// Returns the allocated buffer.
void* os_make_executable(
    size_t bytes,
    void *buffer
);
