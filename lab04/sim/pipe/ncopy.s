	.file	"ncopy.c"
	.text
	.p2align 4,,15
.globl ncopy
	.type	ncopy, @function
ncopy:
	pushl	%ebp
	xorl	%edx, %edx
	movl	%esp, %ebp

	xorl	%eax, %eax
	movl	16(%ebp), %ecx
	pushl	%edi
	movl	8(%ebp), %edi
	pushl	%esi
	movl	12(%ebp), %esi
	pushl	%ebx
	testl	%ecx, %ecx
	jle	.L3
	.p2align 4,,7
	.p2align 3
.L7:
	movl	(%edi,%edx), %ebx
	testl	%ebx, %ebx
	movl	%ebx, (%esi,%edx)
	setg	%bl
	addl	$4, %edx
	movzbl	%bl, %ebx
	addl	%ebx, %eax
	subl	$1, %ecx
	jne	.L7
.L3:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	ncopy, .-ncopy
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"count=%d\n"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	.p2align 4,,7
	.p2align 3
.L11:
	addl	$1, %eax
	cmpl	$8, %eax
	movl	%eax, src-4(,%eax,4)
	jne	.L11
	xorb	%al, %al
	xorl	%ecx, %ecx
	.p2align 4,,7
	.p2align 3
.L13:
	movl	src(%eax), %edx
	testl	%edx, %edx
	movl	%edx, dst(%eax)
	setg	%dl
	addl	$4, %eax
	movzbl	%dl, %edx
	addl	%edx, %ecx
	cmpl	$32, %eax
	jne	.L13
	movl	%ecx, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$1, (%esp)
	call	__printf_chk
	xorl	%eax, %eax
	leave
	ret
	.size	main, .-main
	.comm	src,32,32
	.comm	dst,32,32
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
