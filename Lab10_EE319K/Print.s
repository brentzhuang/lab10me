; Print.s
; Student names: change this to your names or look very silly
; Last modification date: change this to the last modification date or look very silly
; Runs on LM4F120 or TM4C123
; EE319K lab 7 device driver for any LCD
;
; As part of Lab 7, students need to implement these LCD_OutDec and LCD_OutFix
; This driver assumes two low-level LCD functions
; ST7735_OutChar   outputs a single 8-bit ASCII character
; ST7735_OutString outputs a null-terminated string 
remainder	EQU 0
linkage		EQU 4
	
    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix

    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

  

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	PUSH {R4, LR}
	SUB SP, #8
	
	MOV R1, #10
	CMP R0, R1
	BLO printDigit
	
	UDIV R2, R0, R1 ; R2 = R0/10
	MUL R3, R2, R1 ; R3 = R2 * 10
	SUB R4, R0, R3 ; R4 = R0 - R3

	AND R3,R3,#0
	
	MOV R0, R2
	
	STR R4, [SP, #remainder]
	BL LCD_OutDec
	
	LDR R4,[SP, #remainder] 
	ADD R0,R4,#0x30 
	BL ST7735_OutChar 
Done   
	ADD SP, #8
	POP {R4, LR} 
	BX LR 

printDigit 
	ADD R0, #0x30 ;convert to ascii 
	BL ST7735_OutChar 
	
	B Done

      BX  LR
;* * * * * * * * End of LCD_OutDec * * * * * * * *

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999
; Inputs:  R0 is an unsigned 32-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 "
;       R0=3,    then output "0.003 "
;       R0=89,   then output "0.089 "
;       R0=123,  then output "0.123 "
;       R0=9999, then output "9.999 "
;       R0>9999, then output "*.*** "
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
	PUSH {R4,LR}
	MOV R1,#9999 
	CMP R0,R1 
	BHI printStars 

	
	MOV R1,#1000 
	;MOV R2, #5 ;number of iterations 
	MOV R3, R0 	;R3 = input
;	MOV R5, #10 	;R5 = 10

printLoop 
;Ro is the Input
	UDIV R0,R3,R1 ; DIV by the basis 	R0 = input/1000
	ADD R0,#0x30
	PUSH{R0, R1, R2, R3}
	BL ST7735_OutChar	; ().xxx
	POP{R0, R1, R2, R3}
	MOV R0,R3 ;restoring R0
	UDIV R2, R0, R1 ; R2 = R0/R1(1000)
	MUL R4, R2, R1 ; R4 = R2 * 1000
	SUB R0,R0,R4
	MOV R3,R0
	
	MOV R0,#46
	PUSH{R0, R1, R2, R3}
	BL ST7735_OutChar	;x(.)xxx
	POP{R0, R1, R2, R3}
	
	
	MOV R1,#100 
	MOV R0, R3 	;R3 = input
	
	UDIV R0,R3,R1; 	R1= adjusted input / 100
	ADD R0,#0x30
	PUSH{R0, R1, R2, R3}
	BL ST7735_OutChar	;x.(x)xx	;1
	POP{R0, R1, R2, R3}
	MOV R0,R3 ;restoring R0
	UDIV R2, R0, R1 ; R2 = R0/R1(100)
	MUL R4, R2, R1 ; R4 = R2 * 100	; 23
	SUB R0,R0,R4
	MOV R3, R0

	
	MOV R1,#10
	
	UDIV R0,R3,R1	;23 / 10 = 2
	ADD R0,#0x30
	PUSH{R0, R1, R2, R3}
	BL ST7735_OutChar	;x.x(x)x	;2
	POP{R0, R1, R2, R3}
	MOV R0,R3	;restore R0
	UDIV R2,R0,R1	;R2 = R0/10
	MUL R4,R2,R1 ; R4=R2*10 ; 3
	SUB R0,R0,R4
	
	ADD R0,#0x30
	PUSH{R0, R1, R2, R3}
	BL ST7735_OutChar
	POP{R0, R1, R2, R3, R4, LR}
	
	BX LR
	
printStars 
	MOV R0, #42 
	BL ST7735_OutChar ;* 

	MOV R0, #46 
	BL ST7735_OutChar ; . 

	MOV R0, #42 
	BL ST7735_OutChar ;* 
	
	MOV R0, #42 
	BL ST7735_OutChar ;* 
	MOV R0, #42 
	BL ST7735_OutChar ;* 

	POP {R4, LR}
     BX   LR
 
     ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

     ALIGN                           ; make sure the end of this section is aligned
     END                             ; end of file
