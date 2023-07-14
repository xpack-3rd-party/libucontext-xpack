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

## Maintainer info

This page is addressed to developers who plan to include this source
library into their own projects.

For maintainer info, please see the
[README-MAINTAINER-XPACK](README-MAINTAINER-XPACK.md) file.

## Install

As a source code library, this project can be integrated into another project
in the traditional way,
by either copying the relevant files into the target project, or by linking
the entire project as a Git submodule.

However, the workflow can be further automated and the most convenient way is
to **add it as a dependency** to the project via **xpm**.

### Install with xpm/npm

Along with the source files, this project also includes a
`package.json` file with the metadata that allows it to be identified as an
**xpm/npm** package so that it can be directly installed from GitHub.

#### Prerequisites

A recent [xpm](https://xpack.github.io/xpm/),
which is a portable [Node.js](https://nodejs.org/) command line application
that complements [npm](https://docs.npmjs.com)
with several extra features specific to
**C/C++ projects**.

It is recommended to install/update to the latest version with:

```sh
npm install --global xpm@latest
```

For details please follow the instructions in the
[xPack install](https://xpack.github.io/install/) page.

Warning: Be sure **xpm** is not installed with administrative rights.

#### xpm

This project can be installed as a package from GitHub with:

```sh
cd my-project
xpm init # Unless a package.json is already present

xpm install github:xpack-3rd-party/libucontext-xpack#v1.2.0-1 --save-dev --copy

ls -l xpacks/@xpack-3rd-party/libucontext
```

#### npm

The package can also be installed with [npm](https://docs.npmjs.com)
or related, but
the features specific to C/C++ projects will not be available;
therefore, at least for consistency reasons, it is recommended
to use **xpm**.

### Add as a Git submodule

Besides manually copying the relevant files to the target
project, which will later require extra maintenance efforts to keep the
project up to date, a more convenient
solution is to link the entire project as a **Git submodule**,
for example below an `xpacks` folder:

```sh
cd my-project
git init # Unless already a Git project
mkdir -p xpacks

git submodule add https://github.com/xpack-3rd-party/libucontext-xpack.git \
  xpacks/@xpack-3rd-party/libucontext
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
