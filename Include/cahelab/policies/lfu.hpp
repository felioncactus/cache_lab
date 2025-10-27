#pragma once
#include "cachelab/icache.hpp"
#include <unordered_map>
#include <list>

namespace cachelab {

	// classic O(1) LFU with freq-buckets
	class LFUCache final : public ICache {
		struct Node { Key k; Value v; uint32_t f; };
		using List = std::list<Node>;
		size_t cap_;
		std::unordered_map<Key, std::pair<uint32_t, List::iterator>> index_;
		std::unordered_map<uint32_t, List> buckets_;
		uint32_t min_f_ = 0;
	public:
		explicit LFUCache(size_t cap);
		std::optional<Value> get(Key k) override;
		PutResult put(Key k, Value v) override;
		size_t capacity() const override { return cap_; }
		void reset() override;
		size_t size() const override { return index_.size(); }
	};

} // namespace cachelab
