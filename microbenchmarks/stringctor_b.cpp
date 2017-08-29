#include <benchmark/benchmark_api.h>
#include <string>
static void BM_StringCtor(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::string constr("asdfg");
  }
}

BENCHMARK(BM_StringCtor);
