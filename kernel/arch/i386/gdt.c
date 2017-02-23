#include <kernel/tss.h>
#include <kernel/gdt.h>
#include <kernel/type.h>
#include <string.h>

static void write_tss(int num, u16 ss0, u32 esp0);

static struct {
    struct gdt_entry entries[6];
    struct gdt_ptr pointer;
    struct tss_entry tss;
} gdt __attribute__((used));

#define ENTRY(X) (gdt.entries[(X)])

void gdt_set_gate(u8 num, u64 base, u64 limit, u8 access, u8 gran) {
	/* Base Address */
	ENTRY(num).base_low = (base & 0xFFFF);
	ENTRY(num).base_middle = (base >> 16) & 0xFF;
	ENTRY(num).base_high = (base >> 24) & 0xFF;

	/* Limits */
	ENTRY(num).limit_low = (limit & 0xFFFF);
	ENTRY(num).granularity = (limit >> 16) & 0X0F;

	/* Granularity */
	ENTRY(num).granularity |= (gran & 0xF0);

	/* Access flags */
	ENTRY(num).access = access;
}

void gdt_install(void) {
	struct gdt_ptr *gdtp = &gdt.pointer;

	gdtp->limit = sizeof gdt.entries - 1;
	gdtp->base = (u32)&ENTRY(0);

	gdt_set_gate(0, 0, 0, 0, 0);                /* NULL segment */
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* Code segment */
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* Data segment */
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /* User code */
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /* User data */

	write_tss(5, 0x10, 0x0);

	/* Go go go */
	gdt_flush((u32)gdtp);
	tss_flush();
}

static void write_tss(int num, u16 ss0, u32 esp0) {
	struct tss_entry *tss = &gdt.tss;
	u32 base = (u32)tss;
	u32 limit = base + sizeof(*tss);

	/* Add the TSS descriptor to the GDT */
	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	memset(tss, 0x0, sizeof(*tss));

	tss->ss0 = ss0;
	tss->esp0 = esp0;
	tss->cs = 0x0b;
	tss->ss = 0x13;
	tss->ds = 0x13;
	tss->es = 0x13;
	tss->fs = 0x13;
	tss->gs = 0x13;

	tss->iomap_base = sizeof(*tss);
}

void set_kernel_stack(u32 stack) {
	/* Set the kernel stack */
	gdt.tss.esp0 = stack;
}


