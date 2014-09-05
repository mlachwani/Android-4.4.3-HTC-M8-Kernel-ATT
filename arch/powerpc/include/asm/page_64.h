#ifndef _ASM_POWERPC_PAGE_64_H
#define _ASM_POWERPC_PAGE_64_H

/*
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#define HW_PAGE_SHIFT		12
#define HW_PAGE_SIZE		(ASM_CONST(1) << HW_PAGE_SHIFT)
#define HW_PAGE_MASK		(~(HW_PAGE_SIZE-1))

#define PAGE_FACTOR		(PAGE_SHIFT - HW_PAGE_SHIFT)

#define SID_SHIFT		28
#define SID_MASK		ASM_CONST(0xfffffffff)
#define ESID_MASK		0xfffffffff0000000UL
#define GET_ESID(x)		(((x) >> SID_SHIFT) & SID_MASK)

#define SID_SHIFT_1T		40
#define SID_MASK_1T		0xffffffUL
#define ESID_MASK_1T		0xffffff0000000000UL
#define GET_ESID_1T(x)		(((x) >> SID_SHIFT_1T) & SID_MASK_1T)

#ifndef __ASSEMBLY__
#include <asm/cache.h>

typedef unsigned long pte_basic_t;

static __inline__ void clear_page(void *addr)
{
	unsigned long lines, line_size;

	line_size = ppc64_caches.dline_size;
	lines = ppc64_caches.dlines_per_page;

	__asm__ __volatile__(
	"mtctr	%1	# clear_page\n\
1:      dcbz	0,%0\n\
	add	%0,%0,%3\n\
	bdnz+	1b"
        : "=r" (addr)
        : "r" (lines), "0" (addr), "r" (line_size)
	: "ctr", "memory");
}

extern void copy_page(void *to, void *from);

extern u64 ppc64_pft_size;

#endif 

#ifdef CONFIG_PPC_MM_SLICES

#define SLICE_LOW_SHIFT		28
#define SLICE_HIGH_SHIFT	40

#define SLICE_LOW_TOP		(0x100000000ul)
#define SLICE_NUM_LOW		(SLICE_LOW_TOP >> SLICE_LOW_SHIFT)
#define SLICE_NUM_HIGH		(PGTABLE_RANGE >> SLICE_HIGH_SHIFT)

#define GET_LOW_SLICE_INDEX(addr)	((addr) >> SLICE_LOW_SHIFT)
#define GET_HIGH_SLICE_INDEX(addr)	((addr) >> SLICE_HIGH_SHIFT)

#ifndef __ASSEMBLY__

struct slice_mask {
	u16 low_slices;
	u16 high_slices;
};

struct mm_struct;

extern unsigned long slice_get_unmapped_area(unsigned long addr,
					     unsigned long len,
					     unsigned long flags,
					     unsigned int psize,
					     int topdown,
					     int use_cache);

extern unsigned int get_slice_psize(struct mm_struct *mm,
				    unsigned long addr);

extern void slice_init_context(struct mm_struct *mm, unsigned int psize);
extern void slice_set_user_psize(struct mm_struct *mm, unsigned int psize);
extern void slice_set_range_psize(struct mm_struct *mm, unsigned long start,
				  unsigned long len, unsigned int psize);

#define slice_mm_new_context(mm)	((mm)->context.id == MMU_NO_CONTEXT)

#endif 
#else
#define slice_init()
#ifdef CONFIG_PPC_STD_MMU_64
#define get_slice_psize(mm, addr)	((mm)->context.user_psize)
#define slice_set_user_psize(mm, psize)		\
do {						\
	(mm)->context.user_psize = (psize);	\
	(mm)->context.sllp = SLB_VSID_USER | mmu_psize_defs[(psize)].sllp; \
} while (0)
#else 
#ifdef CONFIG_PPC_64K_PAGES
#define get_slice_psize(mm, addr)	MMU_PAGE_64K
#else 
#define get_slice_psize(mm, addr)	MMU_PAGE_4K
#endif 
#define slice_set_user_psize(mm, psize)	do { BUG(); } while(0)
#endif 

#define slice_set_range_psize(mm, start, len, psize)	\
	slice_set_user_psize((mm), (psize))
#define slice_mm_new_context(mm)	1
#endif 

#ifdef CONFIG_HUGETLB_PAGE

#ifdef CONFIG_PPC_MM_SLICES
#define HAVE_ARCH_HUGETLB_UNMAPPED_AREA
#endif

#endif 

#define VM_DATA_DEFAULT_FLAGS \
	(is_32bit_task() ? \
	 VM_DATA_DEFAULT_FLAGS32 : VM_DATA_DEFAULT_FLAGS64)

#define VM_STACK_DEFAULT_FLAGS32	(VM_READ | VM_WRITE | VM_EXEC | \
					 VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#define VM_STACK_DEFAULT_FLAGS64	(VM_READ | VM_WRITE | \
					 VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#define VM_STACK_DEFAULT_FLAGS \
	(is_32bit_task() ? \
	 VM_STACK_DEFAULT_FLAGS32 : VM_STACK_DEFAULT_FLAGS64)

#include <asm-generic/getorder.h>

#endif 
