TITLE Program #5     (template.asm)
; Author: Brandon Dring
; Course / Project ID: Program #5     Date: 2/25/16
; Description: Generates user defined amount of random numbers
; then writes them to an array, then sorts the array and gives the
; median value of array.
;=============================================================================================
INCLUDE Irvine32.inc

lowbound = 100
highbound = 999
min = 9
max = 201
bigarrsize = 1000


;============================================================================================
.data

topthing 	BYTE	"Sorting Random Integers			By Brandon Dring",0
explain 	BYTE 	"This program generates random numbers between [100 - 999]",0
explain2 	BYTE 	"then displays the original list, sorts it, calculates the median.",0
explain3 	BYTE 	"Then it displays the list in descending order", 0
asksize 	BYTE 	"What many numbers do you want to be generated?: ", 0
unsort_array	BYTE 	"The unsorted array is.. ", 0
medval		BYTE 	"The median value is: ", 0
sortedarr 	BYTE 	"The SORTED array is.. ",0
goodbye 	BYTE 	"Certified by Brandon Dring", 0
arrrange 	BYTE 	"The values to be generated are between [10-200]",0
getspace 	BYTE 	" ", 0
sorttrack 	DWORD 	1
runsize 	DWORD	?
bigarray 	DWORD 	bigarrsize		dup(?)
randholder 	DWORD 	?
numperline	DWORD  10


;============================================================================================
.code
main PROC
call 	randomize
push 	offset topthing
push 	offset explain
push 	offset explain2
push 	offset explain3
call 	introstuff

push 	offset runsize
call 	getsize

push 	sorttrack
push 	runsize
push 	offset bigarray
call 	getdata
call 	crlf

push 	sorttrack
push 	offset bigarray
call 	printarray

push 	offset bigarray
call 	sortarray

push 	offset bigarray
push 	runsize
call 	domedian


push 	offset sorttrack
push 	offset bigarray
call 	printarray 	;pass another val to diff from unsort to sort

push 	offset goodbye
call 	outro

	exit	; exit to operating system
main ENDP
;============================================================================

; Description: Just says goodye to the user and says its made by me
; Receives: @goodbye
; Returns: none
; Preconditions: none
; Registers changed: edx
;==============================================================================
outro 	PROC
call 	crlf
push 	ebp
mov 	ebp, esp

mov 	edx, [ebp + 8] 	;move @goodbye
call 	writestring
call 	crlf

pop 	ebp
ret 4
outro 	ENDP
;==============================================================================

; Description: Calculates the median value of the array, both odd and even numbers
; Receives: @bigarray and runsize
; Returns: none
; Preconditions: runsize must have been initalized in prior proc
; Registers changed: eax, ebx, ecx, esi
;===============================================================================
domedian 	PROC
call 	crlf
push 	ebp
mov 	ebp, esp
mov 	eax, [ebp + 8] 	;move runsize
CDQ
mov 	ebx, 2
div 	ebx
CMP 	edx, 0
JE	 	iseven
JNE 	isodd

isodd:
mov 	eax, [ebp + 8]	;move runsize
inc 	eax
CDQ
mov 	ebx, 2
div 	ebx
mov 	ecx, eax
dec  	ecx
mov 	esi, [ebp + 12] 	;move through array

getval:
cmp 	ecx, 0
JE 		print
add 	esi, 4 ;step through array
loop 	getval
JMP 	print

iseven:
mov 	eax, [ebp + 8]	;move runsize
CDQ
mov 	ebx, 2
div 	ebx
mov 	ecx, eax
dec 	ecx
mov 	esi, [ebp + 12]	;moves array[0]

getvaleven:
cmp 	ecx, 0
JE 		printeven
add 	esi, 4 	;step through array
loop 	getvaleven

printeven:
mov 	eax, [esi]
add 	eax, [esi + 4] ;summates middle elements of array
CDQ
mov 	ebx, 2
div 	ebx
mov 	edx, offset medval
call 	writestring
call 	writedec
call 	crlf
JMP 	fin


print:
mov 	eax, [esi]	;prints value of array[x]
mov 	edx, offset medval
call 	writestring
call 	writedec
call 	crlf


fin:
call 	crlf
pop 	ebp
ret 	8
domedian 	ENDP
;============================================================================

