#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>


/*!
 * \brief Find out whether sum can be built as sum of two values in unordered
 *        set of vaules
 *
 * Iterates from begin to end to find out whether there are two distinct values
 * between `first` and `last` that add up to sum.
 *
 * Complexity: O(n)
 *
 * \param It    last   Bidirectional iterator to first object
 * \param It   first   Bidirectional iterator to second object
 * \param Val   sum    Desired sum of two values
 *
 * \return pair of iterators containing the two summands or pair of last
 */
template <class It, class Val>
auto find_summands(It && first, It && last, Val sum) {
  std::unordered_multimap<Val, It> table{};

  // Fill set
  for (auto it = first; it != last; ++it) {
    table.insert(std::make_pair(*it, it));
  }

  // Special case half
  if (table.count(sum / 2) > 1) {
    auto range = table.equal_range(sum / 2);
    return std::make_pair((*(range.first)).second, (*(++range.first)).second);
  } else {
    table.erase(sum / 2);
  }

  // Lookup
  for (auto it = first; it != last; ++it) {
    auto tmp = table.find(sum - *it);
    if (tmp != table.end()) {
      return std::make_pair(it, (*tmp).second);
    }
  }

  return std::make_pair(last, last);
}


int main() {
  std::vector<int> v3{9, 2, 1, 4};
  std::vector<int> v4{1, 4, 2, 4};
  std::vector<int> v5{1, 5, 2, 3};

  auto pair = find_summands(v3.begin(), v3.end(), 8);
  std::cout << "Values: " << *(pair.first) << " " << *(pair.second) << '\n';

  auto pair2 = find_summands(v4.begin(), v4.end(), 8);
  std::cout << "Values: " << *(pair2.first) << " " << *(pair2.second) << '\n';

  auto pair3 = find_summands(v5.begin(), v5.end(), 8);
  std::cout << "Values: " << *(pair3.first) << " " << *(pair3.second) << '\n';
}
