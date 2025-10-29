#pragma once
#include "cachelab/icache.hpp"

namespace cachelab {

class LFUCache : public ICache {
  struct Node { Key k; Value v; std::size_t freq; };
  std::size_t cap_;
  std::unordered_map<Key, std::list<Node>::iterator> pos_;
  // Buckets by frequency: lowest freq at back of order list
  std::list<Node> order_; // front = most recently touched among given freq
public:
  explicit LFUCache(std::size_t cap) : cap_(cap) {}
  std::optional<Value> get(Key) override;
  void put(Key, Value) override;
  std::size_t size() const override { return pos_.size(); }
  std::size_t capacity() const override { return cap_; }
};

} // namespace cachelab
