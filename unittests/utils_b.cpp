#include <catch.hpp>
#include <numeric>

#include <libemptycpp/utils/bitoperations.h>

#ifdef EMPTYCPP_ENABLE_BENCHMARKS

TEST_CASE("utils::bitops", "[bench]") {
  BENCHMARK("crc") { emptycpp::utils::BitOperations::get(int(3), 3); };
}
#endif