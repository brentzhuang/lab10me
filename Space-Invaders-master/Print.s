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


q	EQU 0	; variable offset
r	EQU 4
s	EQU 8
t	EQU 12
u	EQU 16
v	EQU 20
w	EQU 24
x	EQU 28
y	EQU	32
z	EQU 36
	
    IMPORT   ST7735_OutChar
    IMPORT   ST7735_OutString
    EXPORT   LCD_OutDec
    EXPORT   LCD_OutFix
	PRESERVE8					
	
    AREA    |.text|, CODE, READONLY, ALIGN=2
    THUMB

;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number
; Output: none
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
	PUSH {R4 - R11} 			; save callee registers
	SUB SP, #40					; allocate bytes for local vars, max value in each byte is 9
	
	LDR R1, =1000000000			; divisor = 10E9
	UDIV R3, R0, R1				; divide by divisor
	ADD R2, R3, #48				; add 48 to value for ASCII code
	STRB R2, [SP, #q]			; store value in bound variable using offset
	MLS R0, R1, R3, R0			; modulus division, leaves mod in R0
	
	LDR R1, =100000000			; divisor = 10E8
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #r]
	MLS R0, R1, R3, R0
	
	LDR R1, =10000000			; divisor = 10E7
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #s]
	MLS R0, R1, R3, R0
	
	LDR R1, =1000000			; divisor = 10E6
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #t]
	MLS R0, R1, R3, R0
	
	LDR R1, =100000				; divisor = 10E5
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #u]
	MLS R0, R1, R3, R0
	
	LDR R1, =10000				; divisor = 10E4
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #v]
	MLS R0, R1, R3, R0
	
	LDR R1, =1000				; divisor = 10E3
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #w]
	MLS R0, R1, R3, R0
	
	LDR R1, =100				; divisor = 10E2
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #x]
	MLS R0, R1, R3, R0
	
	LDR R1, =10					; divisor = 10E1
	UDIV R3, R0, R1
	ADD R2, R3, #48
	STRB R2, [SP, #y]
	MLS R0, R1, R3, R0
	
	ADD R0, R0, #48				; remaining modulus is ones place
	STRB R0, [SP, #z]
	
	LDRB R0, [SP, #q]			; check vars for first nonzero value 
	CMP R0, #48					; starting with MSB
	BNE A9
	
	LDRB R0, [SP, #r]			
	CMP R0, #48
	BNE A8
	
	LDRB R0, [SP, #s]			
	CMP R0, #48
	BNE A7
	
	LDRB R0, [SP, #t]
	CMP R0, #48
	BNE A6
	
	LDRB R0, [SP, #u]
	CMP R0, #48
	BNE A5
	
	LDRB R0, [SP, #v]
	CMP R0, #48
	BNE A4
	
	LDRB R0, [SP, #w]
	CMP R0, #48
	BNE A3
	
	LDRB R0, [SP, #x]
	CMP R0, #48
	BNE A2
	
	LDRB R0, [SP, #y]
	CMP R0, #48
	BNE A1
	
	LDRB R0, [SP, #z]
	CMP R0, #48
	B A0				; always prints last digit by default
						
; print value starting with first nonzero value
; R0 loaded with q by default
A9 						; output char at q
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP	{LR,R0}
	
A8						; output char at r
	LDRB R0, [SP, #r]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
A7						; output char at s
	LDRB R0, [SP, #s]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
A6						; output char at t
	LDRB R0, [SP, #t]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
A5						; output char at u
	LDRB R0, [SP, #u]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
A4						; output char at v
	LDRB R0, [SP, #v]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
A3						; output char at w
	LDRB R0, [SP, #w]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
A2						; output char at x
	LDRB R0, [SP, #x]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
A1						; output char at y
	LDRB R0, [SP, #y]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}

A0						; output char at z
	LDRB R0, [SP, #z]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
	ADD SP, #40					; deallocate memory for local vars
	POP {R4 - R11}				; pop callee registers
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
	PUSH {R4 - R11} 			; save callee registers
	SUB SP, #20					; allocate bytes for local vars, max value in each byte is 9
	
	MOV R1, #42					; ASCII code for *
	MOV R2, #46					; ASCII code for .
	STRB R1, [SP, #q]			; default value is *.***
	STRB R2, [SP, #r]			; r is always decimal point
	STRB R1, [SP, #s]
	STRB R1, [SP, #t]
	STRB R1, [SP, #u]
	
	MOV R1, #9999				
	CMP R0, R1					; check if R0 > 9999
	BHI print
	
	MOV R1, #1000
	UDIV R2, R0, R1				; divide R0 by 1000
	MLS R0, R1, R2, R0			; modulus division, mod in R0
	ADD R2, #48
	STRB R2, [SP, #q]
	
	MOV R1, #100
	UDIV R2, R0, R1				; divide R0 by 100
	MLS R0, R1, R2, R0			; modulus division, mod in R0
	ADD R2, #48
	STRB R2, [SP, #s]
	
	MOV R1, #10
	UDIV R2, R0, R1				; divide R0 by 10
	MLS R0, R1, R2, R0			; modulus division, mod in R0
	ADD R2, #48
	STRB R2, [SP, #t]
	ADD R0, #48
	STRB R0, [SP, #u]			; remaining modulus is less than 10

print
	LDRB R0, [SP, #q]			; print bound variables
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}

	LDRB R0, [SP, #r]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
	LDRB R0, [SP, #s]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
	LDRB R0, [SP, #t]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
	LDRB R0, [SP, #u]
	PUSH {LR,R0}
	BL ST7735_OutChar
	POP {LR,R0}
	
	ADD SP, #20					; deallocate local variables
	POP {R4 - R11}				; pop callee registers
    BX   LR
 
    ALIGN
;* * * * * * * * End of LCD_OutFix * * * * * * * *

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
