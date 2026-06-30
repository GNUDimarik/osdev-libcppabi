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

#ifndef ___CXXABI_H__
#define ___CXXABI_H__

#include <config.h>
#include <stddef.h>

namespace __cxxabiv1
{

using __cxa_cdtor_type = void (*)(void *);
using __cxa_cdtor_return_type = void;
using __cxa_vec_ctor_return_type = void;

__BEGIN_DECLS

void *__cxa_vec_new(
    size_t __element_count,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor);

void *__cxa_vec_new2(
    size_t __element_count,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor,
    void *(*__alloc)(size_t),
    void (*__dealloc)(void *));

void *__cxa_vec_new3(
    size_t __element_count,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor,
    void *(*__alloc)(size_t),
    void (*__dealloc)(void *, size_t));

__cxa_vec_ctor_return_type
__cxa_vec_ctor(
    void *__array_address,
    size_t __element_count,
    size_t __element_size,
    __cxa_cdtor_type __constructor,
    __cxa_cdtor_type __destructor);

__cxa_vec_ctor_return_type
__cxa_vec_cctor(
    void *__dest_array,
    void *__src_array,
    size_t __element_count,
    size_t __element_size,
    __cxa_cdtor_return_type (*__copy_constructor)(void *, void *),
    __cxa_cdtor_type __destructor);

void
__cxa_vec_dtor(
    void *__array_address,
    size_t __element_count,
    size_t __element_size,
    __cxa_cdtor_type __destructor);

void
__cxa_vec_delete(
    void *__array_address,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __destructor);

void
__cxa_vec_delete2(
    void *__array_address,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __destructor,
    void (*__dealloc)(void *));

void
__cxa_vec_delete3(
    void *__array_address,
    size_t __element_size,
    size_t __padding_size,
    __cxa_cdtor_type __destructor,
    void (*__dealloc)(void *, size_t));

__END_DECLS

} // __cxxabiv1

#endif //___CXXABI_H__
