	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 2
	.globl	_freeBuffer                     ; -- Begin function freeBuffer
	.p2align	2
_freeBuffer:                            ; @freeBuffer
	.cfi_startproc
; %bb.0:
	cbz	x0, LBB0_2
; %bb.1:
	stp	x20, x19, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	ldr	x8, [x0, #24]
	mov	x19, x0
	mov	x0, x8
	bl	_free
	mov	x0, x19
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32             ; 16-byte Folded Reload
	b	_free
LBB0_2:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_initBuffer                     ; -- Begin function initBuffer
	.p2align	2
_initBuffer:                            ; @initBuffer
	.cfi_startproc
; %bb.0:
	stp	x20, x19, [sp, #-32]!           ; 16-byte Folded Spill
	stp	x29, x30, [sp, #16]             ; 16-byte Folded Spill
	add	x29, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	mov	x19, x0
	lsl	x0, x0, #3
	bl	_malloc
	cbz	x0, LBB1_4
; %bb.1:
	mov	x20, x0
	mov	w0, #32                         ; =0x20
	bl	_malloc
	cbz	x0, LBB1_3
; %bb.2:
	stp	xzr, xzr, [x0]
	stp	x19, x20, [x0, #16]
	b	LBB1_4
LBB1_3:
	mov	x0, x20
	bl	_free
	mov	x0, #0                          ; =0x0
LBB1_4:
	ldp	x29, x30, [sp, #16]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp], #32             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_enqueue                        ; -- Begin function enqueue
	.p2align	2
_enqueue:                               ; @enqueue
	.cfi_startproc
; %bb.0:
	cbz	x0, LBB2_3
; %bb.1:
	ldr	x8, [x0]
	ldr	x9, [x0, #8]
	add	x9, x9, #1
	ldr	x10, [x0, #16]
	udiv	x11, x9, x10
	msub	x9, x11, x10, x9
	cmp	x8, x9
	b.ne	LBB2_4
; %bb.2:
	mov	w0, #0                          ; =0x0
LBB2_3:
	ret
LBB2_4:
	ldr	x8, [x0, #8]
	ldr	x9, [x0, #24]
	str	x1, [x9, x8, lsl #3]
	add	x8, x8, #1
	ldr	x9, [x0, #16]
	udiv	x10, x8, x9
	msub	x8, x10, x9, x8
	str	x8, [x0, #8]
	mov	w0, #1                          ; =0x1
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_dequeue                        ; -- Begin function dequeue
	.p2align	2
_dequeue:                               ; @dequeue
	.cfi_startproc
; %bb.0:
	mov	w8, #0                          ; =0x0
	cbz	x0, LBB3_4
; %bb.1:
	cbz	x1, LBB3_4
; %bb.2:
	ldr	x8, [x0]
	ldr	x9, [x0, #8]
	cmp	x8, x9
	b.ne	LBB3_5
; %bb.3:
	mov	w8, #0                          ; =0x0
LBB3_4:
	mov	x0, x8
	ret
LBB3_5:
	ldr	x8, [x0]
	ldr	x9, [x0, #24]
	ldr	x9, [x9, x8, lsl #3]
	str	x9, [x1]
	add	x8, x8, #1
	ldr	x9, [x0, #16]
	udiv	x10, x8, x9
	msub	x8, x10, x9, x8
	str	x8, [x0]
	mov	w0, #1                          ; =0x1
	ret
	.cfi_endproc
                                        ; -- End function
.subsections_via_symbols
