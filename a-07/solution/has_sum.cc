#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

/*!
 * \brief Find out whether sum can be built as sum of two values in ordered set
 *        of values
 *
 * Iterates from begin to end to find out whether there are two distinct values
 * between `first` and `last` that add up to sum.
 *
 * Complexity: O(n)
 *
 * Improvements to google version:
 *     - not limited to int
 *     - not limited to vector
 *     - awesome range overload (such future much wow)
 *
 * \param ItA  last   Bidirectional iterator to first object
 * \param ItB  first  Bidirectional iterator to secodn object
 * \param Val  sum    Desired sum of two values
 */
template <class ItA, class ItB, class Val>
bool has_sum_ordered(ItA && first, ItB && last, Val sum) {
  // because you don't want to dereference this one
  --last;
  while (first < last) {
    auto this_sum = *first + *last;
    if (this_sum == sum) {
      return true;
    } else if (this_sum < sum) {
      ++first;
    } else {
      --last;
    }
  }
  return false;
}

template <class Range, class Val>
auto has_sum_ordered(Range && range, Val sum) {
  return has_sum_ordered(std::begin(range), std::end(range), sum);
}

/*!
 * \brief Find out whether sum can be built as sum of two values in unordered
 *        set of vaules
 *
 * Iterates from begin to end to find out whether there are two distinct values
 * between `first` and `last` that add up to sum.
 *
 * Complexity: O(n)
 *
 * Improvements to google version:
 *     - not limited to int
 *     - not limited to vector
 *     - awesome range overload (such future much wow)
 *     - split up set fill and find -> better dividable tasks for parallel
 *
 * \param ItA  last   Bidirectional iterator to first object
 * \param ItB  first  Bidirectional iterator to secodn object
 * \param Val  sum    Desired sum of two values
 */
template <class ItA, class ItB, class Val>
bool has_sum_unordered(ItA && first, ItB && last, Val sum) {
  std::unordered_set<Val> table{};

  // Fill set with complements
  for (auto it = first; first != last; ++it) { table.insert(sum - *it); }

  // Lookup
  for (auto it = first; first != last; ++it) {
    if (table.find(sum - *it) != table.end()) { return true; }
  }

  return false;
}

template <class Range, class Val>
auto has_sum_unordered(Range && range, Val sum) {
  return has_sum_ordered(std::begin(range), std::end(range), sum);
}


int main() {
  std::vector<int> v1{1, 2, 4, 9};
  std::vector<int> v2{1, 2, 4, 4};

  std::cout << "Vector1: " << has_sum_ordered(v1, 8) << '\n';
  std::cout << "Vector2: " << has_sum_ordered(v2, 8) << '\n';


  std::vector<int> v3{9, 2, 1, 4};
  std::vector<int> v4{1, 4, 2, 4};

  std::cout << "Vector1: " << has_sum_unordered(v3, 8) << '\n';
  std::cout << "Vector2: " << has_sum_unordered(v4, 8) << '\n';
}
