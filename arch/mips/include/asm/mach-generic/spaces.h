/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 - 1999, 2000, 03, 04 Ralf Baechle
 * Copyright (C) 2000, 2002  Maciej W. Rozycki
 * Copyright (C) 1990, 1999, 2000 Silicon Graphics, Inc.
 */
#ifndef _ASM_MACH_GENERIC_SPACES_H
#define _ASM_MACH_GENERIC_SPACES_H

#include <linux/const.h>

#ifndef PHYS_OFFSET
#define PHYS_OFFSET		_AC(0, UL)
#endif

#ifdef CONFIG_32BIT

#define CAC_BASE		_AC(0x80000000, UL)
#define IO_BASE			_AC(0xa0000000, UL)
#define UNCAC_BASE		_AC(0xa0000000, UL)

#ifndef MAP_BASE
#define MAP_BASE		_AC(0xc0000000, UL)
#endif

#ifndef HIGHMEM_START
#define HIGHMEM_START		_AC(0x20000000, UL)
#endif

#endif 

#ifdef CONFIG_64BIT

#ifndef CAC_BASE
#ifdef CONFIG_DMA_NONCOHERENT
#define CAC_BASE		_AC(0x9800000000000000, UL)
#else
#define CAC_BASE		_AC(0xa800000000000000, UL)
#endif
#endif

#ifndef IO_BASE
#define IO_BASE			_AC(0x9000000000000000, UL)
#endif

#ifndef UNCAC_BASE
#define UNCAC_BASE		_AC(0x9000000000000000, UL)
#endif

#ifndef MAP_BASE
#define MAP_BASE		_AC(0xc000000000000000, UL)
#endif

#ifndef HIGHMEM_START
#define HIGHMEM_START		(_AC(1, UL) << _AC(59, UL))
#endif

#define TO_PHYS(x)		(             ((x) & TO_PHYS_MASK))
#define TO_CAC(x)		(CAC_BASE   | ((x) & TO_PHYS_MASK))
#define TO_UNCAC(x)		(UNCAC_BASE | ((x) & TO_PHYS_MASK))

#endif 

#ifndef PAGE_OFFSET
#define PAGE_OFFSET		(CAC_BASE + PHYS_OFFSET)
#endif

#ifndef FIXADDR_TOP
#define FIXADDR_TOP		((unsigned long)(long)(int)0xfffe0000)
#endif

#endif 