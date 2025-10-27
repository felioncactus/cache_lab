#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace cachelab {

	enum class Op : uint8_t { GET = 0, PUT = 1 };

	struct Event { uint64_t key; Op op; };

	struct Workload {
		std::string name;
		std::vector<Event> events;
	};

	// Load "key,op" CSV where op is GET or PUT
	Workload load_trace_csv(const std::string& path, const std::string& name = "trace");

	// Synthetic generators
	Workload gen_zipf(uint64_t n_ops, uint64_t keyspace, double s, const std::string& name);
	Workload gen_sequential_scan(uint64_t n_ops, uint64_t keyspace, uint64_t reps, const std::string& name);
	Workload gen_mixed(uint64_t n_ops, uint64_t hot_keys, uint64_t cold_keys, double hot_prob, const std::string& name);

} // namespace cachelab
