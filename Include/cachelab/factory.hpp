#pragma once
#include "cachelab/icache.hpp"
#include <memory>

namespace cachelab {

std::unique_ptr<ICache> make_cache(const std::string& policy, std::size_t capacity);

} // namespace cachelab
