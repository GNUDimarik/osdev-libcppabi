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

#include <abort.h>

namespace __cxxabiv1
{

__BEGIN_DECLS

extern "C" void __cxa_bad_cast()
{
    /// TODO: add debug output. I guess panic should be called here
    __STD_NAMESPACE::abort();
}

extern "C" void __cxa_bad_typeid()
{
    __STD_NAMESPACE::abort();
}

extern "C" void __cxa_pure_virtual()
{
    __STD_NAMESPACE::abort();
}

extern "C" void __cxa_deleted_virtual()
{
    __STD_NAMESPACE::abort();
}

extern "C" void __cxa_throw_bad_array_new_length()
{
    __STD_NAMESPACE::abort();
}

}

__END_DECLS