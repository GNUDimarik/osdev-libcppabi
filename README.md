# osdev-libcppabi

![License](https://img.shields.io/badge/license-MIT-green)
![Compiler](https://img.shields.io/badge/GCC-16.1+-blue)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![Platform](https://img.shields.io/badge/platform-freestanding-orange)

![ABI](https://raw.githubusercontent.com/GNUDimarik/osdev-libcppabi/main/docs/images/abi.png)

`osdev-libcppabi` is a lightweight freestanding implementation of the low-level C++ ABI runtime required by modern C++ compilers.

The library is designed for operating systems, kernels, bootloaders, and other freestanding environments and is intended to work together with **osdev-libstdc**.

---

# Features

* Thread-safe initialization of local static objects (`__cxa_guard_acquire`, `__cxa_guard_release`, `__cxa_guard_abort`)
* Global `operator new` / `operator delete`
* C++ runtime helper routines
* Compatible with the Itanium C++ ABI
* Freestanding implementation suitable for kernel development
* Zero external dependencies

---

# Implemented Components

## Guard Variables

The library implements the Itanium C++ ABI guard routines required for thread-safe initialization of local static objects.

Implemented functions:

* `__cxa_guard_acquire`
* `__cxa_guard_release`
* `__cxa_guard_abort`

---

## Global Memory Operators

The following global allocation operators are provided:

* `operator new`
* `operator new[]`
* `operator delete`
* `operator delete[]`

Including sized, aligned, and placement overloads required for freestanding C++20 development.

These operators are implemented on top of the memory allocation routines provided by **osdev-libstdc**.

---

## Runtime Helper Functions

The library also provides a minimal set of C++ runtime helper functions required by GCC in freestanding environments.

---

# Dependencies

`osdev-libcppabi` depends on:

* `osdev-libstdc`

Typical link order:

```text
Kernel Objects
      ↓
osdev-libcppabi
      ↓
osdev-libstdc
```

---

# Building

## Clone Repository

### SSH

```bash
git clone --recurse-submodules git@github.com:GNUDimarik/osdev-libcppabi.git
```

### HTTPS

```bash
git clone --recurse-submodules https://github.com/GNUDimarik/osdev-libcppabi.git
```

## Freestanding Build

GCC only.

```bash
cmake \
    -DARCH=x86 \
    -DCMAKE_CXX_COMPILER=your_toolchain-g++ \
    -DCMAKE_C_COMPILER=your_toolchain-gcc \
    -DOSDEV_FREESTANDING=1 \
    -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
    ../

make -j $(nproc)
```

Example:

```bash
cmake \
    -DARCH=x86 \
    -DCMAKE_CXX_COMPILER=/mnt/d/osdev/i686-elf/bin/i686-elf-g++ \
    -DCMAKE_C_COMPILER=/mnt/d/osdev/i686-elf/bin/i686-elf-gcc \
    -DOSDEV_FREESTANDING=1 \
    -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
    ../

make -j $(nproc)
```

---

# Testing

The project includes unit tests for the guard variable implementation to verify thread-safe initialization semantics.

---

# Status

`osdev-libcppabi` currently provides the minimal subset of the Itanium C++ ABI required for freestanding C++ development.

Additional ABI components will be implemented as the DUX operating system evolves.

---

# License

MIT License

Copyright (c) 2026 Dmitry Adzhiev
