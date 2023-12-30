 #
 #	========================================================
 #
 #	mp-boot
 # 	Date Added: 08/01/2023
 # 	Copyright Amlal El Mahrouss, all rights reserved.
 # 	
 # 	========================================================
 #

.PHONY: firmware-riscv64
firmware-riscv64:
	riscv64-unknown-elf-gcc -D__MPBOOT -Werror -Wall -c -nostdlib -ffreestanding -I../ -D__COMPILE_RISCV__ -D__KSTRICT__ -D__KDEBUG__ -D__KSIMP__ -O2 -mcmodel=medany \
	$(wildcard *.c) $(wildcard rv64/*.s)
