#pragma once
#include <cstdint>
#include <string>

namespace cachelab {

    struct Metrics {
        uint64_t ops = 0, gets = 0, puts = 0, hits = 0, misses = 0;
        double   elapsed_ms = 0.0;

        double hit_rate()  const { return gets ? double(hits) / gets : 0.0; }
        double miss_rate() const { return 1.0 - hit_rate(); }
    };

    void write_csv_header_if_new(const std::string& path);
    void append_csv_row(const std::string& path,
        const std::string& policy,
        size_t capacity,
        const std::string& workload_name,
        const Metrics& m);

} // namespace cachelab
