; Filename:     main.s 
; Author:       REPLACE WITH YOUR NAMES 
; Description:  
    export __main

BYTE		EQU 	1
HALF_WORD 	EQU   	2
WORD 		EQU 	4
	
;Indicating where the CODE section of the program starts
    AREA    FLASH, CODE, READONLY
	
LTABLE		DCW	0
			DCW	1
			DCW	8
			DCW 27
			DCW 64
			DCW	125
			DCW	216
			DCW	343
	


;**********************************************
; main program start
;**********************************************
__main    

    
  
  ;LOAD LTABLE AND ARRAY1/ARRAY2
	LDR	R0, =(LTABLE)
	LDR R1, =(ARRAY1)
	LDR R2, =(ARRAY2)
	
  ;LOAD THE 6TH ENTRY OF LTABLE IN R10
	LDR R10, [R0, #HALF_WORD * 3]
	
	
  ;COPY CONTENTS OF LTABLE INTO ARRAY1
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	LDRH R3, [R0], #HALF_WORD
	STRH R3, [R1], #HALF_WORD
	
	;COPY CONTENTS OF LTABLE INTO ARRAY2
	LDM R0, {R4-R10}
	STM R2, {R4-R10}
	
    B        __main
	
    AREA    SRAM, READWRITE
	
ARRAY1	SPACE	8*HALF_WORD
ARRAY2 	SPACE	8*HALF_WORD
	
    END