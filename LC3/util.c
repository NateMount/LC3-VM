
#include "util.h"
#include "core.h"

#include <stdint.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/time.h>

void update_flags(uint16_t r){
    if (reg[r] == 0){
        reg[R_COND] = FL_ZRO;
    } else if (reg[r] >> 15){
        reg[R_COND] = FL_NEG;
    } else {
        reg[R_COND] = FL_POS;
    }
}

void mem_write(uint16_t addr, uint16_t val){
    memory[addr] = val;
}

uint16_t check_key(){
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    return select(1, &readfds, NULL, NULL, &timeout) != 0;
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

// Bit Operation Functs

uint16_t sign_extend(uint16_t x, int bit_count){
    if ((x >> (bit_count - 1)) & 1){
        x |= (0xFFFF << bit_count);
    }
    return x;
}

uint16_t swap16(uint16_t x){
    return (x << 8) | (x >> 8);
}