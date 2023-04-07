#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include "hw6.h"
//#include "hw6.c"

int main() {

    iCPU* cpu_ptr = iCPU_init();

    printf("## TESTING read_instruction():\n");    
    uint32_t x = 0b00000001000000000000000000001010;
    uint32_t x2 = 0b00001001000000000000000000000000;
    uint32_t x3 = 0b00000010000000000000000100000000;
    read_instruction(0b00000001000000010000000000000010, cpu_ptr); // put 2 in r1
    read_instruction(x, cpu_ptr); // put 10 in r0
    read_instruction(0, cpu_ptr); // print r0
    read_instruction(x3, cpu_ptr); // adds: r0 = r0 + r1 = 10 + 2 = 12
    read_instruction(0, cpu_ptr); // print r0
    read_instruction(x2, cpu_ptr); // terminates
    printf("^ The above should print a 10 and then a 12\n\n"); 

    printf("## TESTING write_instruction():\n"); 
    write_instruction(1, 0, 0, 10, 0, cpu_ptr);
    write_instruction(0, 0, 0, 0, 1, cpu_ptr);
    write_instruction(9, 0, 0, 0, 2, cpu_ptr); // terminates 
    printf("prog[1]: %d\n", cpu_ptr->prog[0]); //should print the decimal num 16777226
    printf("prog[2]: %d\n", cpu_ptr->prog[1]); //should print the decimal num 0
    printf("prog[3]: %d\n", cpu_ptr->prog[2]); //should print the decimal num 150994944
    
    run_program(cpu_ptr);
    printf("PC count: %d\n", cpu_ptr->pc); //print pc counter should be 32
    iCPU_destroy(cpu_ptr);

    /////////////////////////////////////////////////////////////////////////////////////////
    /* PROBLEM 2e. Using write_instruction() to write a program on an iCPU that performs the 
    same CPU operations as Checkpoint 3 from homework 5 (init and destroy are not CPU 
    operations, they should not be included in the program). Use run program() to run it.
    The code from Checkpoint 3 from homework 5:
        struct sCPU* cpu_ptr = CPU_init();
        CPU_step(1,1,0,4, cpu_ptr); // put a 4 into r1
        CPU_step(1,2,0,6, cpu_ptr); // put a 6 into r2
        CPU_step(2,0,1,2, cpu_ptr); // r0 = r1 + r2
        CPU_step(5,0,0,1, cpu_ptr); // r0 = r0 * r1
        CPU_step(0,0,0,0, cpu_ptr); // print r0
        CPU_destroy(cpu_ptr);
        The above should result in printing 40 to the console */
    /////////////////////////////////////////////////////////////////////////////////////////

    printf("\n## PROBLEM 2 e) should print 40: result ");
    iCPU* cpu_ptr2 = iCPU_init();
    write_instruction(1, 1, 0, 4, 0, cpu_ptr2);
    write_instruction(1, 2, 0, 6, 1, cpu_ptr2);
    write_instruction(2, 0, 1, 2, 2, cpu_ptr2);
    write_instruction(5, 0, 0, 1, 3, cpu_ptr2);
    write_instruction(0, 0, 0, 0, 4, cpu_ptr2); 
    write_instruction(9, 0, 0, 0, 5, cpu_ptr2); // terminates 
    run_program(cpu_ptr2);
    iCPU_destroy(cpu_ptr2);

    /////////////////////////////////////////////////////////////////////////////////////////
    //// Executing Machine Instructions (PROBLEM 4) ////
    /////////////////////////////////////////////////////////////////////////////////////////
    /* program on an iCPU that computes x++ 100 times, assuming x is stored in the 20th 
    place in ram. It prints x (using the print instruction in iCPU step()), and then 
    terminates. The program use run program() to run it.*/
    
    printf("\n## PROBLEM 4 CODE OUTPUT BELOW\n");
    iCPU* cpu_ptr3 = iCPU_init();

    // X-value one line below, write_instruction(1,0,change this to change x, change this to change x,0,cpu_ptr3)
    write_instruction(1,0,0,100,0,cpu_ptr3); // puts x value in r0
    printf("Your x-value is: ");
    write_instruction(0,0,0,0,1,cpu_ptr3); // print x
    write_instruction(1,1,0,20,2,cpu_ptr3); // puts 20 in r1
    write_instruction(3,0,1,0,3,cpu_ptr3); // stores x in ram[20]
    write_instruction(1,2,0,1,4,cpu_ptr3); // puts 1 in r2
    write_instruction(1,4,0,100,5,cpu_ptr3); // puts 100 in r4
    write_instruction(1,5,0,0,6,cpu_ptr3); // puts 0 in r5, to be the iterator

    write_instruction(7,5,4,12,7,cpu_ptr3); // bnq i = 100
    write_instruction(4,3,1,0,8,cpu_ptr3); // loads ram[20] into r3
    write_instruction(2,0,2,3,9,cpu_ptr3); // r0 = x + 1
    write_instruction(3,0,1,0,10,cpu_ptr3); //stores r0 into ram[20]
    write_instruction(2,5,5,2,11,cpu_ptr3); // i++
    write_instruction(8,5,4,7,12,cpu_ptr3); // bne i != 100

    write_instruction(0, 0, 0, 0, 13, cpu_ptr3); // print result
    write_instruction(9, 0, 0, 0, 14, cpu_ptr3); // terminates 
    run_program(cpu_ptr3);
    iCPU_destroy(cpu_ptr3);

    return 0;
}