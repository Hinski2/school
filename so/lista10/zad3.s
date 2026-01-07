	.file	"zad3.c"
	.text
	.p2align 4
	.globl	total
	.type	total, @function
total:
.LFB0:
	.cfi_startproc
	addl	$50, tally(%rip)
	ret
	.cfi_endproc
.LFE0:
	.size	total, .-total
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	addl	$100, tally(%rip)
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.local	tally
	.comm	tally,4,4
	.globl	n
	.section	.rodata
	.align 4
	.type	n, @object
	.size	n, 4
n:
	.long	50
	.ident	"GCC: (GNU) 15.2.1 20251112"
	.section	.note.GNU-stack,"",@progbits
