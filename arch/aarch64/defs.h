#ifndef ARCH_AARCH64_DEFS_H_
#define ARCH_AARCH64_DEFS_H_

#define REG_SZ		(8)
#define MCONTEXT_GREGS	(184)

#define R0_OFFSET	REG_OFFSET(0)

#define SP_OFFSET	432
#define PC_OFFSET	440
#define PSTATE_OFFSET	448
#define FPSIMD_CONTEXT_OFFSET 464

#ifndef FPSIMD_MAGIC
# define FPSIMD_MAGIC	0x46508001
#endif

#ifndef ESR_MAGIC
# define ESR_MAGIC	0x45535201
#endif

#if defined(__GNUC__)
#define FETCH_LINKPTR(dest) \
	__asm__("mov	%0, x19" : "=r" ((dest)))
#else
#define FETCH_LINKPTR(dest) \
	asm("mov	%0, x19" : "=r" ((dest)))
#endif

#include "common-defs.h"

#endif
