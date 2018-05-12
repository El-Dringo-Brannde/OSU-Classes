TITLE Program Template     (template.asm)

; Author: Brandon Dring
; Course / Project ID: CS 271, Program #3                Date: 2/2/16
; Description:	Finds the sum and average of a bunch of negative numbers entered by user

INCLUDE Irvine32.inc
;========================================================================================
;CONSTANTS
upperbound	EQU		-100
lowerbound 	EQU 	0
;========================================================================================
.data
;VARIABLES
;========================================================================================
greeting	BYTE	"Welcome to the Integer Accumulator by Brandon Dring", 0
ask_name	BYTE	"What is your name?", 0
get_name	DWORD	 ?
name_size	DWORD	32 dup(0)
talk		BYTE	"Hello, ", 0
direction	BYTE	"Please enter a number between [-100, -1]",0
direction2	BYTE	"When you are done, enter a non negative number to see results",0
roll_sum	SDWORD	?
enter_num	BYTE	"Enter a number: ", 0
user_int	DWORD	?
counter		SDWORD	?
total_num	BYTE	"You have entered: ", 0
numbers		BYTE	" numbers", 0
sum			BYTE	"The sum of the numbers is.. " , 0
average		BYTE	"The rounded integer average of the numbers is.. ", 0
avg			SDWORD	?
outro		BYTE	"Thanks for playing the Integer Accumulator thing!, It's been fun, ", 0
holder		SDWORD	?



.code
main PROC

mov		edx, offset greeting
call	writestring
call	crlf
call	crlf


mov		edx, offset ask_name
call	writestring
call	crlf
call	crlf

mov		edx, offset get_name
mov		ecx, sizeof name_size
call	readstring
call	crlf

mov		edx, offset talk
call	writestring
mov		edx, offset get_name
call	writestring
call	crlf
call	crlf

mov		edx, offset direction
call	writestring
call	crlf
mov		edx, offset direction2
call	writestring
call	crlf
call	crlf


big_loop:
mov		edx, offset enter_num
call	writestring
call	readint
mov		user_int, eax
cmp		user_int, lowerbound
JGE		done
mov		eax, 0
inc		eax
add		counter, eax
mov		eax, user_int
add		roll_sum, eax
cmp		user_int, upperbound
JGE		big_loop


done:
mov		eax, counter
mov		holder, eax
mov		edx, offset total_num
call	writestring
mov		eax, holder
call	writeint
mov		edx, offset numbers
call	writestring
call	crlf
mov		edx, offset sum
call	writestring
mov		eax, roll_sum
call	writeint
call	crlf
mov		edx, offset average
call	writestring
mov		eax, roll_sum
cdq
mov		ebx, holder
idiv	ebx

imul	eax, 2
cdq
mov		ebx, 2
idiv		ebx

call	writeint
call	crlf
mov		edx, offset outro
call	writestring
mov		edx, offset get_name
call	writestring


call	crlf
call	crlf
	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
