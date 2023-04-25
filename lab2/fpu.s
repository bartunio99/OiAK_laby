SYSEXIT = 1
EXIT_SUCCESS = 0

.data

num1: .float 1000
num2: .float 12
.text


.global _start
_start:

#load numbers to stack 

flds num1
flds num2 

#add
faddp

flds num1
flds num2 

#subtract
fsubp

flds num1
flds num2 

#multiply
fmulp

flds num1
flds num2 

#divide
fdivp



mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
