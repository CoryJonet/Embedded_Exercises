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
     
     
startOuter

    ; Add a line of code to check if the outer for loop should terminate

    BEQ     endBubbleSort
   
    ; Initialize the count of the inner loop (j)   

    
    ; Load the array's starting address into R7

    
    ; Calculate the remaining unsorted elements
    ; (size - i - 1)

    
startInner
    ; Add a line of code to check if the inner loop terminates

    BEQ     endInner
    
    ; Load the two values
    ; Use R7 as the base register for the loads.
    ; Remember to use BYTE loads.

    
    ; Check if the numbers need to be swapped

    
    ; Swap the values if A[i] > A[j]

    
    ; Increment innter loop

    
    B       startInner
endInner

    ; Increment the outer loop count

    B     startOuter

endBubbleSort
     POP    {R4-R10}
     BX     LR
     
    END     
