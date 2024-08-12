#ifndef _INSTRUCTION_INDEX
#define _INSTRUCTION_INDEX

#include <stdint.h>

// Trap Codes
enum {
    TRAP_GETC = 0x20,
    TRAP_OUT = 0x21,
    TRAP_PUTS = 0x22,
    TRAP_IN = 0x23,
    TRAP_PUTSP = 0x24,
    TRAP_HALT = 0x25
};

void op_add(uint16_t instr);
void op_and(uint16_t instr);
void op_not(uint16_t instr);
void op_branch(uint16_t instr);
void op_jump(uint16_t instr);
void op_jump_reg(uint16_t instr);
void op_load(uint16_t instr);
void op_load_indr(uint16_t instr);
void op_load_reg(uint16_t instr);
void op_load_effect_addr(uint16_t instr);
void op_store(uint16_t instr);
void op_store_indr(uint16_t instr);
void op_store_reg(uint16_t instr);
void op_trap(uint16_t instr);

#endif