#pragma once

#ifdef __x86_64
    #define X86_RM_AX   0
    #define X86_RM_CX   1
    #define X86_RM_DX   2
    #define X86_RM_BX   3
    #define X86_RM_SP   4
    #define X86_RM_BP   5
    #define X86_RM_SI   6
    #define X86_RM_DI   7

    #define X86_OPSIZE_OVERRIDE     0x66   
#endif
