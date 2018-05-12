TITLE Homeowork #4     (template.asm)

; Author: Brandon Dring
; Course / Project ID: CS 271, Homework #4    Date: 2/12/16
; Description: Calculates a range of composite numbers from 0-400
; Depending on user input.


;=============================================================
INCLUDE Irvine32.inc

upperbound = 400
lowerbound = 1
;=============================================================

;==============================================================
.data
;-------------------------------------------------------------
author BYTE "Composite Numbers, Built by Brandon Dring", 0
intro  BYTE "Enter the number of composite number you would like to see. ",0
intro2 BYTE "I accept orders for numbers up to 400", 0
getnum BYTE "Enter the number of composites to display [0..400] ",0
excred	BYTE	"With extra credit! The outputs are aligned! (EC #1)", 0
usernum DWORD ?
holdnum	DWORD	?
outro 	BYTE	"Results certified by Brandon Dring",0
done BYTE 	"You done son!", 0
linecnt		DWORD	?
blank	BYTE	"   ", 0
compcount DWORD ?

;===============================================================
.code
;---------------------------------------------------------------
main PROC
call	heyo

call	getinfo

call	mathworks

call 	byebye

	exit	; exit to operating system
main ENDP
;===================================================


;----------------------------------------------------
;Procedure to introduce user to program, and tell my
;name
;receives: none
;Preconditions: None
;returns: none
; Registers changed: none
;====================================================
heyo	PROC

mov		edx, offset author
call	writestring		;tells the player my name
call	crlf
mov		edx, offset	excred
call	writestring
call	crlf
mov		edx, offset intro
call	writestring
call	crlf
call	crlf
mov		edx, offset intro2
call	writestring
call	crlf


ret
heyo ENDP
;====================================================

;----------------------------------------------------
;Procedure to bid farewell to user.
;Preconditions: None
;receives: none
;Returns: none
;Registers changed: none
;====================================================
byebye 	PROC
call	crlf
mov 	edx, offset outro
call 	writestring
call 	crlf
mov 	edx, offset done
call 	writestring
call 	crlf
ret
byebye ENDP
;=====================================================

;-----------------------------------------------------
;Procedure to check if the number is prime, if not,
;increment until it reaches the value of the divisor
;if it is not prime, print it.
;Recieves: None
;Returns: None
;Preconditions: None
;Registers changed: EAX, EBX, ECX, EDX
;=====================================================
MATHWORKS	PROC
mov		eax, 4
mov		holdnum, 4
mov		compcount, 0	;initializes print counter
mov		linecnt, 0	;initializes line counter

primeloop:		;while loop
mov		edx, compcount
cmp		edx, usernum	;checks to see if printed #'s == usernum entered
JE		fin		;jump to return
mov		ebx, 2		;start dividing at 2
cdq
div		ebx			;divide usernum by ebx
cmp		edx, 0		;check to see if remainder is 0
JE		print	;jumps to print if remainder = 0
mov		ebx, 3
JNE		inloop

inloop:
mov		eax, holdnum	;moves original value back to eax
cdq
div		ebx
CMP		edx, 0	;checks if remainder is 0 when divided by 3
JE		print  	;jumps to print if remainder = 0
CMP		ebx, eax	;checks to make sure divisor isnt less than divider
JL  	again
inc		ebx		;increments divider by 1

back:
mov		eax, holdnum
inc		eax		;increments divisor by 1
inc		holdnum	;increments divider holder by 1
loop	primeloop

print:
call	printcompnum	;prints the number if it is composite <---SUB-PROC!!!
cmp		linecnt, 10	;check to make sure num count in line isn't 10
JE		skip
JMP		back

skip:
call	crlf
mov		linecnt, 0
JMP		back


again:
inc		ebx		;increments divisor by one to be divided again
JMP		inloop

fin:

ret
Mathworks ENDP
;============================================================

;------------------------------------------------------------
;Procedure prints the composite number, increments linecount and
;composite number count
;Recieves: None
;Returns: None
;Preconditions: Number must be composite
;============================================================
printcompnum	PROC

mov		eax, holdnum	;prints whatever number has remainder 0
call	writedec
mov		edx, offset blank	;add's blank after num
call	writestring
inc		compcount
inc		linecnt

ret
printcompnum	ENDP


;------------------------------------------------------------
;Procedure gets user number and validates the data entered
;Recieves: none
;Returns: none
;Preconditions: None
;Registers used: EAX
;============================================================
GETINFO		PROC

call	failedtry	;<------ SUB-PROC!!!

mov		usernum, eax

ret
getinfo		ENDP
;============================================================


;------------------------------------------------------------
;Procedure prompts user to get number, and does input validation
;Receives: None
;Returns: None
;Preconditions: None
;Registers used: EAX
;=============================================================

failedtry		PROC
tryagain:

mov		edx, offset getnum
call	writestring		;prints get num range
call	readdec

CMP		eax, upperbound
JG		tryagain	;checks against upperbound
CMP		eax, lowerbound
JL		tryagain	;checks against lowerbound

ret
failedtry		ENDP
;==============================================================


END main
