#include <libemptycpp/utils/strings.h>
#include <libemptycpp/utils/utils.h>
#include <libemptycpp/utils/cz.h>
#include <libemptycpp/utils/bitoperations.h>
#include <libemptycpp/utils/fs.h>

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

TEST_CASE("Utils.FileUtils") {
  std::string filename = "foo/bar/test.txt";
  EXPECT_EQ(emptycpp::utils::fs::filename(filename), "test");
  EXPECT_EQ(emptycpp::utils::fs::parent_path(filename), "foo/bar");
  EXPECT_EQ(emptycpp::utils::fs::extract_filename(filename), "test.txt");

  auto ls_res = emptycpp::utils::fs::ls(".");
  EXPECT_TRUE(ls_res.size() > 0);

  const std::string fname = "mapped_file.test";
  auto mapf = emptycpp::utils::fs::MappedFile::touch(fname, 1024);
  for (uint8_t i = 0; i < 100; i++) {
    mapf->data()[i] = i;
  }
  mapf->close();

  ls_res = emptycpp::utils::fs::ls(".", ".test");
  EXPECT_TRUE(ls_res.size() == 1);
  auto reopen_mapf = emptycpp::utils::fs::MappedFile::open(fname);
  for (uint8_t i = 0; i < 100; i++) {
    EXPECT_EQ(reopen_mapf->data()[i], i);
  }
  reopen_mapf->close();
  emptycpp::utils::fs::rm(fname);

  std::string parent_p = "path1";
  std::string child_p = "path2";
  auto concat_p = emptycpp::utils::fs::append_path(parent_p, child_p);
  EXPECT_EQ(emptycpp::utils::fs::parent_path(concat_p), parent_p);
}
