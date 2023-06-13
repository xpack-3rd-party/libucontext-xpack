#ifndef ARCH_COMMON_COMMON_DEFS_H_
#define ARCH_COMMON_COMMON_DEFS_H_

#ifndef SETUP_FRAME
# define SETUP_FRAME(__proc)
#endif

#ifndef PUSH_FRAME
# define PUSH_FRAME(__proc)
#endif

#ifndef POP_FRAME
# define POP_FRAME(__proc)
#endif

#ifndef ENT
# define ENT(__proc)
#endif

#ifndef TYPE
# if defined (__APPLE__)
#  define TYPE(__proc) // .type not supported
# elif defined (__clang__)
#  define TYPE(__proc) // .type not supported
# else
#  define TYPE(__proc)	.type	__proc, @function;
#endif
#endif

#ifndef PROC_NAME
# ifdef __MACH__
#  define PROC_NAME(__proc) _ ## __proc
# else
#  define PROC_NAME(__proc) __proc
# endif
#endif

#define FUNC(__proc)				\
	.global PROC_NAME(__proc);		\
	.align  2;						\
	TYPE(__proc)					\
	ENT(__proc)						\
PROC_NAME(__proc):					\
	SETUP_FRAME(__proc)

#if defined(__APPLE__)
#define END(__proc) 				\
	.end;							\
	.size	__proc,.-__proc;
#elif defined(__clang__)
#define END(__proc)
#else
#define END(__proc)					\
	.end	__proc;					\
	.size	__proc,.-__proc;
#endif

#ifdef EXPORT_UNPREFIXED
#define ALIAS(__alias, __real)		\
	.weak	__alias;				\
	__alias = __real;
#else
#define ALIAS(...)
#endif

#define REG_OFFSET(__reg)       (MCONTEXT_GREGS + ((__reg) * REG_SZ))

#endif
