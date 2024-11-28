[bits 16]
[org 0x7c00]

;; mp-boot BIOS extension from Amlal El Mahrouss.

_start:
	mov si, __stuff_0
    call __print
_probe_disk:
    mov bl, 4
    call __beep

_first_disk:
	mov cl, 0x80
    jmp _disk_boot

	jmp _loop

_error_disk:
	mov si, __stuff_3
    call __print
_loop:
	cli 
	hlt
    jmp $

%define BOOT_SEG 	0xF000
%define BOOT_AT  	0x7C80

_disk_boot:
	mov si, _disk_packet
	mov ah, 0x42
	mov dl, cl
	int 0x13
	jnc _disk_boot_success
	jmp _disk_inc

_disk_inc:
	inc cl
	cmp cl, 0xFF
	je _error_disk
	jmp _disk_boot

_disk_boot_success:
    mov si, __stuff_2
    call __print
	jmp BOOT_SEG:BOOT_AT

_disk_packet:
	db 0x10
	db 0
_disk_blk_cnt:
	dw 148 ;; doesn't really matter here, interrupt 0x13 resets that.
_disk_block_add:
	dw BOOT_SEG
	dw BOOT_AT
_disk_block_lba:
	dq 0 ;; put the lba to read here.
_disk_packet_end:

__stuff_0:
    db ">> MPSYS MP Boot Sector ROM (C) 2023 MPSYS all rights reserved.", 0xd, 0xa, 0

__stuff_2:
    db ">> Booting from media...", 0xd, 0xa, 0

__stuff_3:
    db ">> Not a bootable media.", 0xd, 0xa, 0

;; beep routine from pc speaker
__beep:
	push ax
	push cx
	mov al, 10110110b
	out 43h, al
	mov ax, 528h
	out 42h, al
	mov al, ah
	out 42h, al
	in al, 61h
	push ax
	or al, 00000011b
	out 61h, al
	xor cx, cx
;; beep loop, wait or return.
__beep_1:
	loop __beep_1
	dec bl
	jnz __beep_1
	pop ax
	out 61h, al
	pop cx
	pop ax
	ret

__print:
	lodsb
	or al, al
	jnz __print1
	ret

__out_char:
	push bx
	push ax
	mov ah, 0eh
	mov bl, 7
	int 10h
	pop ax
	pop bx
	ret

__print1:
	call __out_char
	jmp __print

__locate:
	push dx
	push bx
	mov dx, ax
	mov ah, 2
	mov bh, 0
	int 10h
	pop bx
	pop dx
	ret

;; BOOT_AT
__code:
	times 148 nop
__end_code:

times 510 - ($-$$) nop

dw 0xaa55

;; Custom mp-boot Bootable header

db "EPMROM", 0
;; build date
db "02/11/23", 0
;; Start code
dw 0x7c00
;; segment
dw 0xff00
