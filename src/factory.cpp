#include "cachelab/factory.hpp"
#include "cachelab/policies/lru.hpp"
#include "cachelab/policies/lfu.hpp"
#include "cachelab/policies/lecar.hpp"
#include <algorithm>

namespace cachelab {

std::unique_ptr<ICache> make_cache(const std::string& policy, std::size_t capacity) {
  std::string p = policy;
  std::transform(p.begin(), p.end(), p.begin(), [](unsigned char c){ return std::tolower(c); });
  if (p == "lru")  return std::make_unique<LRUCache>(capacity);
  if (p == "lfu")  return std::make_unique<LFUCache>(capacity);
  if (p == "lecar" || p == "lecar_cache") return std::make_unique<LeCarCache>(capacity);
  throw std::runtime_error("Unknown policy: " + policy);
}

} // namespace cachelab
