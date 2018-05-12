TITLE Program#6B     (template.asm)

; Author: Brandon Dring
; Course / Project ID  CS 271    Date: 3/9/16
; Description: Lets the user guess the answer to a random combinatorics problems
; 	and tells them if they got it right or wrong

INCLUDE Irvine32.inc
;============================================================
mwritestring Macro buffer		;writes with clear line
push 	edx
mov 	edx, offset buffer
call 	writestring
call 	crlf
pop 	edx
ENDM

mwritething 	MACRO 	buffer  	;writes without clear line
push 	edx
mov 	edx, offset buffer
call 	writestring
pop 	edx
ENDM
;==================================================================



;====================================================================
.data
hola 		BYTE 	"Welcome to the Combinatorics Calculator",0
sayname 	BYTE 	"By Brandon Dring",0
descript 	BYTE 	"I'll give you a combinatorics problem, you enter the answer", 0
descript2	BYTE 	"and, I'll let you know if it is right or not", 0
problem 	BYTE 	"Problem: ", 0
numset 		BYTE 	"Number of elements in the set: ", 0
numeleinset	BYTE 	"Number of elements to choose from the set: ", 0
choose 		BYTE	"How many ways can you choose? ", 0
there 		BYTE 	"There are ",0
comb 		BYTE 	" Combinations of ", 0
from 		BYTE 	" from a set of ",0
fail 		BYTE 	"Yikes.. You got it wrong, you should do something about that..",0
dunno 		BYTE 	"I'm not sure how to convert a user string to an int, ",0
dunno2 		BYTE 	"Or how to concatenate a string byte to a DWORD,dock me if you must :(",0
right 		BYTE 	"You deserve a gold star, you got it right!!",0
another 	BYTE 	"Wanna do another problem? (y/n)" ,0
byebye 		BYTE 	"Ok goodbye and have a nice day", 0
againchar	BYTE 	?
randval 	DWORD 	?
R_randval	DWORD 	?
badinput	BYTE 	"Follow directions please :(",0
usr_str 	BYTE 	12 DUP (?)
result 		DWORD 	?
denominator DWORD 	?
r_fact 		DWORD 	?
n_rfact		DWORD 	?
nfact 		DWORD 	?
usr_int		DWORD 	?
n_hi		DWORD 	12
n_lo 		DWORD  	3
r_low		DWORD 	1
;====================================================================


;====================================================================
.code
main PROC

call	randomize
call 	crlf

pushad
call	intro 		;says hi and everything
popad


pushad
push 	offset 	R_randval
push 	r_low
push 	offset randval
push 	n_hi
push 	n_lo
call 	showproblem  	;gets the random values of n and r and shows user the problem
popad


pushad
push 	offset usr_int
push 	offset usr_str
call 	get_data	;gets the guess from the user, I didn't know how to move a string to an int
popad


pushad
push 	offset 	nfact
push 	offset 	n_rfact
push 	offset 	r_fact
push 	offset result
push 	offset denominator
push 	randval
push 	r_randval
call 	combination	;calculates all the factorials of the values in the equation n!/(r!(n-r)!)
popad



pushad
push 	nfact
push 	n_rfact
push 	r_fact
push 	offset result
push 	offset denominator
call 	do_math		;calculates what the actual combinatorics value is from the equation
popad


pushad
push 	usr_int
push 	randval
push 	r_randval
push 	result
call 	show_results 	;shows the actual computer generated correct number, and compares to user input
popad

pushad
call 	try_again 	;gives the user a chance to repeat the program again
popad

mwritestring	byebye 	;says bye bye to the user


	exit	; exit to operating system
main ENDP
;=============================================================
;Description: Gives the opion for the user to start the program over again
;Recieves:  none
;Returns:  none
;Preconditions:  none
;Registers Changed:  none
;=============================================================
try_again	PROC
mwritething 	another
begin:
	call 	readchar
	CMP 	al,  121	;compare to Y
	JNE 	seeya
	JE 		main

seeya:
call 	crlf
ret
try_again 	ENDP
;==============================================================
;Description: Shows the combinatorics output, nrandval, and rrandval
; compares the user and computer output and checks to see if they are right
;Recieves: result, rrandval, nrandval, user_int
;Returns:  none
;Preconditions: none
;Registers Changed: none, all registers saved with push/popad
;=============================================================
show_results	PROC
push 	ebp
mov 	ebp, esp

call 	crlf
mwritething 	there
mov 	eax, [ebp + 8]	;shows result
call 	writedec
mwritething 	comb
mov 	eax, [ebp+12]	;shows rrandval
call 	writedec
mwritething		from
mov 	eax, [ebp + 16]	;shows nrandval
call 	writedec
call 	crlf
call 	crlf

mov 	eax, [ebp+20] 	;gets user_int
mov 	ebx, [ebp + 8] 	;gets resut
cmp 	eax, ebx 	;checks to see if they got it right or wrong
JNE 	bad
JE 		good

good:
	mwritestring 	right

	JMP fin
bad:
	mwritestring	fail

fin:
pop 	ebp
ret		12
show_results 	ENDP
;=================================================================
;Description: calculates the end result from the factorial equation
;Recieves:  rfact, n_rfact, r_fact, n_fact, result, denominator
;Returns:  result, denominator
;Preconditions:  none
;Registers Changed: all registers saved with push/popad
;=================================================================
do_math		PROC
push 	ebp
mov 	ebp, esp

