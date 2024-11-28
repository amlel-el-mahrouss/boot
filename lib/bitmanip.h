/*
 *	========================================================
 *
 *	kickStart
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */
 
#ifndef __BITMANIP_H__
#define __BITMANIP_H__

// mp-boot Bits API.
// Purpose: Bit manip helpers.

#define mpboot_set_bit(X, O) X = (1 << O) | X
#define mpboot_clear_bit(X, O) X = ~(1 << O) & X
#define mpboot_toogle(X, O) X = (1 << O) ^ X
#define mpboot_lsb(X) X = X & -X
#define mpboot_msb(X) X = -(mpboot_lsb(X)) & X

#endif // ifndef __BITMANIP_H__
