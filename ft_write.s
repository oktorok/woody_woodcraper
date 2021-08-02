	[bits 64]
	push	rax
	push	rsi
	push	rdi
	push	rdx
	push	rcx
	


	mov	rdi, 1
	mov	rsi, woody
	mov	rdx, 12
	mov	rax, 1
	syscall

	pop	rcx
	pop	rdx
	pop	rdi
	pop	rsi
	pop	rax
	woody	db	'...WOODY...', 0x0a
