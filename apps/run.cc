// Copyright (c) 2020 ICLUE @ UIUC. All rights reserved.

#include <gflags/gflags.h>
#include <hook_length/partitions.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>

DEFINE_uint32(n, 0, "n");
DEFINE_bool(by_length, false, "by-length");

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

// Prints each partition \lambda along with (f^\lambda)/n! _in order_
// lexicographically decreasing.
void PrintPartitions(const Partitions& partitions) {
  for (const Partition& partition : partitions) {
    const size_t hl = HookLengths(partition);
    std::cout << partition << "\t|" << hl << "\n";
  }
  std::cout << std::flush;
}

// Prints each essential partition \lambda along with (f^\lambda)/n! _in order_
// by decreasing hook lengths.
void PrintPartitionsByHookLength(const Partitions& partitions) {
  std::vector<Partition> parts;
  std::vector<size_t> hls;

  for (const Partition& partition : partitions) {
    parts.push_back(partition);
    hls.push_back(HookLengths(partition));
  }

  // Sort by hook length product.
  std::vector<size_t> idxs(parts.size());
  std::iota(idxs.begin(), idxs.end(), 0);
  std::stable_sort(idxs.begin(), idxs.end(),
                   [&hls](size_t i, size_t j) { return hls[i] < hls[j]; });

  // Only print dominant partitions (i.e., no conjugates).
  size_t hlp = 0;
  std::vector<Partition> saved_parts;

  // Prints each essential partition with hook length denom hlp.
  auto print = [](std::vector<Partition>& saved_parts, size_t hlp) {
    const size_t sps = saved_parts.size();
    if (sps % 2 == 1 && sps > 1) {
      std::cerr << "something is wrong here" << std::endl;
    }
    for (size_t j = 0; j < (sps + 1) / 2; ++j) {
      std::cout << saved_parts[j] << "\t| " << hlp << std::endl;
    }
  };

  for (size_t i : idxs) {
    if (hls[i] != hlp) {
      print(saved_parts, hlp);
      hlp = hls[i];
      saved_parts.clear();
    }
    saved_parts.push_back(parts[i]);
  }
  print(saved_parts, hlp);
}

int main(int argc, char** argv) {
  gflags::SetUsageMessage("Prints each partition of n");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (FLAGS_n <= 0) {
    std::cerr << "Please provide a value of n" << std::endl;
    return EXIT_FAILURE;
  }

  const Partitions partitions{FLAGS_n};
  const auto printFn =
      FLAGS_by_length ? PrintPartitionsByHookLength : PrintPartitions;

  printFn(partitions);

  return EXIT_SUCCESS;
}
