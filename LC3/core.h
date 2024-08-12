#ifndef _LC3_CORE
#define _LC3_CORE

#include <stdint.h>

#define REG_COUNT 11
#define MEM_MAX (1 << 16)

// Registerss
enum {
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

// Memory Mapped Registers
enum {
    MMR_KBSR = 0xFE00, // Keyboard Status
    MMR_KBDR = 0xFE02, // Keyboard Data
};

// Opcodes
enum {
    OP_BR = 0,
    OP_ADD,
    OP_LD,
    OP_ST,
    OP_JSR,
    OP_AND,
    OP_LDR,
    OP_STR,
    OP_RTI,
    OP_NOT,
    OP_LDI,
    OP_STI,
    OP_JMP,
    OP_RES,
    OP_LEA,
    OP_TRAP
};

extern uint16_t memory[MEM_MAX];
extern uint16_t reg[REG_COUNT];

#endif