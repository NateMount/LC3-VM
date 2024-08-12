
#include "util.h"
#include "core.h"

#include <stdint.h>

void update_flags(uint16_t r){
    if (reg[r] == 0){
        reg[R_COND] = FL_ZRO;
    } else if (reg[r] >> 15){
        reg[R_COND] = FL_NEG;
    } else {
        reg[R_COND] = FL_POS;
    }
}

uint16_t sign_extend(uint16_t x, int bit_count){
    if ((x >> (bit_count - 1)) & 1){
        x |= (0xFFFF << bit_count);
    }
    return x;
}

void mem_write(uint16_t addr, uint16_t val){
    memory[addr] = val;
}

uint16_t mem_read(uint16_t addr){
    if (addr == MMR_KBSR){
        if (check_key()){
            memory[MMR_KBSR] = (1 << 15);
            memory[MMR_KBDR] = getchar();
        } else {
            memory[MMR_KBSR] = 0;
        }
    }
    return memory[addr];
}