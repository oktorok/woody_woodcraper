	extern __errno_location

	section	.data
	hello_world	db 'Hello, world!', 0xa

	section	.text
	global	_start

_start:
	mov	rdi, 1
	mov	rax, 1
	mov	rsi, hello_world
	mov	rdx, 13
	syscall
	ret

