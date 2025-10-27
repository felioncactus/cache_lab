cachelab/
├─ CMakeLists.txt
├─ README.md
├─ include/
│  └─ cachelab/
│     ├─ common.hpp           # type aliases, helpers
│     ├─ icache.hpp           # abstract cache interface
│     ├─ metrics.hpp          # hit/miss meters + CSV writer
│     ├─ workload.hpp         # trace format + generators API
│     ├─ policies/
│     │  ├─ lru.hpp
│     │  ├─ lfu.hpp
│     │  └─ lecar.hpp
│     └─ factory.hpp          # make_cache(policy_name, params)
├─ src/
│  ├─ metrics.cpp
│  ├─ workload.cpp
│  ├─ factory.cpp
│  ├─ policies/
│  │  ├─ lru.cpp
│  │  ├─ lfu.cpp
│  │  └─ lecar.cpp
│  └─ util/
│     ├─ zipf.hpp            # header-only zipf sampler (optional)
│     └─ fast_rng.hpp        # small PRNG
├─ bench/
│  ├─ bench_main.cpp         # CLI benchmark runner
│  ├─ traces/
│  │  └─ sample_trace.csv    # optional: key,op (op: GET/PUT)
│  └─ configs/
│     └─ example.toml        # optional batch configs
├─ tests/
│  ├─ CMakeLists.txt
│  └─ cache_tests.cpp        # unit tests (Catch2 or GTest)
├─ data/
│  └─ README.md              # where to put external traces
├─ results/
│  └─ (created at runtime)   # *.csv results from bench
└─ python/
   └─ plot_results.py        # matplotlib plotter (reads results/*.csv)
