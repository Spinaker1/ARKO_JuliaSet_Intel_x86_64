PUBLIC juliaSet

.data
two dq 2.0
three dq 3.0
mone dq -1.0
moneh dq -1.5

.code

juliaSet PROC
    push rbp
    mov rbp, rsp

	;rcx - rejestr bazowy dla bufora pikseli
	;rdx - szerokoœæ
	;r8 - wysokoœæ
	;r10 - iterator dla kolejnych pikseli w wierszy
	;r11 - iterator dla wierszy
	;r12 - rejestr indeksowy dla bufora pikseli

	;xmm0 - cX
	;xmm1 - cY
	;xmm2 - zoom
	;xmm3 - deltaX
	;xmm4 - deltaY
	;xmm5 - zX
	;xmm6 - zY

	mov r10,0
	mov r11,0
	mov r12,0

	;deltaX=3/w
	CVTSI2SD xmm5, rdx
	movsd xmm3,[three]
	divsd xmm3,xmm5

	; deltaY=2/h
	CVTSI2SD xmm6, r8
	movsd xmm4,[two]
	divsd xmm4,xmm6

	movsd xmm5,[moneh]
	movsd xmm6,[mone]

next:
	movsd xmm7,xmm5
	movsd xmm8,xmm6

calc:
	

	mov rax,255
	mov [rcx+4*r12],rax
	mov [rcx+4*r12+1],rax
	mov [rcx+4*r12+2],rax
	mov [rcx+4*r12+3],rax

	addsd xmm5,xmm3

	inc r10
	inc r12

	cmp r10,rdx
	jne next

nextRow:
	mov r10,0
	movsd xmm5,[moneh]

	addsd xmm6,xmm4

	inc r11
	cmp r11,r8
	jne next

	mov rsp,rbp 
    pop rbp 
    ret
juliaSet ENDP

END