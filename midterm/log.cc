#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

namespace cpppc {
void log10(int num) {
  std::cout << "Int:" << std::log10(num) << '\n';
}

void log10(float num) {
  std::cout << "Float: " << std::log10(sqrt(num)) << '\n';
}

template <class T>
void print_walk(T begin, T end, std::random_access_iterator_tag) {
  std::cout << "Random Access Iterator" << '\n';

  std::vector<int> cpy{begin, end};
  std::random_shuffle(cpy.begin(), cpy.end());

  for (auto & i : cpy) { std::cout << i << '\n'; }
}

template <class T>
void print_walk(T begin, T end, std::input_iterator_tag) {
  std::cout << "Input Iterator" << '\n';
  while (begin != end) {
    std::cout << *begin << '\n';
    ++begin;
  }
}

template <class T>
void print_walk(T begin, T end, std::bidirectional_iterator_tag) {
  std::cout << "Bidirectional Iterator" << '\n';
  --end;
  while (end != begin) {
    std::cout << *end << '\n';
    --end;
  }
  std::cout << *end << '\n';
}

template <class T>
void print_walk(T begin, T end) {
  print_walk(
    begin, end, typename std::iterator_traits<T>::iterator_category());
}

}  // namespace cpppc

int main() {
  std::cout << "Log10: " << '\n';
  cpppc::log10(10);
  cpppc::log10(static_cast<float>(10));

  std::cout << "print_walk: " << '\n';
  std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int>   l = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  cpppc::print_walk(v.begin(), v.end());
  cpppc::print_walk(l.begin(), l.end());

  return 0;
}
