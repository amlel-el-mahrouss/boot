/*
*	========================================================
 *
 *	mp-boot
 * 	Copyright Amlal El Mahrouss, all rights reserved.
 *
 * 	========================================================
 */

#pragma once

typedef __UINTPTR_TYPE__ uintptr_t;

typedef unsigned long long int uint64_t;
typedef unsigned uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define __mpboot__ 7

typedef __INTPTR_TYPE__ intptr_t;

typedef long long int int64_t;
typedef int int32_t;
typedef short int16_t;
typedef char int8_t;

typedef void* voidptr_t;
typedef char* caddr_t;

typedef __UINTPTR_TYPE__ ptrtype_t;
typedef ptrtype_t size_t;

#define array_size(arr) (sizeof(arr[0])/sizeof(arr))

#ifndef nil
#   define nil ((voidptr_t)0)
#endif

#ifndef null
#   define null ((voidptr_t)0)
#endif

#define no 0
#define yes 1

#define boolean char

void panic(const char* reason);
void puts(const char* text);