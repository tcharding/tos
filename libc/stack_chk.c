#include <stdint.h>
#include <stdlib.h>

#include <stack_chk.h>

/*
 * Note how the secret guard value is hard-coded rather than being decided
 * during program load. You should have the program loader (the bootloader
 * in the case of the kernel) randomize the values. You can do this by putting
 * the guard value in a special segment that the loader knows to randomize. You
 * can still take advantage of the bug-discovering properties of SSP even if
 * the guard value is not cryptographically secure (unless you anticipate
 * sufficiently obscure bugs that intelligently circumvent SSP).
 */

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn)) void __stack_chk_fail(void)
{
#if __STDC_HOSTED__
	abort();
#elif __is_kernel
	panic("Stack smashing detected");
#endif
	while(1)	  /* no return */
		;
}
