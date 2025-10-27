#pragma once
#include "cachelab/icache.hpp"
#include <list>
#include <unordered_map>

namespace cachelab {

	class LRUCache final : public ICache {
		using List = std::list<std::pair<Key, Value>>;
		size_t cap_;
		List lst_;
		std::unordered_map<Key, typename List::iterator> pos_;
	public:
		explicit LRUCache(size_t cap);
		std::optional<Value> get(Key k) override;
		PutResult put(Key k, Value v) override;
		size_t capacity() const override { return cap_; }
		void reset() override;
		size_t size() const override { return pos_.size(); }
	};

} // namespace cachelab
