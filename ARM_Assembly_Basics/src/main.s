;Indicating where the CODE section of the program starts
    AREA    FLASH, CODE, READONLY



;**********************************************
; main program start
;**********************************************
__main    

    
    B        __main
  

    AREA    SRAM, READWRITE
    END