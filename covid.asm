	[bits 64]

_start:
	push rax
	push rdi
	push rsi
	push rdx
	push r11
	mov rax, 1
	mov rdi, 1
	lea rsi, [rel woody]
	mov rdx, 12
	syscall
	jmp decrypt

decrypt:
	lea rsi, [rel size]
	mov esi, [rsi]
	lea rax, [rel key]
	xor r11, r11
	mov r11b, [rax]
	lea rdi, [rel text]
	mov eax, [rdi]
	test eax, eax
	js .signed2
	sub rdi, rax
	.loop:
	xor rax, rax
	mov al, [rdi]
	xor al, r11b
	mov [rdi], al
	sub rsi, 1
	add rdi, 1
	test rsi, rsi
	jz finish
	jmp .loop

	.signed2:
	not eax
	inc eax
	add rdi, rax
	jmp .loop
	
finish:
	pop r11
	pop rdx
	pop rsi
	pop rdi
	pop rax
	lea r9, [rel entry]
	mov r8w, [r9]
	test r8w, r8w
	js .signed
	sub r9, r8
	jmp r9
	.signed:
	not r8w
	inc r8w
	add r9, r8
	jmp r9

	aling	db "+"
	woody	db "...WOODY...", 0x0a
	entry	db "@ne@"
	text	db "@et@"
	size	db "@is@"
	key	db "@ek@"
	
