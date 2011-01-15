	.file	"ctimer.c"
	.section	.rodata
	.align 4
.LC0:
	.string	"Get time, then get time again\n"
.globl __divdi3
.LC1:
	.string	"Average: %lld ticks\n"
.LC2:
	.string	"Maximum: %lld ticks\n"
.LC3:
	.string	"Minimum: %lld ticks\n"
	.align 4
.LC4:
	.string	"Get time, then add in assmembly /wo lock, then get the time again\n"
	.align 4
.LC5:
	.string	"Get time, then add in assmembly with lock, then get the time again\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	subl	$208, %esp
	movl	$0, -116(%ebp)
	movl	$0, -112(%ebp)
	movl	$0, -108(%ebp)
	movl	$0, -104(%ebp)
	movl	$0, -100(%ebp)
	movl	$0, -96(%ebp)
	movl	$0, -92(%ebp)
	movl	$0, -88(%ebp)
	movl	$0, -84(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -76(%ebp)
	movl	$100000000, -72(%ebp)
	movl	$0, -68(%ebp)
	jmp	.L2
.L7:
#APP
# 22 "ctimer.c" 1
	rdtsc		    
	
# 0 "" 2
#NO_APP
	movl	%eax, -56(%ebp)
	movl	%edx, -52(%ebp)
	movl	-56(%ebp), %eax
	movl	-52(%ebp), %edx
	movl	%eax, -112(%ebp)
	movl	%edx, -108(%ebp)
#APP
# 23 "ctimer.c" 1
	rdtsc		    
	
# 0 "" 2
#NO_APP
	movl	%eax, -48(%ebp)
	movl	%edx, -44(%ebp)
	movl	-48(%ebp), %eax
	movl	-44(%ebp), %edx
	movl	%eax, -104(%ebp)
	movl	%edx, -100(%ebp)
	movl	-104(%ebp), %ecx
	movl	-100(%ebp), %ebx
	movl	-112(%ebp), %eax
	movl	-108(%ebp), %edx
	subl	%ecx, %eax
	sbbl	%ebx, %edx
	movl	%eax, -96(%ebp)
	movl	%edx, -92(%ebp)
	fildll	-96(%ebp)
	fabs
	fnstcw	-138(%ebp)
	movzwl	-138(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -140(%ebp)
	fldcw	-140(%ebp)
	fistpll	-96(%ebp)
	fldcw	-138(%ebp)
	movl	-80(%ebp), %eax
	movl	-76(%ebp), %edx
	movl	%eax, -152(%ebp)
	movl	%edx, -148(%ebp)
	movl	-148(%ebp), %edx
	cmpl	-92(%ebp), %edx
	jg	.L3
	movl	-148(%ebp), %eax
	cmpl	-92(%ebp), %eax
	jl	.L21
	movl	-152(%ebp), %edx
	cmpl	-96(%ebp), %edx
	jae	.L3
.L21:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	movl	%eax, -80(%ebp)
	movl	%edx, -76(%ebp)
.L3:
	movl	-72(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%eax, -160(%ebp)
	movl	%edx, -156(%ebp)
	movl	-156(%ebp), %edx
	cmpl	-92(%ebp), %edx
	jl	.L5
	movl	-156(%ebp), %eax
	cmpl	-92(%ebp), %eax
	jg	.L22
	movl	-160(%ebp), %edx
	cmpl	-96(%ebp), %edx
	jbe	.L5
.L22:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	movl	%eax, -72(%ebp)
	movl	%edx, -68(%ebp)
.L5:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	addl	%eax, -88(%ebp)
	adcl	%edx, -84(%ebp)
	addl	$1, -116(%ebp)
.L2:
	cmpl	$999999, -116(%ebp)
	jle	.L7
	movl	stdout, %eax
	movl	%eax, 12(%esp)
	movl	$30, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC0, (%esp)
	call	fwrite
	movl	-88(%ebp), %eax
	movl	-84(%ebp), %edx
	movl	$1000000, 8(%esp)
	movl	$0, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	__divdi3
	movl	stdout, %ecx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC1, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	stdout, %ecx
	movl	-80(%ebp), %eax
	movl	-76(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC2, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	stdout, %ecx
	movl	-72(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC3, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	$1, -120(%ebp)
	movl	$2, -124(%ebp)
	movl	$4, -60(%ebp)
	movl	$0, -116(%ebp)
	movl	$0, -112(%ebp)
	movl	$0, -108(%ebp)
	movl	$0, -104(%ebp)
	movl	$0, -100(%ebp)
	movl	$0, -96(%ebp)
	movl	$0, -92(%ebp)
	movl	$0, -88(%ebp)
	movl	$0, -84(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -76(%ebp)
	movl	$100000000, -72(%ebp)
	movl	$0, -68(%ebp)
	jmp	.L8
.L13:
#APP
# 52 "ctimer.c" 1
	rdtsc		    
	
# 0 "" 2
#NO_APP
	movl	%eax, -40(%ebp)
	movl	%edx, -36(%ebp)
	movl	-40(%ebp), %eax
	movl	-36(%ebp), %edx
	movl	%eax, -112(%ebp)
	movl	%edx, -108(%ebp)
	movl	-60(%ebp), %eax
#APP
# 54 "ctimer.c" 1
	   addl %eax,-120(%ebp) ;

# 0 "" 2
# 60 "ctimer.c" 1
	rdtsc		    
	
# 0 "" 2
#NO_APP
	movl	%eax, -32(%ebp)
	movl	%edx, -28(%ebp)
	movl	-32(%ebp), %eax
	movl	-28(%ebp), %edx
	movl	%eax, -104(%ebp)
	movl	%edx, -100(%ebp)
	movl	-104(%ebp), %ecx
	movl	-100(%ebp), %ebx
	movl	-112(%ebp), %eax
	movl	-108(%ebp), %edx
	subl	%ecx, %eax
	sbbl	%ebx, %edx
	movl	%eax, -96(%ebp)
	movl	%edx, -92(%ebp)
	fildll	-96(%ebp)
	fabs
	fnstcw	-138(%ebp)
	movzwl	-138(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -140(%ebp)
	fldcw	-140(%ebp)
	fistpll	-96(%ebp)
	fldcw	-138(%ebp)
	movl	-80(%ebp), %eax
	movl	-76(%ebp), %edx
	movl	%eax, -168(%ebp)
	movl	%edx, -164(%ebp)
	movl	-164(%ebp), %edx
	cmpl	-92(%ebp), %edx
	jg	.L9
	movl	-164(%ebp), %eax
	cmpl	-92(%ebp), %eax
	jl	.L23
	movl	-168(%ebp), %edx
	cmpl	-96(%ebp), %edx
	jae	.L9
.L23:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	movl	%eax, -80(%ebp)
	movl	%edx, -76(%ebp)
.L9:
	movl	-72(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%eax, -176(%ebp)
	movl	%edx, -172(%ebp)
	movl	-172(%ebp), %edx
	cmpl	-92(%ebp), %edx
	jl	.L11
	movl	-172(%ebp), %eax
	cmpl	-92(%ebp), %eax
	jg	.L24
	movl	-176(%ebp), %edx
	cmpl	-96(%ebp), %edx
	jbe	.L11
.L24:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	movl	%eax, -72(%ebp)
	movl	%edx, -68(%ebp)
.L11:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	addl	%eax, -88(%ebp)
	adcl	%edx, -84(%ebp)
	addl	$1, -116(%ebp)
.L8:
	cmpl	$999999, -116(%ebp)
	jle	.L13
	movl	stdout, %eax
	movl	%eax, 12(%esp)
	movl	$66, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC4, (%esp)
	call	fwrite
	movl	-88(%ebp), %eax
	movl	-84(%ebp), %edx
	movl	$1000000, 8(%esp)
	movl	$0, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	__divdi3
	movl	stdout, %ecx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC1, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	stdout, %ecx
	movl	-80(%ebp), %eax
	movl	-76(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC2, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	stdout, %ecx
	movl	-72(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC3, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	$1, -120(%ebp)
	movl	$2, -124(%ebp)
	movl	$4, -60(%ebp)
	movl	$0, -116(%ebp)
	movl	$0, -112(%ebp)
	movl	$0, -108(%ebp)
	movl	$0, -104(%ebp)
	movl	$0, -100(%ebp)
	movl	$0, -96(%ebp)
	movl	$0, -92(%ebp)
	movl	$0, -88(%ebp)
	movl	$0, -84(%ebp)
	movl	$0, -80(%ebp)
	movl	$0, -76(%ebp)
	movl	$100000000, -72(%ebp)
	movl	$0, -68(%ebp)
	jmp	.L14
.L19:
#APP
# 89 "ctimer.c" 1
	rdtsc		    
	
# 0 "" 2
#NO_APP
	movl	%eax, -24(%ebp)
	movl	%edx, -20(%ebp)
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, -112(%ebp)
	movl	%edx, -108(%ebp)
	movl	-60(%ebp), %eax
#APP
# 91 "ctimer.c" 1
	   lock       ;
   addl %eax,-120(%ebp) ;

# 0 "" 2
# 98 "ctimer.c" 1
	rdtsc		    
	
# 0 "" 2
#NO_APP
	movl	%eax, -16(%ebp)
	movl	%edx, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, -104(%ebp)
	movl	%edx, -100(%ebp)
	movl	-104(%ebp), %ecx
	movl	-100(%ebp), %ebx
	movl	-112(%ebp), %eax
	movl	-108(%ebp), %edx
	subl	%ecx, %eax
	sbbl	%ebx, %edx
	movl	%eax, -96(%ebp)
	movl	%edx, -92(%ebp)
	fildll	-96(%ebp)
	fabs
	fnstcw	-138(%ebp)
	movzwl	-138(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -140(%ebp)
	fldcw	-140(%ebp)
	fistpll	-96(%ebp)
	fldcw	-138(%ebp)
	movl	-80(%ebp), %eax
	movl	-76(%ebp), %edx
	movl	%eax, -184(%ebp)
	movl	%edx, -180(%ebp)
	movl	-180(%ebp), %edx
	cmpl	-92(%ebp), %edx
	jg	.L15
	movl	-180(%ebp), %eax
	cmpl	-92(%ebp), %eax
	jl	.L25
	movl	-184(%ebp), %edx
	cmpl	-96(%ebp), %edx
	jae	.L15
.L25:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	movl	%eax, -80(%ebp)
	movl	%edx, -76(%ebp)
.L15:
	movl	-72(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%eax, -192(%ebp)
	movl	%edx, -188(%ebp)
	movl	-188(%ebp), %edx
	cmpl	-92(%ebp), %edx
	jl	.L17
	movl	-188(%ebp), %eax
	cmpl	-92(%ebp), %eax
	jg	.L26
	movl	-192(%ebp), %edx
	cmpl	-96(%ebp), %edx
	jbe	.L17
.L26:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	movl	%eax, -72(%ebp)
	movl	%edx, -68(%ebp)
.L17:
	movl	-96(%ebp), %eax
	movl	-92(%ebp), %edx
	addl	%eax, -88(%ebp)
	adcl	%edx, -84(%ebp)
	addl	$1, -116(%ebp)
.L14:
	cmpl	$999999, -116(%ebp)
	jle	.L19
	movl	stdout, %eax
	movl	%eax, 12(%esp)
	movl	$67, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC5, (%esp)
	call	fwrite
	movl	-88(%ebp), %eax
	movl	-84(%ebp), %edx
	movl	$1000000, 8(%esp)
	movl	$0, 12(%esp)
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	__divdi3
	movl	stdout, %ecx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC1, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	stdout, %ecx
	movl	-80(%ebp), %eax
	movl	-76(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC2, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	stdout, %ecx
	movl	-72(%ebp), %eax
	movl	-68(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$.LC3, 4(%esp)
	movl	%ecx, (%esp)
	call	fprintf
	movl	$0, %eax
	addl	$208, %esp
	popl	%ecx
	popl	%ebx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.3.0 20080428 (Red Hat 4.3.0-8)"
	.section	.note.GNU-stack,"",@progbits
