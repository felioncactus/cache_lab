#include "cachelab/policies/lru.hpp"

namespace cachelab {

    LRUCache::LRUCache(size_t cap) : cap_(cap) {}

    std::optional<Value> LRUCache::get(Key k) {
        auto it = pos_.find(k);
        if (it == pos_.end()) return std::nullopt;
        // move to front (MRU)
        lst_.splice(lst_.begin(), lst_, it->second);
        return it->second->second;
    }

    PutResult LRUCache::put(Key k, Value v) {
        PutResult r{ false, std::nullopt };
        auto it = pos_.find(k);
        if (it != pos_.end()) {
            it->second->second = v;
            lst_.splice(lst_.begin(), lst_, it->second);
            return r;
        }
        if (lst_.size() >= cap_ && cap_ > 0) {
            auto& back = lst_.back();
            r = { true, back.first };
            pos_.erase(back.first);
            lst_.pop_back();
        }
        lst_.emplace_front(k, v);
        pos_[k] = lst_.begin();
        return r;
    }

    void LRUCache::reset() { lst_.clear(); pos_.clear(); }

} // namespace cachelab
