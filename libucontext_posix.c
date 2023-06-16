/*
 * Copyright (c) 2020 Ariadne Conill <ariadne@dereferenced.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#include <stddef.h>
#include <stdio.h>
#include <signal.h>
#include <libucontext/libucontext.h>

#ifdef FREESTANDING
# error libucontext_posix cannot be built in FREESTANDING mode.
#endif

#ifdef DEBUG_
# define TRACE_(...)	fprintf(stderr, "TRACE: " __VA_ARGS__)
#else
# define TRACE_(...)
#endif

int
libucontext_posix_getcontext(libucontext_ucontext_t *ucp)
{
	TRACE_("getcontext(%p)\n", ucp);

	if (sigprocmask(SIG_SETMASK, NULL, &ucp->uc_sigmask_posix))
		return -1;

	return libucontext_getcontext(ucp);
}

int
libucontext_posix_setcontext(const libucontext_ucontext_t *ucp)
{
	TRACE_("setcontext(%p)\n", ucp);

	if (sigprocmask(SIG_SETMASK, &ucp->uc_sigmask_posix, NULL))
		return -1;

	return libucontext_setcontext(ucp);
}

int
libucontext_posix_swapcontext(libucontext_ucontext_t *oucp, const libucontext_ucontext_t *ucp)
{
	TRACE_("swapcontext(%p, %p)\n", oucp, ucp);

	if (sigprocmask(SIG_SETMASK, &ucp->uc_sigmask_posix, &oucp->uc_sigmask_posix))
		return -1;

	return libucontext_swapcontext(oucp, ucp);
}