mov 	eax, [ebp + 16]	;gets rfact
mov 	ebx, [ebp + 20]	;gets n-r!
mul 	ebx
mov 	ebx, [ebp + 8]
mov 	[ebx], eax 	;stores r! * (n-r)! in denominator



mov 	eax, [ebp + 24]
mov 	edx, [ebp + 8]	;gets denominator
mov 	ebx, [edx]
mov 	edx, 0
div 	ebx
mov 	ecx, [ebp+12]
mov 	[ecx], eax



pop 	ebp
ret 	20
do_math 	ENDP
;===============================================================
;Description:  calculates the 3 different parts and turns them to x! from the factorial equation
;Recieves: nfact, n_rfact, r_fact, result,denominator,randval,r_randval
;Returns:  nfact, n_rfact,r_fact
;Preconditions: none
;Registers Changed: all registers saved with push/popad
;================================================================
combination 	PROC

push 	ebp
mov 	ebp, esp

mov 	eax, [ebp + 12]
mov 	ebx, [ebp + 8]	;does n-r!
sub 	eax, ebx
mov 	ebx, eax
push 	ebx
call 	factorial
mov 	edx, [ebp + 28]	;stores in nminusrfact
mov 	[edx], eax


mov 	ebx, [ebp + 8] ;does r!
push 	ebx
call 	factorial
mov 	edx, [ebp + 24] ;stores in r_fact
mov 	[edx], eax


mov 	ebx, [ebp + 12] ;does n!
push 	ebx
call 	factorial
mov 	edx, [ebp + 32]
mov 	[edx], eax  ;stores in nfact




pop 	ebp
ret 	28
combination		ENDP
;====================================================
;Description: gets the user input as both a string and int
;Recieves:  @user_int, @usr_str
;Returns:  usr_int, usr_str
;Preconditions: none
;Registers Changed:  all registers saved with push/popad
;====================================================
get_data	PROC
push 	ebp
mov 	ebp, esp
mov 	edx, [ebp + 8]
mov 	ecx, 1000

get_input:
	mwritething choose
	call 	readstring
	call 	crlf
	mov 	esi, edx 	;loads string to esi
	CMP 	eax, 3	;see if entry is larger than 3
	JA 	large
	cld
	mov 	ecx, eax
validate:
	lodsb 	;checks first byte of string
	cmp 	al, 48
	JB 		error	;makes sure it is between 0-9
	cmp 	al, 57
	JA 		error
	loop 	validate
	JMP		 fin


large:
	mwritestring badinput
	JMP do_over

error:
	mwritestring badinput
	JMP do_over

do_over:
	mwritestring choose
	JMP get_input

fin:
	mwritestring 	dunno
	mwritestring	dunno2
	mwritething		choose
	call 	readdec		;asks for input again to put it into an int variable. :(
	mov 	ebx, [ebp + 12]
	mov 	[ebx], eax
	pop 	ebp
	ret 	8
get_data	ENDP



;===============================================================
;Description: shows the combinatorics output, and the rand values generated
;Recieves: @r_randval,r_low, @randval, n_hi, n_lo
;Returns:  r_randval, randval
;Preconditions: none
;Registers Changed: all registers saved with push/popad
;================================================================
showproblem 	PROC

mwritestring problem
push 	ebp
mov 	ebp, esp
mov 	eax, [ebp + 12]	;gets n_hi
mov 	ebx, [ebp + 8] ;gets n_lo
mov 	ecx, [ebp + 16] ; gets randval to be stored in
sub 	eax, ebx
inc 	eax ;gets difference between n_hi and n_low
call 	randomrange
add 	eax, ebx

mwritething numset
call 	writedec
call 	crlf
mov 	[ecx], eax 	;eax is the rand number at this point, stores in randval
sub 	eax, [ebp + 20]	;subtracts r_low from r_randval
inc 	eax
call 	randomrange
add 	eax, [ebp + 20]	;adds back the r_low
mov 	ecx, [ebp + 24]
mov 	[ecx], eax 	;saves it as variable val
mwritething numeleinset
call 	writedec
call 	crlf



pop 	ebp
ret 	16
showproblem 	ENDP
;======================================================================
;Description: just does all the intro stuff for the user
;Recieves: none
;Returns: none
;Preconditions:	none
;Registers Changed: none
;========================================================================
Intro PROC
mwritestring	hola
mwritestring	sayname
mwritestring		descript
mwritestring		descript2
call 	crlf

ret
Intro ENDP
;============================================================================
;Description: does the factorial work of inputs
;Recieves: ebx, is also the number to be computed on
;Returns: eax
;Preconditions:	none, program prevents all.
;Registers Changed: ebx, eax
;==========================================================================
factorial 	PROC
push 	ebp
mov 	ebp, esp
mov 	eax, [ebp + 8]	;gets the number to factorialized
cmp 	eax, 0
ja 		do_recursion	;if greater than 0
mov 	eax, 1
JMP 	fin

do_recursion:
	dec 	eax
	push 	eax
	call 	factorial
	mov 	ebx, [ebp + 8]
	mul 	ebx		;multiplies by n-1 til 0

fin:
	pop ebp
	ret 4
factorial 	ENDP

;=====================================================================
END main
