#include "cachelab/factory.hpp"
#include "cachelab/workload.hpp"
#include "cachelab/metrics.hpp"

#include <chrono>
#include <iostream>

using namespace cachelab;

int main(int argc, char** argv) {
    // naive arg parse: --policy lru|lfu|lecar --capacity 10000
    //                  (--trace path.csv) OR synthetic: --zipf n_ops keyspace s
    std::string policy = "lru";
    size_t capacity = 10000;
    std::string out = "results/results.csv";
    Workload wl; wl.name = "unset";

    // (Very light parsing for brevity)
    for (int i = 1;i < argc;i++) {
        std::string a = argv[i];
        auto next = [&](int& i) { return std::string(argv[++i]); };
        if (a == "--policy") policy = next(i);
        else if (a == "--capacity") capacity = std::stoull(next(i));
        else if (a == "--trace") { wl = load_trace_csv(next(i)); }
        else if (a == "--zipf") {
            uint64_t n = std::stoull(next(i));
            uint64_t ks = std::stoull(next(i));
            double s = std::stod(next(i));
            wl = gen_zipf(n, ks, s, "zipf");
        }
        else if (a == "--scan") {
            uint64_t n = std::stoull(next(i));
            uint64_t ks = std::stoull(next(i));
            uint64_t reps = std::stoull(next(i));
            wl = gen_sequential_scan(n, ks, reps, "scan");
        }
        else if (a == "--out") out = next(i);
    }

    if (wl.events.empty()) {
        std::cerr << "No workload specified. Use --trace or --zipf/--scan.\n";
        return 1;
    }

    auto cache = make_cache(policy, capacity);
    Metrics m{};
    write_csv_header_if_new(out);

    auto t0 = std::chrono::steady_clock::now();
    for (auto& e : wl.events) {
        if (e.op == Op::GET) {
            m.gets++; m.ops++;
            auto v = cache->get(e.key);
            if (v) m.hits++; else m.misses++;
        }
        else {
            m.puts++; m.ops++;
            cache->put(e.key, e.key); // store key as value for simplicity
        }
    }
    auto t1 = std::chrono::steady_clock::now();
    m.elapsed_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    append_csv_row(out, policy, capacity, wl.name, m);
    std::cout << "Policy=" << policy
        << " cap=" << capacity
        << " hr=" << m.hit_rate() * 100.0 << "% "
        << "ops=" << m.ops
        << " time=" << m.elapsed_ms << "ms\n";
    return 0;
}
