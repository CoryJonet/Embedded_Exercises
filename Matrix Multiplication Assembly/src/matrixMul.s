    export matrixMuliply
    AREA    FLASH, CODE, READONLY
    ALIGN
    
;******************************************************************************
; Description
;    Performs matrix multiplication on two 2x2 arrays  AB = C.  
; Parameters
;    1st parameter:  Address of Matrix A
;    2nd parameter:  Address of Matrix B
;    3rd parameter:  Address of Matrix C (destination of multiplication)
;
; Returns
;    0  for success 
;    -1 for failure
;******************************************************************************
matrixMuliply

     ; Make sure that none of the parameters passes is NULL (0)
     ; ** ADD CODE **
     
     
     
     ; Save registers required by EABI
     ; ADD CODE
     
     
     
     ; Set the Frame Pointer
     ; ** ADD CODE **
     
     
     
     ; Allocate 4 1-byte local Variables to store the 
     ; four elements of the resulting matrix
     ; ** ADD CODE **
   
     
     
     ; Save the Address of the C Matrix to the stack
     ; ** ADD CODE **
    
 
     ; Load the values of matrix A into R3-R6
     LDRB   R3, [R0, #0] ; R3  - A00
     LDRB   R4, [R0, #1] ; R4  - A01
     LDRB   R5, [R0, #2] ; R5  - A10
     LDRB   R6, [R0, #3] ; R6  - A11
     
     ; Load the values of matrix B into R7-R8
     LDRB   R7, [R1, #0] ; R7  - B00
     LDRB   R8, [R1, #1] ; R8  - B01
     LDRB   R9, [R1, #2] ; R9  - B10
     LDRB   R10,[R1, #3] ; R10 - B11
     
     ; Calculate C00 = (A00 * B00) + (A01 * B10)
     MUL    R0, R3, R7
     MUL    R1, R4, R9
     ADD    R2, R1, R0
     
     
     
     
     ; Save the C00 value to a local variable
     ; ** ADD CODE **
     
     
     
     ; Calculate C01 = (A00 * B01) + (A01 * B11)
     MUL    R0, R3, R8
     MUL    R1, R4, R10
     ADD    R2, R1, R0
     
     
     
     ; Save the C01 value to a local variable
     ; ** ADD CODE **
     
     
     
     ; Calculate C10 = (A10 * B00) + (A11 * B10)
     MUL    R0, R5, R7
     MUL    R1, R6, R9
     ADD    R2, R1, R0
     
     
     
     ; Save the C10 value to a local variable
     ; ** ADD CODE **
     
     
     
     ; Calculate C11 = (A10 * B01) + (A11 * B11)
     MUL    R0, R5, R8
     MUL    R1, R6, R10
     ADD    R2, R1, R0
     
     
     
     ; Save the C11 value to a local variable
     ; ** ADD CODE **
     
     
     
     ; Restore the value of C2 from the stack
     ; ** ADD CODE **
     
     
     
     ; Read the 4 saved local variables
     ; ** ADD CODE **
     
     
     
     ; Save C00, C01, C10, and C11 to the C
     ; address
     STRB   R3, [R2, #0]
     STRB   R4, [R2, #1]
     STRB   R5, [R2, #2]
     STRB   R6, [R2, #3]



     ; De-allocate the local variables
     ; ** ADD CODE **
     
     
     
     ; Restore Registers from the stack
     ; ** ADD CODE **
     
     
     
     ; Return to the main routine
     BX     LR
     
    END     

