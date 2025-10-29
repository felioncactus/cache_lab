#pragma once
#include "cachelab/icache.hpp"

namespace cachelab {

class LRUCache : public ICache {
  std::size_t cap_;
  std::list<std::pair<Key,Value>> lst_; // front = MRU
  std::unordered_map<Key, std::list<std::pair<Key,Value>>::iterator> pos_;
public:
  explicit LRUCache(std::size_t cap) : cap_(cap) {}
  std::optional<Value> get(Key) override;
  void put(Key, Value) override;
  std::size_t size() const override { return pos_.size(); }
  std::size_t capacity() const override { return cap_; }
};

} // namespace cachelab
