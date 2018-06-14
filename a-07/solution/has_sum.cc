#include <algorithm>
#include <iostream>
#include <vector>

/*!
 * \brief Find out whether sum can be built as sum of two values in range
 *
 * Iterates from begin to end to find out whether there are two distinct values
 * between `first` and `last` that add up to sum.
 *
 * Complexity: O(n)
 *
 * Improvements to google version:
 *     - not limited to int
 *     - not using raw pointers
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


int main() {
  std::vector<int> v1{1, 2, 4, 9};
  std::vector<int> v2{1, 2, 4, 4};

  std::cout << "Vector1: " << has_sum_ordered(v1, 8) << '\n';
  std::cout << "Vector2: " << has_sum_ordered(v2, 8) << '\n';
}
