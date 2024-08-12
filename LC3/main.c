// Includes
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
/* unix only */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#include "core.h"
#include "util.h"
#include "instruction-index.h"
#include "input-buffering.h"



// [MAIN]
int main(int argc, const char* argv[]){


    if (argc < 2){
        printf("lc3 [image-file1] ...\n");
        exit(2);
    }

    for (int j = 1; j < argc; ++j){
        if (!read_image(argv[j])){
            printf("failed to load image: %s\n", argv[j]);
            exit(1);
        }
    }

    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    // Setting initial condition flag
    reg[R_COND] = FL_ZRO;

    enum { PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    uint16_t instr;
    uint16_t opcode;

    int running = 1;
    while (1){
        instr = mem_read(reg[R_PC]++);
        opcode = instr >> 12;

        switch (opcode){
            case OP_ADD:
                op_add(instr);
                break;
            case OP_AND:
                op_and(instr);
                break;
            case OP_NOT:
                op_not(instr);
                break;
            case OP_BR:
                op_branch(instr);
                break;
            case OP_JMP:
                op_jump(instr);
                break;
            case OP_JSR:
                op_jump_reg(instr);
                break;
            case OP_LD:
                op_load(instr);
                break;
            case OP_LDI:
                op_load_indr(instr);
                break;
            case OP_LDR:
                op_load_reg(instr);
                break;
            case OP_LEA:
                op_load_effect_addr(instr);
                break;
            case OP_ST:
                op_store(instr);
                break;
            case OP_STI:
                op_store_indr(instr);
                break;
            case OP_STR:
                op_store_reg(instr);
                break;
            case OP_TRAP:
                op_trap(instr);
                break;
            case OP_RES:
            case OP_RTI:
            default:
                abort();
                break;
        }
    }
    restore_input_buffering();
    return 0;
}