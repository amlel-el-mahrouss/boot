/*
 *	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 * 	
 *  Brief: Runtime 0 code for RISC-V.
 * 
 * 	========================================================
 */

.section .init
.align 4

/* Code starts at 8M, everything below is memory mapped hardware. */

.option norvc

.extern mpboot_start
.global mpboot_hart_present

boot_start_proc:
	.cfi_startproc

.option push
.option norelax

	la gp, mpboot_global_pointer

.option pop

	la sp, mpboot_stack_end

	la t5, mpboot_bss_start
	la t6, mpboot_bss_end

crt0_bss_clear:
	sd zero, (t5)
	addi t5, t5, 8
	bgeu t5, t6, crt0_bss_clear

	csrr t0, mhartid
	beqz t0, mpboot_start

	j mpboot_hang

	.cfi_endproc

mpboot_hang:
	wfi
	j mpboot_hang

.section .data
.align 4
mpboot_hart_present:
	.long 0
