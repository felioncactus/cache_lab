#pragma once
#include "common.hpp"

namespace cachelab {
struct Metrics {
  std::size_t gets = 0;
  std::size_t puts = 0;
  std::size_t hits = 0;
  std::size_t misses = 0;

  double hit_rate() const { return gets ? double(hits)/double(gets) : 0.0; }
  double miss_rate() const { return gets ? double(misses)/double(gets) : 0.0; }
};

inline void write_csv(const std::string& path, const std::vector<std::pair<std::size_t, Metrics>>& rows) {
  std::ofstream out(path);
  out << "capacity,gets,puts,hits,misses,hit_rate,miss_rate\n";
  for (auto& [cap, m] : rows) {
    out << cap << "," << m.gets << "," << m.puts << "," << m.hits << "," << m.misses << ","
        << m.hit_rate() << "," << m.miss_rate() << "\n";
  }
}
} // namespace cachelab
