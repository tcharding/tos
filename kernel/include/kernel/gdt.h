#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <kernel/type.h>

/*
 * Defines a GDT entry. We say packed, because it prevents the
 * compiler from doing things that it thinks is best: Prevent
 * compiler "optimization" by packing
 */
struct gdt_entry
{
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
} __attribute__((packed));

/*
 * Special pointer which includes the limit: The max bytes
 * taken up by the GDT, minus 1. Again, this NEEDS to be packed.
 */
struct gdt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

/* gdt_flush.S. */
extern void gdt_flush(u32 gdtp);

/* gdt.c */
void gdt_install(void);

#endif	/* _KERNEL_GDT_H */
