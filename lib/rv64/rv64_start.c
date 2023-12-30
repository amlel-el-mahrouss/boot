/*
 *	========================================================
 *
 *	mp-boot
 * 	Date Added: 08/11/2023
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 * 	
 * 	========================================================
 */

#include <lib/types.h>
#include <lib/bitmanip.h>
#include <lib/memory_map.h>
#include <lib/partition_map.h>

/////////////////////////////////////////////////////////////////////////////////////////

// @brief Start unit                                                                   //

/////////////////////////////////////////////////////////////////////////////////////////

long long int __mp_hart_counter = 0UL;

/* @brief makes a power on self test on memory, cpu, master disk and network card. */
extern void mp_make_post(void);

extern void mp_start(void)
{
    ++__mp_hart_counter;
    mp_make_post();
}

extern void mp_hang(void)
{
    ++__mp_hart_counter;

    while (yes) {}
}