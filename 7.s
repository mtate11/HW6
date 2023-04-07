# Using only the MIPS32 instructions described below, write the code for a MIPS32 function
# named with the label numberOfBitsNotSet that, when given a 32-bit integer parameter, returns the
# number of times a zero bit occurs within the 32-bit encoding of that integer. According to the standard
# calling conventions of MIPS32 assembly, the integer to be checked will be passed as register a0 and
# the returned value resulting from the check should be stored in register v0.

# For example, the 32 bit sequence 00001110100100111100100101110000 encodes the value 244566384.
# Because this bit sequence contains 14 ones and 18 zeros, then your code should set register v0 to 18
# if a0 is set to 244566384. If instead a0 is set to 3 then the code should set v0 to 30 since the bit
# sequence 00000000000000000000000000000011 has 2 ones and 30 zeros.

# The registers you can access are named $v0-v1, $a0-a3, $t0-t9, $s0-s7, $sp, $fp, and $ra.

# ----------------------------------------
# Data Declarations (change the variable x to test
# numberOfBitsNotSet, I used 3 (its commented out)
# and 244566384 as seem below).
.data
# x:            .word 3 # 30 zeros
x:            .word 244566384 # 18 zeros

# ----------------------------------------
# Main Routine
.text
.globl  main
.ent    main
main:
        addi $sp, $sp, -4 
        lw $a0, x
        sw $a0, ($sp) # save x to $sp
        jal numberOfBitsNotSet

# -----
        # printing the results and deallocating
        addu $sp, $sp, 4 # deallocate arguments
        move $a0, $v0 # place result in $a0
        li $v0, 1 # code to print $a0 as integer
        syscall # print $a0 to the console as integer

# -----
# Done, terminate program.

        li $v0, 10 # call code for terminate
        syscall # system call (all done!)
.end main

# ----------------------------------------
# Function to count the zeros of a binary number
# -----
# stack
#       $sp - PC       
#       $4($sp) – integer x
# Returns
#       $v0 - int number of zeros

.globl numberOfBitsNotSet
.ent numberOfBitsNotSet
numberOfBitsNotSet: 
        addi $sp, $sp, -4 # allocate space for PC
        sw $ra, ($sp) # save PC

        li $t0,0 # i = 0 for loop
        lw $t1, 4($sp) # load our int into $t1
        li $v0, 0 # initialize $v0 to store the number of zeros

loop:
        and $t2,$t1,1 #and number with 1
        beqz $t2,increaseZero # branch if $t2 is equal to 0
        j exit

increaseZero:
        addi $v0,$v0,1 # increases 0-bit count by 1

exit:
        srl $t1,$t1,1
        addi $t0,$t0,1
        blt $t0,32,loop # iterate throught 32-bit 

        # return our result and deallocate
        lw $ra, ($sp)
        addi $sp, $sp, 4
        jr $ra
.end numberOfBitsNotSet