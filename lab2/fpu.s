SYSEXIT = 1
EXIT_SUCCESS = 0

.section .data

zero: .float 0
none: .float -1.0
num1: .float 10
num2: .float 100 


#control word:

    #precision
    single: .word 0x0000
    reserved: .word 0x0100
    double: .word 0x0200
    doubleExtended: .word 0x0300

    #roundings
    nearest: .word 0x0000
    down: .word 0x0400
    up: .word 0x0800
    cut: .word 0x0c00

    mask: .word 0x007f      #to preserve all exceptions - +/-0, +/-inf, NaN

control_word: .word 0x0  

.text

.global _start
_start:
finit

#double precision and cut

movl double, %eax
movl mask, %ebx
or %ebx, %eax       # stores result in second operand!!!

movl cut, %ebx
or %ebx, %eax

mov %eax, control_word



fldcw control_word

#load numbers to stack 
flds num1
flds num2 
# addition
faddp   

flds num1
flds num2 
# subtraction
fsubp

flds num1
flds num2 
#multiplication
fmulp

flds num1
flds num2 
# division
fdivp

#call IEEE754 exceptions and special values:

finit

movl single, %eax
movl mask, %ebx
or %ebx, %eax       

movl up, %ebx
or %ebx, %eax

mov %eax, control_word

fldcw control_word


#+0
flds zero
flds zero
fsubp

#-0
flds zero
flds none
fmulp

#-inf
flds zero
flds none
fdivp

#inf
flds zero
flds num1
fdivp

#NaN
flds zero
flds zero
fdivp

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
