.section .text
.global _start
.type _start, @function
_start:
    lea stack_top(%rip), %rsp
    andq $-16, %rsp
    call kernel_main
1:
    hlt
    jmp 1b

.section .data
.align 16
stack:
    .skip 16384
stack_top:
