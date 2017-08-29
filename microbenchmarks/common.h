#pragma once
#include <libemptycpp/utils/logger.h>
namespace microbenchmark_common {
class BenchmarkLogger : public emptycpp::utils::ILogger {
public:
  BenchmarkLogger() {}
  ~BenchmarkLogger() {}
  void message(emptycpp::utils::LOG_MESSAGE_KIND, const std::string &) {}
};

void replace_std_logger();
} // namespace microbenchmark_common