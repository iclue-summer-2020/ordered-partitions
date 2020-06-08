// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <gflags/gflags.h>

#include <hook_length/partitions.h>
#include <cstdlib>
#include <iostream>
#include <string>

DEFINE_uint32(n, 0, "n");

using hook_length::Partitions;
using hook_length::Partition;

std::ostream& operator<<(std::ostream& os, const Partition& partition) {
  for (const size_t part : partition) {
    os << part;
    os << ", ";
  }
  return os;
}

int main(int argc, char** argv) {
  gflags::SetUsageMessage("Prints each partition of n");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_n <= 0) {
    std::cerr << "Please provide a value of n" << std::endl;
    return EXIT_FAILURE;
  }

  const Partitions partitions{FLAGS_n};
  for (const Partition& partition : partitions) {
    std::cout << partition << std::endl;
  }
  return EXIT_SUCCESS;
}
