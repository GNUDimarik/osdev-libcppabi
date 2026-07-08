#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <array>
#include <atomic>

#include "test.h"

static pthread_barrier_t g_barrier;
static std::atomic<int> g_constructor_calls{0};

struct Singleton {
    int a = 0;

    explicit Singleton(int val)
        : a(val) {
        int count = g_constructor_calls.fetch_add(1, std::memory_order_acq_rel) + 1;

        printf("%s constructor call #%d thread [%lu]\n",
               __PRETTY_FUNCTION__,
               count,
               pthread_self());

        /*
         * Искусственно держим конструктор.
         * Пока первый поток строит объект, второй поток должен успеть
         * зайти в guard acquire для того же static Singleton x.
         */
        usleep(500000);

        a++;
    }

    ~Singleton() {
        printf("%s\n", __PRETTY_FUNCTION__);
    }

    static Singleton *instance() {
        printf("before static thread [%lu]\n", pthread_self());

        static Singleton x(13);

        printf("after static, x.a = %d thread [%lu]\n", x.a, pthread_self());

        return &x;
    }
};

void *make_singleton(void *) {
    pthread_barrier_wait(&g_barrier);

    auto a = Singleton::instance();

    printf("%s a = %d thread [%lu]\n",
           __PRETTY_FUNCTION__,
           a->a,
           pthread_self());

    return nullptr;
}

void habr_test() {
    constexpr size_t kThreadNumber = 2;
    std::array<pthread_t, kThreadNumber> threads;

    g_constructor_calls.store(0, std::memory_order_release);

    pthread_barrier_init(&g_barrier, nullptr, kThreadNumber);

    for (size_t i = 0; i < kThreadNumber; ++i) {
        pthread_create(&threads[i], nullptr, make_singleton, nullptr);
        printf("pthread_create threads[%zu] = [%lu]\n", i, threads[i]);
    }

    for (size_t i = 0; i < kThreadNumber; ++i) {
        pthread_join(threads[i], nullptr);
    }

    pthread_barrier_destroy(&g_barrier);
    TEST(g_constructor_calls.load(std::memory_order_acquire) == 1, "constructor calls more than 1");
}
