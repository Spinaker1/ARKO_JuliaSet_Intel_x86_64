section .data
two: dq 2.0
three: dq 3.0

section .text 
bits 64 
global juliaSet
juliaSet:
    push rbp
    mov rbp, rsp

	;rcx - rejestr bazowy dla bufora pikseli
	;rdx - szerokosc
	;rbx - wysokosc
	;r10 - iterator dla kolejnych pikseli w wierszy
	;r11 - iterator dla wierszy
	;r12 - rejestr indeksowy dla bufora pikseli

	;xmm0 - cX
	;xmm1 - cY
	;xmm2 - zX0
	;xmm3 - zY
	;xmm4 - zoom
	;xmm5 - deltaX
	;xmm6 - deltaY
	;xmm7 - zX


	mov cl,[rbp+16]
	mov edx,[rbp+24]
	mov ebx,[rbp+32]

	mov r10,0
	mov r11,0
	mov r12,0
	
	CVTSI2SD xmm7, rdx
	movsd xmm5,[three]
	divsd xmm5,xmm7

	; deltaY=2/h
	CVTSI2SD xmm8, rbx
	movsd xmm6,[two]
	divsd xmm6,xmm8

	movsd xmm7,xmm2
next:
	movsd xmm8,xmm6
	movsd xmm9,xmm7
	mov rax,0

calc:


	mov [rcx+4*r12],rax
	mov [rcx+4*r12+1],rax
	mov [rcx+4*r12+2],rax
	mov [rcx+4*r12+3],rax

	inc r10
	inc r12

	addsd xmm7,xmm5

	cmp r10,rdx
	jne next
	
nextRow:
	mov r10,0

	movsd xmm7,xmm2
	addsd xmm3,xmm6

	inc r11
	cmp r11,rbx
	jne next

	pop rbp 
    ret