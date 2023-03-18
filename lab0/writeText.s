SYSEXIT = 1
EXIT_SUCCESS = 0
SYSREAD = 3
SYSWRITE = 4
STDIN = 0
STDOUT = 1

.text
msg: .ascii "Write text (5): \n"
msg_len = . - msg

msg2: .ascii "Written text: "
msg2_len = . - msg

newline: .ascii "\n"
newline_len = . - newline

.data
buf: .ascii "     "
buf_len = . - buf

.global _start
_start:

mov $SYSWRITE, %eax     #wyswietla tekst msg
mov $STDOUT, %ebx
mov $msg, %ecx
mov $msg_len, %edx
int $0x80

mov $SYSREAD, %eax      #zczytuje tekst z klawiatury
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $SYSWRITE, %eax     #wyswietla tekst msg2
mov $STDOUT, %ebx
mov $msg2, %ecx
mov $msg2_len, %edx
int $0x80

mov $SYSWRITE, %eax     #wyswietla tekst buf
mov $STDOUT, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $SYSWRITE, %eax     #wyswietla tekst newlina
mov $STDOUT, %ebx
mov $newline, %ecx
mov $newline_len, %edx
int $0x80


mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80


