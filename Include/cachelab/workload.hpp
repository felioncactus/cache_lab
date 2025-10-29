#pragma once
#include "common.hpp"

namespace cachelab {

enum class Op : uint8_t { Get=0, Put=1 };

struct Access { Op op; Key k; Value v; };

struct Workload {
  std::vector<Access> ops;
  static Workload zipf_sequence(std::size_t n, std::size_t keyspace, double s, double write_ratio=0.05);
  static Workload from_csv(const std::string& path); // columns: op,key,value
};

} // namespace cachelab
