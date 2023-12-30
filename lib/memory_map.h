/*
 *	========================================================
 *
 *	kickStart
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __MP_MEMORY_MAP_H__
#define __MP_MEMORY_MAP_H__

struct mp_hw_memmap
{
    __UINTPTR_TYPE__ base_ptr;
    __SIZE_TYPE__    length_ptr;
    __UINT32_TYPE__   feature_set;
};

#define HW_FEATURE_VGA           10
#define HW_FEATURE_HDMI          11
#define HW_FEATURE_VIRT_BLK      12
#define HW_FEATURE_VIRT_NET      13
#define HW_FEATURE_POWER_MANAGER 14
#define HW_FEATURE_PCI_TREE      15

#define HW_MEMORY_MAP_LEN 15

extern struct mp_hw_memmap g_memmap[HW_MEMORY_MAP_LEN];

#ifdef __COMPILE_RISCV__

enum
{
    HW_MEMMAP_DEBUG,
    HW_MEMMAP_MROM,
    HW_MEMMAP_RESR,
    HW_MEMMAP_SYS_CLINT,
    HW_MEMMAP_PLIC,
    HW_MEMMAP_UART,
    HW_MEMMAP_VIRT_BLK,
    HW_MEMMAP_DRAM,
    HW_MEMMAP_PCIE_MMIO,
    HW_MEMMAP_PCIE_PIO,
    HW_MEMMAP_PCIE_ECAM,
    HW_MEMMAP_RTC,
    HW_MEMMAP_PVC, // platform video controller
    HW_MEMMAP_VIRT_NET, // platform video controller
    HW_MEMMAP_PCI_TREE, // pci device tree
    HW_MEMMAP_COUNT,
};

#endif

#endif /* ifndef __MP_MEMORY_MAP_H__ */