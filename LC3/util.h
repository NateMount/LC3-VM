#ifndef _LC3_UTIL
#define _LC3_UTIL

#include <stdint.h>

#define get_r0 (instr >> 9) & 0x7
#define get_r1 (instr >> 6) & 0x7
#define get_r2 instr & 0x7

#define get_imm_flag (instr >> 5) & 0x1
#define get_imm sign_extend(instr & 0x1F, 5)

#define get_pc_offset sign_extend(instr & 0x1FF, 9)
#define get_offset sign_extend(instr & 0x3F, 6)

enum{
    FL_POS = 1 << 0,
    FL_ZRO = 1 << 1,
    FL_NEG = 1 << 2
};

void update_flags(uint16_t r);
uint16_t sign_extend(uint16_t x, int bit_count);

void mem_write(uint16_t addr, uint16_t val);
uint16_t mem_read(uint16_t addr);

#endif