/*
 *	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#include <lib/partition_map.h>
#include <lib/string.h>

// include this for documentation.

static const size_t g_filesystems_count = 4;

static const caddr_t g_filesystems[] = { 
    "ffs",
    "ffs_2",
    "zfs",
    "ufs",
};

boolean mpboot_filesystem_exists(caddr_t fs, size_t len)
{

    for (size_t i = 0; i < g_filesystems_count; i++)
    {
        if (len != strlen(g_filesystems[i]))
            continue;
        
        if (strncmp(g_filesystems[i], fs, strlen(g_filesystems[i])) == 0)
        {
            return yes;
        }
    }

    return no;
}

boolean mpboot_is_mbs(caddr_t blob, size_t len)
{
    struct boot_block* bb = (struct boot_block*)blob;

    if (bb && strncmp(bb->magic, MBS_MAG, MBS_MAG_LEN) == 0)
        return yes;

    return no;
}