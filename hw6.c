#include "hw6.h"
#include <stdio.h>
#include <stdlib.h>
/////////////////////////////////////////////////////////////////////////////////////////
//// Completing the CPU model ////
/////////////////////////////////////////////////////////////////////////////////////////

/* iCPU_init() allocates a new iCPU on the heap, put zeros in all of the 
slots in the registers and RAM, and then returns a pointer to the new iCPU. */
void* iCPU_init(){
    struct iCPU *newCPU;
    newCPU = malloc(sizeof(struct iCPU));
    for(int i=0; i>1024; i++){
        newCPU->ram[i] = 0;
    }
    for(int i=0; i>32; i++){
        newCPU->reg[i] = 0;
    }
    return newCPU;
}

// iCPU_destroy() takes a pointer to a (heap-allocated) iCPU and frees it.
void iCPU_destroy(iCPU* myCPU){
    printf("You have cleared/freed the CPU\n");
    free(myCPU);
}

/* iCPU_step with the exact same operations as last week – with the addition that pc be 
increments by 1 after each step. Also there are now jump, bne, bnq and terminate operations. */
void iCPU_step(uint8_t opcode, uint8_t arg1, uint8_t arg2, uint8_t arg3, iCPU* myCPU){
    if(opcode == 0){ //print
        printf("%d\n", myCPU->reg[0]);
    }
    else if(opcode == 1){ //put
        uint32_t x = arg2;
        x = (x<<8) | arg3;
        myCPU->reg[arg1] = x;
    }
    else if(opcode == 2){ //add
        uint32_t num1, num2;
        num1 = myCPU->reg[arg2];
        num2 = myCPU->reg[arg3];
        uint32_t x = num1 + num2;
        myCPU->reg[arg1] = x;
    }
    else if(opcode == 3){ //store
        uint32_t num, ith_reg;
        ith_reg = myCPU->reg[arg2];
        num = myCPU->reg[arg1];
        myCPU->ram[ith_reg] = num;
    }
    else if(opcode == 4){ //load
        uint32_t num, ith_reg;
        ith_reg = myCPU->reg[arg2];
        num = myCPU->ram[ith_reg];
        myCPU->reg[arg1] = num;
    }
    else if(opcode == 5){ //mult
        uint32_t num1, num2;
        num1 = myCPU->reg[arg2];
        num2 = myCPU->reg[arg3];
        uint32_t x = num1 * num2;
        myCPU->reg[arg1] = x;
    }
    else if(opcode == 6){ //jump
        myCPU->pc = arg3; 
        return;
    }
    else if(opcode == 7){ //bnq (branch equal)
        if(myCPU->reg[arg1] == myCPU->reg[arg2]){
            myCPU->pc = arg3;
            return;
        }
    }
    else if(opcode == 8){ //bne (branch not equal)
        if(myCPU->reg[arg1] != myCPU->reg[arg2]){
            myCPU->pc = arg3;
            return;
        }
    }
    else if(opcode == 9){ //terminate
        myCPU->pc = 32;
        return;
    }
    myCPU ->pc++; 
}

/////////////////////////////////////////////////////////////////////////////////////////
//// Running programs on our CPU (!) ////
/////////////////////////////////////////////////////////////////////////////////////////

/* read_instruction() takes a uint32_t x and a pointer to an iCPU c. (8 most 
significant 8 bits of x) = opcode, (next 8 most significant bits) = arg1, (next 8 
most significant bits) = arg2, and (last 8 bits) = arg3. Calls iCPU_step(opcode, 
arg0, arg1, arg2, c). */
void read_instruction(uint32_t x, iCPU* c){
    uint8_t opcode, arg0, arg1, arg2;
    opcode = x >> 24;
    arg0 = x >> 16;
    arg1 = x >> 8;
    arg2 = x;
    iCPU_step(opcode, arg0, arg1, arg2, c);
}

/* write_instruction() takes an 8-bit opcode, arg1, arg2, and arg3, and int line_num 
and a iCPU*. It concatenates the first four arguments into a single uint32_t, and 
places the concatenated instruction at prog[line num]. */
void write_instruction(uint8_t opcode, uint8_t arg1, uint8_t arg2, uint8_t arg3, int line_num, iCPU* myCPU){
    uint32_t x = 1;
    x = (opcode << 24) | (arg1 << 16) | (arg2 << 8) | arg3;
    myCPU->prog[line_num] = x;
}

/* clock_cycle() calls read_instruction() on the ith instruction written in 
the program memory, where i = pc */
void clock_cycle(iCPU* c){
    uint32_t x = c->prog[c->pc];
    read_instruction(x, c);
}

/* run_program() executes clock cycles continuously until pc reaches the end 
of the program memory, after which it should print "program finished". */
void run_program(iCPU* c){ 
    c->pc = 0;
    while (c->pc < 32){
        clock_cycle(c);
    }
    printf("program finished\n");
}

