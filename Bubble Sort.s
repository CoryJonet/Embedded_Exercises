    export bubbleSort
    AREA    FLASH, CODE, READONLY
    ALIGN
    
;******************************************************************************
; Description
; Uses Bubble Sort to sort an array of unsigned 8-bit numbers.
; Parameters
; R0 - Array Address
; R1 - Array Size  
;******************************************************************************
bubbleSort
     PUSH   {R4-R10}
     
     ; Suggested Register Usage
     ;R2 : i - 1
     ;R3 : j
     ;R4 : (size - i - 1)
     ;R5 : A[j]
     ;R6 : A[j+1]
     ;R7 : Saved Value of R0
     
	 
     ; Calculate size - 1 business
     SUB    R1, R1, #1
     
     ; Initialize outer count (i)
	 MOV R8, #0	
     
startOuter

    ; Add a line of code to check if the outer for loop should terminate
	CMP R1, R8
    BEQ     endBubbleSort
   
    ; Initialize the count of the inner loop (j)   
	MOV R3, #0
    
    ; Load the array's starting address into R7
	MOV R7, R0
    
    ; Calculate the remaining unsorted elements
    ; (size - i - 1)
	SUB R4, R1, R8 
    
startInner
    ; Add a line of code to check if the inner loop terminates
	CMP R4, R3
    BEQ     endInner
    
    ; Load the two values
    ; Use R7 as the base register for the loads.
    ; Remember to use BYTE loads.
	LDRB R5, [R7, R3]
	ADD R9, R3, #1
	LDRB R6, [R7, R9]
    
    ; Check if the numbers need to be swapped
	CMP R5, R6
	BLT Branch		;Inner loop if statement
    
    ; Swap the values if A[i] > A[j]
	MOV R10, R5				;TEMP
	MOV R5, R6				;[j] gets [j+1]
	MOV R6, R10				;[j+1] gets TEMP
	STRB R5, [R7, R3]		;Store [j] @ array address
	STRB R6, [R7, R9]		;Store [j+1] @ array address
    
    ; Increment innter loop
Branch
    
	ADD R3, R3, #1
	
    B       startInner
endInner

    ; Increment the outer loop count

	ADD R8, R8, #1

    B     startOuter

endBubbleSort
     POP    {R4-R10}
     BX     LR
     
    END     
