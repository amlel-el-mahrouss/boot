/*
 *	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 * 	
 * 	========================================================
 */

.balign 4
.global __start
.extern __mpboot_stack_end
 
__start
	mv sp, __mpboot_stack_end
    b mpboot_start
	
	/* Jump to cold reset. */