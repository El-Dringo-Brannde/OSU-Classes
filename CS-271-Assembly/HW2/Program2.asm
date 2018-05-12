TITLE Program Template     (template.asm)

; Author: Brandon Dring
; Course / Project ID: CS 271, HW #2    Date:1/24/16
; Description: Calculates the Fibonacci numbers between 1, and whatever
; the user decides to go up to. Includes range checking to make sure input is
; between 1 and 46.

INCLUDE Irvine32.inc

;================================================================================
;Constants
;=================================================================================
upperbound equ 47
lowerbound equ 1

;=================================================================================
.data
;=================================================================================


prog_name BYTE "Fibonacci Number Program", 0
credit BYTE "Professionally built by Brandon Dring", 0
ask_name byte "What's your name?", 0
direction byte "Enter the number of fibonacci numbers you want", 0
description BYTE "This is a Fibonacci sequence generator, use at your own risk :D", 0
range byte 	"The range must be between 1-46",0
talk byte "Alright let's get this thing started, ", 0
prompt_int byte "Enter how high you want to do the fibonacci sequence ", 0
user_name DWORD 32 dup(0)
user_int DWORD ?
byte_count DWORD ?
proud byte "I'm so proud of you for good input :) " , 0
go_time byte "The fibonacci numbers are..", 0
val1 DWORD ?
val2 DWORD ?
sum DWORD ?
byebye BYTE "Results certified by Brandon Dring :D", 0
goodbye BYTE "Goodbye, ",0


;===============================================================================
.code
;===============================================================================
main PROC

;==============================================================
Intro:
;program intro
;==============================================================
mov 	edx, offset prog_name	;intro
call 	writestring
call 	crlf

mov 	edx, offset credit 	;my name
call 	writestring
call 	crlf
call	crlf

mov 	edx, offset ask_name 	;asks for name
call 	writestring
call 	crlf

mov 	edx, offset byte_count 	;reads string from user
mov 	ecx, sizeof user_name
call 	readstring
call 	crlf


;==============================================================
userInstructions:
;directs user
;==============================================================
mov 	user_name, edx
mov 	edx, offset talk	 ;intro to user name
call 	writestring
mov 	edx, offset byte_count 	;prints back out the user name
call 	writestring
call 	crlf
mov 	edx, offset description 	;tells what program does
call 	writestring
call 	crlf
call	crlf

mov 	edx, offset direction 	;asks for amount user wants to use
call 	writestring
call 	crlf



;===============================================================
isvalid: 			;checks to see if the input is valid
;===============================================================
mov 	edx, offset range ;shows user range to be used
call 	writestring
call	crlf
call 	readint
mov 	user_int, eax
cmp 	user_int, upperbound 	;checks if input is <= 46
JGE 	isvalid		;jumps to top of segment (Post test)
cmp 	user_int, lowerbound	; checks if input is >= 0
JLE 	isvalid
mov 	edx, offset proud
call 	writestring		;proud of good input
call 	crlf
mov 	edx, offset go_time
call 	writestring
call 	crlf
call 	crlf

;Preps for the fib_seq by initializing the values to be used
mov		val1, 0
mov		val2, 1
mov		sum, 0
dec		user_int
mov 	ecx, user_int
mov 	ebx, 1


;===============================================================
fib_seq:
; calculates the fibonacci sequence
;===============================================================
mov		eax, val1
add		eax, val2	;adds values together
call	writedec	;prints out fib number
call	crlf
mov		sum, eax	;moves addition to sum
mov		eax, val2 	;move val2 and val1
mov		val1, eax
mov		eax, sum
mov		val2, eax 	;move sum of this iteration to val2
loop 	fib_seq		;jump back to top of loop



;===============================================================
Adios: ;tells user bye bye
;===============================================================
call	crlf
mov		edx, OFFSET byebye
call	writestring
call 	crlf
mov 	edx, OFFSET goodbye
call 	writestring
mov		edx, OFFSET byte_count
call 	writestring
call 	crlf

	exit	; exit to operating system

	main ENDP

END main
