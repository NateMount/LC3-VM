
// Includes 
#include <stdio.h>
#include <stdint.h>

// Defines
#define REG_COUNT 11
#define MEM_MAX (1 << 16)

// Memory Mapped Registers
enum {
    MMR_KBSR = 0xFE00, // Keyboard Status
    MMR_KBDR = 0xFE02, // Keyboard Data
};

// Trap Codes
enum {
    TRAP_GETC = 0x20,
    TRAP_OUT = 0x21,
    TRAP_PUTS = 0x22,
    TRAP_IN = 0x23,
    TRAP_PUTSP = 0x24,
    TRAP_HALT = 0x25
};

// Register Setup
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

uint16_t memory[MEM_MAX];
uint16_t reg[REG_COUNT];

// Condition FLags
enum{
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2
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

// [MAIN]
int main(int argc, const char* argv[]){

    return 0;
}