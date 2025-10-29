#include "cachelab/policies/lru.hpp"

namespace cachelab {

std::optional<Value> LRUCache::get(Key k) {
  auto it = pos_.find(k);
  if (it == pos_.end()) return std::nullopt;
  // move to front (MRU)
  lst_.splice(lst_.begin(), lst_, it->second);
  return it->second->second;
}

void LRUCache::put(Key k, Value v) {
  auto it = pos_.find(k);
  if (it != pos_.end()) {
    it->second->second = v;
    lst_.splice(lst_.begin(), lst_, it->second);
    return;
  }
  if (pos_.size() >= cap_) {
    auto victim = lst_.back();
    pos_.erase(victim.first);
    lst_.pop_back();
  }
  lst_.emplace_front(k, v);
  pos_[k] = lst_.begin();
}

} // namespace cachelab
