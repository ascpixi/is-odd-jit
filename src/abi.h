#pragma once

#include "arch.h"

#ifdef __x86_64
    #ifdef WIN32
        // Microsoft x64 ABI
        #define CALLCONV_ARG1   X86_RM_CX
    #else
        // System V x64 ABI
        #define CALLCONV_ARG1   X86_RM_DI
    #endif
#else
    #error Unsupported architecture.
#endif

