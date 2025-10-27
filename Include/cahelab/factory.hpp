#pragma once
#include "cachelab/icache.hpp"
#include <memory>
#include <string>

namespace cachelab {

	std::unique_ptr<ICache> make_cache(const std::string& policy, size_t capacity);

} // namespace cachelab
