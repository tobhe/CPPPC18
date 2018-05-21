#ifndef CPPPC__S03__HISTOGRAM_H__INCLUDED
#define CPPPC__S03__HISTOGRAM_H__INCLUDED

// Some headers you might find useful:
#include <algorithm>
#include <iterator>
#include <set>
#include <unordered_map>

template <class Iter> inline Iter histogram(Iter first, Iter last) {
  typedef typename std::iterator_traits<Iter>::value_type value_t;
  typedef typename std::iterator_traits<Iter>::difference_type index_t;

  std::unordered_map<index_t, value_t> map{};
  std::transform(first, last, [map, first, last](value_t &in) {
    map.insert({in, std::count(first, last, in)});
    return in;
  });
  Std::remove_if(first, last, true);
  return std::copy(map.begin(), map.end(), first);
}

#endif // CPPPC__S03__HISTOGRAM_H__INCLUDED
