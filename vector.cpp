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

#include "cxxabi.h"
#include <malloc.h>

namespace __cxxabiv1
{
void *__cxa_vec_new(
    size_t __element_count,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor)
{
    // No exceptions anyway
    return __cxa_vec_new2(__element_count,
                          __element_size,
                          __padding_size,
                          __constructor,
                          __destructor,
                          &::operator new[],
                          &::operator delete[]);
}

void *__cxa_vec_new2(
    size_t __element_count,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor,
    void *(*__alloc)(size_t),
    void (*__dealloc)(void *))
{
    char *__base = nullptr;

    if (__alloc) {
        size_t __sz = __element_count * __element_size + __padding_size;
        __base = static_cast<char *>(__alloc(__sz));

        if (__padding_size > 0) {
            __base += __padding_size;
            reinterpret_cast<size_t *>(__base)[-1] = __element_count;
        }

        __cxa_vec_ctor(__base, __element_count, __element_size,
                       __constructor, __destructor);
    }
    return __base;
}

void *__cxa_vec_new3(
    size_t __element_count,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor,
    void *(*__alloc)(size_t),
    void (*__dealloc)(void *, size_t))
{
    // No exceptions anyway
    return __cxa_vec_new2(__element_count,
                          __element_size,
                          __padding_size,
                          __constructor,
                          __destructor,
                          __alloc,
                          nullptr);
}

__cxa_vec_ctor_return_type
__cxa_vec_ctor(
    void *__array_address,
    size_t __element_count,
    size_t __element_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor [[maybe_unused]])
{
    if (__constructor) {
        auto __c = static_cast<char *> (__array_address);

        for (size_t __i = 0; __i < __element_count; ++__i) {
            __constructor(__c);
            __c += __element_size;
        }
    }
}

__cxa_vec_ctor_return_type
__cxa_vec_cctor(
    void *__dest_array,
    void *__src_array,
    size_t __element_count,
    size_t __element_size,
    __cxa_cdtor_return_type (*__copy_constructor)(void *, void *),
    __cxa_cdtor_type __destructor [[maybe_unused]])
{
    if (__copy_constructor && __src_array && __dest_array) {
        auto __s = static_cast<char *> (__src_array);
        auto __d = static_cast<char *> (__dest_array);

        for (size_t __i = 0; __i < __element_count; ++__i) {
            __copy_constructor(__d, __s);
            __s += __element_size;
            __d += __element_size;
        }
    }
}

void
__cxa_vec_dtor(
    void *__array_address,
    size_t __element_count,
    size_t __element_size,
    __cxa_cdtor_type __destructor)
{
    if (__destructor) {
        auto __c = static_cast<char *> (__array_address) + __element_count * __element_size;

        for (size_t __i = __element_count; __i > 0; --__i) {
            __c -= __element_size;
            __destructor(__c);
        }
    }
}

void
__cxa_vec_delete(
    void *__array_address,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __destructor)
{
    __cxa_vec_delete2(__array_address, __element_size, __padding_size,
                      __destructor, &::operator delete[]);
}

void
__cxa_vec_delete2(
    void *__array_address,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __destructor,
    void (*__dealloc)(void *))
{
    if (__array_address && __dealloc) {
        char *__base = static_cast<char *>(__array_address);

        if (__padding_size > 0) {
            size_t __element_count = reinterpret_cast<size_t *>(__base)[-1];
            __base -= __padding_size;
            __cxa_vec_dtor(__array_address, __element_count, __element_size, __destructor);
        }

        __dealloc(__base);
    }
}

void
__cxa_vec_delete3(
    void *__array_address,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __destructor,
    void (*__dealloc)(void *, size_t))
{
    if (__array_address && __dealloc) {
        char *__base = static_cast<char *>(__array_address);
        size_t __element_count = 0;

        if (__padding_size > 0) {
            __element_count = reinterpret_cast<size_t *>(__base)[-1];
            __base -= __padding_size;
            __cxa_vec_dtor(__array_address, __element_count, __element_size, __destructor);
        }

        size_t __sz = __element_count * __element_size + __padding_size;
        __dealloc(__base, __sz);
    }
}
} // __cxxabiv1
