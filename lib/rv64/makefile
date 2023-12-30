 #
 #	========================================================
 #
 #	mp-boot
 # 	Date Added: 08/11/2023
 # 	Copyright Amlal El Mahrouss, all rights reserved.
 # 	
 # 	========================================================
 #

.PHONY: hal
hal:
	riscv64-unknown-elf-gcc -Werror -I../../../ -Wall -c -nostdlib -ffreestanding -fno-builtin -D__BSTRICT__ -D__BDEBUG__ -mcmodel=medany -O2 -fsanitize=undefined\
	 $(wildcard *.s) $(wildcard *.c) -c

.PHONY: clean
clean:
	rm -f $(wildcard *.o)
