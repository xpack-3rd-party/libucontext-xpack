#include <stddef.h>
#include <signal.h>

#ifndef LIBUCONTEXT_BITS_H
#define LIBUCONTEXT_BITS_H

// Linux defines an enum with these values.
#if !defined(__USE_GNU)
#define REG_R8		(0)
#define REG_R9 		(1)
#define REG_R10 	(2)
#define REG_R11		(3)
#define REG_R12		(4)
#define REG_R13		(5)
#define REG_R14		(6)
#define REG_R15		(7)
#define REG_RDI		(8)
#define REG_RSI		(9)
#define REG_RBP		(10)
#define REG_RBX		(11)
#define REG_RDX		(12)
#define REG_RAX		(13)
#define REG_RCX		(14)
#define REG_RSP		(15)
#define REG_RIP		(16)
#define REG_EFL		(17)
#define REG_CSGSFS	(18)
#define REG_ERR		(19)
#define REG_TRAPNO	(20)
#define REG_OLDMASK	(21)
#define REG_CR2		(22)
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#elif defined(__GNUC__)
#if defined(__cplusplus)
#pragma GCC diagnostic ignored "-Wredundant-tags"
#endif
#endif

typedef long long libucontext_greg_t, libucontext_gregset_t[23];

typedef struct libucontext_fpstate {
	unsigned short cwd, swd, ftw, fop;
	unsigned long long rip, rdp;
	unsigned mxcsr, mxcr_mask;
	struct {
		unsigned short significand[4], exponent, padding[3];
	} _st[8];
	struct {
		unsigned element[4];
	} _xmm[16];
	unsigned padding[24];
} *libucontext_fpregset_t;

typedef struct {
	libucontext_gregset_t gregs;
	libucontext_fpregset_t fpregs;
	unsigned long long __reserved1[8];
} libucontext_mcontext_t;

typedef struct {
	void *ss_sp;
	int ss_flags;
	size_t ss_size;
} libucontext_stack_t;

typedef struct libucontext_ucontext {
	unsigned long uc_flags;
	struct libucontext_ucontext *uc_link;
	libucontext_stack_t uc_stack;
	libucontext_mcontext_t uc_mcontext;
	sigset_t uc_sigmask_posix;
} libucontext_ucontext_t;

#pragma GCC diagnostic pop

#endif
