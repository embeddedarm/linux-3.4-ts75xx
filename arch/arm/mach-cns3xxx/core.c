/*
 * Copyright 1999 - 2003 ARM Limited
 * Copyright 2000 Deep Blue Solutions Ltd
 * Copyright 2008 Cavium Networks
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 */

#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/clockchips.h>
#include <linux/io.h>
#include <asm/mach/map.h>
#include <asm/mach/time.h>
#include <asm/mach/irq.h>
#include <asm/hardware/gic.h>
#include <asm/hardware/cache-l2x0.h>
#include <mach/cns3xxx.h>
#include <mach/pm.h>
#include "core.h"

static struct map_desc cns3xxx_io_desc[] __initdata = {
   
	{
		.virtual	= CNS3XXX_TC11MP_TWD_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TC11MP_TWD_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},

	{
		.virtual	= CNS3XXX_TC11MP_GIC_CPU_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TC11MP_GIC_CPU_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, 
		
	{
		.virtual	= CNS3XXX_TC11MP_GIC_DIST_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TC11MP_GIC_DIST_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, 
		
	{
		.virtual	= CNS3XXX_TIMER1_2_3_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_TIMER1_2_3_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_GPIOA_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_GPIOA_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_GPIOB_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_GPIOB_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_MISC_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_MISC_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
	
	
	{
		.virtual	= CNS3XXX_PM_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PM_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	},
	
	{
		.virtual	= CNS3XXX_UART0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_UART0_BASE),
		.length		= SZ_4K,
		.type		= MT_DEVICE,
	}, { 
		.virtual	= CNS3XXX_PCIE0_MEM_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_MEM_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE0_HOST_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_HOST_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE0_CFG0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_CFG0_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE0_CFG1_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_CFG1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE0_MSG_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_MSG_BASE),
		.length		= PAGE_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE0_IO_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE0_IO_BASE),
		.length		= PAGE_SIZE,
		.type		= MT_DEVICE,
   },
#if 1
      { 
		.virtual	= CNS3XXX_PCIE1_MEM_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_MEM_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_HOST_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_HOST_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_CFG0_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_CFG0_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_CFG1_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_CFG1_BASE),
		.length		= SZ_16M,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_MSG_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_MSG_BASE),
		.length		= PAGE_SIZE,
		.type		= MT_DEVICE,
	}, {
		.virtual	= CNS3XXX_PCIE1_IO_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_PCIE1_IO_BASE),
		.length		= PAGE_SIZE,
		.type		= MT_DEVICE,
	},
#endif
	   
  {
		.virtual	= CNS3XXX_SWITCH_BASE_VIRT,
		.pfn		= __phys_to_pfn(CNS3XXX_SWITCH_BASE),
		.length		= PAGE_SIZE,
		.type		= MT_DEVICE,
	},
		
};



void __init cns3xxx_map_io(void)
{        
	iotable_init(cns3xxx_io_desc, ARRAY_SIZE(cns3xxx_io_desc));	
}

/* used by entry-macro.S */
void __init cns3xxx_init_irq(void)
{   
	gic_init(0, 29, IOMEM(CNS3XXX_TC11MP_GIC_DIST_BASE_VIRT),
		 IOMEM(CNS3XXX_TC11MP_GIC_CPU_BASE_VIRT));	
}

void cns3xxx_power_off(void)
{
#if (0)   
	u32 __iomem *pm_base = IOMEM(CNS3XXX_PM_BASE_VIRT);
	u32 clkctrl;

	printk(KERN_INFO "powering system down...\n");

	clkctrl = readl(pm_base + PM_SYS_CLK_CTRL_OFFSET);
	clkctrl &= 0xfffff1ff;
	clkctrl |= (0x5 << 9);		/* Hibernate */
	writel(clkctrl, pm_base + PM_SYS_CLK_CTRL_OFFSET);
#endif
}

/*
 * Timer
 */
static void __iomem *cns3xxx_tmr1;

static void cns3xxx_timer_set_mode(enum clock_event_mode mode,
				   struct clock_event_device *clk)
{
	unsigned long ctrl = readl(cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);
	int pclk = cns3xxx_cpu_clock() / 8;
	int reload;

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		reload = pclk * 20 / (3 * HZ) * 0x25000;
		writel(reload, cns3xxx_tmr1 + TIMER1_AUTO_RELOAD_OFFSET);
		ctrl |= (1 << 0) | (1 << 2) | (1 << 9);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		/* period set, and timer enabled in 'next_event' hook */
		ctrl |= (1 << 2) | (1 << 9);
		break;
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_SHUTDOWN:
	default:
		ctrl = 0;
	}

	writel(ctrl, cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);
}

static int cns3xxx_timer_set_next_event(unsigned long evt,
					struct clock_event_device *unused)
{
	unsigned long ctrl = readl(cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);

	writel(evt, cns3xxx_tmr1 + TIMER1_AUTO_RELOAD_OFFSET);
	writel(ctrl | (1 << 0), cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);

