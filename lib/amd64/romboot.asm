; /********************************************************************************/
; /* NASM Assembler Settings:                                                      */
; /********************************************************************************/

[bits 16]
[org 0x0000]

; /********************************************************************************/
; /* @brief BIOS, code is based on computron's BIOS to avoid starting from scatch. */
; /********************************************************************************/

%define LEGACY_VM_PORT 0xE6

jmp 0xF000:__bios_power_on

__no_boot_drive:
	mov si, __award_no_xpm
	call __print_screen
	hlt

__init_bios_area:
    jmp _vga_init
    jmp _com_init
    
    ret
_vga_init:
    push ds
    mov ax, 0x40 
    mov ds, ax

    mov bx, 0x10
    mov ax, [bx]
    and ax, 0xffcf
    or ax, 0x0020
    mov [bx], ax

    mov bx, 0x85
    mov al, 0x10
    mov [bx], al

    mov bx, 0x87 ;; clear screen
    mov al, 0x60
    mov [bx], al

    mov bx, 0x88 ;; setup basic screen
    mov al, 0xf9
    mov [bx], al

    mov bx, 0x89 ;; setup basic screen
    mov al, 0x51
    mov [bx], al

    mov bx, 0x65 ;; setup basic screen
    mov al, 0x09
    mov [bx], al

    pop ds

_com_init:
    ret

__graphics_init:
    mov dx, 0x3c2
    mov al, 0xc3

    out dx, al

    mov dx, 0x3C4
    mov al, 0x04

    out dx, al

    mov dx, 0x3C5
    mov al, 0x02

    out dx, al

    ret

__print_screen:
    pusha
    push    es

    push    cs
    pop     es
    mov     di, si
    xor     cx, cx
    not     cx
    xor     al, al
    
    cld
    repnz   scasb
    
    not     cx
    dec     cx
    push    cx

    mov     ax, 0x0300
    mov     bx, 0x0000

    int     0x10

    pop     cx

    mov     ax, 0x1301
    mov     bx, 0x0007
    mov     bp, si

    int     0x10

    pop     es
    popa

    ret

__reboot_on_key:
    mov     si, __press_any_key
    call    __print_screen
	
__reboot_on_key_loop:
    mov     ax, 0x1600
    out     LEGACY_VM_PORT, al ;; legacy vm port
    or      ax, 0 ;; or ax with 0
    jz      __reboot_on_key
    jmp     0xF000:0 ;; finally cold boot again.

__vector_unimpl_isr:
    push    si
    mov     si, __award_umipl
    call    __print_screen
    pop     si
    iret

__vector_division_by_zero_isr:
    push    si
    mov     si, __division_by_zero
    call    __print_screen
    pop     si
    jmp 	__reboot_on_key

__vector_single_step:
	iret

__vector_breakpoint:
	iret
	
__vector_overflow:
    push    si
    mov     si, __overflow
    call    __print_screen
    pop     si
    jmp 	__reboot_on_key

__vector_invalid_opcode:
    push    si
    mov     si, __invalid_opcode
    call    __print_screen
    pop     si
    jmp 	__reboot_on_key

__vector_video_service:
    sti
    cld
    pusha
    mov bx, 40h
    mov ds, bx
    mov bl, ds:10h
    and bl, 00110000b
    cmp bl, 00110000b
    mov bx, 0xb800
    jnz __vector_video_issue
    mov bx, 0xb000    

__vector_video_issue:
    push bx
    mov bp, sp
    call __vector_video_call_issue
    popa
    iret

__vector_video_call_issue:
    cmp ah, 0fh
    shl ah, 1
    mov bl, ah
    mov bh, 0
    jmp [cs:bx+__vector_video_tbl]
    iret

__vector_init:
	push ds
	mov dx, [__vector_unimpl_isr]
	xor al, al

__vector_init_loop:
	call __install
	inc al
	jnz __vector_init_loop

	mov al, 0x00
	mov dx, __vector_division_by_zero_isr
	call __install

	mov al, 0x01
	mov dx, __vector_single_step
	call __install

	mov al, 0x03
	mov dx, __vector_breakpoint
	call __install
	
	mov al, 0x04
	mov dx, __vector_overflow
	call __install

	mov al, 0x06
	mov dx, __vector_invalid_opcode
	call __install

	mov al, 0x0a
	mov dx, __vector_video_service
	call __install

    ret

__install:
    push    ax
    mov     cl, 4
    mul     byte cl
    xor     bx, bx
    mov     ds, bx
    mov     bx, ax
    mov     ax, cs
    mov     word [bx], dx
    mov     word [bx+2], ax
    pop     ax
    ret

;; DATA
__award_splash: db "mp-boot, Copyright Amlal El Mahrouss", 0xd, 0xa
				db ">> Booting...", 0xd, 0xa, 0x0

__award_no_xpm: db ">> Not an MP Boot Sector drive.", 0xd, 0xa, 0x0

__award_umipl:  db ">> Unimplemented.", 0xd, 0xa, 0x0

__overflow:  db ">> Stack Overflow.", 0xd, 0xa, 0x0

__invalid_opcode:  db ">> Invalid op-code.", 0xd, 0xa, 0x0

__division_by_zero:  db ">> Division by zero.", 0xd, 0xa, 0x0

__press_any_key: db ">> Press any key...", 0xd, 0xa, 0x0

__vector_video_tbl:
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr
    dw __vector_unimpl_isr

__bios_power_on:
    cli 
    cld

	mov ax, cs
	mov ss, ax
	mov sp, ax
	
	push cs
	pop ds

	xor ax, ax
	mov es, ax

    ;; irq stuff.
	out 0x21, al ;; master PIC IMR
	out 0xA1, al ;; slave PIC IMR

	mov [es:0x500], byte 0xFF
	
    call __vector_init
    call __init_bios_area
	call __graphics_init

	mov si, __award_splash
	call __print_screen
	
	sti

    ;; jump again here
    jmp 0xF000:0x7c00

L0:
    jmp 0xF000:0

__kstem_descriptor_table:
    dw 8               ; Length of table
    db 0xFC            ; IBM AT (same as F000:FFFE)
    db 0x01            ;        (same as F000:FFFF)
    db 0x01            ; BIOS revision level
    db 01100000b       ; Feature information
    dw 0

times 0xfff0-($-$$) nop ; pad up to fff0

jmp 0xF000:0x0000 ; fff0: We start here after CPU reset

__bios_date: db "12/14/23", 0 ; fff5: BIOS release date

db 0xFC ; fffe: IBM AT
db 0x01 ; ffff: sub model id or something like that