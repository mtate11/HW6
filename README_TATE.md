## Homework 6: Assembly and Architecture Part 2

To compile this code, run the following command:

```gcc hw6.c test.c -o test```

### 1. Completing the CPU model
- **WHERE**: code for the struct iCPU is in hw6.h. The code for iCPU_init(), iCPU_destroy() and iCPU_step() is in hw6.h and hw6.c. 
- **HOW**: 
    - run iCPU_init() by setting struct iCPU <name> = iCPU_init(). The function allocates a new iCPU on the heap, put zeros in all of the slots in the registers and RAM, and then returns a pointer to the new iCPU.
    - run iCPU_destroy() by inputting a pointer to  (heap-allocated) iCPU, the function frees it.
    - run iCPU_step() by inputting a uint8_t opcode, three additional uint8_ts called arg1, arg2, and arg3, as well as a pointer to an iCPU. Runs the operations of print, put, add, store, load, mul, jump, beq, bne, and terminate. Read the notes above iCPU_step() in hw6.h for more information on each individual operation.
- **NOTES**: 

### 2. Running programs on our CPU (!)
- **WHERE**: code for read_instruction(), write_instruction(), clock_cycle() and run_program() is in hw6.h and hw6.c. Code that emulates checkpoint 3 from last week’s homework (part e), is in test.c.
- **HOW**:
    - run read_instruction() by inputting a uint32_t (its easiest to do so in binary form to make sure you are doing the instruction you want) and a pointer to an iCPU. This function results in a call to iCPU_step().
        example: read_instruction(0b00000001000000010000000000000010, cpu_ptr); // put 2 in r1
    - run write_instruction() by inputting a 8-bit opcode, 8-bit arg1, arg2, and arg3, a int line_num, and a pointer to an iCPU. The instuctions of write_instruction() work via calling run_program().
        example: write_instruction(1, 0, 0, 10, 0, cpu_ptr); // puts a 10 in r0
    - clock_cycle() doesn't need to be called by the user, as it is called in run_program()
    - run run_program() by inputting a pointer to an iCPU. run_program() sets the program counter to 0, and then executes clock cycles continuously until pc reaches the end of the program memory, after which it prints "program finished". 
        example: run_program(<cpu_ptr>);
- **NOTES**:

/* write_instruction() takes an 8-bit opcode, an 8-bit arg1, arg2, and arg3, 
and an int line_num and a pointer to an iCPU. It concatenates the first four
arguments into a single uint32_t, and places the concatenated instruction 
at prog[line num]. */
void write_instruction(uint8_t, uint8_t, uint8_t, uint8_t, int, iCPU*);

/* run_program() sets the program counter to 0, and then executes
clock cycles continuously until pc reaches the end of the program memory, 
after which it prints "program finished". */
void run_program(iCPU*);


### 3. iCPU_step(): Control Unit Instructions
- **WHERE**: code for the extended version of iCPU_step(), (it includes jump, beq, bne, and terminate) in hw6.h and hw6.c
- **HOW**: either directly call iCPU_step() as indicated above, or use write_instruction() (with the specifications indicated above).
    - jump instruction: executed when the opcode is 6. Sets pc = arg3 (interpreted as an immediate). 
    (After setting the pc it returns immediately – i.e. it doesn't increment pc by 1 afterwards).
    - beq (branch equal) instruction: executed when the opcode is 7. It compares the values stored 
    in the registers indicated by arg1 and arg2. If they are equal, it sets pc = x where x is 
    arg3 interpreted as an immediate (and then immediately returns). Otherwise, does nothing
    (though pc is incremented as normal).
    - bne (branch not equal) instruction: executed when the opcode is 8. Does the same as beq but 
    flips the cases.
    - terminate instruction: executed when the opcode is 9. It sets the program counter so that 
    the program finishes after it is executed (when run using run_program()). */
- **NOTES**:

### 4. Executing Machine Instructions
- **WHERE**: code is in test.c
- **HOW**: Run by running the compiled test.c file. x is indicated so that you can change it to test the program.
Its code / a program on an iCPU that computes x++ 100 times, assuming x is stored in the 20th place in ram. Then it prints x (using the print instruction in iCPU_step()), and then terminates, it uses run program() to run it.
- **NOTES**:

### 5. MIPS array problem
- **WHERE**: code is in 5.s
- **HOW**: run the file in QtSpim. Preforms opperation of xs[y]++ where xs is an array of 32-bit integers, and y is each element from ys (another array of 32-bit integers).
- **NOTES**: I coded it so the result should be printed to the console. You can change the values of the arrays, ys and xs, as well as the length of the arrays under the .data section.

### 6. MIPS function call problem
- **WHERE**: code is in 6.s file
- **HOW**: run the file in QtSpim. The code emulates C code arithmetic function code, and should result in z = 11.
- **NOTES**: I have the console print z so the user knows that the functions are working correctly.

### 7. MIPS qual problem
- **WHERE**: code is in 7.s
- **HOW**: run the file in QtSpim. Input a 32-bit number (x, under .data section), the code prints the number of 0's in the binary representation of the number.
- **NOTES**: I coded it so the result (the number of 0's of the 32-bit number) should be printed to the console. You can change the int, as it is listed by the label 'x:' under .data section.