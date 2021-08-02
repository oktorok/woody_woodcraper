	section .text
	global decrypt

decrypt:
	mov rdi, rdi
	mov rsi, rsi
	xor rax, rax
	.loop:
	mov al, [rdi]
	xor al, 0x42
	mov [rdi], al
	sub rsi, 1
	add rdi, 1
	test rsi, rsi
	jz .finish
	jmp .loop
	.finish:
	ret