	return 0;
}

static struct clock_event_device cns3xxx_tmr1_clockevent = {
	.name		= "cns3xxx timer1",
	.shift		= 8,
	.features       = CLOCK_EVT_FEAT_PERIODIC | CLOCK_EVT_FEAT_ONESHOT,
	.set_mode	= cns3xxx_timer_set_mode,
	.set_next_event	= cns3xxx_timer_set_next_event,
	.rating		= 350,
	.cpumask	= cpu_all_mask,
};

static void __init cns3xxx_clockevents_init(unsigned int timer_irq)
{
	cns3xxx_tmr1_clockevent.irq = timer_irq;
	cns3xxx_tmr1_clockevent.mult =
		div_sc((cns3xxx_cpu_clock() >> 3) * 1000000, NSEC_PER_SEC,
		       cns3xxx_tmr1_clockevent.shift);
	cns3xxx_tmr1_clockevent.max_delta_ns =
		clockevent_delta2ns(0xffffffff, &cns3xxx_tmr1_clockevent);
	cns3xxx_tmr1_clockevent.min_delta_ns =
		clockevent_delta2ns(0xf, &cns3xxx_tmr1_clockevent);

	clockevents_register_device(&cns3xxx_tmr1_clockevent);
}

/*
 * IRQ handler for the timer
 */
static irqreturn_t cns3xxx_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *evt = &cns3xxx_tmr1_clockevent;
	u32 __iomem *stat = cns3xxx_tmr1 + TIMER1_2_INTERRUPT_STATUS_OFFSET;
	u32 val;

	/* Clear the interrupt */
	val = readl(stat);
	writel(val & ~(1 << 2), stat);

	evt->event_handler(evt);

	return IRQ_HANDLED;
} 

static struct irqaction cns3xxx_timer_irq = {
	.name		= "timer",
	.flags		= IRQF_DISABLED | IRQF_TIMER | IRQF_IRQPOLL,
	.handler	= cns3xxx_timer_interrupt,
};

/*
 * Set up the clock source and clock events devices
 */
static void __init __cns3xxx_timer_init(unsigned int timer_irq)
{
	u32 val;
	u32 irq_mask;
	
	printk("__cns3xxx_timer_init()\n");
	
	/*
	 * Initialise to a known state (all timers off)
	 */

	/* disable timer1 and timer2 */
	writel(0, cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);
	/* stop free running timer3 */
	writel(0, cns3xxx_tmr1 + TIMER_FREERUN_CONTROL_OFFSET);

	/* timer1 */
	writel(0x5C800, cns3xxx_tmr1 + TIMER1_COUNTER_OFFSET);
	writel(0x5C800, cns3xxx_tmr1 + TIMER1_AUTO_RELOAD_OFFSET);

	writel(0, cns3xxx_tmr1 + TIMER1_MATCH_V1_OFFSET);
	writel(0, cns3xxx_tmr1 + TIMER1_MATCH_V2_OFFSET);

	/* mask irq, non-mask timer1 overflow */
	irq_mask = readl(cns3xxx_tmr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);
	irq_mask &= ~(1 << 2);
	irq_mask |= 0x03;
	writel(irq_mask, cns3xxx_tmr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);

	/* down counter */
	val = readl(cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);
	val |= (1 << 9);
	writel(val, cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);

	/* timer2 */
	writel(0, cns3xxx_tmr1 + TIMER2_MATCH_V1_OFFSET);
	writel(0, cns3xxx_tmr1 + TIMER2_MATCH_V2_OFFSET);

	/* mask irq */
	irq_mask = readl(cns3xxx_tmr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);
	irq_mask |= ((1 << 3) | (1 << 4) | (1 << 5));
	writel(irq_mask, cns3xxx_tmr1 + TIMER1_2_INTERRUPT_MASK_OFFSET);

	/* down counter */
	val = readl(cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);
	val |= (1 << 10);
	writel(val, cns3xxx_tmr1 + TIMER1_2_CONTROL_OFFSET);

		printk("__cns3xxx_timer_init() calling setup_irq()\n");

	
	/* Make irqs happen for the system timer */
	setup_irq(timer_irq, &cns3xxx_timer_irq);

	cns3xxx_clockevents_init(timer_irq);
	
printk("__cns3xxx_timer_init() done\n");

	
}

static void __init cns3xxx_timer_init(void)
{
   printk("cns3xxx_timer_init()\n");
   
   
	cns3xxx_tmr1 = IOMEM(CNS3XXX_TIMER1_2_3_BASE_VIRT);

	__cns3xxx_timer_init(IRQ_CNS3XXX_TIMER0);
	
   printk("cns3xxx_timer_init() done\n");

}

struct sys_timer cns3xxx_timer = {
	.init = cns3xxx_timer_init,
};

#ifdef CONFIG_CACHE_L2X0

