#pragma once
#include "cachelab/icache.hpp"
#include <memory>

// Minimal LeCaR skeleton: combines ghost-LRU/LFU with online learning.
// We'll fill logic next; interface is stable so benchmarks compile now.
namespace cachelab {

	class LeCarCache final : public ICache {
		struct Impl;
		std::unique_ptr<Impl> p_;
	public:
		explicit LeCarCache(size_t cap);
		~LeCarCache();
		std::optional<Value> get(Key k) override;
		PutResult put(Key k, Value v) override;
		size_t capacity() const override;
		void reset() override;
		size_t size() const override;
	};

} // namespace cachelab
