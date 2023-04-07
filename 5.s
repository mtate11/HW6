# MIPS array problem. MIPS code that takes 
# two arrays of 32-bit integers, xs and ys. 
# Assumes that a pointer to the 0th element of 
# xs is stored in $a0 and the length of xs is 
# stored in $a1. Assumes that a pointer to the 
# 0th element of ys is stored in $a2 and the 
# length of ys is stored in $a3. For each 
# element y in ys, the code should performs
# the MIPS equivalent of xs[y]++.

# ----------------------------------------
# Data declarations go in this section.
.data
# xs:                .word 10, 5, 3, 1, 9  
        # result should be: 4, 11, 2, 10
xs:                .word 1, 3, 5, 15, 27
        # result should be: 6, 2, 16, 28

length_xs:         .word 5
ys:                .word 2, 0, 3, 4
length_ys:         .word 4

# ----------------------------------------
# Program code goes in this section.
.text
.globl  main
main:
        la $a0, xs # loads address of xs array in $a0
        lw $a1, length_xs # loads length of xs array in $a1
        la $a2, ys # loads address of ys array in $a2
        lw $a3, length_ys  # loads length of ys array in $a3
        li $t0, 0 # $t0 is stores the iterator (i)
        
        move $t8, $a0
begin_loop:
        beq $t0, $a3, exit_loop

        sll $t1, $t0, 2 # $t1 = i * 4
        add $t1, $t1, $a2 # $t1 = &(ys[i]) 
        lw $t3, 0($t1) # $t3 = y[i]

        sll $t3, $t3, 2 # t3 = y[i] * 4
        add $t4, $t3, $t8 # $t4 = &(xs[y[i]])
        lw $t3, 0($t4)
        addi $t3, $t3, 1

        # syscall to print value
        li      $v0, 1      
        move    $a0, $t3
        syscall
        # syscall for printing character (space)
        li      $a0, 32
        li      $v0, 11  
        syscall

        # increment loop: i = i+1
        addi $t0, $t0, 1 
        j begin_loop

exit_loop:
# -----
# Done, terminate program.
        li $v0, 10 # call code for terminate
        syscall # system call (all done!)
        
.end main

