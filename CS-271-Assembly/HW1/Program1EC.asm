TITLE Program #1     (template.asm)

; Author: Brandon Dring
; Course / Project ID:  CS 271, Program 1    Date: 1/08/16
; Description: Addtwo.asm

;-------------------------------------------------

INCLUDE Irvine32.inc
.386
.model flat,stdcall
.stack 4096
EXITProcess PROTO, dwExitCode: DWORD

; ------------------------------------------------
.data


intro BYTE "Program #1, By Brandon Dring.",0
script BYTE "Enter 2 numbers, and I'll show you the sum, difference", 0
script2 BYTE "product and quotient, and the remainder!", 0
firstnum DWORD ?
secnum DWORD ?
mulnum DWORD ?
temp DWORD ?
xtracred BYTE "I did the Extra Credit option #1 giving option to try again", 0
xtratwo BYTE "AND!!! I also did the EC option 2, checking that num2 is < num1", 0
getnum BYTE "What is the first number?", 0
getnum2 BYTE "What is the second number?", 0
bye BYTE "Impressed, huh? Took me forever! Bye!", 0
addit BYTE "The Addition of the two numbers are..", 0
subtr BYTE "The subtraction of the two numbers are..",0
mult BYTE "The multiplication of the two numbers are.. ", 0
divis BYTE "The division of the two numbers are.. ", 0
reman BYTE " Remainder: ", 0
numtest BYTE "The second number must be less than the first!", 0
tryagain BYTE "Would you like to try again? '1' for yes, '2' for no", 0
joke BYTE "You done son!", 0

;-------------------------------------------------
.code
main PROC

mov		edx, OFFSET intro
call	WriteString		;Title and my name
call	CrLf
mov		edx, OFFSET xtracred
call	WriteString		;says that I did Extra Credit
call	Crlf
mov		edx, OFFSET	xtratwo
call	WriteString
call	Crlf
call	Crlf

;Program description
mov		edx, OFFSET script	;gives intro and tells user what to do
call	WriteString
mov		edx, OFFSET script2	;explains program
call	WriteString
call	CrLf

;prompt user for numbers
start:						; section of program to be reset on
mov		edx, OFFSET getnum	;asks for first num
call	WriteString
call	Crlf
call	ReadInt		; get's first number to compute
mov		firstnum, eax	; moves value to firstnum for maths later
mov		edx, OFFSET getnum2
call	WriteString		;asks for second number to compute
call	Crlf
call	ReadInt		;reads second number
call	Crlf
mov		secnum, eax		;also moves eax to variable to be used later

mov 	eax, firstnum
cmp 	eax, secnum		;test the numbers to make sure num2 < num1
JLE		 Byebye		;jump to outro


;Doing the addition/subtract
mov		eax, secnum		;moves variable to register for math prep
add		eax, firstnum	; adds the two variables together
mov		edx, OFFSET addit	;writes addtion
call	WriteString
call	WriteDec	; writes added value
call	Crlf
mov		eax, firstnum
sub		eax, secnum		;subtracts the two variables
mov		edx, OFFSET subtr
call	WriteString
call	WriteDec	; prints subtraction value
call	Crlf

; Multiple the two numbers
mov		eax, 0			;clears eax register and sets to 0
mov		eax, firstnum
mov		ebx, secnum
mul		ebx				;multiplies variables together
mov		mulnum, eax
mov		eax, mulnum
mov		edx, OFFSET mult
call	WriteString
call	WriteDec		;prints the multipled value
call	Crlf

;Divide the two numbers

mov		edx, OFFSET divis
call	WriteString
mov		eax, firstnum
cdq						;extend sign to EDX
mov		ebx, secnum
div		ebx
call	WriteDec		;prints divisible value
mov		eax, 0		;clear eax register
mov		eax, edx	;prep remainder for printing
mov		edx, OFFSET reman
call	WriteString		;prints remainder value
call	WriteDec		;prints remainder
call	Crlf
call	Crlf

;Outro/try again?
mov		edx, OFFSET tryagain
call	Writestring		;gives option to play again
call	Crlf
call	ReadInt
cmp		eax, 1
JE		start		;if input = 1 starts program again
jmp		Done		; jump to quit


Byebye:
mov		edx, OFFSET numtest
call	Writestring		; number 2 must be lower than num 1
call	Crlf
mov		edx, OFFSET tryagain
call	Writestring		;prompt user to try again
call	Crlf
call	ReadInt
cmp		eax, 1
JE		start		; jump back to start if input = 1

; Ends program
Done:
mov		edx, OFFSET bye
call	Writestring
call	crlf
INVOKE ExitProcess, 0

	exit	; exit to operating system
main ENDP
END main
