#pragma once
#include <optional>
#include <cstddef>

namespace cachelab {

	using Key = uint64_t;
	using Value = uint64_t;

	struct PutResult { bool evicted; std::optional<Key> evicted_key; };

	class ICache {
	public:
		virtual ~ICache() = default;

		// returns value on hit; std::nullopt on miss
		virtual std::optional<Value> get(Key k) = 0;

		// inserts/updates; may evict oldest/least-used
		virtual PutResult put(Key k, Value v) = 0;

		// capacity in number of items
		virtual size_t capacity() const = 0;

		// clear internal state
		virtual void reset() = 0;

		// stats (optional quick access, metrics.hpp is canonical)
		virtual size_t size() const = 0;
	};

} // namespace cachelab
