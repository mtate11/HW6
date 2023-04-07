# MIPS function call problem - MIPS code 
# that emulates the following C code:
        # int g(int y) {
        #         int i = 3;
        #         return i + y;
        # }
        # int f(int x) {
        #         int i = 5;
        #         i = i + g(x);
        #         return i;
        # }
        # int main() {
        #         int z = 2;
        #         z = f(z);
        #         z++;
        #         return 0;
        # }
# z should end up being 11

# ----------------------------------------
# Data declarations go in this section.
.data

# ----------------------------------------
# Program code goes in this section.
.text
.globl  main
.ent    main
main:
        # int main() {
        #         int z = 2;
        #         z = f(z);
        #         z++;
        #         return 0;
        # }
# -----
        # allocate memory for z
        addu $sp, $sp, -4 # extend the stack downwards by 4 bytes
        li $t0, 2
        sw $t0, ($sp) # assign z to be 2

        # jump to the instruction inside the function f
        jal f # store current PC in $ra, then jump to j
        move $t0, $v0 # places result of f(z) in z
        addu $t0, $t0, 1 # z++
        move $a0, $t0 # move z to $a0 

        addu $sp, $sp, 4 # deallocate arguments
        li $v0, 1 # code to print $a0 as integer
        syscall # print $a0 aka z to the console as integer

# -----
# Done, terminate program.

        li $v0, 10 # terminate
        syscall # all done!
.end main 

# ----------------------------------------
# Function f()
        # int f(int x) {
        #         int i = 5;
        #         i = i + g(x);
        #         return i;
        # }
# -----
# Stack:
        # ($sp) - addr of i
        # 4($sp) - PC
        # 8($sp) - addr of x

.globl f
.ent f
f:
        addu $sp, $sp, -4 # allocate space to save PC
        sw $ra, ($sp) # save PC on stack
        
        addu $sp, $sp, -4 # allocate space for local vars
        li $t0, 5 
        sw $t0, ($sp) # assigns i to be 5

        lw $t0, ($sp) # loads i in $t0
        lw $t1, 8($sp) # loads x into $t1

        # jump to the instruction inside the function g
        jal g # store current PC in $ra, then jump to g

        move $t3, $v0 # sets $t3 as g(x) result
        add $t0, $t0, $t3 # i = i + g(x);
        move $v0, $t0 # returns i

        # exit and return to main
        lw $ra, 4($sp) # put saved PC in $ra to jump to it
        addu $sp, $sp, 8 #deallocate local vars
        jr $ra # jump back to where we were in main
.end f

# ----------------------------------------
        # int g(int y) {
        #         int i = 3;
        #         return i + y;
        # }
# -----
# Stack:
        # ($sp) - addr of i
        # 4($sp) - PC
        # 8($sp) - addr of i
        # 12($sp) - PC
        # 16($sp) - addr of x

.globl g
.ent g
g:
        addu $sp, $sp, -4 # allocate space to save PC
        sw $ra, ($sp) # save PC on stack
        
        addu $sp, $sp, -4 # allocate space for local vars
        li $t0, 3 
        sw $t0, ($sp) # assigns i to be 3

        lw $t1, 16($sp) # load y (aka x) into $t1
        add $t0, $t0, $t1 # $t0 = i + y
        move $v0, $t0 # returns i + y

        # exit and return to f
        lw $ra, 4($sp) # put saved PC in $ra to jump to it
        addu $sp, $sp, 8 #deallocate local vars
        jr $ra # jump back to where we were in f
.end g