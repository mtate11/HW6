#ifndef HOMEWORK_SIX_H
#define HOMEWORK_SIX_H
#include <stdint.h>

/* struct iCPU, aka improved CPU. Has a register set (reg) and a 32-kilobyte memoryRAM (ram). 
reg is represented by an array of thirty two 32-bit signed integers. ram is represented by an 
array of 1024 32-bit signed integers. To implement Control Unit functionality, the iCPU has a 
program counter (pc), which is represented as a int, and iCPU also has a 1-kilobyte program
memory (prog), which is represented as an array of 32 uint32_ts*/
typedef struct iCPU{
    int32_t reg[32];
    int32_t ram[1024];
    int pc;
    uint32_t prog[32];
}iCPU;

/* CPU_init() allocates a new iCPU on the heap, put zeros in all of the 
slots in the registers and RAM, and then returns a pointer to the new iCPU. */
void* iCPU_init();

// CPU_destroy() takes a pointer to a (heap-allocated) iCPU and frees it.
void iCPU_destroy(iCPU*);

/*  iCPU_step() executes a single machine instruction on our iCPU. It takes a uint8_t opcode, 
three additional uint8_ts called arg1, arg2, and arg3, as well as a pointer to an iCPU.
    print instruction: executed when the opcode is 0. Prints the value held in the 0th register.

    put instruction: executed when the opcode is 1. Treats arg2 and arg3 as a single immediate, 
    and places its value in the register indicated by arg1. In other words, it should set 
    reg[arg1] = x, where x is a 32-bit integer formed by concatenating 16 zeros followed by 
    the bits of arg2 and arg3.

    add instruction: executed when the opcode is 2. Takes the values in the registers indicated 
    by arg2 and arg3, adds them, and places their sum into the register indicated by arg1.

    store instruction: executed when the opcode is 3. Takes the value in the register indicated 
    by arg1, and place it in the ith place in RAM, where i is the value stored in the register 
    indicated by arg2.

    load instruction: executed when the opcode is 4. Takes the value stored in the ith place in 
    RAM, where i is the value stored in the register indicated by arg2, and places it in the 
    register indicated by arg1.

    mul instruction: executed when the opcode is 5. Does the same as add but with multiplication.

    jump instruction: executed when the opcode is 6. Sets pc = arg3 (interpreted as an immediate). 
    (After setting the pc it returns immediately – i.e. it doesn't increment pc by 1 afterwards).

    beq (branch equal) instruction: executed when the opcode is 7. It compares the values stored 
    in the registers indicated by arg1 and arg2. If they are equal, it sets pc = x where x is 
    arg3 interpreted as an immediate (and then immediately returns). Otherwise, does nothing
    (though pc is incremented as normal).

    bne (branch not equal) instruction: executed when the opcode is 8. Does the same as beq but 
    flips the cases.

    terminate instruction: executed when the opcode is 9. It sets the program counter so that 
    the program finishes after it is executed (when run using run_program()). */
void iCPU_step(uint8_t, uint8_t, uint8_t, uint8_t, iCPU*);

/* read_instruction() interprets a 32-bit integer as a CPU instruction. Takes a 
uint32_t x and a pointer to an iCPU c, interprets the 8 most significant 8 bits 
of x as an opcode, its 8 next most significant bits as arg1, its 8 next most 
significant bits as arg2, and its last 8 bits as arg3. Then makes a call to
iCPU_step(opcode, arg0, arg1, arg2, c). */
void read_instruction(uint32_t, iCPU*);

/* write_instruction() takes an 8-bit opcode, an 8-bit arg1, arg2, and arg3, 
and an int line_num and a pointer to an iCPU. It concatenates the first four
arguments into a single uint32_t, and places the concatenated instruction 
at prog[line num]. */
void write_instruction(uint8_t, uint8_t, uint8_t, uint8_t, int, iCPU*);

/* clock_cycle() calls read_instruction() on the ith instruction written in 
the program memory, where i = pc */
void clock_cycle(iCPU*);

/* run_program() sets the program counter to 0, and then executes
clock cycles continuously until pc reaches the end of the program memory, 
after which it prints "program finished". */
void run_program(iCPU*);

#endif