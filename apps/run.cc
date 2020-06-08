// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <gflags/gflags.h>
#include <hook_length/partitions.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>

DEFINE_uint32(n, 0, "n");

using hook_length::HookLengths;
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
  std::vector<Partition> parts;
  std::vector<size_t> hls;

  for (const Partition& partition : partitions) {
    // std::cout << partition << std::endl;
    parts.push_back(partition);
    hls.push_back(HookLengths(partition));
  }

  // Sort by hook length product.
  std::vector<size_t> idxs(parts.size());
  std::iota(idxs.begin(), idxs.end(), 0);
  std::stable_sort(idxs.begin(), idxs.end(),
      [&hls](size_t i, size_t j) { return hls[i] < hls[j]; }
  );

  // Only print dominant partitions (i.e., no conjugates).
  size_t hlp = 0;
  std::vector<Partition> saved_parts;
  for (size_t i : idxs) {
    if (hls[i] != hlp) {

      size_t sps = saved_parts.size();
      if (sps % 2 == 1 && sps > 1) {
        std::cerr << "something is wrong here" << std::endl;
      }
      for (size_t j = 0; j < (sps+1)/2; ++j) {
        std::cout << saved_parts[j] << "\t| " << hlp << std::endl;
      }

      hlp = hls[i];
      saved_parts.clear();
    }
    saved_parts.push_back(parts[i]);
  }

  size_t sps = saved_parts.size();
  if (sps % 2 == 1 && sps > 1) {
    std::cerr << "something is wrong here" << std::endl;
  }
  for (size_t j = 0; j < (sps+1)/2; ++j) {
    std::cout << saved_parts[j] << "\t| " << hlp << std::endl;
  }

  return EXIT_SUCCESS;
}
