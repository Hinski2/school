.global cmp

# argumenty
    # rdi x
    # rsi y
# wynik
    # rax
cmp:
	# zerowanie rejestrów
	xor		%rax,	%rax
	xor		%rcx,	%rcx

	cmpq	%rsi,	%rdi	# porównuje rsi i rdi
	setg	%al				# jeśli x > y ustawia na 1 najmłodszy bit rax
	setl	%cl				# jeśli x < y ustawia na 1 najmłodszy bit rcx

	subq	%rcx,	%rax	# rax - rcx jeśli x = y to 0, jeśli x > y to 1, jeśli x < y to -1
	ret

    
