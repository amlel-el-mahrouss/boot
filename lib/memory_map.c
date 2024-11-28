/*
 *	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <lib/memory_map.h>

#ifdef __COMPILE_RISCV__

struct mpboot_hw_memmap g_riscv_memmap[] = {
    [0] = { .base_ptr = 0x0, .length_ptr = 0x100, .feature_set = 0 }, // debug
    [1] = { .base_ptr = 0x100, .length_ptr = 0x11000, .feature_set = 0 }, // mrom
    [2] = { .base_ptr = 0x100000, .length_ptr  = 0x1000, .feature_set = HW_FEATURE_POWER_MANAGER }, // resr
    [3] = { .base_ptr = 0x2000000, .length_ptr = 0x10000, .feature_set = 0 }, // clint
    [4] = { .base_ptr = 0x0c000000, .length_ptr  = 0x4000, .feature_set = 0 }, // plic
    [5] = { .base_ptr = 0x10000000, .length_ptr = 0x100, .feature_set = 0 }, // uart
    [6] = { .base_ptr = 0x10001000, .length_ptr = 0x1000, .feature_set = HW_FEATURE_VIRT_BLK }, // virtio block device
    [7] = { .base_ptr = 0x80000000, .length_ptr = 0x0, .feature_set = 0 }, // dram
    [8] = { .base_ptr = 0x40000000, .length_ptr = 0x40000000, .feature_set = 0 }, // pcie mmio
    [9] = { .base_ptr = 0x03000000, .length_ptr = 0x00010000, .feature_set = 0 }, // pcie pio
    [10] = { .base_ptr = 0x30000000, .length_ptr = 0x10000000, .feature_set = 0 }, // pcie ecam
    [11] = { .base_ptr = 0x101000, .length_ptr = 0x1000, .feature_set = 0 }, // real time clock
    [12] = { .base_ptr = 0x00008000, .length_ptr = 0x0000bfff, .feature_set = HW_FEATURE_VGA }, // video graphics array
    [13] = { .base_ptr = 0x00001000, .length_ptr = 0x1000, .feature_set = HW_FEATURE_VIRT_NET }, // virtio block device
    [14] = { .base_ptr = 0x90000000, .length_ptr = 0x1000, .feature_set = HW_FEATURE_PCI_TREE }, // virtio block device
};

#else

#   warning [mp-boot] no memory map for your platform, please define one.

#endif