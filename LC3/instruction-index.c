#include "instruction-index.h"
#include "util.h"
#include "core.h"

#include <stdint.h>

void op_add(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t r1 = get_r1;
    uint16_t imm_flag = get_imm_flag;

    if (imm_flag){
        uint16_t imm = get_imm;
        reg[r0] = reg[r1] + imm;
    } else {
        uint16_t r2 = get_r2;
        reg[r0] = reg[r1] + reg[r2];
    }

    update_flags(r0);
}

void op_and(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t r1 = get_r1;
    uint16_t imm_flag = get_imm_flag;

    if (imm_flag){
        uint16_t imm = get_imm;
        reg[r0] = reg[r1] & imm;
    } else {
        uint16_t r2 = get_r2;
        reg[r0] = reg[r1] & reg[r2];
    }

    update_flags(r0);
}

void op_not(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t r1 = get_r1;

    reg[r0] = ~reg[r1];
    update_flags(r0);
}

void op_branch(uint16_t instr){
    uint16_t pc_offset = get_pc_offset;
    uint16_t cond_flag = get_r0;
    if (cond_flag & reg[R_COND]){
        reg[R_PC] += pc_offset;
    }
}

void op_jump(uint16_t instr){
    uint16_t r1 = get_r1;
    reg[R_PC] = reg[r1];
}

void op_jump_reg(uint16_t instr){
    uint16_t long_flag = (instr >> 11) & 1;
    reg[R_R7] = reg[R_PC];
    if (long_flag){
        uint16_t long_pc_offset = sign_extend(instr & 0x7FF, 11);
        reg[R_PC] += long_pc_offset;
    } else {
        uint16_t r1 = get_r1;
        reg[R_PC] = reg[r1];
    }
}

void op_load(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    reg[r0] = mem_read(reg[R_PC] + pc_offset);
    update_flags(r0);
}

void op_load_indr(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset));
    update_flags(r0);
}

void op_load_reg(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t r1 = get_r1;
    uint16_t offset = get_offset;
    reg[r0] = mem_read(reg[r1] + offset);
    update_flags(r0);
}

void op_load_effect_addr(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    reg[r0] = reg[R_PC] + pc_offset;
    update_flags(r0);
}

void op_store(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    mem_write(reg[R_PC] + pc_offset, reg[r0]);
}

void op_store_indr(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    mem_write(mem_read(reg[R_PC] + pc_offset), reg[r0]);
}

void op_store_reg(uint16_t instr);

void op_trap(uint16_t instr);