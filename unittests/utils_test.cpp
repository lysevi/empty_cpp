#include <libemptycpp/utils/strings.h>
#include <libemptycpp/utils/utils.h>
#include <libemptycpp/utils/cz.h>
#include <libemptycpp/utils/bitoperations.h>

#include "helpers.h"
#include <catch.hpp>

TEST_CASE("Utils.split") {
  std::string str = "1 2 3 4 5 6 7 8";
  auto splitted = emptycpp::utils::strings::tokens(str);
  EXPECT_EQ(splitted.size(), size_t(8));

  splitted = emptycpp::utils::strings::split(str, ' ');
  EXPECT_EQ(splitted.size(), size_t(8));
}

TEST_CASE("Utils.to_upper") {
  auto s = "lower string";
  auto res = emptycpp::utils::strings::to_upper(s);
  EXPECT_EQ(res, "LOWER STRING");
}

TEST_CASE("Utils.to_lower") {
  auto s = "UPPER STRING";
  auto res = emptycpp::utils::strings::to_lower(s);
  EXPECT_EQ(res, "upper string");
}

TEST_CASE("Utils.CountZero") {
  EXPECT_EQ(emptycpp::utils::clz(67553994410557440), 8);
  EXPECT_EQ(emptycpp::utils::clz(3458764513820540928), 2);
  EXPECT_EQ(emptycpp::utils::clz(15), 60);

  EXPECT_EQ(emptycpp::utils::ctz(240), 4);
  EXPECT_EQ(emptycpp::utils::ctz(3840), 8);
}

TEST_CASE("Utils.BitOperations") {
  uint8_t value = 0;
  for (int8_t i = 0; i < 7; i++) {
    value = emptycpp::utils::BitOperations::set(value, i);
    EXPECT_EQ(emptycpp::utils::BitOperations::check(value, i), true);
  }

  for (int8_t i = 0; i < 7; i++) {
    value = emptycpp::utils::BitOperations::clr(value, i);
  }

  for (int8_t i = 0; i < 7; i++) {
    EXPECT_EQ(emptycpp::utils::BitOperations::check(value, i), false);
  }
}
