![License](https://img.shields.io/badge/license-MIT-green)
![Compiler](https://img.shields.io/badge/GCC-16.1+-blue)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![Platform](https://img.shields.io/badge/platform-freestanding-orange)

# osdev-libcppabi

`osdev-libcppabi` is a lightweight freestanding implementation of the low-level C++ ABI runtime required by modern C++ compilers. It is designed for operating systems, kernels, bootloaders, and other freestanding environments.

The library is intended to work together with **osdev-libstdc** and provides the compiler support routines that are not part of the C++ standard library itself.

## Features

- Thread-safe initialization of local static objects (`__cxa_guard_*`)
- C++ runtime helper routines
- Freestanding implementation suitable for kernel development
- Global `new` / `delete` operators
- Compatible with the Itanium C++ ABI

## Project Structure

### Imported from [libcxxrt](https://github.com/libcxxrt/libcxxrt)

The following files are adapted from the **libcxxrt** project:

- `guard.cc`
- `auxhelper.cc`
- `atomic.h`

Repository:

https://github.com/libcxxrt/libcxxrt

The original project provides a BSD-licensed implementation of the [Itanium C++ ABI](https://itanium-cxx-abi.github.io/cxx-abi/abi.html) runtime.

## Custom Implementation

The following components are implemented specifically for this project:

- All global `operator new` overloads
- All global `operator delete` overloads

These implementations are designed to work with **osdev-libstdc** memory allocation routines.

## Dependencies

`osdev-libcppabi` depends on:

- osdev-libstdc

The final kernel or executable should be linked in the following order:

```text
kernel objects
    ↓
osdev-libcppabi
    ↓
osdev-libstdc
    ↓
libgcc
```

```bash
git clone --recurse-submodules git@github.com:GNUDimarik/osdev-libcppabi.git
```

### HTTPS

```bash
git clone --recurse-submodules [https://github.com/GNUDimarik/osdev-libstdc.git](https://github.com/GNUDimarik/osdev-libcppabi.git)
```

## Freestanding build

GCC Only!!!

```bash
cmake -DARCH=x86 -DCMAKE_CXX_COMPILER=your_toolchain-g++ -DCMAKE_C_COMPILER=your_toolchain-gcc -DOSDEV_FREESTANDING=1 -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY ../

Example:

cmake -DARCH=x86 -DCMAKE_CXX_COMPILER=/mnt/d/osdev/i686-elf/bin/i686-elf-g++ -DCMAKE_C_COMPILER=/mnt/d/osdev/i686-elf/bin/i686-elf-gcc -DOSDEV_FREESTANDING=1 -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY ../

make -j $(nproc)
```

## Status

The project currently provides the minimal runtime required for freestanding C++ development and is intended for osdev
