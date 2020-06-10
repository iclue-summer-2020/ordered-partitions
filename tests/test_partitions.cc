// Copyright (c) 2020 ICLUE @ UIUC. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <hook_length/partitions.h>


TEST_CASE("There are 7 partitions of 5", "[count]") {
  hook_length::Partitions partitions{5};
  size_t count = 0;
  for (const hook_length::Partition& _ : partitions) {
    ++count;
  }
  REQUIRE(count == 7);
}

TEST_CASE("Need partitions to be weakly decreasing", "[decreasing]") {
  hook_length::Partitions partitions{5};
  for (const hook_length::Partition& partition : partitions) {
    size_t last = SIZE_MAX;
    for (size_t part : partition) {
      REQUIRE(last >= part);
      last = part;
    }
  }
}

TEST_CASE("Partitions match up", "[values]") {
  const std::vector<hook_length::Partition> expected_partitions = {
      {5},
      {4, 1},
      {3, 2},
      {3, 1, 1},
      {2, 2, 1},
      {2, 1, 1, 1},
      {1, 1, 1, 1, 1},
  };

  hook_length::Partitions partitions{5};
  auto it1 = partitions.begin();
  auto it2 = expected_partitions.begin();

  while (it1 != partitions.end() && it2 != expected_partitions.end()) {
    REQUIRE(*it1 == *it2);
    ++it1;
    ++it2;
  }

  REQUIRE(it1 == partitions.end());
  REQUIRE(it2 == expected_partitions.end());
}

TEST_CASE("Hook lengths" "[product]") {
  const hook_length::Partition partition = {5, 1};
  REQUIRE(hook_length::HookLengths(partition) == 6*4*3*2*1*1);
}