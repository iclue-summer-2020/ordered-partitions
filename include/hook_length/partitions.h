// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef HOOK_LENGTH_PARTITIONS_H_
#define HOOK_LENGTH_PARTITIONS_H_

#include <iterator>
#include <vector>


namespace hook_length {
typedef std::vector<size_t> Partition;

// A class for iterating through partitions (reverse-lexicographically).
class Partitions {
 public:
  Partitions(size_t n);

  class const_iterator : std::iterator<std::forward_iterator_tag, Partition> {
   public:
    const_iterator(size_t n);
    const_iterator& operator++();
    const Partition& operator*() const;
    bool operator!=(const const_iterator&) const;
   private:
    Partition partition_;
  };

 public:
  const_iterator begin() const;
  const_iterator end() const;
 private:
  const size_t n_;
};

bool operator==(
    const Partitions::const_iterator& lhs,
    const Partitions::const_iterator& rhs);

// Returns the product of the hook lengths
size_t HookLengths(const Partition& partition);

}  // namespace hook_length

#endif  // HOOK_LENGTH_PARTITIONS_H_
