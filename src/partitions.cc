// Copyright 2020 ICLUE @ UIUC. All rights reserved.

#include <nlohmann/json.hpp>
#include <hook_length/partitions.h>


namespace hook_length {

Partitions::Partitions(size_t n) : n_{n} { }

Partitions::const_iterator Partitions::begin() const {
  return n_;
}

Partitions::const_iterator Partitions::end() const {
  return 0;
}

Partitions::const_iterator::const_iterator(size_t n) {
  if (n > 0) {
    partition_.push_back(n);
  }
}

Partitions::const_iterator& Partitions::const_iterator::operator++() {
  size_t num_pops = 0;
  while (!partition_.empty() && partition_.back() == 1) {
    partition_.pop_back();
    ++num_pops;
  }

  if (partition_.empty()) return *this;

  const size_t k = partition_.back();
  partition_.pop_back();
  partition_.push_back(k - 1);

  size_t rem = num_pops + 1;
  while (rem > 0) {
    const size_t part = std::min(partition_.back(), rem);
    partition_.push_back(part);
    rem -= part;
  }

  return *this;
}

const Partition& Partitions::const_iterator::operator*() const {
  return partition_;
}

bool Partitions::const_iterator::operator!=(
    const Partitions::const_iterator& rhs) const {
  return partition_ != rhs.partition_;
}

bool operator==(
    const Partitions::const_iterator& lhs,
    const Partitions::const_iterator& rhs) {
  return !(lhs != rhs);
}

}  // namespace hook_length

