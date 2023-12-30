/*
 *	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#ifndef __PARTITION_MAP_H__
#define __PARTITION_MAP_H__

#include <lib/types.h>

#define UUID_LEN 37

/* the first 512 > x > 1024 bytes of a disk contains this headers. */

/**
 * @brief The EPM bootloader block.
 * 
 */
struct boot_block
{
	char magic[4];
    char name[32];
    char uuid[UUID_LEN];
    int version;
    long long int num_blocks;
    long long int sector_sz;
    long long int sector_start;
    
};

/**
 * @brief The EPM partition block.
 * 
 */
struct part_block
{
    char name[32];
    int magic;
    long long int sector_end;
    long long int sector_sz;
    long long int sector_start;
    short type;
    int version;
    char fs[16]; /* ffs_2 */

};

typedef struct part_block part_block_t;
typedef struct boot_block boot_block_t;

/* @brief AMD64 magic for EPM */
#define EPM_MAGIC_X86   "EPMAM"

/* @brief RISC-V magic for EPM */
#define EPM_MAGIC_RV    "EPMRV"

/* @brief ARM magic for EPM */
#define EPM_MAGIC_ARM   "EPMAR"

#define EPM_MAX_BLKS   128

#define EPM_BOOT_BLK_SZ sizeof(struct boot_block)
#define EPM_PART_BLK_SZ sizeof(struct part_block)

//! version types.
//! use in boot block version field.

enum
{
    EPM_MPUNIX            = 0xcf,
    EPM_LINUX             = 0x8f,
    EPM_BERKELEY_SOFTWARE = 0x9f,
    EPM_HCORE             = 0x1f,
};

#endif // ifndef __PARTITION_MAP_H__
