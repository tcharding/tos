#include <stack_chk.h>
#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>

void kernel_main(void)
{
	gdt_install();

	terminal_initialize();
	printf("Hello, kernel World!\n");
}
