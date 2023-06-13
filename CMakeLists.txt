# -----------------------------------------------------------------------------
#
# This file is part of the µOS++ distribution.
#   (https://github.com/micro-os-plus/)
# Copyright (c) 2023 Liviu Ionescu. All rights reserved.
#
# Permission to use, copy, modify, and/or distribute this software
# for any purpose is hereby granted, under the terms of the MIT license.
#
# If a copy of the license was not distributed with this file, it can
# be obtained from https://opensource.org/licenses/MIT/.
#
# -----------------------------------------------------------------------------

# This file is intended to be consumed by applications with:
#
# `add_subdirectory("xpacks/@xpack-3rd-party/libucontext")`
#
# The result is an interface library that can be added to the linker with:
#
# `target_link_libraries(your-target PUBLIC xpack-3rd-party::libucontext)`

# -----------------------------------------------------------------------------
## Preamble ##

# https://cmake.org/cmake/help/v3.20/
cmake_minimum_required(VERSION 3.20)

project(xpack-3rd-party-libucontext
  DESCRIPTION "The ucontext.h C API"
)

if(COMMAND xpack_get_package_name_and_version)
  xpack_get_package_name_and_version("${CMAKE_CURRENT_SOURCE_DIR}/package.json")
  message(VERBOSE "Processing xPack ${PACKAGE_JSON_NAME}@${PACKAGE_JSON_VERSION}...")
endif()

# -----------------------------------------------------------------------------
## The project library definitions ##

add_library(xpack-3rd-party-libucontext-interface INTERFACE EXCLUDE_FROM_ALL)

# -----------------------------------------------------------------------------
# Target settings.

# x86_64, aarch64, arm
set(arch "${CMAKE_HOST_SYSTEM_PROCESSOR}")

target_include_directories(xpack-3rd-party-libucontext-interface INTERFACE
  "include"
  "arch/${arch}/include"
  "arch/common"
)

target_sources(xpack-3rd-party-libucontext-interface INTERFACE
  "arch/${arch}/getcontext.S"
  "arch/${arch}/makecontext.c"
  "arch/${arch}/setcontext.S"
  "arch/${arch}/swapcontext.S"
  "arch/${arch}/trampoline.c"
)

target_compile_definitions(xpack-3rd-party-libucontext-interface INTERFACE
  "_XOPEN_SOURCE=700L"
)

target_compile_options(xpack-3rd-party-libucontext-interface INTERFACE
  # None.
)

target_link_libraries(xpack-3rd-party-libucontext-interface INTERFACE
  # None.
)

if (COMMAND xpack_display_target_lists)
  xpack_display_target_lists(xpack-3rd-party-libucontext-interface)
endif()

# -----------------------------------------------------------------------------
# Aliases.

# https://cmake.org/cmake/help/v3.20/command/add_library.html#alias-libraries
add_library(xpack-3rd-party::libucontext ALIAS xpack-3rd-party-libucontext-interface)
message(VERBOSE "> xpack-3rd-party::libucontext -> xpack-3rd-party-libucontext-interface")

# -----------------------------------------------------------------------------
