#pragma once
#include "common.hpp"

namespace cachelab {
struct ICache {
  virtual ~ICache() = default;
  virtual std::optional<Value> get(Key k) = 0;
  virtual void put(Key k, Value v) = 0;
  virtual std::size_t size() const = 0;
  virtual std::size_t capacity() const = 0;
};
} // namespace cachelab
