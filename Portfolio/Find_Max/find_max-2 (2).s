	.file	"find_max_template.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"The length of the array is %d\n"
	.text
	.globl	Find_Max
	.type	Find_Max, @function
Find_Max:

/* Prologue - setting up the stack */
    .cfi_startproc
    endbr64 
    pushq  %rbp 
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6  
//end of Prologue
 
/* reserve space for local variables */
    subq    $32, %rsp #reserving space on the stack
    movl    %edi, -20(%rbp) #holds value of "n", length of array
    movq    %rsi, -32(%rbp) #holds value of &A[0] and puts the pointer to stack
    movl    $0, -8(%rbp) #0 value for max_index
    movl    $1, -4(%rbp) #1 value for "i"
    jmp     TOP_OF_LOOP #jump to TOP_OF_LOOP without conditions
        

/* Function to find index of the maximum value */

//Finds the value of number in array in index 
FOR_TRUE_CONDITIONAL:
    movl    -8(%rbp), %eax #store max_index in eax
    cltq #sign extends 4 bytes to 8 (same thing as movslq) 
    leaq    0(,%rax,4), %rdx #Moving address of pointer to %rdx
    movq    -32(%rbp), %rax #dereference address of A and put inside rax
    addq    %rdx, %rax #add address of pointer to rax 
    movl    (%rax), %edx #dereference rax and store in edx

//Same as before but now storing value of "i" in eax instead of max_index
    movl    -4(%rbp), %eax #store value of "i" in eax
    cltq
    leaq    0(,%rax,4), %rcx
    movq    -32(%rbp), %rax
    addq    %rcx, %rax
    movl    (%rax), %eax
    cmpl    %eax, %edx #compare eax and edx (the value of index A[i] and A[max_index]) 
    jge     TRUE_BLOCK #if greater than or equal to, jump to TRUE_BLOCK
 
    movl    -4(%rbp), %eax #if less than, put value of "i" into %eax
    movl    %eax, -8(%rbp) #changes max_index to current value of "i"

/* Incrementing the value i */
TRUE_BLOCK:
    addl    $1, -4(%rbp) #increments the value i by 1

/* Looks at the top of the for loop conditional to determine whether "i" is less than "n" */
TOP_OF_LOOP:
    movl    -4(%rbp), %eax #move value of "i" into eax
    cmpl    -20(%rbp), %eax #compares "i" value and the "n" value
    jl      FOR_TRUE_CONDITIONAL #if "i" is less than "n", jump to FOR_TRUE_CONDITIONAL
    

/* Returns value of max_index and epilogue */
    movl    -8(%rbp), %eax
    leave
    .cfi_def_cfa 7, 8
	ret
    .cfi_endproc


.LFE0:
	.size	Find_Max, .-Find_Max
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
