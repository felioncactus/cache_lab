#include "cachelab/factory.hpp"
#include <cassert>
#include <iostream>

using namespace cachelab;

static void test_lru_basic() {
  auto c = make_cache("lru", 2);
  c->put(1, 10);
  c->put(2, 20);
  assert(c->get(1).value() == 10);
  c->put(3, 30); // evicts 2
  assert(!c->get(2).has_value());
  assert(c->get(1).value() == 10);
  assert(c->get(3).value() == 30);
}

static void test_lfu_basic() {
  auto c = make_cache("lfu", 2);
  c->put(1, 10);
  c->put(2, 20);
  (void)c->get(1);
  (void)c->get(1); // freq(1) higher
  c->put(3, 30);   // should evict key 2
  assert(c->get(1).has_value());
  assert(!c->get(2).has_value());
  assert(c->get(3).has_value());
}

static void test_lecar_smoke() {
  auto c = make_cache("lecar", 2);
  c->put(1, 10);
  c->put(2, 20);
  (void)c->get(1);
  c->put(3, 30); // some eviction
  assert(c->size() == 2);
  // should still return something reasonable
  (void)c->get(1);
  (void)c->get(2);
  (void)c->get(3);
}

int main() {
  test_lru_basic();
  test_lfu_basic();
  test_lecar_smoke();
  std::cout << "All tests passed.\n";
  return 0;
}
