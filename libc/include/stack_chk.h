#ifndef _STACK_CHK
#define _STACK_CHK

/* Reference: http://wiki.osdev.org/Stack_Smashing_Protector */

/*
 * The Stack Smashing Protector (SSP) compiler feature helps detect
 * stack buffer overrun by aborting if a secret value on the stack is
 * changed. This serves a dual purpose in making the occurrence of such
 * bugs visible and as exploit mitigation against return-oriented
 * programming. SSP merely detects stack buffer overruns, they are not
 * prevented. The detection can be beaten by preparing the input such
 * that the stack canary is overwritten with the correct value and thus
 * does not offer perfect protection. The stack canary is native word
 * sized and if chosen randomly, an attacker will have to guess the right
 * value among 2^32 or 2^64 combinations (and revealing the bug if the
 * guess is wrong), or resort to clever means of determining it.
 */

void __stack_chk_fail(void) __attribute__((noreturn));

#endif	/* _STACK_CHK */
