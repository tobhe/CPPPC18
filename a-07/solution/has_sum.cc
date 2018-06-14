#include <algorithm>
#include <iostream>
#include <vector>

template <class ItA, class ItB, class Val>
bool has_sum_ordered(ItA && first, ItB && last, Val sum) {
  --last;
  while (first < last) {
    auto this_sum = *first + *last;
    if (this_sum == sum) {
      return true;
    } else if (this_sum < sum) {
      ++first;
    } else if (this_sum > sum) {
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
