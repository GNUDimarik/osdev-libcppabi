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

#include "libstdc/include/atomic.h"
#include <asm/cpu.h>

#include <stdint.h>

namespace __cxxabiv1
{

__BEGIN_DECLS

namespace
{
constexpr uint8_t __obj_initialized = 1;

constexpr uint8_t __obj_not_initialized = 0;

constexpr uint8_t __lock_free = 0;

constexpr uint8_t __lock_busy = 1;

constexpr int __cxa_guard_done = 0;

constexpr int __cxa_guard_creating = 1;

} // namespace

struct _Guard
{
    uint8_t _M_init;
    uint8_t _M_lock;
    uint8_t _M_unused[6];

    bool _M_try_lock()
    {
        __STD_NAMESPACE::atomic_ref<uint8_t> __in_use(_M_lock);
        uint8_t __expected = __lock_free;

        return __in_use.compare_exchange_strong(__expected,
                                                __lock_busy,
                                                __STD_NAMESPACE::memory_order_acquire,
                                                __STD_NAMESPACE::memory_order_relaxed);
    }

    bool _M_is_done()
    {
        __STD_NAMESPACE::atomic_ref<uint8_t> __init(_M_init);
        return __init.load(__STD_NAMESPACE::memory_order_acquire) == __obj_initialized;
    }

    void _M_release()
    {
        __STD_NAMESPACE::atomic_ref<uint8_t> __in_use(_M_lock);
        __in_use.store(__lock_free, __STD_NAMESPACE::memory_order_release);
    }

    void _M_set_initialized(uint8_t state)
    {
        __STD_NAMESPACE::atomic_ref<uint8_t> __init(_M_init);
        __init.store(state, __STD_NAMESPACE::memory_order_release);
    }
};

int __cxa_guard_acquire(_Guard *__g)
{
    for (;;) {
        if (__g->_M_is_done()) {
            return __cxa_guard_done;
        }

        if (__g->_M_try_lock()) {
            if (__g->_M_is_done()) {
                __g->_M_release();
                return __cxa_guard_done;
            }
            return __cxa_guard_creating;
        }

        cpu_relax();
    }
}

void __cxa_guard_release(_Guard *__g)
{
    __g->_M_set_initialized(__obj_initialized);
    __g->_M_release();
}

void __cxa_guard_abort(_Guard *__g)
{
    __g->_M_set_initialized(__obj_not_initialized);
    __g->_M_release();
}

__END_DECLS

} // namespace __cxxabiv1