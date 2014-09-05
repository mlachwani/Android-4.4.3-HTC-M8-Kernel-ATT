/*
 *  Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_MXC_IRQS_H__
#define __ASM_ARCH_MXC_IRQS_H__

#include <asm-generic/gpio.h>

#if defined CONFIG_ARM_GIC
#define MXC_INTERNAL_IRQS	160
#elif defined CONFIG_MXC_TZIC
#define MXC_INTERNAL_IRQS	128
#else
#define MXC_INTERNAL_IRQS	64
#endif

#define MXC_GPIO_IRQ_START	MXC_INTERNAL_IRQS

#define MXC_BOARD_IRQ_START	(MXC_INTERNAL_IRQS + ARCH_NR_GPIOS)

#ifdef CONFIG_MACH_MX31ADS_WM1133_EV1
#define MXC_BOARD_IRQS  80
#else
#define MXC_BOARD_IRQS	16
#endif

#define MXC_IPU_IRQ_START	(MXC_BOARD_IRQ_START + MXC_BOARD_IRQS)

#ifdef CONFIG_MX3_IPU_IRQS
#define MX3_IPU_IRQS CONFIG_MX3_IPU_IRQS
#else
#define MX3_IPU_IRQS 0
#endif

#define NR_IRQS			(MXC_IPU_IRQ_START + MX3_IPU_IRQS)

extern int imx_irq_set_priority(unsigned char irq, unsigned char prio);

#define FIQ_START	0
extern int mxc_set_irq_fiq(unsigned int irq, unsigned int type);

#endif 