#include "cachelab/workload.hpp"
#include <random>
#include <numeric>   
#include <cmath>   
#include <cctype> 


namespace cachelab {

Workload Workload::zipf_sequence(std::size_t n, std::size_t keyspace, double s, double write_ratio) {
  std::vector<double> w(keyspace);
  for (std::size_t i=1;i<=keyspace;++i) w[i-1] = 1.0/std::pow(double(i), s);
  double sum = std::accumulate(w.begin(), w.end(), 0.0);
  for (auto& x : w) x /= sum;

  std::discrete_distribution<std::size_t> dist(w.begin(), w.end());
  std::mt19937_64 rng(42);
  std::bernoulli_distribution write(write_ratio);

  Workload wl;
  wl.ops.reserve(n);
  for (std::size_t i=0;i<n;++i) {
    auto k = dist(rng);
    if (write(rng)) wl.ops.push_back({Op::Put, k, (Value)k});
    else            wl.ops.push_back({Op::Get, k, 0});
  }
  return wl;
}

Workload Workload::from_csv(const std::string& path) {
  Workload wl;
  std::ifstream in(path);
  std::string line;
  // header optional
  while (std::getline(in, line)) {
    if (line.empty()) continue;
    if (!std::isdigit(line[0])) continue; // skip header
    std::stringstream ss(line);
    int opi; Key k; Value v;
    char comma;
    ss >> opi >> comma >> k >> comma >> v;
    wl.ops.push_back({ opi==0?Op::Get:Op::Put, k, v});
  }
  return wl;
}

} // namespace cachelab
