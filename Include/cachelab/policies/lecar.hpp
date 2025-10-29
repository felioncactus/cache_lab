#pragma once
#include "cachelab/icache.hpp"

namespace cachelab {

// Simplified LeCaR: maintains two internal caches (LRU+LFU) of same capacity
// and learns a convex weight w \in [0,1] to choose victim leaning.
// On miss, insert into both; on evict, choose victim by score combining ranks.
class LeCarCache : public ICache {
  std::size_t cap_;
  // Internal states for ranking
  std::list<std::pair<Key,Value>> lru_;
  std::unordered_map<Key, std::list<std::pair<Key,Value>>::iterator> lru_pos_;

  struct F { Value v; std::size_t freq; };
  std::list<std::pair<Key,F>> lfu_;
  std::unordered_map<Key, std::list<std::pair<Key,F>>::iterator> lfu_pos_;

  double w_ = 0.5;      // weight toward LRU
  double eta_ = 0.05;   // learning rate

  void touch_lru(Key k);
  void touch_lfu(Key k);
  void evict_if_needed();

public:
  explicit LeCarCache(std::size_t cap) : cap_(cap) {}
  std::optional<Value> get(Key) override;
  void put(Key, Value) override;
  std::size_t size() const override { return lru_pos_.size(); }
  std::size_t capacity() const override { return cap_; }
};

} // namespace cachelab