void __init cns3xxx_l2x0_init(void)
{
	void __iomem *base = ioremap(CNS3XXX_L2C_BASE, SZ_4K);
	u32 val;

	if (WARN_ON(!base))
		return;

	/*
	 * Tag RAM Control register
	 *
	 * bit[10:8]	- 1 cycle of write accesses latency
	 * bit[6:4]	- 1 cycle of read accesses latency
	 * bit[3:0]	- 1 cycle of setup latency
	 *
	 * 1 cycle of latency for setup, read and write accesses
	 */
	val = readl(base + L2X0_TAG_LATENCY_CTRL);
	val &= 0xfffff888;
	writel(val, base + L2X0_TAG_LATENCY_CTRL);

	/*
	 * Data RAM Control register
	 *
	 * bit[10:8]	- 1 cycles of write accesses latency
	 * bit[6:4]	- 1 cycles of read accesses latency
	 * bit[3:0]	- 1 cycle of setup latency
	 *
	 * 1 cycle of latency for setup, read and write accesses
	 */
	val = readl(base + L2X0_DATA_LATENCY_CTRL);
	val &= 0xfffff888;
	writel(val, base + L2X0_DATA_LATENCY_CTRL);

	/* 32 KiB, 8-way, parity disable */
	l2x0_init(base, 0x00540000, 0xfe000fff);
}

#endif /* CONFIG_CACHE_L2X0 */


void get_interrupt_type_by_base(void __iomem *base, u32 id, u32 *type)
{
        unsigned char int_type_bit=0;
        u32 gic_v=0;
	//u16 offset=id/16*4;

        // judge gic offset
        int_type_bit=(id%16*2+1);
        
        //gic_v = readl(base + GIC_DIST_CONFIG + 4);
        gic_v = readl(base + GIC_DIST_CONFIG + id/16*4);

        *type = ((gic_v >> int_type_bit) & 0x1);

        //writel(0, base + GIC_DIST_CONFIG + id/16*4);
}

void get_interrupt_type(u32 id, u32 *type)
{
	get_interrupt_type_by_base((void __iomem *) CNS3XXX_TC11MP_GIC_DIST_BASE_VIRT, id, type);
}


// type: level or edge 
// 0 - level high active, 1 - rising edge sensitive
void set_interrupt_type_by_base(void __iomem *base, int id, u32 type)
{
        unsigned char int_type_bit=0;
        u32 gic_v=0;

        // judge gic offset
        //printk("gic addr: %#x\n", id/16*4 + 0xc00);
        //printk("gic addr bits: %#x\n", id%16*2);
        int_type_bit=(id%16*2+1);
        
        gic_v = readl(base + GIC_DIST_CONFIG + id/16*4);

        gic_v &= (~(1 << int_type_bit));
        gic_v |= ( type << int_type_bit);

        writel(gic_v, base + GIC_DIST_CONFIG + id/16*4);
}

// type: level or edge 
// 0 - level high active, 1 - rising edge sensitive
void set_interrupt_type(int id, u32 type)
{
	set_interrupt_type_by_base((void __iomem *) CNS3XXX_TC11MP_GIC_DIST_BASE_VIRT, id, type);
}


// set interrupt priority
void set_interrupt_pri_by_base(void __iomem *base, u32 id, u32 pri)
{
        unsigned char int_type_bit=0;
        u32 gic_v=0;


        // judge gic offset
        int_type_bit=(id%4*8+4);

        gic_v = readl(base + GIC_DIST_PRI + id/4*4);

        gic_v &= (~(0xf << int_type_bit));
        gic_v |= (pri << int_type_bit);

        writel(gic_v, base + GIC_DIST_PRI + id/4*4);

        gic_v = 0;
        gic_v = readl(base + GIC_DIST_PRI + id/4*4);
	//printk("read gic_v: %x\n", gic_v);
}

void set_interrupt_pri(u32 id, u32 pri)
{
	set_interrupt_pri_by_base((void __iomem *) CNS3XXX_TC11MP_GIC_DIST_BASE_VIRT, id, pri);
}

void get_interrupt_pri_by_base(void __iomem *base, int id, u32 *type)
{
        unsigned char int_type_bit=0;
        u32 gic_v=0;

        // judge gic offset
        int_type_bit=(id%4*8+4);
        
        gic_v = readl(base + GIC_DIST_PRI + id/4*4);

	//printk("int_type_bit: %d\n", int_type_bit);
	//printk("gic_v: %#x\n", gic_v);
        *type = ((gic_v >> int_type_bit) & 0xf);
        //gic_v &= (~(1 << int_type_bit));
        //gic_v |= ( type << int_type_bit);

        //writel(0, base + GIC_DIST_CONFIG + id/16*4);
}

void get_interrupt_pri(int id, u32 *pri)
{
	get_interrupt_pri_by_base((void __iomem *) CNS3XXX_TC11MP_GIC_DIST_BASE_VIRT, id, pri);
}

void cns3xxx_write_pri_mask(u8 pri_mask)
{
        writel(pri_mask, (void __iomem *) CNS3XXX_TC11MP_GIC_CPU_BASE_VIRT + GIC_CPU_PRIMASK);
}
