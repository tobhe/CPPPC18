#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace std {

template <class Iter,
          class = typename std::iterator_traits<Iter>::iterator_category>
std::pair<Iter, int> make_pair(Iter && iter, int count) {
  return std::pair<Iter, int>{iter, count};
}

template <class Iter,
          class = typename std::iterator_traits<Iter>::iterator_category>
auto begin(std::pair<Iter, int> & pair) {
  return std::get<0>(pair);
}

template <class Iter,
          class = typename std::iterator_traits<Iter>::iterator_category>
auto end(std::pair<Iter, int> & pair) {
  auto & it = std::get<0>(pair);
  std::advance(it, std::get<1>(pair));
  return it;
}


}  // namespace std


int main() {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7};

  // This is caugt by my overload, yay
  auto p = std::make_pair(v.begin(), 6);

  for (auto & var : p) { std::cout << var << '\n'; }

  return 0;
}
