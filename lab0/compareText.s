SYSEXIT = 1
EXIT_SUCCESS = 0
SYSREAD = 3
SYSWRITE = 4
STDIN = 0
STDOUT = 1

.text
msg: .ascii "Write text (): \n"
msg_len = . - msg

true: .ascii "sa takie same \n" 
true_len = . - true

false: .ascii "nie sa takie same \n"
false_len = . - false


.data
buf: .ascii "       "
buf_len = . - buf

slowo: .ascii "kwiatek"


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

mov $buf_len, %esi            #licznik petli, ktora porownuje slowa znak po znaku - ma dlugosc rowna dlugosci slowa w pamieci


mov $buf, %ebx                  #wstaw wskaznik na pierwszy element bufora              
mov $slowo, %ecx                #wskaznik na pierwszy element slowa porownywanego

porownaj:

mov (%ebx), %al                 #kopiuje wskazany bit do akumulatora
mov (%ecx), %dl                 #kopiuje wskazany bit na rejestr dl
cmp %dl, %al                    

jne rozne                       #jesli okaze sie ze ktorekolwiek bity sa rozne, skacze do etykiety rozne               

inc %ebx                        #przesuwa wskazniki na nastepny
inc %ecx
dec %esi                        #zmiejsza licznik o 1
jnz porownaj                    #wraca na poczatek petli


mov $SYSWRITE, %eax     #wyswietla jesli oba teksty sa takie same
mov $STDOUT, %ebx
mov $true, %ecx
mov $true_len, %edx
int $0x80
jmp end

rozne:
mov $SYSWRITE, %eax     #wyswietla jesli nie sa takie same
mov $STDOUT, %ebx
mov $false, %ecx
mov $false_len, %edx
int $0x80

end:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80

