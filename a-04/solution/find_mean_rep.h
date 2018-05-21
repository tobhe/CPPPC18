#ifndef CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
#define CPPPC__S03__FIND_MEAN_REP_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

namespace cpppc {

template <class Iter> Iter find_mean_rep(Iter first, Iter last) {
  using value_t = typename std::iterator_traits<Iter>::value_type;
  auto count = distance(first, last);
  if (count < 1) {
    return last;
  }

  auto mean = std::accumulate(first, last, 0) / count;
  return std::min_element(first, last, [mean](value_t left, value_t right) {
    return std::abs(mean - left) < std::abs(mean - right);
  });
}

} // namespace cpppc

#endif // CPPPC__S03__FIND_MEAN_REP_H__INCLUDED
