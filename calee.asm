PUBLIC juliaSet

.data


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

	mov r10,0
	mov r11,0
	mov r12,0

next:
	mov rax,255
	mov [rcx+4*r12],rax
	mov [rcx+4*r12+1],rax
	mov [rcx+4*r12+2],rax
	mov [rcx+4*r12+3],rax

	inc r10
	inc r12

	cmp r10,rdx
	jne next

nextRow:
	inc r11
	mov r10,0
	cmp r11,r8
	jne next

	mov rsp,rbp 
    pop rbp 
    ret
juliaSet ENDP

END