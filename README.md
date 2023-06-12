[![GitHub package.json version](https://img.shields.io/github/package-json/v/xpack-3rd-party/libucontext-xpack)](https://github.com/xpack-3rd-party/libucontext-xpack/blob/xpack/package.json)
[![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/xpack-3rd-party/libucontext-xpack)](https://github.com/xpack-3rd-party/libucontext-xpack/tags/)
[![npm (scoped)](https://img.shields.io/npm/v/@xpack-3rd-party/libucontext.svg?color=blue)](https://www.npmjs.com/package/@xpack-3rd-party/libucontext/)
[![license](https://img.shields.io/github/license/xpack-3rd-party/libucontext-xpack)](https://github.com/xpack-3rd-party/libucontext-xpack/blob/xpack/LICENSE)

# An xpm/npm package which provides the `ucontext.h` C API

This project provides a convenient way to integrate the
[libucontext](https://github.com/kaniini/libucontext) library
into the xpm/npm ecosystem, by allowing to install it as a package dependency.

The open-source project is hosted on GitHub as
[xpack-3rd-party/libucontext-xpack](https://github.com/xpack-3rd-party/libucontext-xpack).

## Install

This project is available from the `npmjs.com` registry as the package
[`@xpack-3rd-party/libucontext`](https://www.npmjs.com/package/@xpack-3rd-party/libucontext),
and the easiest way to add it to a project is via
**xpm** or **npm**; it can also be used as any Git project, but for
this better use the upstream project.

### Prerequisites

A recent [xpm](https://xpack.github.io/xpm/),
which is a portable [Node.js](https://nodejs.org/) command line application.

It is recommended to update to the latest version with:

```sh
npm install --global xpm@latest
```

For details please follow the instructions in the
[xPack install](https://xpack.github.io/install/) page.

### xpm

To install this project as a dependency in xPack projects,
use **xpm**:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install @xpack-3rd-party/libucontext@latest

ls -l xpacks/@xpack-3rd-party/libucontext
```

### npm

To install the project as a dependency in **npm** projects:

```sh
cd my-project
npm init # Unless a package.json is already present

npm install @xpack-3rd-party/libucontext@latest --save-dev

ls -l node_module/@xpack-3rd-party/libucontext
```

## Branches

In addition to the original `main` branch, there are two
xPack specific branches:

- `xpack`, with the latest stable version (default)
- `xpack-develop`, with the current development version

All development is done in the `xpack-develop` branch, and contributions via
Pull Requests should be directed to this branch.

When new releases are published, the `xpack-develop` branch is merged
into `xpack`.

When there are new upstream releases:

- upstream `master` is merged into the local `master`
- the local `master` is merged into `xpack-develop`
- the project is tested
- `xpack-develop` is merged into `xpack`

The original README follows.

---

# `libucontext`

`libucontext` is a library which provides the `ucontext.h` C API.  Unlike other implementations,
it faithfully follows the kernel process ABI when doing context swaps.

Notably, when combined with `gcompat`, it provides a fully compatible implementation of the ucontext
functions that are ABI compatible with glibc.

Since version 0.13, for some architectures, you can deploy to bare metal using newlib via the
`FREESTANDING=yes` make option.  Systems which use a syscall cannot work this way.  The table
below shows which architecture ports have been adapted to build with `FREESTANDING=yes`.

Adding support for new architectures is easy, but you need to know assembly language for the
target to do it.


## supported features

| Architecture | Works on musl | Syscall | Supports FREESTANDING | Common trampoline |
|--------------|---------------|---------|-----------------------|-------------------|
|    aarch64   | ✓             |         | ✓                     | ✓                 |
|      arm     | ✓             |         | ✓                     | ✓                 |
| loongarch64  | ✓             |         | ✓                     |                   |
|     m68k     | ✓             |         | ✓                     | ✓                 |
|     mips     | ✓             |         | ✓                     |                   |
|    mips64    | ✓             |         | ✓                     |                   |
|     or1k     | ✓             |         | ✓                     | ✓                 |
|      ppc     | ✓             | ✓       |                       |                   |
|     ppc64    | ✓             | ✓       |                       |                   |
|    riscv32   | ✓             |         | ✓                     | ✓                 |
|    riscv64   | ✓             |         | ✓                     | ✓                 |
|     s390x    | ✓             |         | ✓                     |                   |
|      sh      | ✓             |         | ✓                     | ✓                 |
|      x86     | ✓             |         | ✓                     | ✓                 |
|    x86_64    | ✓             |         | ✓                     | ✓                 |


## building

`libucontext` uses a simple makefile build system.  You should define `ARCH=` at build time, otherwise
the build system will attempt to guess using `uname -m`.

```
$ make ARCH=x86_64
$ make ARCH=x86_64 check
$ make ARCH=x86_64 DESTDIR=out install
```

There are a few options:

* `ARCH`: The architecture libucontext is being built for.  Must be set to one of the architectures
  listed in the feature support table.  If unset, the build system will attempt to guess based on what
  architecture the host is running.  Setting this option explicitly is highly recommended.

* `FREESTANDING`: If this is set to `yes`, the system ucontext.h headers will not be used.  Instead,
  the headers in `arch/${ARCH}/freestanding` will be used for definitions where appropriate.
  Default is `no`.

* `EXPORT_UNPREFIXED`: If this is set to `yes`, the POSIX 2004 names `getcontext`, `setcontext`,
  `swapcontext` and `makecontext` will be provided as weak symbols aliased against their `libucontext_`
  namespaced equivalents.  This is necessary for libucontext to provide these functions on musl
  systems, but you may wish to disable this when using `FREESTANDING` mode to avoid conflicts with
  the target's libc.  Default is `yes`.

* `DESTDIR`: If this variable is set, the installed files will be installed to the specified path instead
  of the system root.

If you have `scdoc` installed, you can build manpages and install them:

```
$ make docs
$ make DESTDIR=out install_docs
```


## real-world use cases

`libucontext` is used on almost all musl distributions to provide the legacy `ucontext.h` API.
Additionally, it is used by:

* [UTM](https://getutm.app) -- friendly qemu distribution for macOS and iOS devices.  UTM uses libucontext
  as qemu's coroutine backend.

* [Lwan](https://lwan.ws) -- a high-performance embeddable asynchronous web server.  Lwan uses libucontext
  to provide green threads when building on non-x86 architectures.


## caveats

`libucontext`, while largely functionally equivalent does have some differences over traditional POSIX
ucontext functions:

* Saving and restoring the signal mask is not implemented by default in order to avoid kernel syscall
  overhead.  Use `-lucontext_posix` if you actually need this functionality, which provides a POSIX
  compliant implementation at the cost of performance.

* Only basic GPR registers are saved and restored when context swapping.  The glibc implementation uses
  hardware capability detection to save/restore other register groups, such as the FPU registers or
  vector processing (AltiVec/AVX/NEON) registers.  Adding this capability detection would significantly
  increase the complexity of the project and thus is not implemented.  Support for compiling in code to
  save/restore FPU registers or vector registers may be added in a later release as a build-time
  setting -- for now, we assume a soft-float ABI with no optional processor features.  In practice, this
  does not really matter, code using these functions are unlikely to be impacted by this design
  assumption. This is a work in progress, as newer compilers will spill even non-floating-point state
  through floating point registers when allowed to do so.
