/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2026 Dmitry Adzhiev <dmitry.adjiev@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stddef.h>
#include <config.h>
#include "libstdc/include/malloc.h"
#include "new.h"

void *operator new(size_t size)
{
    return __OSDEV_STD_SYMBOL(malloc)(size);
}

void *operator new[](size_t size)
{
    return __OSDEV_STD_SYMBOL(malloc)(size);
}

void operator delete(void *ptr) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}

void operator delete[](void *ptr) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}

void operator delete(void *ptr, size_t size [[maybe_unused]]) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}

void operator delete[](void *ptr, size_t size [[maybe_unused]]) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}

void *operator new(size_t size, __STD_NAMESPACE::align_val_t alignment)
{
    return __OSDEV_STD_SYMBOL(aligned_alloc)(static_cast<size_t>(alignment), size);
}

void *operator new[](size_t size, __STD_NAMESPACE::align_val_t alignment)
{
    return __OSDEV_STD_SYMBOL(aligned_alloc)(static_cast<size_t>(alignment), size);
}

void operator delete(void *ptr, __STD_NAMESPACE::align_val_t alignment [[maybe_unused]]) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}
void operator delete[](void *ptr, __STD_NAMESPACE::align_val_t alignment [[maybe_unused]]) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}

void operator delete(void *ptr, size_t size, __STD_NAMESPACE::align_val_t alignment [[maybe_unused]]) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}

void operator delete[](void *ptr, size_t size, __STD_NAMESPACE::align_val_t alignment [[maybe_unused]]) noexcept
{
    __OSDEV_STD_SYMBOL(free)(ptr);
}

void *operator new(size_t size, void *ptr) noexcept
{
    return ptr;
}

void *operator new[](size_t size, void *ptr) noexcept
{
    return ptr;
}

void operator delete(void *ptr, void *place) noexcept
{}

void operator delete[](void *ptr, void *place) noexcept
{}
