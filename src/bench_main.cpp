#include "cachelab/factory.hpp"
#include "cachelab/metrics.hpp"
#include "cachelab/workload.hpp"
#include <iostream>

using namespace cachelab;

int main(int argc, char** argv) {
  // Minimal CLI: bench <policy> <capacity> [zipf_n=100000] [keyspace=10000] [s=1.1]
  std::string policy = (argc>1? argv[1] : "lru");
  std::size_t cap = (argc>2? std::stoull(argv[2]) : 1024);
  std::size_t n = (argc>3? std::stoull(argv[3]) : 100000);
  std::size_t keyspace = (argc>4? std::stoull(argv[4]) : 10000);
  double s = (argc>5? std::stod(argv[5]) : 1.1);

  auto cache = make_cache(policy, cap);
  auto wl = Workload::zipf_sequence(n, keyspace, s);

  Metrics m;
  for (auto& a : wl.ops) {
    if (a.op == Op::Get) {
      m.gets++;
      auto r = cache->get(a.k);
      if (r) m.hits++; else m.misses++;
    } else {
      m.puts++;
      cache->put(a.k, a.v);
    }
  }
  std::cout << "policy="<<policy<<" cap="<<cap<<" gets="<<m.gets<<" hits="<<m.hits
            <<" misses="<<m.misses<<" hit_rate="<<m.hit_rate()<<"\n";
  return 0;
}
