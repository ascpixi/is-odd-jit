#if WIN32

#include <windows.h>

void* os_make_executable(size_t bytes, void* buffer) {
    DWORD unused;

    void *out = VirtualAlloc(NULL, bytes, MEM_COMMIT, PAGE_READWRITE);
    memcpy(out, buffer, bytes);
    VirtualProtect(out, bytes, PAGE_EXECUTE_READ, &unused);
    return out;
}

#else

#include <sys/mman.h>
#include <string.h>

void* os_make_executable(size_t bytes, void* buffer) {
    void *out = mmap(0, bytes, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memcpy(out, buffer, bytes);
    return out;
}

#endif