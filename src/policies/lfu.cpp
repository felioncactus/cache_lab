#include "cachelab/policies/lfu.hpp"

namespace cachelab {

std::optional<Value> LFUCache::get(Key k) {
  auto it = pos_.find(k);
  if (it == pos_.end()) return std::nullopt;
  auto node_it = it->second;
  node_it->freq++;
  // move to front to represent recency within same freq
  order_.splice(order_.begin(), order_, node_it);
  return node_it->v;
}

void LFUCache::put(Key k, Value v) {
  if (cap_ == 0) return;
  auto it = pos_.find(k);
  if (it != pos_.end()) {
    it->second->v = v;
    it->second->freq++;
    order_.splice(order_.begin(), order_, it->second);
    return;
  }
  if (pos_.size() >= cap_) {
    // find min freq (approx: at tail; if multiple, LRU among them)
    auto victim_it = --order_.end();
    pos_.erase(victim_it->k);
    order_.erase(victim_it);
  }
  order_.push_front(Node{ k, v, 1 });
  pos_[k] = order_.begin();
}

} // namespace cachelab
