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

static const __SIZE_TYPE__ g_filesystems_count = 4;

static const caddr_t g_filesystems[] = { 
    "ffs",
    "ffs_2",
    "zfs",
    "ufs",
};

boolean mpboot_filesystem_exists(caddr_t fs)
{
    for (__SIZE_TYPE__ i = 0; i < g_filesystems_count; i++)
    {
        if (strncmp(g_filesystems[i], fs, strlen(g_filesystems[i])) == 0)
        {
            return yes;
        }

    }

    return no;
}