#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <atomic>

#include "test.h"

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

void *make_singleton(void *)
{
    const auto a = Singleton::instance();
    printf("%s a = %d\n", __PRETTY_FUNCTION__, a->a);
    return nullptr;
}

void habr_test() {
    pthread_t t1;
    pthread_create(&t1, nullptr, make_singleton, nullptr);
    printf("pthread_create t1 = [%lu]\n", t1);
    pthread_t t2;
    pthread_create(&t2, nullptr, make_singleton, nullptr);
    printf("pthread_create t2 = [%lu]\n", t2);
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    make_singleton(nullptr);
    TEST(g_constructor_calls.load() == 1, "Constructor called more than once");
}
