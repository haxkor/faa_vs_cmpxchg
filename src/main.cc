
#include <cstdint>
#include <memory>
#include <mutex>

#include "spinlock_benchmark.h"
#include "refcount_benchmark.h"
#include "faa_refcount.h"
#include "faa_spinlock.h"
#include "cmpxchg_refcount.h"
#include "cmpxchg_spinlock.h"


benchmarks_table_t benchmarks {
    {"spinlock", {
        {"fetch_or", &get_spinlock_benchmark<for_spinlock>, 0},
        {"fetch_add", &get_spinlock_benchmark<faa_spinlock>, 7},
        {"cmpxchg_strong", &get_spinlock_benchmark<cmpxchg_strong_spinlock>, 0},
        {"cmpxchg_strong_pause", &get_spinlock_benchmark<cmpxchg_strong_pause_spinlock>, 0},
        {"cmpxchg_weak", &get_spinlock_benchmark<cmpxchg_weak_spinlock>, 0},
        {"cmpxchg_weak_pause", &get_spinlock_benchmark<cmpxchg_weak_pause_spinlock>, 0},
        {"std::mutex", &get_spinlock_benchmark<std::mutex>, 0},
    }},
    {"refcount", {
        {"fetch_sub", &get_shared_ptr_benchmark<faa_shared_ptr>, 0},
        {"cmpxchg_strong", &get_shared_ptr_benchmark<cmpxchg_strong_shared_ptr>, 0},
        {"cmpxchg_weak", &get_shared_ptr_benchmark<cmpxchg_weak_shared_ptr>, 0},
        {"std::shared_ptr", &get_shared_ptr_benchmark<std::shared_ptr>, 0},
    }},
};


int main(int argc, const char* argv[])
{
    int64_t counter = 1024000;
    if (argc == 2) {
        counter = strtol(argv[1], 0, 0);
    }

    run_benchmarks(benchmarks, counter);

    printf("second iteration\n");
    run_benchmarks(benchmarks, counter);

    return 0;
}
























