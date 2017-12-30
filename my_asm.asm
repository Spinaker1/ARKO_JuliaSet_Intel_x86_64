section .data
two: dq 2.0
three: dq 3.0
four: dq 4.0
moneh: dq -1.5
mone: dq -1.0

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
	;xmm13 - 4
	;xmm15 - zoom

	mov cl,[rbp+16]
	mov edx,[rbp+24]
	mov ebx,[rbp+32]
	mov eax,[rbp+72]

	mov r10,0
	mov r11,0
	mov r12,0
	
	addsd xmm2,[moneh]
	addsd xmm3,[mone]

	CVTSI2SD xmm15, rax

	; deltaX=3/(w*zoom)
	CVTSI2SD xmm7, rdx
	mulsd xmm7,xmm15
	movsd xmm5,[three]
	divsd xmm5,xmm7

	; deltaY=2/(h*zoom)
	CVTSI2SD xmm8, rbx
	mulsd xmm8,xmm15
	movsd xmm6,[two]
	divsd xmm6,xmm8

	movsd xmm7,xmm2

	movsd xmm13,[four]
next:
	movsd xmm8,xmm7
	movsd xmm9,xmm3
	mov rax,255

calc:
	cmp rax,0
	jz end_calc

	;xmm10 - zX*zX
	;xmm11 - zY*zY
	;xmm12 - zX*zX+zY*zY

	movsd xmm10,xmm8; 
	mulsd xmm10,xmm10

	movsd xmm11,xmm9; 
	mulsd xmm11,xmm11

	movsd xmm12,xmm10
	addsd xmm12,xmm11

	ucomisd xmm12,xmm13
	jle end_calc

	dec rax

	movsd xmm14,xmm8
	mulsd xmm14,xmm9
	mulsd xmm14,[two]
	addsd xmm14,xmm1

	movsd xmm8,xmm10
	subsd xmm8,xmm11
	addsd xmm8,xmm0

	movsd xmm9,xmm14

	jmp calc

end_calc:
	mov [rcx+4*r12],rax
	mov [rcx+4*r12+1],rax
	mov [rcx+4*r12+2],rax
	mov rax,255
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

	movsd xmm0,xmm15

	pop rbp 
    ret