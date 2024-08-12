#include "instruction-index.h"
#include "util.h"
#include "core.h"

#include <stdint.h>
#include <stdio.h>

// Opcode: Add
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

// Opcode: And
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

// Opcode: Not
void op_not(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t r1 = get_r1;

    reg[r0] = ~reg[r1];
    update_flags(r0);
}

// Opcode: Branch
void op_branch(uint16_t instr){
    uint16_t pc_offset = get_pc_offset;
    uint16_t cond_flag = get_r0;
    if (cond_flag & reg[R_COND]){
        reg[R_PC] += pc_offset;
    }
}

// Opcode: Jump
void op_jump(uint16_t instr){
    uint16_t r1 = get_r1;
    reg[R_PC] = reg[r1];
}

// Opcode: Jump Register
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

// Opcode: Load
void op_load(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    reg[r0] = mem_read(reg[R_PC] + pc_offset);
    update_flags(r0);
}

// Opcode: Load Indirect
void op_load_indr(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    reg[r0] = mem_read(mem_read(reg[R_PC] + pc_offset));
    update_flags(r0);
}

// Opcode: Load Register
void op_load_reg(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t r1 = get_r1;
    uint16_t offset = get_offset;
    reg[r0] = mem_read(reg[r1] + offset);
    update_flags(r0);
}

// Opcode: Load Effective Address
void op_load_effect_addr(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    reg[r0] = reg[R_PC] + pc_offset;
    update_flags(r0);
}

// Opcode: Store
void op_store(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    mem_write(reg[R_PC] + pc_offset, reg[r0]);
}

// Opcode: Store Indirect
void op_store_indr(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t pc_offset = get_pc_offset;
    mem_write(mem_read(reg[R_PC] + pc_offset), reg[r0]);
}

// Opcode: Store Register
void op_store_reg(uint16_t instr){
    uint16_t r0 = get_r0;
    uint16_t r1 = get_r1;
    uint16_t offset = get_offset;
    mem_write(reg[r1] + offset, reg[r0]);
}

// TRAP CODE FUNCT IMPL

void trap_puts(){
    uint16_t* c = memory + reg[R_R0];
    while (*c){
        putc((char)*c, stdout);
        ++c;
    }
    fflush(stdout);
}

void trap_out(){
    putc((char)reg[R_R0], stdout);
    fflush(stdout);
}

void trap_in(){
    printf("Enter a character: ");
    char c = getchar();
    putc(c, stdout);
    fflush(stdout);
    reg[R_R0] = (uint16_t)c;
    update_flags(R_R0);
}

void trap_putsp(){
    uint16_t* c = memory + reg[R_R0];
    while (*c){
        char ch1 = (*c) & 0xFF;
        putc(ch1, stdout);
        char ch2 = (*c) >> 8;
        if (ch2) putc(ch2, stdout);
        ++c;
    }
    fflush(stdout);
}

void trap_halt(){
    puts("HALT");
    fflush(stdout);
    exit(0);
}

// Opcode: Trap
// Handles: Getc, Out, Puts, In, Putsp, Halt
void op_trap(uint16_t instr){
    reg[R_R7] = reg[R_PC];
    switch (instr & 0xFF){
        case TRAP_GETC:
            trap_puts();
            break;
        case TRAP_OUT:
            trap_out();
            break;
        case TRAP_PUTS:
            trap_in();
            break;
        case TRAP_IN:
            trap_in();
            break;
        case TRAP_PUTSP:
            trap_putsp();
            break;
        case TRAP_HALT:
            trap_halt();
            break;
    }
}