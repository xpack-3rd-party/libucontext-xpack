#ifndef LIBUCONTEXT_LIBUCONTEXT_H
#define LIBUCONTEXT_LIBUCONTEXT_H

#include <stddef.h>
#include <libucontext/bits.h>

#ifdef __cplusplus
extern "C" {
#endif

int  libucontext_getcontext(libucontext_ucontext_t *);

#if defined(__GNUC__)
#pragma GCC diagnostic push

#if defined(__clang__)
#pragma clang diagnostic ignored "-Wstrict-prototypes"
#elif defined(__GNUC__)
#if !defined(__cplusplus)
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#endif
#endif
#endif // defined(__GNUC__)

void libucontext_makecontext(libucontext_ucontext_t *, void (*)(), int, ...);

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__)

int  libucontext_setcontext(const libucontext_ucontext_t *);
int  libucontext_swapcontext(libucontext_ucontext_t *, const libucontext_ucontext_t *);

int  libucontext_posix_getcontext(libucontext_ucontext_t *);
int  libucontext_posix_setcontext(const libucontext_ucontext_t *);
int  libucontext_posix_swapcontext(libucontext_ucontext_t *, const libucontext_ucontext_t *);

#ifdef __cplusplus
}
#endif

#endif