; Description: Sorts the array using bubble sort from high to low
; Receives: @bigarray
; Returns: none
; Preconditions: bigarray must have been filled with integers
; Registers changed:	ecx, eax, esi,
;==============================================================================
sortarray 	PROC
push 	ebp
mov 	ebp, esp

mov 	ecx, runsize
dec 	ecx

spot1:
push 	ecx	;saves outer loop
mov 	esi, [ebp + 8]	;moves array[0]

spot2:
mov 	eax, [esi]
cmp 	[esi +4], eax ;compares array[n] to array [n +1]
jl 		spot3
xchg 	eax, [esi+4]	;exchange array[n] and array [n+1]
mov 	[esi], eax 	; move new val to array element

spot3:
add 	esi, 4	;step through array
loop 	spot2
pop 	ecx
loop 	spot1

spot4:
pop 	ebp
ret 	4
sortarray 	ENDP
;==================================================================

; Description: prints the contents of the array sorted and unsorted
; Receives: @sortarray, @bigarray, sortarray
; Returns: noe
; Preconditions: array must be full of DWORD ints
; Registers changed:	eax, ecx, edx, ebx, esi
;====================================================================
printarray 	PROC
push 	ebp
mov 	ebp, esp
mov 	ecx, runsize
mov 	esi, [ebp + 8]	;moves array[0]
mov 	ebx, [ebp + 12]	;moves sortarray
cmp 	ebx, 1
JNE 	sorted


mov 	edx, offset unsort_array
call 	writestring
call 	crlf
add 	ebx, 10
mov		[ebp + 12], ebx	;updates value of sortarray
JMP 	again

sorted:
mov 	edx, offset sortedarr
call 	writestring
call 	crlf


again:
cmp 	numperline, 0
JE 		skipline	;skips every 10 values
dec 	numperline
mov 	eax, [esi] 	;moves arr data to be printed
call 	writedec
mov 	edx, offset getspace
call 	writestring
add 	esi, 4
loop 	again
JMP 	done

skipline:
call 	crlf
mov 	numperline, 10
JMP 	again


done:
call 	crlf
pop 	ebp
ret 	8
printarray 	ENDP
;==============================================================

; Description: gets random numbers to fill the array
; Receives: sorttrack, runsize, @bigarray
; Returns: none
; Preconditions: runsize must be within range
; Registers changed: esi, ecx, ebx, eax
;================================================================
getdata PROC
push 	ebp
mov 	ebp, esp
mov 	esi, [ebp + 8]	;moves array[0] to esi
mov 	ecx, [ebp + 12]	;moves runsize to ecx


looping:
mov 	eax, highbound
call 	randomrange
mov 	randholder, eax
CMP 	randholder, lowbound	;checks against the lowerbound
JLE 	looping
mov 	[esi], eax	;if valid, moves value to array
add 	esi, 4
loop 	looping

pop 	ebp
ret 	8
getdata ENDP
;===================================================================

; Description: gets the number of random numbers to generate
; Receives: @runsize
; Returns: none
; Preconditions: none
; Registers changed: ebx, eax,
;====================================================================
getsize PROC
push 	ebp
mov 	ebp, esp
mov 	ebx, [ebp + 8] 	;runsize variable
again:
mov 	edx, offset asksize
call 	writestring
call 	readdec	;gets the val from user
CMP 	eax, max	;tests against max
JGE		again
CMP 	eax, min	;tests against min
JLE		again

mov 	[ebx], eax 	;moves valid data to runsize var

pop 	ebp
ret 	4
getsize ENDP
;====================================================================

; Description: Just gives user intro detail stuff
; Receives: @topthing, @explain, @explain2, @explain3
; Returns: none
; Preconditions: none
; Registers changed: edx
;=======================================================================
introstuff PROC
push 	ebp
mov 	ebp, esp

mov 	edx, [ebp + 20] 	;prints topthing
call 	writestring
call 	crlf
call 	crlf

mov 	edx, [ebp + 16] 	;prints explain
call 	writestring
call 	crlf

mov 	edx, [ebp + 12]	;prints explain2
call 	writestring
call 	crlf

mov 	edx, [ebp + 8]	; prints explain3
call 	writestring
call 	crlf
call 	crlf

mov 	edx, offset arrrange
call 	writestring
call 	crlf

pop 	ebp
ret 	12
introstuff ENDP
;=============================================================================

END main
