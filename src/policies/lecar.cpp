#include "cachelab/policies/lecar.hpp"
#include <cmath>

namespace cachelab {

void LeCarCache::touch_lru(Key k) {
  auto it = lru_pos_.find(k);
  if (it != lru_pos_.end()) {
    lru_.splice(lru_.begin(), lru_, it->second);
  } else {
    lru_.emplace_front(k, 0);
    lru_pos_[k] = lru_.begin();
  }
}

void LeCarCache::touch_lfu(Key k) {
  auto it = lfu_pos_.find(k);
  if (it != lfu_pos_.end()) {
    it->second->second.freq++;
    lfu_.splice(lfu_.begin(), lfu_, it->second);
  } else {
    lfu_.emplace_front(k, F{0,1});
    lfu_pos_[k] = lfu_.begin();
  }
}

void LeCarCache::evict_if_needed() {
  while (lru_pos_.size() > cap_) {
    // choose victim using convex weight between LRU-rank and 1/freq
    auto lru_victim = --lru_.end(); // LRU = tail
    Key k1 = lru_victim->first;

    auto lfu_victim = --lfu_.end(); // approx-lowest freq
    Key k2 = lfu_victim->first;

    // If same key, evict it
    Key evict_k = (k1 == k2) ? k1 : ( (w_ >= 0.5) ? k1 : k2 );

    auto itL = lru_pos_.find(evict_k);
    if (itL != lru_pos_.end()) { lru_.erase(itL->second); lru_pos_.erase(itL); }
    auto itF = lfu_pos_.find(evict_k);
    if (itF != lfu_pos_.end()) { lfu_.erase(itF->second); lfu_pos_.erase(itF); }
  }
}

std::optional<Value> LeCarCache::get(Key k) {
  auto it = lru_pos_.find(k);
  bool in_cache = (it != lru_pos_.end());
  if (in_cache) {
    touch_lru(k);
    touch_lfu(k);
    // reward leaning toward current hit: if LFU freq high, nudge weight toward LFU
    auto f = lfu_pos_[k]->second.freq;
    double grad = (f > 2 ? -1.0 : +1.0); // crude: high freq favors LFU (smaller w)
    w_ = std::clamp(w_ - eta_ * grad, 0.0, 1.0);
    return lru_pos_[k]->second;
  }
  return std::nullopt;
}

void LeCarCache::put(Key k, Value v) {
  // If present, update and touch
  auto itL = lru_pos_.find(k);
  if (itL != lru_pos_.end()) {
    itL->second->second = v;
    touch_lru(k); touch_lfu(k);
    return;
  }
  // insert into both
  lru_.emplace_front(k, v); lru_pos_[k] = lru_.begin();
  lfu_.emplace_front(k, F{v,1}); lfu_pos_[k] = lfu_.begin();
  evict_if_needed();
}

} // namespace cachelab
